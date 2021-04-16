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

#include "mycss/selectors/state.h"

void mycss_selectors_state_end(mycss_entry_t* entry)
{
    mycss_selectors_entry_t* selector = entry->selectors->entry_last;
    
    if(selector == NULL)
        return;
    
    if(selector->type == MyCSS_SELECTORS_TYPE_ATTRIBUTE ||
       selector->type == MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION ||
       (selector->key == NULL && selector->value == NULL))
    {
        mycss_selectors_entry_clean(selector);
    }
    else {
        mycss_selectors_parser_selector_end(entry, NULL);
    }
}

/* for unknown functions */
bool mycss_selectors_state_function_skip_all(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
//    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS)
//        return entry->parser_switch(entry, token);
    
    return true;
}

/* <drop> */
bool mycss_selectors_state_drop(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
            
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            if(mycss_entry_parser_list_length(entry) == 0) {
                entry->parser = mycss_selectors_state_drop_component_value;
            }
            else if(mycss_entry_parser_list_length(entry) <= 1) {
                mycss_entry_parser_list_pop(entry);
                
            }
            return false;
        }
        default:
            if(entry->selectors->list_last)
                entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
            
            entry->parser = mycss_selectors_state_drop_component_value;
            return false;
    }
    
    return true;
}

bool mycss_selectors_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == entry->selectors->ending_token) {
        if(mycss_entry_parser_list_current_is_local(entry) == false) {
            mycss_entry_parser_list_pop(entry);
            return true;
        }
    }
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
            
        case MyCSS_TOKEN_TYPE_FUNCTION: {
            mycss_entry_parser_list_push(entry, mycss_selectors_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_selectors_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_selectors_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS: {
            mycss_entry_parser_list_push(entry, mycss_selectors_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        default: {
            if(mycss_entry_parser_list_current_is_local(entry) &&
               token->type == entry->parser_ending_token)
            {
                mycss_entry_parser_list_pop(entry);
            }
            
            break;
        }
    }
    
    return true;
}

/* <combinator> */
bool mycss_selectors_state_combinator(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_COLUMN: {
            *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_COLUMN;
            MyCORE_DEBUG("mycss_selectors_state_combinator_column");
            entry->parser = entry->parser_switch;
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '+') {
                *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_NEXT_SIBLING;
                MyCORE_DEBUG("mycss_selectors_state_combinator_plus");
                entry->parser = entry->parser_switch;
            }
            else if(*token->data == '>') {
                *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_CHILD;
                MyCORE_DEBUG("mycss_selectors_state_combinator_greater_than");
                entry->parser = mycss_selectors_state_combinator_greater_than;
            }
            else if(*token->data == '~') {
                *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_FOLLOWING_SIBLING;
                MyCORE_DEBUG("mycss_selectors_state_combinator_tilde");
                entry->parser = entry->parser_switch;
            }
            else {
                *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_UNDEF;
                entry->parser = entry->parser_switch;
                return false;
            }
            
            break;
        }
        default: {
            *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_UNDEF;
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_combinator_greater_than(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_DELIM) {
        if(*token->data == '>') {
            *entry->selectors->combinator = MyCSS_SELECTORS_COMBINATOR_DESCENDANT;
            MyCORE_DEBUG("mycss_selectors_state_combinator_greater_than_greater_than");
            entry->parser = entry->parser_switch;
        }
        else {
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

/* <complex-selector-list> */
bool mycss_selectors_state_complex_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    
    mycss_selectors_list_t *sel_list = mycss_selectors_list_create(entry->selectors);
    mycss_selectors_list_append_to_current(entry->selectors, sel_list);
    
    mycss_selectors_list_append_selector(selectors, sel_list, NULL);
    selectors->entry = &sel_list->entries_list[0].entry;
    selectors->entry_last = NULL;
    
    entry->parser = mycss_selectors_state_complex_selector_list_need_selector;
    return false;
}

bool mycss_selectors_state_complex_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        if(entry->selectors->list_last)
            entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_complex_selector_list_need_combinator_or_selector;
    
    if(entry->selectors->entry_last && entry->selectors->entry_last->key == NULL) {
        if(mycss_selectors_state_simple_selector(entry, token, true))
            return true;
    }
    else {
        if(mycss_selectors_state_simple_selector_begin(entry, token, true))
            return true;
    }
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_complex_selector_list_need_combinator_or_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        entry->parser = mycss_selectors_state_complex_selector_list_need_combinator_or_selector_ws;
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_complex_selector_list_need_selector;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_complex_selector_list_need_combinator_or_selector;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_complex_selector_list_need_combinator_or_selector_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_complex_selector_list_need_selector;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_complex_selector_list_need_combinator_or_selector;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true)) {
        entry->selectors->entry_last->combinator = MyCSS_SELECTORS_COMBINATOR_DESCENDANT;
        return true;
    }
    
    entry->parser_switch = mycss_selectors_state_complex_selector_list_need_selector;
    entry->selectors->combinator = &entry->selectors->entry_last->combinator;
    
    if(mycss_selectors_state_combinator(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

/* <compound-selector-list> */
bool mycss_selectors_state_compound_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    
    mycss_selectors_list_t *sel_list = mycss_selectors_list_create(entry->selectors);
    mycss_selectors_list_append_to_current(entry->selectors, sel_list);
    
    mycss_selectors_list_append_selector(selectors, sel_list, NULL);
    selectors->entry = &sel_list->entries_list[0].entry;
    selectors->entry_last = NULL;
    
    entry->parser = mycss_selectors_state_compound_selector_list_comma_ws;
    return false;
}

bool mycss_selectors_state_compound_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == entry->selectors->ending_token) {
        if(entry->selectors->list_last)
            entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_compound_selector_list_need_selector_or_comma;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_compound_selector_list_need_selector_or_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_compound_selector_list_comma_ws;
        return true;
    }
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        entry->parser = mycss_selectors_state_compound_selector_list_need_ending_or_comma;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_compound_selector_list_comma_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    entry->parser = mycss_selectors_state_compound_selector_list_need_selector;
    
    return false;
}

bool mycss_selectors_state_compound_selector_list_need_ending_or_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_compound_selector_list_comma_ws;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

/* <relative-selector-list> */
bool mycss_selectors_state_relative_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    
    mycss_selectors_list_t *sel_list = mycss_selectors_list_create(entry->selectors);
    mycss_selectors_list_append_to_current(entry->selectors, sel_list);
    
    mycss_selectors_list_append_selector(selectors, sel_list, NULL);
    selectors->entry = &sel_list->entries_list[0].entry;
    selectors->entry_last = NULL;
    
    entry->parser = mycss_selectors_state_relative_selector_list_need_combinator_or_selector_begin;
    return false;
}

bool mycss_selectors_state_relative_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    if(token->type == entry->selectors->ending_token) {
        if(entry->selectors->list_last)
            entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_combinator_or_selector;
    
    if(entry->selectors->entry_last && entry->selectors->entry_last->key == NULL) {
        if(mycss_selectors_state_simple_selector(entry, token, true))
            return true;
    }
    else {
        if(mycss_selectors_state_simple_selector_begin(entry, token, true))
            return true;
    }
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        if(entry->selectors->list_last)
            entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_combinator_or_selector;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true))
        return true;
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_selector;
    entry->selectors->combinator = &entry->selectors->entry_last->combinator;
    
    if(mycss_selectors_state_combinator(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}


bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        entry->parser = mycss_selectors_state_relative_selector_list_need_combinator_or_selector_ws;
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_relative_selector_list_need_combinator_or_selector_begin;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_combinator_or_selector;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true))
        return true;
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_selector;
    entry->selectors->combinator = &entry->selectors->entry_last->combinator;
    
    if(mycss_selectors_state_combinator(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_selectors_t *selectors = entry->selectors;
        
        mycss_selectors_list_append_selector(selectors, selectors->list_last, NULL);
        
        selectors->entry = &selectors->list_last->entries_list[ (selectors->list_last->entries_list_length - 1) ].entry;
        selectors->entry_last = NULL;
        
        entry->parser = mycss_selectors_state_relative_selector_list_need_combinator_or_selector_begin;
        return true;
    }
    else if(token->type == entry->selectors->ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_combinator_or_selector;
    
    if(mycss_selectors_state_simple_selector_begin(entry, token, true)) {
        entry->selectors->entry_last->combinator = MyCSS_SELECTORS_COMBINATOR_DESCENDANT;
        return true;
    }
    
    entry->parser_switch = mycss_selectors_state_relative_selector_list_need_selector;
    entry->selectors->combinator = &entry->selectors->entry_last->combinator;
    
    if(mycss_selectors_state_combinator(entry, token, true))
        return true;
    
    entry->parser = mycss_selectors_state_drop;
    
    return false;
}

/* <simple-selector> */
bool mycss_selectors_state_simple_selector_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_parser_selector_begin(entry, token);
    return mycss_selectors_state_simple_selector(entry, token, last_response);
}

bool mycss_selectors_state_simple_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycss_selectors_parser_selector_ident_type(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_ident");
            
            entry->parser = mycss_selectors_state_simple_selector_ident;
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            // HAND_EDIT_BEGIN
            if(*token->data == '*') {
                mycss_selectors_parser_selector_ident_type(entry, token);
                MyCORE_DEBUG("mycss_selectors_state_simple_selector_asterisk");
                
                entry->parser = mycss_selectors_state_simple_selector_ident;
            }
            // HAND_EDIT_END
            else if(*token->data == '.') {
                entry->parser = mycss_selectors_state_simple_selector_full_stop;
            }
            else if(*token->data == '|') {
                // HAND_EDIT_BEGIN
                mycss_selectors_parser_selector_namespace_ident(entry, token);
                // HAND_EDIT_END
                entry->parser = mycss_selectors_state_simple_selector_vertical_bar;
            }
            else {
                entry->parser = entry->parser_switch;
                return false;
            }
            
            break;
        }
        case MyCSS_TOKEN_TYPE_COLON: {
            entry->parser = mycss_selectors_state_simple_selector_colon;
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET: {
            entry->parser = mycss_selectors_state_simple_selector_left_bracket;
            break;
        }
        case MyCSS_TOKEN_TYPE_HASH: {
            mycss_selectors_parser_selector_id(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_hash");
            entry->parser = entry->parser_switch;
            break;
        }
        default: {
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_left_bracket(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE: {
            break;
        }
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycss_selectors_parser_selector_ident_attr(entry, token);
            entry->parser = mycss_selectors_state_simple_selector_left_bracket_ident;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '*') {
                // HAND_EDIT_BEGIN
                mycss_selectors_parser_selector_ident_attr(entry, token);
                // HAND_EDIT_END
                entry->parser = mycss_selectors_state_simple_selector_left_bracket_ident;
            }
            else if(*token->data == '|') {
                // HAND_EDIT_BEGIN
                mycss_selectors_parser_selector_namespace_attr(entry, token);
                // HAND_EDIT_END
                entry->parser = mycss_selectors_state_simple_selector_left_bracket_vertical_bar;
            }
            else {
                mycss_selectors_parser_expectations_error(entry, token);
                
                mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
                entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
                
                entry->parser = mycss_selectors_state_drop;
                return false;
            }
            
            break;
        }
        default: {
            mycss_selectors_parser_expectations_error(entry, token);
            
            mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
            entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            entry->parser = mycss_selectors_state_drop;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_left_bracket_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_after_namespace(entry, token);
        entry->parser = mycss_selectors_state_left_bracket_after_wq_name_attr;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        
        mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
        entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
        
        entry->parser = mycss_selectors_state_drop;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_left_bracket_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE: {
            entry->parser = mycss_selectors_state_left_bracket_after_wq_name_attr;
            break;
        }
        case MyCSS_TOKEN_TYPE_INCLUDE_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_INCLUDE;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            break;
        }
        case MyCSS_TOKEN_TYPE_DASH_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_DASH;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            break;
        }
        case MyCSS_TOKEN_TYPE_PREFIX_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_PREFIX;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            break;
        }
        case MyCSS_TOKEN_TYPE_SUFFIX_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUFFIX;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            break;
        }
        case MyCSS_TOKEN_TYPE_SUBSTRING_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUBSTRING;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '=') {
                if(selector->value == NULL)
                    selector->value = mycss_selectors_value_attribute_create(entry, true);
                
                mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_EQUAL;
                entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            }
            else if(*token->data == '|') {
                // HAND_EDIT_BEGIN
                mycss_selectors_parser_selector_namespace_attr(entry, token);
                // HAND_EDIT_END
                entry->parser = mycss_selectors_state_simple_selector_left_bracket_ident_vertical_bar;
            }
            else {
                mycss_selectors_parser_expectations_error(entry, token);
                
                mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
                entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
                
                entry->parser = mycss_selectors_state_drop;
                return false;
            }
            break;
        }
        case MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET: {
            mycss_selectors_parser_selector_end(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_left_bracket_ident_right_bracket");
            entry->parser = entry->parser_switch;
            break;
        }
        default: {
            mycss_selectors_parser_expectations_error(entry, token);
            
            mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
            entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            entry->parser = mycss_selectors_state_drop;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_left_bracket_ident_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_after_namespace(entry, token);
        entry->parser = mycss_selectors_state_left_bracket_after_wq_name_attr;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        
        mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
        entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
        
        entry->parser = mycss_selectors_state_drop;
        return false;
    }
    
    return true;
}

// HAND_EDIT_BEGIN
bool mycss_selectors_state_simple_selector_colon(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycss_selectors_parser_selector_pseudo_class(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_colon_ident");
            entry->parser = entry->parser_switch;
            break;
        }
        case MyCSS_TOKEN_TYPE_COLON: {
            entry->parser = mycss_selectors_state_simple_selector_colon_colon;
            break;
        }
        case MyCSS_TOKEN_TYPE_FUNCTION: {
            mycss_selectors_parser_selector_pseudo_class_function(entry, token);
            break;
        }
        default: {
            mycss_selectors_parser_expectations_error(entry, token);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_colon_colon(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_pseudo_element(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_colon_colon_ident");
        entry->parser = entry->parser_switch;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_FUNCTION) {
        mycss_selectors_parser_selector_pseudo_element_function(entry, token);
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_colon_colon_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS) {
        mycss_selectors_parser_selector_pseudo_element_function_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_colon_colon_function_right_parenthesis");
        entry->parser = entry->parser_switch;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_colon_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS) {
        mycss_selectors_parser_selector_pseudo_class_function_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_colon_function_right_parenthesis");
        entry->parser = entry->parser_switch;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}
// HAND_EDIT_END

bool mycss_selectors_state_simple_selector_full_stop(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_class(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_full_stop_ident");
        entry->parser = entry->parser_switch;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_after_namespace(entry, token);
        mycss_selectors_parser_selector_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_vertical_bar_ident");
        entry->parser = entry->parser_switch;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_DELIM) {
        if(*token->data == '*') {
            mycss_selectors_parser_selector_after_namespace(entry, token);
            mycss_selectors_parser_selector_end(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_vertical_bar_asterisk");
            entry->parser = entry->parser_switch;
        }
        else {
            mycss_selectors_parser_expectations_error(entry, token);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_DELIM) {
        if(*token->data == '|') {
            // HAND_EDIT_BEGIN
            mycss_selectors_parser_selector_namespace_ident(entry, token);
            // HAND_EDIT_END
            entry->parser = mycss_selectors_state_simple_selector_ident_vertical_bar;
        }
        else {
            mycss_selectors_parser_selector_end(entry, token);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        mycss_selectors_parser_selector_end(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_simple_selector_ident_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_after_namespace(entry, token);
        mycss_selectors_parser_selector_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_simple_selector_ident_vertical_bar_ident");
        entry->parser = entry->parser_switch;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_DELIM) {
        if(*token->data == '*') {
            mycss_selectors_parser_selector_after_namespace(entry, token);
            mycss_selectors_parser_selector_end(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_simple_selector_ident_vertical_bar_asterisk");
            entry->parser = entry->parser_switch;
        }
        else {
            mycss_selectors_parser_expectations_error(entry, token);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_left_bracket_after_wq_name_attr(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE: {
            break;
        }
        case MyCSS_TOKEN_TYPE_INCLUDE_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_INCLUDE;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_DASH_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_DASH;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_PREFIX_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_PREFIX;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_SUFFIX_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUFFIX;
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_SUBSTRING_MATCH: {
            if(selector->value == NULL)
                selector->value = mycss_selectors_value_attribute_create(entry, true);
            
            mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_SUBSTRING;
            
            entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '=') {
                if(selector->value == NULL)
                    selector->value = mycss_selectors_value_attribute_create(entry, true);
                
                mycss_selector_value_attribute(selector->value)->match = MyCSS_SELECTORS_MATCH_EQUAL;
                entry->parser = mycss_selectors_state_shared_after_attr_matcher;
            }
            else {
                mycss_selectors_parser_expectations_error(entry, token);
                
                mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
                entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
                
                entry->parser = mycss_selectors_state_drop;
                return false;
            }
            break;
        }
        case MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET: {
            mycss_selectors_parser_selector_end(entry, token);
            MyCORE_DEBUG("mycss_selectors_state_shared_after_wq_name_attr_right_bracket");
            entry->parser = entry->parser_switch;
            break;
        }
        default: {
            mycss_selectors_parser_expectations_error(entry, token);
            
            mycss_entry_parser_list_push(entry, entry->parser_switch, NULL, entry->selectors->ending_token, false);
            entry->selectors->ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            entry->parser = mycss_selectors_state_drop;
            return false;
        }
    }
    
    return true;
}

bool mycss_selectors_state_shared_after_attr_modifier(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET) {
        mycss_selectors_parser_selector_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_shared_after_attr_modifier_right_bracket");
        entry->parser = entry->parser_switch;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_shared_after_attribute_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        if(*token->data == 'i') {
            mycss_selectors_parser_selector_modifier(entry, token);
            entry->parser = mycss_selectors_state_shared_after_attr_modifier;
        }
        else {
            mycss_selectors_parser_expectations_error(entry, token);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else if(token->type == MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET) {
        mycss_selectors_parser_selector_end(entry, token);
        MyCORE_DEBUG("mycss_selectors_state_shared_after_attribute_value_right_bracket");
        entry->parser = entry->parser_switch;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_selectors_state_shared_after_attr_matcher(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_parser_selector_value(entry, token);
        entry->parser = mycss_selectors_state_shared_after_attribute_value;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_STRING) {
        mycss_selectors_parser_selector_value(entry, token);
        entry->parser = mycss_selectors_state_shared_after_attribute_value;
    }
    else {
        mycss_selectors_parser_expectations_error(entry, token);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}


