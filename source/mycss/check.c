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

#include "mycss/check.h"
#include "mycss/tokenizer_resource.h"

#define MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED          \
    if(css_offset >= buffer->size) {                        \
        buffer = buffer->next;                              \
        css_offset = 0;                                     \
    }

/////////////////////////////////////////////////////////
//// For chunk
////
/////////////////////////////////////////////////////////
bool mycss_check_two_code_points_valid_escape_chunk(mycss_entry_t* entry, size_t css_offset)
{
    mycore_incoming_buffer_t* buffer = entry->current_buffer;
    
    MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
    
    if(buffer->data[css_offset] == '\\') {
        ++css_offset;
        
        MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
        
        if(buffer->data[css_offset] != '\n')
            return true;
    }
    
    return false;
}

bool mycss_check_three_code_points_would_start_identifier_chunk(mycss_entry_t* entry, size_t css_offset)
{
    mycore_incoming_buffer_t* buffer = entry->current_buffer;
    
    MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
    const unsigned char *u_css = (const unsigned char*)buffer->data;
    
    if(buffer->data[css_offset] == '-')
    {
        ++css_offset;
        
        MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
        u_css = (const unsigned char*)buffer->data;
        
        if(buffer->data[css_offset] == '-' ||
           mycss_begin_chars_state_map[ u_css[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT ||
           mycss_check_two_code_points_valid_escape_chunk(entry, css_offset))
        {
            return true;
        }
    }
    else if(mycss_begin_chars_state_map[ u_css[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        return true;
    }
    else if(buffer->data[css_offset] == '\\' && mycss_check_two_code_points_valid_escape_chunk(entry, css_offset)) {
        return true;
    }
    
    return false;
}

bool mycss_check_three_code_points_would_start_number_chunk(mycss_entry_t* entry, size_t css_offset)
{
    mycore_incoming_buffer_t* buffer = entry->current_buffer;
    
    MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
    
    if(buffer->data[css_offset] == '-' || buffer->data[css_offset] == '+')
    {
        ++css_offset;
        
        MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
        
        if(buffer->data[css_offset] >= '0' && buffer->data[css_offset] <= '9')
            return true;
        
        if(buffer->data[css_offset] == '.') {
            ++css_offset;
            
            MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
            
            if(buffer->data[css_offset] >= '0' && buffer->data[css_offset] <= '9')
                return true;
        }
    }
    else if(buffer->data[css_offset] == '.') {
        ++css_offset;
        
        MyCSS_CHECK_CHUNK_POSITION_AND_SET_IF_NEED
        
        if(buffer->data[css_offset] >= '0' && buffer->data[css_offset] <= '9')
            return true;
    }
    else if(buffer->data[css_offset] >= '0' && buffer->data[css_offset] <= '9')
        return true;
    
    return false;
}

/////////////////////////////////////////////////////////
//// basic checks
////
/////////////////////////////////////////////////////////
bool mycss_check_three_code_points_would_start_identifier(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css_offset >= css_size)
        return mycss_check_three_code_points_would_start_identifier_chunk(entry, css_offset);
    
    const unsigned char *u_css = (const unsigned char*)css;
    
    if(css[css_offset] == '-')
    {
        ++css_offset;
        
        if(css[css_offset] == '-' ||
           mycss_begin_chars_state_map[ u_css[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT ||
           mycss_check_two_code_points_valid_escape(entry, token, css, css_offset, css_size))
        {
            return true;
        }
    }
    else if(mycss_begin_chars_state_map[ u_css[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        return true;
    }
    else if(css[css_offset] == '\\' && mycss_check_two_code_points_valid_escape(entry, token, css, css_offset, css_size)) {
        return true;
    }
    
    return false;
}

bool mycss_check_two_code_points_valid_escape(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css_offset >= css_size)
        return mycss_check_two_code_points_valid_escape_chunk(entry, css_offset);
    
    if(css[css_offset] == '\\' && css[(css_offset + 1)] != '\n')
        return true;
    
    return false;
}

bool mycss_check_three_code_points_would_start_number(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css_offset >= css_size)
        return mycss_check_three_code_points_would_start_number_chunk(entry, css_offset);
    
    if(css[css_offset] == '-' || css[css_offset] == '+')
    {
        ++css_offset;
        
        if(css[css_offset] >= '0' && css[css_offset] <= '9')
            return true;
        
        if(css[css_offset] == '.') {
            ++css_offset;
            
            if(css[css_offset] >= '0' && css[css_offset] <= '9')
                return true;
        }
    }
    else if(css[css_offset] == '.') {
        ++css_offset;
        
        if(css[css_offset] >= '0' && css[css_offset] <= '9')
            return true;
    }
    else if(css[css_offset] >= '0' && css[css_offset] <= '9')
        return true;
    
    return false;
}


