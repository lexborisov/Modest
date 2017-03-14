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

#include "mycss/declaration/state.h"

bool mycss_declaration_state_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_declaration_parser_begin(entry, token);
    
    return mycss_declaration_state_data(entry, token, last_response);
}

bool mycss_declaration_state_data(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
        case MyCSS_TOKEN_TYPE_SEMICOLON:{
            break;
        }
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycss_declaration_parser_ident(entry, token);
            break;
        }
        case MyCSS_TOKEN_TYPE_AT_KEYWORD: {
            break;
        }
        default: {
            /* parse error */
            entry->parser = mycss_declaration_state_find_ending;
            return false;
        }
    }
    
    return true;
}

bool mycss_declaration_state_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE: {
            break;
        }
        case MyCSS_TOKEN_TYPE_COLON: {
            entry->parser = entry->parser_switch;
            break;
        }
        default: {
            /* parse error */
            entry->parser = mycss_declaration_state_parse_error;
            return false;
        }
    }
    
    return true;
}

bool mycss_declaration_state_colon_before_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    else if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        entry->parser = mycss_declaration_state_data;
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_DELIM && *token->data == '!') {
        entry->parser = mycss_declaration_state_colon_important;
        return true;
    }
    else if(token->type == entry->declaration->ending_token) {
        mycss_entry_parser_list_pop(entry);
        mycss_declaration_parser_end(entry, token);
        
        return true;
    }
    
    /* parse error */
    entry->parser = mycss_declaration_state_parse_error;
    
    return false;
}

bool mycss_declaration_state_colon_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, true);
        
        if(mycore_strcmp(str.data, "important") == 0) {
            mycore_string_destroy(&str, false);
            
            entry->parser = mycss_declaration_state_colon_delim_after_important;
            (entry->declaration->entry_last)->is_important = true;
            
            return true;
        }
        
        mycore_string_destroy(&str, false);
        
        /* parse error */
        entry->parser = mycss_declaration_state_parse_error;
        return false;
    }
    
    /* parse error */
    entry->parser = mycss_declaration_state_parse_error;
    
    return false;
}

bool mycss_declaration_state_colon_delim_after_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE: {
            break;
        }
        case MyCSS_TOKEN_TYPE_SEMICOLON:{
            entry->parser = mycss_declaration_state_data;
            break;
        }
        default: {
            if(token->type == entry->declaration->ending_token) {
                mycss_entry_parser_list_pop(entry);
                mycss_declaration_parser_end(entry, token);
                
                return true;
            }
            
            /* parse error */
            entry->parser = mycss_declaration_state_parse_error;
            return false;
        }
    }
    
    return true;
}

bool mycss_declaration_state_find_ending(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        entry->parser = mycss_declaration_state_data;
        return true;
    }
    else if(token->type == entry->declaration->ending_token) {
        mycss_entry_parser_list_pop(entry);
        mycss_declaration_parser_end(entry, token);
        
        return true;
    }
    
    entry->parser = mycss_declaration_state_drop_component_value;
    return false;
}

bool mycss_declaration_state_parse_error(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_declaration_entry_t *decl_entry = entry->declaration->entry_last;
    
    decl_entry->flags = MyCSS_DECLARATION_FLAGS_BAD;
    decl_entry->value_type = MyCSS_PROPERTY_VALUE_UNDEF;
    
    mycss_declaration_entry_destroy(entry->declaration, decl_entry, false);
    
    entry->parser = mycss_declaration_state_find_ending;
    return false;
}

bool mycss_declaration_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_FUNCTION: {
            mycss_entry_parser_list_push(entry, mycss_declaration_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_declaration_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_declaration_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS: {
            mycss_entry_parser_list_push(entry, mycss_declaration_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_SEMICOLON: {
            if(mycss_entry_parser_list_current_is_local(entry) == false)
                entry->parser = mycss_declaration_state_data;
            
            break;
        }
        default: {
            if(mycss_entry_parser_list_current_is_local(entry) == false) {
                if(token->type == entry->declaration->ending_token) {
                    mycss_entry_parser_list_pop(entry);
                    mycss_declaration_parser_end(entry, token);
                }
            }
            else {
                if(token->type == entry->parser_ending_token)
                    mycss_entry_parser_list_pop(entry);
            }
        }
    }
    
    return true;
}


