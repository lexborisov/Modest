/*
 Copyright (C) 2016-2017 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include "mycss/mystring.h"
#include "mycss/tokenizer_resource.h"
#include "mycore/utils/resources.h"
#include "myencoding/encoding.h"

static const mycss_string_process_state_f mycss_string_state_list_map[] = {
    mycss_string_process_state_data, mycss_string_process_state_escaped
};

static const mycss_string_process_state_f mycss_string_state_list_map_utf_8[] = {
    mycss_string_process_state_data_utf_8, mycss_string_process_state_escaped_utf_8
};

void mycss_string_append_codepoint_to_string(mycore_string_t* str, size_t code_point)
{
    if((str->length + 4) >= str->size) {
        mycore_string_realloc(str, (str->size + 8));
    }
    
    // If this number is zero
    if(code_point == 0) {
        str->length += mycore_string_raw_set_replacement_character(str, str->length);
    }
    else if(code_point >= 0xD800 && code_point <= 0xDFFF) {
        str->length += mycore_string_raw_set_replacement_character(str, str->length);
    }
    // maximum allowed code point
    else if(code_point > 0x10FFFF) {
        str->length += mycore_string_raw_set_replacement_character(str, str->length);
    }
    else
        str->length += myencoding_codepoint_to_ascii_utf_8(code_point, &str->data[str->length]);
}

size_t mycss_string_process_state_escaped(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res)
{
    const unsigned char *u_data = (const unsigned char*)data;
    
    myencoding_custom_f func = myencoding_get_function_by_id(out_res->encoding);
    myencoding_result_t *encoding_res = &out_res->encoding_res;
    
    char convert_data[4] = {0};
    
    while(length < size)
    {
        myencoding_status_t encoding_status = func(u_data[length], encoding_res);
        
        if(encoding_status == MyENCODING_STATUS_OK)
        {
            myencoding_codepoint_to_ascii_utf_8(encoding_res->result, convert_data);
            
            if(mycore_string_chars_hex_map[(unsigned char)convert_data[0]] != 0xff) {
                out_res->escaped.code_point <<= 4;
                out_res->escaped.code_point |= mycore_string_chars_hex_map[ (unsigned char)convert_data[0] ];
                
                ++out_res->escaped.consumed;
                
                if(out_res->escaped.consumed == 6) {
                    mycss_string_append_codepoint_to_string(str, out_res->escaped.code_point);
                    
                    out_res->state = MyCSS_STRING_PROCESS_STATE_DATA;
                    break;
                }
            }
            else {
                mycss_string_append_codepoint_to_string(str, out_res->escaped.code_point);
                
                out_res->state = MyCSS_STRING_PROCESS_STATE_DATA;
                break;
            }
        }
        
        ++length;
    }
    
    return length;
}

size_t mycss_string_process_state_escaped_utf_8(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res)
{
    const unsigned char *u_data = (const unsigned char*)data;
    
    while(length < size)
    {
        if(mycore_string_chars_hex_map[u_data[length]] != 0xff) {
            out_res->escaped.code_point <<= 4;
            out_res->escaped.code_point |= mycore_string_chars_hex_map[ u_data[length] ];
            
            ++out_res->escaped.consumed;
            
            if(out_res->escaped.consumed == 6) {
                mycss_string_append_codepoint_to_string(str, out_res->escaped.code_point);
                
                out_res->state = MyCSS_STRING_PROCESS_STATE_DATA;
                break;
            }
        }
        else {
            mycss_string_append_codepoint_to_string(str, out_res->escaped.code_point);
            
            out_res->state = MyCSS_STRING_PROCESS_STATE_DATA;
            break;
        }
        
        ++length;
    }
    
    return length;
}


void mycss_string_escaped_res_clean(mycss_string_escaped_res_t* res)
{
    memset(res, 0, sizeof(mycss_string_escaped_res_t));
}

void mycss_string_res_clean(mycss_string_res_t* res)
{
    memset(res, 0, sizeof(mycss_string_res_t));
    memset(&res->encoding_res, 0, sizeof(myencoding_result_t));
}

size_t mycss_string_process_state_data(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res)
{
    char *str_data = str->data;
    unsigned const char* u_str_data = (unsigned const char*)data;
    
    myencoding_custom_f func = myencoding_get_function_by_id(out_res->encoding);
    myencoding_result_t *encoding_res = &out_res->encoding_res;
    
    while(length < size)
    {
        myencoding_status_t encoding_status = func(u_str_data[length], encoding_res);
        
        if(encoding_status == MyENCODING_STATUS_OK)
        {
            if((str->length + 4) >= str->size) {
                mycore_string_realloc(str, (str->size + 16));
                
                str_data = str->data;
            }
            
            size_t len = myencoding_codepoint_to_ascii_utf_8(encoding_res->result, &str_data[str->length]);
            
            if(len == 1) {
                if(str_data[str->length] == '\\') {
                    ++length;
                    
                    out_res->state = MyCSS_STRING_PROCESS_STATE_ESCAPED;
                    break;
                }
                else if(str_data[str->length] == '\n' &&
                        str->length > 0 &&
                        str_data[(str->length - 1)] == '\r')
                {
                    --str->length;
                    str_data[str->length] = '\n';
                }
                else if(str_data[str->length] == 0x0C) {
                    str_data[str->length] = '\n';
                }
                else if(str_data[str->length] == '\0') {
                    mycore_string_raw_set_replacement_character(str, str->length);
                    str->length += 2;
                }
            }
            
            str->length += len;
        }
        
        ++length;
    }
    
    return length;
}

size_t mycss_string_process_state_data_utf_8(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res)
{
    char *str_data = str->data;
    
    while(length < size)
    {
        if(data[length] == '\\') {
            ++length;
            
            out_res->state = MyCSS_STRING_PROCESS_STATE_ESCAPED;
            break;
        }
        
        if(str->length >= str->size) {
            mycore_string_realloc(str, (str->size + 16));
            
            str_data = str->data;
        }
        
        if(data[length] == '\n' &&
           str->length > 0 &&
           str_data[(str->length - 1)] == '\r')
        {
            --str->length;
            str_data[str->length] = '\n';
        }
        else if(data[length] == 0x0C) {
            str_data[str->length] = '\n';
        }
        else if(data[length] == '\0') {
            mycore_string_raw_set_replacement_character(str, str->length);
            str->length += 2;
        }
        else
            str_data[str->length] = data[length];
        
        ++str->length;
        ++length;
    }
    
    return length;
}

size_t mycss_string_data_process(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res)
{
    if(out_res->encoding == MyENCODING_UTF_8) {
        while(length < size) {
            length = mycss_string_state_list_map_utf_8[ out_res->state ](str, data, length, size, out_res);
        }
    }
    else {
        while(length < size) {
            length = mycss_string_state_list_map[ out_res->state ](str, data, length, size, out_res);
        }
    }
    
    return length;
}

void mycss_string_data_process_end(mycore_string_t* str, mycss_string_res_t *out_res)
{
    if(out_res->state == MyCSS_STRING_PROCESS_STATE_ESCAPED) {
        mycss_string_append_codepoint_to_string(str, out_res->escaped.code_point);
    }
    else if(str->length > 0) {
        if(str->data[(str->length - 1)] == '\r')
            str->data[(str->length - 1)] = '\n';
    }
    
    if(str->length >= str->size)
        mycore_string_realloc(str, (str->size + 2));
    
    str->data[str->length] = '\0';
    
    if(out_res->case_insensitive) {
        unsigned char *u_data = (unsigned char*)str->data;
        
        for(size_t i = 0; i < str->length; i++)
            u_data[i] = mycore_string_chars_lowercase_map[u_data[i]];
    }
}


