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

#include "mycss/media/state.h"


bool mycss_media_state_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return true;
}

/* <mf-range> */
// greater than
// <mf-range> =
//   <mf-name> [ '<' | '>' ]? '='? <mf-value>
// | <mf-value> [ '<' | '>' ]? '='? <mf-name>
// | <mf-value> '<' '='? <mf-name> '<' '='? <mf-value>
// | <mf-value> '>' '='? <mf-name> '>' '='? <mf-value>
bool mycss_media_state_mf_range(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        // <mf-name> [ '<' | '>' ]? '='? <mf-value>
        case MyCSS_TOKEN_TYPE_IDENT:
            // mycss_media_state_mf_range_ident
            break;
            
        case MyCSS_TOKEN_TYPE_NUMBER:
            // mycss_media_state_mf_range_number
            break;
            
        case MyCSS_TOKEN_TYPE_DIMENSION:
            // mycss_media_state_mf_range_dimension
            break;
            
        default:
            break;
    }
    
    return true;
}

/* <mf-range> step 1 */
bool mycss_media_state_mf_range_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_DELIM)
    {
        if(*token->data == '<') {
            
        }
    }
    
    return true;
}

bool mycss_media_state_mf_range_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return true;
}

bool mycss_media_state_mf_range_dimension(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return true;
}

/* <mf-range> step 1 */
bool mycss_media_state_mf_range_ident_less_than(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_DELIM)
    {
        if(*token->data == '<') {
            
        }
        else if(*token->data == '=') {
            
        }
    }
    
    return true;
}

/* general enclosed */
bool mycss_media_state_general_enclosed(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_FUNCTION) {
        
    }
    else if(token->type == MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS) {
        
    }
    
    return true;
}

bool mycss_media_state_general_enclosed_left_parenthesis(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        
    }
    else {
        
    }
    
    return true;
}

bool mycss_media_state_general_enclosed_any_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    /* get <any-value> ) */
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS) {
        
    }
    
    return true;
}

