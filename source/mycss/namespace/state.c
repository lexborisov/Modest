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

#include "mycss/namespace/state.h"

bool mycss_namespace_state_namespace(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_AT_KEYWORD) {
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, true);
        
        if(mycore_strcmp(str.data, "namespace") == 0) {
            entry->parser = mycss_namespace_state_namespace_namespace;
        }
        else {
            mycss_namespace_parser_expectations_error(entry, token);
            entry->parser = mycss_parser_token;
        }
        
        mycore_string_destroy(&str, false);
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
        
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycss_namespace_parser_begin(entry);
            mycss_namespace_parser_name(entry, token);
            entry->parser = mycss_namespace_state_namespace_namespace_ident;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_STRING: {
            mycss_namespace_parser_begin(entry);
            mycss_namespace_parser_url(entry, token);
            entry->parser = mycss_namespace_state_namespace_namespace_string;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_URL: {
            mycss_namespace_parser_begin(entry);
            mycss_namespace_parser_url(entry, token);
            entry->parser = mycss_namespace_state_namespace_namespace_url;
            
            break;
        }
        default: {
            mycss_namespace_parser_expectations_error(entry, token);
            entry->parser = mycss_parser_token_drop_at_rule;
            return false;
        }
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_STRING) {
        mycss_namespace_parser_url(entry, token);
        entry->parser = mycss_namespace_state_namespace_namespace_ident_string;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_URL) {
        mycss_namespace_parser_url(entry, token);
        entry->parser = mycss_namespace_state_namespace_namespace_ident_url;
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
        return false;
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace_ident_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        mycss_namespace_parser_end(entry, token);
        MyCORE_DEBUG("mycss_namespace_state_namespace_namespace_ident_string_semicolon");
        entry->parser = mycss_parser_token;
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
        return false;
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace_ident_url(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        mycss_namespace_parser_end(entry, token);
        MyCORE_DEBUG("mycss_namespace_state_namespace_namespace_ident_url_semicolon");
        entry->parser = mycss_parser_token;
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
        return false;
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        mycss_namespace_parser_end(entry, token);
        MyCORE_DEBUG("mycss_namespace_state_namespace_namespace_string_semicolon");
        entry->parser = mycss_parser_token;
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
        return false;
    }
    
    return true;
}

bool mycss_namespace_state_namespace_namespace_url(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        mycss_namespace_parser_end(entry, token);
        MyCORE_DEBUG("mycss_namespace_state_namespace_namespace_url_semicolon");
        entry->parser = mycss_parser_token;
    }
    else {
        mycss_namespace_parser_expectations_error(entry, token);
        entry->parser = mycss_parser_token_drop_at_rule;
        return false;
    }
    
    return true;
}


