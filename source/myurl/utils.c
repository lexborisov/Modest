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
 Foundation, Inc., 51 Franklin avl_treet, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include "myurl/url.h"
#include "myurl/utils.h"
#include "myurl/resources.h"
#include "mycore/utils/resources.h"

/* data */
char * myurl_utils_data_copy(myurl_t* url, const char* data, size_t size)
{
    char *copy = url->callback_malloc(((sizeof(char) * size) + 1), url->callback_ctx);
    
    if(copy) {
        memcpy(copy, data, sizeof(char) * size);
        copy[size] = '\0';
    }
    
    return copy;
}

mystatus_t myurl_utils_data_copy_set(myurl_t* url, const char* data, size_t size, char** to, size_t* to_length)
{
    if(data == NULL) {
        *to = NULL;
        *to_length = 0;
        
        return MyURL_STATUS_OK;
    }
    
    char *copy;
    
    /* mem */
    if(*to) {
        if((*to_length + 1) < size)
            copy = url->callback_realloc(*to, (sizeof(char) * (size + 1)), url->callback_ctx);
        else
            copy = *to;
    }
    else
        copy = url->callback_malloc(((sizeof(char) * size) + 1), url->callback_ctx);
    
    /* process */
    if(copy) {
        *to = copy;
        *to_length = size;
        
        memcpy(copy, data, sizeof(char) * size);
        
        copy[size] = '\0';
    }
    else {
        *to_length = 0;
        return MyURL_STATUS_ERROR;
    }
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_utils_data_copy_append(myurl_t* url, const char* data, size_t size, char** to, size_t* to_length)
{
    if(data == NULL) {
        if(*to)
            *to = url->callback_free(*to, url->callback_ctx);
        
        *to = NULL;
        *to_length = 0;
        
        return MyURL_STATUS_OK;
    }
    
    char *copy;
    
    /* mem */
    if(*to) {
        if((*to_length + 1) < size)
            copy = url->callback_realloc(*to, (sizeof(char) * (size + *to_length)) + 1, url->callback_ctx);
        else
            copy = *to;
    }
    else
        copy = url->callback_malloc(((sizeof(char) * size) + 1), url->callback_ctx);
    
    /* process */
    if(copy) {
        *to = copy;
        
        memcpy(&copy[ *to_length ], data, sizeof(char) * size);
        (*to_length) += size;
        
        copy[size] = '\0';
    }
    else {
        *to_length = 0;
        return MyURL_STATUS_ERROR;
    }
    
    return MyURL_STATUS_OK;
}

void myurl_utils_data_set_null(myurl_t* url, char** to, size_t* length)
{
    if(*to)
        *to = url->callback_free(*to, url->callback_ctx);
    
    if(length)
        *length = 0;
}

void myurl_utils_data_set_empty(myurl_t* url, char** to, size_t* length)
{
    if(*to == NULL)
        *to = url->callback_malloc(sizeof(char), url->callback_ctx);
    
    if(length)
        *length = 0;
    
    *to[0] = '\0';
}

/* converter */
char * myurl_utils_percent_encode(myurl_t* url, const char* data, size_t size, const unsigned char* encode_set, size_t* return_length)
{
    size_t new_size = size;
    const unsigned char *u_data = (const unsigned char*)data;
    
    size_t len;
    for(len = 0; len < size; len++) {
        if(encode_set[ u_data[len] ] == 0x00)
            new_size += 2;
    }
    
    char *out = url->callback_malloc((sizeof(char) * new_size) + 1, url->callback_ctx);
    if(out == NULL) {
        if(return_length)
            *return_length = 0;
        
        return NULL;
    }
    
    char *out_link = out;
    
    len = 0;
    while(len < size)
    {
        if(encode_set[ u_data[len] ] == 0x00) {
            const char *two_hex = mycore_string_char_to_two_hex_value[ u_data[len] ];
            
            *out = '%'; out++;
            *out = (char)mycore_string_chars_uppercase_map[ (unsigned char)two_hex[0] ]; out++;
            *out = (char)mycore_string_chars_uppercase_map[ (unsigned char)two_hex[1] ]; out++;
            *out = '\0';
        }
        else {
            *out = data[len];
            out++;
        }
        
        len++;
    }
    
    *out = '\0';
    
    if(return_length)
        *return_length = new_size;
    
    return out_link;
}

/* converter */
size_t myurl_utils_percent_decode_bytes_in_data(char* data, size_t size)
{
    unsigned char *u_data = (unsigned char*)data;
    unsigned char tmp = '\0';
    
    size_t len = 0, offset = 0;
    while(len < size)
    {
        if(u_data[len] == '%' && (len + 2) < size) {
            size_t pos = len;
            len++;
            
            if(mycore_string_chars_hex_map[ u_data[len] ] != 0xFF &&
               mycore_string_chars_hex_map[ u_data[(len + 1)] ] != 0xFF)
            {
                tmp = mycore_string_chars_hex_map[ u_data[len] ];
                tmp = (tmp << 4) | mycore_string_chars_hex_map[ u_data[(len + 1)] ];
                
                u_data[(pos - offset)] = tmp;
                
                offset += 2;
                len++;
            }
            else {
                len--;
                
                if(offset)
                    u_data[(len - offset)] = data[len];
            }
            
            len++;
        }
        else {
            if(offset)
                u_data[(len - offset)] = data[len];
            
            len++;
        }
    }
    
    if(offset) {
        size_t new_size = (len - offset);
        data[new_size] = '\0';
        
        return new_size;
    }
    
    return size;
}

bool myurl_utils_is_windows_drive_letter(const char* data, size_t length, size_t size)
{
    if(data == NULL)
        return false;
    
    length++;
    
    if(length >= size)
        return false;
    
    return mycore_string_alpha_character[ (unsigned char)data[(length - 1)] ] != 0xff &&
        (data[length] == ':' || data[length] == '|');
}

bool myurl_utils_is_double_dot_path_segment(const char* data, size_t length)
{
    if(length < 2)
        return false;
    
    if(*data == '.' && data[1] == '.') {
        if(length == 2)
            return true;
        
        return false;
    }
    
    if(length < 4)
        return false;
    
    if(*data == '.' && data[1] == '%' && data[2] == '2' && data[3] == 'e') {
        if(length == 4)
            return true;
        
        return false;
    }
    
    if(*data == '%' && data[1] == '2' && data[2] == 'e' && data[3] == '.') {
        if(length == 4)
            return true;
        
        return false;
    }
    
    if(length != 6)
        return false;
    
    if(*data == '%' && data[1] == '2' && data[2] == 'e' && data[3] == '%' && data[4] == '2' && data[5] == 'e') {
        return true;
    }
    
    return false;
}

bool myurl_utils_is_single_dot_path_segment(const char* data, size_t length)
{
    if(length < 1)
        return false;
    
    if(*data == '.') {
        if(length == 1)
            return true;
        
        return false;
    }
    
    if(length != 3)
        return false;
    
    if(*data == '%' && data[1] == '2' && data[2] == 'e') {
        return true;
    }
    
    return false;
}

size_t myurl_convert_integer_to_data_without_check_buffer(long digit, char* return_str)
{
    size_t length = 0;
    
    if(digit != 0) {
        if(digit < 0) {
            length++;
            digit -= digit;
            
            return_str[0] = '-';
        }
        
        /* calc end char count */
        length += (size_t)floor(log10( labs(digit) )) + 1;
    }
    else {
        return_str[0] = '0';
        return_str[1] = '\0';
        
        return 1;
    }
    
    for(size_t i = 0; i < length; i++) {
        return_str[ ((length - i) - 1) ] = (char)myurl_resources_static_map_digits[ digit % 10 ];
        digit /= 10;
    }
    
    return_str[length] = '\0';
    return length;
}

size_t myurl_convert_integer_to_hex_data_without_check_buffer(long digit, char* return_str)
{
    size_t length = 0;
    
    if(digit != 0) {
        if(digit < 0) {
            length++;
            digit -= digit;
            
            return_str[0] = '-';
        }
        
        /* calc end char count */
        long tmp_digit = digit;
        while(tmp_digit) {length++; tmp_digit /= 16;}
    }
    else {
        return_str[0] = '0';
        return_str[1] = '\0';
        
        return 1;
    }
    
    size_t tmp_length = length;
    
    while(digit) {
        unsigned long temp = digit % 16;
        
        tmp_length--;
        if(temp < 10)
            return_str[tmp_length] = (char)(temp + 48);
        else
            return_str[tmp_length] = (char)(temp + 87);
        
        digit /= 16;
    }
    
    return_str[length] = '\0';
    return length;
}

//void myurl_utils_data_set(myurl_parser_t* parser, myurl_parser_data_t* parse_data, const unsigned char* data, size_t length)
//{
//    if(parse_data->data == NULL) {
//        parse_data->size   = (length + 1);
//        parse_data->length = length;
//        
//        parse_data->data = (unsigned char*)mchar_async_malloc(parser->mchar, parser->node_idx, parse_data->size);
//    }
//    else if(length >= parse_data->size) {
//        parse_data->size   = (length + 1);
//        parse_data->length = length;
//        
//        parse_data->data = (unsigned char*)mchar_async_realloc(parser->mchar, parser->node_idx,
//                                                                (char*)parse_data->data, 0, parse_data->size);
//    }
//    
//    if(data && length) {
//        memcpy(parse_data->data, data, sizeof(unsigned char) * length);
//    }
//    
//    parse_data->data[length] = '\0';
//}
//
//void myurl_utils_data_append(myurl_parser_t* parser, myurl_parser_data_t* parse_data, const unsigned char* data, size_t length)
//{
//    if(parse_data->data == NULL) {
//        parse_data->size = (length + 1);
//        parse_data->data = (unsigned char*)mchar_async_malloc(parser->mchar, parser->node_idx, parse_data->size);
//    }
//    else if((parse_data->length + length) >= parse_data->size) {
//        parse_data->size = (parse_data->length + length + 1);
//        parse_data->data = (unsigned char*)mchar_async_realloc(parser->mchar, parser->node_idx,
//                                                               (char*)parse_data->data, 0, parse_data->size);
//    }
//    
//    if(data && length) {
//        memcpy(&parse_data->data[parse_data->length], data, sizeof(unsigned char) * length);
//    }
//    
//    parse_data->length = parse_data->length + length;
//    parse_data->data[parse_data->length] = '\0';
//}
//
//void myurl_utils_data_copy(myurl_parser_t* parser, myurl_parser_data_t* to, const myurl_parser_data_t* from)
//{
//    if(to->data == NULL) {
//        to->size   = (from->length + 1);
//        to->length = from->length;
//        
//        to->data = (unsigned char*)mchar_async_malloc(parser->mchar, parser->node_idx, to->size);
//    }
//    else if(from->length >= to->size) {
//        to->size   = (from->length + 1);
//        to->length = from->length;
//        
//        to->data = (unsigned char*)mchar_async_realloc(parser->mchar, parser->node_idx,
//                                                        (char*)to->data, 0, to->size);
//    }
//    
//    if(from->data && to->length) {
//        memcpy(to->data, from->data, sizeof(unsigned char) * to->length);
//    }
//    
//    to->data[to->length] = '\0';
//}
//
//void myurl_utils_data_destroy(myurl_parser_t* parser, myurl_parser_data_t* parse_data, bool self_destroy)
//{
//    mchar_async_free(parser->mchar, parser->node_idx, (char*)parse_data->data);
//    
//    if(self_destroy) {
//        mycore_free(parse_data);
//    }
//}



