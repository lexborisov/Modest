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

#include "mycss/selectors/function_parser.h"

/* <drop> */
bool mycss_selectors_function_parser_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == entry->parser_ending_token) {
        if(mycss_entry_parser_list_current_is_local(entry) == false) {
            mycss_entry_parser_list_pop(entry);
            return false;
        }
    }
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
            
        case MyCSS_TOKEN_TYPE_FUNCTION: {
            mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET: {
            mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_state_drop_component_value, NULL, entry->parser_ending_token, true);
            entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
            
            break;
        }
        case MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS: {
            mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_state_drop_component_value, NULL, entry->parser_ending_token, true);
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

bool mycss_selectors_unknown_parser(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    return false;
}

mycss_selectors_list_t * mycss_selectors_parser_check_selector_list(mycss_selectors_t* selectors, mycss_selectors_list_t *list)
{
    if(list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)
        mycss_selectors_list_destroy_last_empty_selector(selectors, list, true);
    
    if(list->entries_list_length == 0 || list->entries_list[0].entry == NULL) {
        return mycss_selectors_list_destroy(selectors, list, true);
    }
    
    return list;
}

///////////////////////////////////////////////////////////
////// NOT AND MATCHES AND CURRENT
//////
///////////////////////////////////////////////////////////
void mycss_selectors_function_parser_not_or_matches_or_current_find_bad_selector(mycss_selectors_list_t* selectors_list)
{
    for(size_t i = 0; i < selectors_list->entries_list_length; i++) {
        mycss_selectors_entry_t* selector = selectors_list->entries_list[i].entry;
        
        while(selector) {
            if(selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES ||
               selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT ||
               selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CURRENT ||
               selector->type == MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT)
            {
                if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
                    selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
                
                return;
            }
            
            selector = selector->next;
        }
    }
}

bool mycss_selectors_function_parser_not_or_matches_or_current_parser(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t *selectors_list = selectors->list_last;
    mycss_selectors_list_t *parent_list = selectors->list_last->parent;
    
    selectors->entry_last = mycss_selectors_list_last_entry(parent_list);
    selectors->list_last = parent_list;
    selectors->specificity = &parent_list->entries_list[ (parent_list->entries_list_length - 1) ].specificity;
    
    if(selectors->specificity && selectors->entry_last && (
                                 selectors->entry_last->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES ||
                                 selectors->entry_last->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT))
    {
        selectors->specificity->b--;
    }
    
    mycss_selectors_function_parser_not_or_matches_or_current_find_bad_selector(selectors_list);
    selectors_list = mycss_selectors_parser_check_selector_list(selectors, selectors_list);
    
    if(selectors_list == NULL) {
        if(selectors->entry_last) {
            selectors->entry_last->value = NULL;
            selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
    }
    else if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) && selectors->entry_last) {
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    }
    
    if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if(selectors_list)
        selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(selectors->entry_last)
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    
    return false;
}

///////////////////////////////////////////////////////////
////// HAS
//////
///////////////////////////////////////////////////////////
void mycss_selectors_function_parser_has_find_bad_selector(mycss_selectors_list_t* selectors_list)
{
    for(size_t i = 0; i < selectors_list->entries_list_length; i++) {
        mycss_selectors_entry_t* selector = selectors_list->entries_list[i].entry;

        while(selector) {
            if(selector->type == MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT) {
                if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
                    selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;

                return;
            }

            selector = selector->next;
        }
    }
}

bool mycss_selectors_function_parser_has(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t *selectors_list = selectors->list_last;
    mycss_selectors_list_t *parent_list = selectors->list_last->parent;
    
    selectors->entry_last = mycss_selectors_list_last_entry(parent_list);
    selectors->list_last = parent_list;
    selectors->specificity = &parent_list->entries_list[ (parent_list->entries_list_length - 1) ].specificity;
    
    mycss_selectors_function_parser_has_find_bad_selector(selectors_list);
    selectors_list = mycss_selectors_parser_check_selector_list(selectors, selectors_list);
    
    if(selectors_list == NULL) {
        if(selectors->entry_last) {
            selectors->entry_last->value = NULL;
            selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
    }
    else if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) && selectors->entry_last) {
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    }
    
    if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if(selectors_list)
        selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(selectors->entry_last)
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    
    return false;
}

///////////////////////////////////////////////////////////
////// CONTAINS
//////
///////////////////////////////////////////////////////////
void mycss_selectors_function_parser_contains_find_bad_selector(mycss_selectors_list_t* selectors_list)
{
    for(size_t i = 0; i < selectors_list->entries_list_length; i++) {
        mycss_selectors_entry_t* selector = selectors_list->entries_list[i].entry;

        while(selector) {
            if(selector->type == MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT) {
                if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
                    selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;

                return;
            }

            selector = selector->next;
        }
    }
}

bool mycss_selectors_function_parser_contains(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t *selectors_list = selectors->list_last;
    mycss_selectors_list_t *parent_list = selectors->list_last->parent;
    
    selectors->entry_last = mycss_selectors_list_last_entry(parent_list);
    selectors->list_last = parent_list;
    selectors->specificity = &parent_list->entries_list[ (parent_list->entries_list_length - 1) ].specificity;
    
    mycss_selectors_function_parser_contains_find_bad_selector(selectors_list);
    selectors_list = mycss_selectors_parser_check_selector_list(selectors, selectors_list);
    
    if(selectors_list == NULL) {
        if(selectors->entry_last) {
            selectors->entry_last->value = NULL;
            selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
    }
    else if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) && selectors->entry_last) {
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    }
    
    if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if(selectors_list)
        selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(selectors->entry_last)
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    
    return false;
}

///////////////////////////////////////////////////////////
////// NTH OF SELECTORS
//////
///////////////////////////////////////////////////////////
bool mycss_selectors_function_parser_nth_with_selectors(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_entry_t *selector = selectors->entry_last;
    
    if(mycss_selector_value_an_plus_b(selector->value)->is_broken)
    {
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        selector->value = mycss_selectors_value_pseudo_class_function_nth_child_destroy(entry, selector->value, true);
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    entry->parser = mycss_selectors_function_parser_nth_with_selectors_need_of;
    
    return false;
}

bool mycss_selectors_function_parser_nth_with_selectors_need_of(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_t *selectors = entry->selectors;
        mycss_selectors_entry_t *selector = selectors->entry_last;
        
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, false);
        
        mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
        
        if(mycore_strcasecmp(str.data, "of") != 0) {
            if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
                selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
            
            anb->of = NULL;
            
            mycore_string_destroy(&str, false);
            
            entry->parser = mycss_selectors_function_parser_state_drop_component_value;
            return true;
        }
        
        mycore_string_destroy(&str, false);
        
        /* create and switch entry, and create selector */
        mycss_selectors_list_t *current_list = selectors->list_last;
        
        selectors->list = &anb->of;
        selectors->list_last = NULL;
        selectors->ending_token = entry->parser_ending_token;
        
        mycss_selectors_state_compound_selector_list(entry, token, true);
        
        anb->of->parent = current_list;
        
        mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_nth_with_selectors_need_of_after, entry->parser_switch, entry->parser_ending_token, false);
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    return true;
}

bool mycss_selectors_function_parser_nth_with_selectors_need_of_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t *parent_list = selectors->list_last->parent;
    mycss_selectors_list_t *selectors_list = mycss_selectors_parser_check_selector_list(selectors, selectors->list_last);
    
    selectors->list_last = parent_list;
    selectors->entry_last = mycss_selectors_list_last_entry(parent_list);
    selectors->specificity = &parent_list->entries_list[ (parent_list->entries_list_length - 1) ].specificity;
    
    if(selectors_list == NULL) {
        if(selectors->entry_last) {
            mycss_selector_value_an_plus_b(selectors->entry_last->value)->of = NULL;
            selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
    }
    else if((selectors_list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) && selectors->entry_last) {
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    }
    
    if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if(selectors_list)
        selectors_list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(selectors->entry_last)
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    
    return false;
}

///////////////////////////////////////////////////////////
////// NTH
//////
///////////////////////////////////////////////////////////
bool mycss_selectors_function_parser_nth_without_selectors(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_entry_t *selector = selectors->entry_last;
    
    if(mycss_selector_value_an_plus_b(selector->value)->is_broken)
    {
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        selector->value = mycss_selectors_value_pseudo_class_function_nth_child_destroy(entry, selector->value, true);
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    entry->parser = mycss_selectors_function_parser_nth_without_selectors_after;
    
    return false;
}

bool mycss_selectors_function_parser_nth_without_selectors_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    
    mycss_selectors_t *selectors = entry->selectors;
    
    if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    
    if((selectors->entry_last->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
        selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    
    return false;
}

///////////////////////////////////////////////////////////
////// DROP
//////
///////////////////////////////////////////////////////////
bool mycss_selectors_function_parser_drop(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        mycss_selectors_function_drop_type_t drop_val = mycss_selector_value_drop(selector->value);
        
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, false);

        if(mycore_strcasecmp(str.data ,"active") == 0) {
            drop_val |= MyCSS_SELECTORS_FUNCTION_DROP_TYPE_ACTIVE;
        }
        else if(mycore_strcasecmp(str.data ,"valid") == 0) {
            drop_val |= MyCSS_SELECTORS_FUNCTION_DROP_TYPE_VALID;
        }
        else if(mycore_strcasecmp(str.data ,"invalid") == 0) {
            drop_val |= MyCSS_SELECTORS_FUNCTION_DROP_TYPE_INVALID;
        }
        else {
            if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
                selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
        
        selector->value = (void*)drop_val;
        
        mycore_string_destroy(&str, false);
        
        entry->parser = mycss_selectors_function_parser_drop_after;
    }
    else if(token->type == entry->parser_ending_token) {
        /* it may be empty? */
//        mycss_selectors_t *selectors = entry->selectors;
//        mycss_selectors_entry_t *selector = selectors->entry_last;
//        
//        mycss_selectors_function_drop_type_t drop_val = mycss_selector_value_drop(selector->value);
//        
//        if(drop_val == MyCSS_SELECTORS_FUNCTION_DROP_TYPE_UNDEF &&
//           (selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
//        {
//            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
//        }
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }

    return true;
}

bool mycss_selectors_function_parser_drop_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COLUMN) {
        entry->parser = mycss_selectors_function_parser_drop_after_column;
    }
    else if(token->type == entry->parser_ending_token) {
        entry->parser = mycss_selectors_function_parser_drop;
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;

        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;

        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }

    return true;
}

bool mycss_selectors_function_parser_drop_after_column(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        entry->parser = mycss_selectors_function_parser_drop;
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_drop;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    }
    
    return false;
}

///////////////////////////////////////////////////////////
////// DIR
//////
///////////////////////////////////////////////////////////
bool mycss_selectors_function_parser_dir(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT) {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        selector->value = mycss_selectors_value_pseudo_class_function_dir_create(entry, true);
        mycss_token_data_to_string(entry, token, selector->value, true, false);
        
        entry->parser = mycss_selectors_function_parser_dir_after;
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_drop;
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    return true;
}

bool mycss_selectors_function_parser_dir_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
    }
    else {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
    }
    
    return false;
}

///////////////////////////////////////////////////////////
////// LANG
//////
///////////////////////////////////////////////////////////
bool mycss_selectors_function_parser_lang(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT ||
            token->type == MyCSS_TOKEN_TYPE_STRING)
    {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        mycss_selectors_value_lang_t *lang;
        
        if(selector->value) {
            lang = mycss_selector_value_lang(selector->value);
            
            while(lang->next)
                lang = lang->next;
            
            lang->next = mycss_selectors_value_pseudo_class_function_lang_create(entry, true);
            mycss_token_data_to_string(entry, token, &lang->next->str, true, false);
        }
        else {
            lang = mycss_selectors_value_pseudo_class_function_lang_create(entry, true);
            mycss_token_data_to_string(entry, token, &lang->str, true, false);
            
            selector->value = lang;
        }
        
        entry->parser = mycss_selectors_function_parser_lang_after;
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    return true;
}

bool mycss_selectors_function_parser_lang_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_selectors_function_parser_lang_comma;
    }
    else if(token->type == entry->parser_ending_token) {
        mycss_entry_parser_list_pop(entry);
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
    
    return true;
}

bool mycss_selectors_function_parser_lang_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE) {
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT ||
            token->type == MyCSS_TOKEN_TYPE_STRING)
    {
        entry->parser = mycss_selectors_function_parser_lang;
        return false;
    }
    else {
        /* parse error */
        mycss_selectors_entry_t *selector = entry->selectors->entry_last;
        
        if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        entry->parser = mycss_selectors_function_parser_state_drop_component_value;
        return false;
    }
}



