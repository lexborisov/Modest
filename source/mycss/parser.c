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

#include "mycss/parser.h"
#include "mycss/tokenizer_resource.h"

mycss_token_t * mycss_parser_token_ready_callback_function(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_COMMENT)
        return token;
    
    bool last_response = true;
    while((last_response = entry->parser(entry, token, last_response)) == false) {};
    
    return entry->token;
}

bool mycss_parser_token(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
            
        case MyCSS_TOKEN_TYPE_CDC:
        case MyCSS_TOKEN_TYPE_CDO:
            break;
            
        case MyCSS_TOKEN_TYPE_AT_KEYWORD: {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, true);
            
            if(mycore_strcmp(str.data, "namespace") == 0) {
                mycss_namespace_t *ns = entry->ns;
                
                ns->ns_stylesheet = &entry->stylesheet->ns_stylesheet;
                ns->entry = &ns->ns_stylesheet->entry_first;
                
                entry->parser = mycss_namespace_state_namespace_namespace;
            }
            else {
                entry->parser = mycss_parser_token_drop_at_rule;
            }
            
            mycore_string_destroy(&str, false);
            
            mycss_entry_parser_list_push(entry, mycss_parser_token, entry->parser_switch, MyCSS_TOKEN_TYPE_UNDEF, false);
            break;
        }
        
        default: {
            /* see selectors */
            entry->parser = mycss_selectors_state_complex_selector_list;
            
            entry->selectors->list = &entry->stylesheet->sel_list_first;
            entry->selectors->ending_token = MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET;
            
            mycss_entry_parser_list_push(entry, mycss_parser_token_selector_list_end, entry->parser_switch, MyCSS_TOKEN_TYPE_UNDEF, false);
            return false;
        }
    }
    
    return true;
}

bool mycss_parser_token_selector_list_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            entry->declaration->entry = &entry->selectors->list_last->declaration_entry;
            entry->declaration->entry_last = NULL;
            
            entry->parser = mycss_declaration_state_begin;
            entry->declaration->ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            mycss_entry_parser_list_push(entry, mycss_parser_token, entry->parser_switch, MyCSS_TOKEN_TYPE_UNDEF, false);
            break;
        }
        default:
            mycss_entry_parser_list_push(entry, mycss_parser_token_selector_list_end, NULL, entry->parser_ending_token, false);
            
            entry->parser = mycss_parser_token_drop_component_value;
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET;
            
            return false;
    }
    
    return true;
}

bool mycss_parser_token_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == entry->parser_ending_token) {
        if(mycss_entry_parser_list_current_is_local(entry) == false) {
            mycss_entry_parser_list_pop(entry);
            return false;
        }
    }
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_FUNCTION: {
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS: {
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        default: {
            if(token->type == entry->parser_ending_token) {
                mycss_entry_parser_list_pop(entry);
                return true;
            }
        }
    }
    
    return true;
}

//
//
//bool mycss_parser_token_drop_qualified_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
//{
//    switch (token->type) {
//        case MyCSS_TOKEN_TYPE_SEMICOLON:
//            mycss_entry_parser_list_pop(entry);
//            break;
//            
//        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET:
//            entry->parser = mycss_parser_token_drop_at_rule_component_value;
//            
//            mycss_entry_parser_list_push(entry, NULL, NULL, entry->parser_ending_token, false);
//            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
//            
//            break;
//            
//        default:
//            entry->parser = mycss_parser_token_drop_at_rule_component_value;
//            return false;
//    }
//    
//    return true;
//}


bool mycss_parser_token_drop_at_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_SEMICOLON:
            mycss_entry_parser_list_pop(entry);
            break;
            
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET:
            entry->parser = mycss_parser_token_drop_at_rule_component_value;
            
            mycss_entry_parser_list_push(entry, mycss_parser_token, NULL, entry->parser_ending_token, false);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
            
        default:
            entry->parser = mycss_parser_token_drop_at_rule_component_value;
            return false;
    }
    
    return true;
}

bool mycss_parser_token_drop_at_rule_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_FUNCTION:
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_at_rule_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
            
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET:
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_at_rule_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
            
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET:
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_at_rule_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            break;
            
        case MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS:
            mycss_entry_parser_list_push(entry, mycss_parser_token_drop_at_rule_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
        case MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET:
        case MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET:
            if(mycss_entry_parser_list_current_is_local(entry) &&
               token->type == entry->parser_ending_token)
            {
                mycss_entry_parser_list_pop(entry);
                
                if(token->type == MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET &&
                   mycss_entry_parser_list_current_is_local(entry) == false)
                {
                    mycss_entry_parser_list_pop(entry);
                }
            }
            
            break;
            
        default:
            break;
    }
    
    return true;
}


