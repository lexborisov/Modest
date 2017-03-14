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

#include "mycss/tokenizer_global.h"
#include "mycss/tokenizer_resource.h"
#include "mycore/utils/resources.h"

/////////////////////////////////////////////////////////
//// Global back
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a numeric
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_numeric(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '%')
    {
        css_offset++;
        
        token->length = (entry->current_buffer->offset + css_offset) - token->begin;
        token->type   = MyCSS_TOKEN_TYPE_PERCENTAGE;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        return css_offset;
    }
    else if(css[css_offset] == '-') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_RSOLIDUS;
    }
    else if(mycss_begin_chars_state_map[ (const unsigned char)(css[css_offset]) ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        token->type = MyCSS_TOKEN_TYPE_DIMENSION;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_BACK;
    }
    else
    {
        token->length = (entry->current_buffer->offset + css_offset) - token->begin;
        token->type   = MyCSS_TOKEN_TYPE_NUMBER;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_numeric_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(mycss_begin_chars_state_map[ (const unsigned char)(css[css_offset]) ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        token->type = MyCSS_TOKEN_TYPE_DIMENSION;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_BACK;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS_RSOLIDUS;
    }
    else {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        token->type   = MyCSS_TOKEN_TYPE_NUMBER;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_numeric_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 2;
        token->type   = MyCSS_TOKEN_TYPE_NUMBER;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 2);
    }
    else {
        css_offset++;
        
        token->type = MyCSS_TOKEN_TYPE_DIMENSION;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_BACK;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_numeric_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        token->type   = MyCSS_TOKEN_TYPE_NUMBER;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    else {
        css_offset++;
        
        token->type = MyCSS_TOKEN_TYPE_DIMENSION;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_BACK;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a number
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_number_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] < '0' || css[css_offset] > '9')
        {
            if(css[css_offset] == '.') {
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DOT;
                
                css_offset++;
                break;
            }
            else if(css[css_offset] == 'E' || css[css_offset] == 'e') {
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E;
                
                css_offset++;
                break;
            }
            else {
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                
                entry->state = entry->state_back;
                break;
            }
        }
        
        css_offset++;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_number_dot(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL;
        css_offset++;
    }
    else {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        entry->state = entry->state_back;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_number_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] < '0' || css[css_offset] > '9')
        {
            if(css[css_offset] == 'E' || css[css_offset] == 'e') {
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E;
                
                css_offset++;
                break;
            }
            else {
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                entry->state = entry->state_back;
                break;
            }
        }
        
        css_offset++;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_number_e(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '+' || css[css_offset] == '-') {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_PLUS_MINUS;
        css_offset++;
    }
    else if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_DECIMAL;
        css_offset++;
    }
    else {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        entry->state = entry->state_back;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_number_e_plus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_DECIMAL;
        css_offset++;
    }
    else {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 2;
        entry->state = entry->state_back;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_number_e_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] < '0' || css[css_offset] > '9')
        {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            entry->state = entry->state_back;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a url token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] != '\r' && css[css_offset] != 0x0C &&
           css[css_offset] != '\n' && css[css_offset] != '\t' && css[css_offset] != ' ')
        {
            if(css[css_offset] == '"') {
                css_offset++;
                
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED;
                entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_URL_STRING_BACK;
                
                token->begin = entry->current_buffer->offset + css_offset;
                break;
            }
            else if(css[css_offset] == '\'') {
                css_offset++;
                
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED;
                entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_URL_STRING_BACK;
                
                token->begin = entry->current_buffer->offset + css_offset;
                break;
            }
            
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER;
            
            token->begin = entry->current_buffer->offset + css_offset;
            break;
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_url_string_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(token->type == MyCSS_TOKEN_TYPE_BAD_STRING)
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL;
    else
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER_WHITESPACE;
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_url_after(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while(css_offset < css_size)
    {
        if(css[css_offset] == ')') {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_URL;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            
            css_offset++;
            break;
        }
        else if(css[css_offset] == '\r' || css[css_offset] == 0x0C ||
                css[css_offset] == '\n' || css[css_offset] == '\t' || css[css_offset] == ' ')
        {
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER_WHITESPACE;
            
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            
            css_offset++;
            break;
        }
        else if(css[css_offset] == '"' || css[css_offset] == '\'' || css[css_offset] == '(' ||
                // non-printable code point
                u_css[css_offset] == 0x00 || u_css[css_offset] == 0x08 || u_css[css_offset] == 0x0B ||
                u_css[css_offset] == 0x7F || (u_css[css_offset] >= 0x0E && u_css[css_offset] <= 0x1F))
        {
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL;
            
            css_offset++;
            break;
        }
        else if(css[css_offset] == '\\') {
            css_offset++;
            
            break;
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_url_after_whitespace(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] != '\r' && css[css_offset] != 0x0C &&
           css[css_offset] != '\n' && css[css_offset] != '\t' && css[css_offset] != ' ')
        {
            if(css[css_offset] == ')') {
                token->type = MyCSS_TOKEN_TYPE_URL;
                
                MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
                
                entry->state = MyCSS_TOKENIZER_STATE_DATA;
                
                css_offset++;
                break;
            }
            
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL;
            break;
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_url_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] != '\n' && css[css_offset] != '\r' && css[css_offset] != 0x0C) {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER;
        return (css_offset + 1);
    }
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL;
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_bad_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] == ')') {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_BAD_URL;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            
            css_offset++;
            break;
        }
//        else if(css[css_offset] == '\\') {
//            css_offset++;
//            break;
//        }
        
        ++css_offset;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a string token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_string_double_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] == '"')
        {
            token->type   = MyCSS_TOKEN_TYPE_STRING;
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            
            // skip QUOTATION MARK (")
            ++css_offset;
            entry->state = entry->state_back;
            break;
        }
        else if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
            token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            
            entry->state = entry->state_back;
            break;
        }
        else if(css[css_offset] == '\\') {
            css_offset++;
            
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS;
            break;
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_string_double_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\r')
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS_R;
    else
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED;
    
    css_offset++;
    return css_offset;
}

size_t mycss_tokenizer_global_state_string_double_quoted_rsolidus_r(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n')
        css_offset++;
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED;
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_string_single_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] == '\'')
        {
            token->type   = MyCSS_TOKEN_TYPE_STRING;
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            
            // skip APOSTROPHE (')
            ++css_offset;
            
            entry->state = entry->state_back;
            break;
        }
        else if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
            token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            
            entry->state = entry->state_back;
            break;
        }
        else if(css[css_offset] == '\\') {
            css_offset++;
            
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS;
            break;
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_string_single_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\r')
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS_R;
    else
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED;
    
    css_offset++;
    return css_offset;
}

size_t mycss_tokenizer_global_state_string_single_quoted_rsolidus_r(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n')
        css_offset++;
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED;
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume an ident-like token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_ident(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '(')
    {
        if(mycss_tokenizer_token_strcasecmp(entry, token, "url", 3) == 0) {
            css_offset++;
            
            token->begin = css_offset;
            token->type  = MyCSS_TOKEN_TYPE_URL;
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_URL;
        }
        else {
            css_offset++;
            
            token->type = MyCSS_TOKEN_TYPE_FUNCTION;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
        }
    }
    else {
        token->type = MyCSS_TOKEN_TYPE_IDENT;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a name
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_name(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while(css_offset < css_size)
    {
        if(mycss_chars_name_code_point_map[ u_css[css_offset] ] == 0xff)
        {
            if(css[css_offset] == '\\') {
                ++css_offset;
                
                if(css_offset >= css_size) {
                    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME_RSOLIDUS;
                    break;
                }
                
                if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
                    --css_offset;
                    
                    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                    entry->state = entry->state_back;
                    
                    break;
                }
            }
            else {
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                entry->state = entry->state_back;
                
                break;
            }
        }
        
        css_offset++;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        entry->state = entry->state_back;
        
        return mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    else {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        css_offset++;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Consume a unicode-range token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_global_state_unicode_range_before(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    entry->help_counter = 0;
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE;
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_unicode_range(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while(css_offset < css_size)
    {
        if(mycore_string_chars_hex_map[ u_css[css_offset] ] != 0xff)
        {
            entry->help_counter++;
            
            if(entry->help_counter == 6) {
                css_offset++;
                
                entry->help_counter = 0;
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_MINUS;
                
                break;
            }
        }
        else if(css[css_offset] == '?') {
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_QUESTION;
            break;
        }
        else if(css[css_offset] == '-') {
            css_offset++;
            
            entry->help_counter = 0;
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_MINUS;
            break;
        }
        else {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
            
            // TODO
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_unicode_range_question(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] == '?') {
            entry->help_counter++;
            
            if(entry->help_counter == 6) {
                css_offset++;
                
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
                
                MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
                
                entry->state = MyCSS_TOKENIZER_STATE_DATA;
                break;
            }
        }
        else {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_global_state_unicode_range_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while(css_offset < css_size)
    {
        if(mycore_string_chars_hex_map[ u_css[css_offset] ] != 0xff)
        {
            entry->help_counter++;
            
            if(entry->help_counter == 6) {
                css_offset++;
                
                entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_MINUS;
                break;
            }
        }
        else {
            if(entry->help_counter == 0) {
                token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
                css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
            }
            else {
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            }
            
            token->type = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}



