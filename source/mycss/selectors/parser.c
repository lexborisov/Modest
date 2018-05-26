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

#include "mycss/selectors/parser.h"
#include "mycss/selectors/value_resource.h"

/////////////////////////////////////////////////////////
//// Selectors Begin
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_begin(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = mycss_selectors_entry_create(entry->selectors);
    mycss_selectors_entry_append_to_current(entry->selectors, selector);
}

/////////////////////////////////////////////////////////
//// Selector type
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_ident_type(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    /* set default namespace */
    if(entry->stylesheet)
        selector->ns_entry = entry->stylesheet->ns_stylesheet.entry_default;
    
    selector->type = MyCSS_SELECTORS_TYPE_ELEMENT;
    selector->key  = str;
    
    if(entry->selectors->specificity)
        if(str->length != 1 || *str->data != '*')
            entry->selectors->specificity->c++;
}

void mycss_selectors_parser_selector_ident_attr(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    /* set default namespace */
    if(entry->stylesheet)
        selector->ns_entry = entry->stylesheet->ns_stylesheet.entry_default;
    
    selector->type = MyCSS_SELECTORS_TYPE_ATTRIBUTE;
    selector->key  = str;
    
    if(entry->selectors->specificity)
        if(str->length != 1 || *str->data != '*')
            entry->selectors->specificity->b++;
}

void mycss_selectors_parser_selector_id(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    /* set default namespace */
    if(entry->stylesheet)
        selector->ns_entry = entry->stylesheet->ns_stylesheet.entry_default;
    
    selector->type = MyCSS_SELECTORS_TYPE_ID;
    selector->key  = str;
    
    if(entry->selectors->specificity)
        entry->selectors->specificity->a++;
    
    mycss_selectors_parser_selector_end(entry, token);
}

void mycss_selectors_parser_selector_class(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    /* set default namespace */
    if(entry->stylesheet)
        selector->ns_entry = entry->stylesheet->ns_stylesheet.entry_default;
    
    selector->type = MyCSS_SELECTORS_TYPE_CLASS;
    selector->key  = str;
    
    if(entry->selectors->specificity)
        entry->selectors->specificity->b++;
    
    mycss_selectors_parser_selector_end(entry, token);
}

/////////////////////////////////////////////////////////
//// Namespace
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_namespace(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    mycore_string_t *str = selector->key;
    
    if(str == NULL || str->length == 0) {
        mycore_string_destroy(str, 0);
        
        selector->key = NULL;
        
        if(entry->stylesheet)
            selector->ns_entry = &entry->stylesheet->ns_stylesheet.entry_undef;
        
        return;
    }
    
    if(str->length == 1 && *str->data == '*') {
        mycore_string_destroy(str, 0);
        
        selector->key = NULL;
        
        if(entry->stylesheet)
            selector->ns_entry = &entry->stylesheet->ns_stylesheet.entry_any;
        
        return;
    }
    
    if(entry->stylesheet)
        selector->ns_entry = mycss_namespace_entry_by_name(entry->ns, entry->stylesheet->ns_stylesheet.name_tree, str->data, str->length, false);
    
    if(selector->ns_entry == NULL)
        mycss_selectors_parser_expectations_error(entry, token);
    
    mycore_string_destroy(str, 0);
    selector->key = NULL;
}

void mycss_selectors_parser_selector_namespace_ident(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycss_selectors_parser_selector_namespace(entry, token);
    
    if(selector->type == MyCSS_SELECTORS_TYPE_UNDEF)
        selector->type = MyCSS_SELECTORS_TYPE_ELEMENT;
}

void mycss_selectors_parser_selector_namespace_attr(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycss_selectors_parser_selector_namespace(entry, token);
    
    if(selector->type == MyCSS_SELECTORS_TYPE_UNDEF)
        selector->type = MyCSS_SELECTORS_TYPE_ATTRIBUTE;
}

void mycss_selectors_parser_selector_after_namespace(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, true);
    
    selector->key = str;
    
    if(entry->selectors->specificity) {
        if(selector->ns_entry == &entry->stylesheet->ns_stylesheet.entry_any) {
            if(selector->type == MyCSS_SELECTORS_TYPE_ATTRIBUTE)
                entry->selectors->specificity->b--;
            else
                entry->selectors->specificity->c--;
        }
        
        if(str->length != 1 || *str->data != '*') {
            if(selector->type == MyCSS_SELECTORS_TYPE_ATTRIBUTE)
                entry->selectors->specificity->b++;
            else
                entry->selectors->specificity->c++;
        }
    }
}

/////////////////////////////////////////////////////////
//// Value and Modifier
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_value(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    mycss_selectors_object_attribute_t *attr = selector->value;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    attr->value = str;
}

void mycss_selectors_parser_selector_modifier(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    mycss_selector_value_attribute(selector->value)->mod = MyCSS_SELECTORS_MOD_I;
}

/////////////////////////////////////////////////////////
//// Pseudo Class
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_pseudo_class(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, true);
    
    selector->sub_type = mycss_pseudo_class_by_name(str->data, str->length);
    selector->key      = str;
    selector->type     = MyCSS_SELECTORS_TYPE_PSEUDO_CLASS;
    
    /* hack for elements */
    if(selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_UNKNOWN) {
        selector->sub_type = mycss_pseudo_element_by_name(str->data, str->length);
        
        if(selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_UNKNOWN) {
            selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        }
        else {
            selector->type = MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT;
        }
    }
    
    if(selector->type == MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT) {
        if(entry->selectors->specificity)
            entry->selectors->specificity->c++;
    } else {
        if(entry->selectors->specificity)
            entry->selectors->specificity->b++;
    }
    
    mycss_selectors_parser_check_and_set_bad_parent_selector(entry, entry->selectors->list_last);
    mycss_selectors_parser_selector_end(entry, token);
}

void mycss_selectors_parser_selector_pseudo_class_function(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, true);
    
    selector->key   = str;
    selector->type  = MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION;
    
    entry->parser_ending_token = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
    mycss_entry_parser_list_push(entry, mycss_selectors_state_simple_selector_colon_function, entry->parser_switch, entry->selectors->ending_token, false);
    
    if(entry->selectors->specificity)
        entry->selectors->specificity->b++;
    
    mycss_selectors_function_begin_f to_func = mycss_function_begin_by_name(str->data, str->length);
    
    if(to_func) {
        to_func(entry, selector);
    }
    else {
        /* skip and set bad type for current selector */
        selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        if(entry->selectors->list_last)
            entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycss_selectors_begin_unknown(entry, selector);
    }
}

void mycss_selectors_parser_selector_pseudo_class_function_end(mycss_entry_t* entry, mycss_token_t* token)
{
    entry->selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_parser_check_and_set_bad_parent_selector(entry, entry->selectors->list_last);
    mycss_selectors_parser_selector_end(entry, token);
}

/////////////////////////////////////////////////////////
//// Pseudo Element
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_pseudo_element(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, true);
    
    selector->key  = str;
    selector->type = MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT;
    
    selector->sub_type = mycss_pseudo_element_by_name(str->data, str->length);
    
    if(selector->sub_type == MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_UNKNOWN)
        selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(entry->selectors->specificity)
        entry->selectors->specificity->c++;
    
    mycss_selectors_parser_check_and_set_bad_parent_selector(entry, entry->selectors->list_last);
    mycss_selectors_parser_selector_end(entry, token);
}

void mycss_selectors_parser_selector_pseudo_element_function(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, true);
    
    selector->key   = str;
    selector->type  = MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT_FUNCTION;
    
    selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    mycss_selectors_begin_unknown(entry, selector);
    
    if(entry->selectors->specificity)
        entry->selectors->specificity->c++;
}

void mycss_selectors_parser_selector_pseudo_element_function_end(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_parser_check_and_set_bad_parent_selector(entry, entry->selectors->list_last);
    mycss_selectors_parser_selector_end(entry, token);
}

/////////////////////////////////////////////////////////
//// End and bad selectors
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_selector_end(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    if(entry->callback_selector_done)
        entry->callback_selector_done(entry->selectors, selector);
}

void mycss_selectors_parser_expectations_error(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_t *selectors = entry->selectors;
    
    selectors->entry_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    
    if(entry->selectors->list_last)
        entry->selectors->list_last->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
}

void mycss_selectors_parser_bad_token(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_selectors_entry_t *selector = entry->selectors->entry_last;
    
    if((selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0) {
        selector->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
        
        mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
        selector->key = str;
        
        mycss_token_data_to_string(entry, token, selector->key, true, false);
        return;
    }
    
    mycss_token_data_to_string(entry, token, selector->key, false, false);
}

/////////////////////////////////////////////////////////
//// Set bad
////
/////////////////////////////////////////////////////////
void mycss_selectors_parser_check_and_set_bad_parent_selector(mycss_entry_t* entry, mycss_selectors_list_t* selectors_list)
{
    mycss_selectors_list_t *list = entry->selectors->list_last;
    
    if(list && entry->selectors->entry_last->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)
    {
        if((list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) == 0)
            list->flags |= MyCSS_SELECTORS_FLAGS_SELECTOR_BAD;
    }
}


