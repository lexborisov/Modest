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

#include "mycss/selectors/serialization.h"
#include "mycss/selectors/myosi_resource.h"

void mycss_selectors_serialization_chain(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector,
                                         mycore_callback_serialize_f callback, void* context)
{
    while(selector) {
        if(selector->combinator == MyCSS_SELECTORS_COMBINATOR_DESCENDANT)
            callback(" ", 1, context);
        else if(selector->combinator == MyCSS_SELECTORS_COMBINATOR_UNDEF) {
            /* "" */
        }
        else {
            callback(" ", 1, context);
            
            const char *comb_name = mycss_selectors_resource_combinator_names_map[ selector->combinator ];
            callback(comb_name, strlen(comb_name), context);
            
            callback(" ", 1, context);
        }
        
        mycss_selectors_serialization_selector(selectors, selector, callback, context);
        
        selector = selector->next;
    }
}

bool mycss_selectors_serialization_list(mycss_selectors_t* selectors, mycss_selectors_list_t* selectors_list,
                                        mycore_callback_serialize_f callback, void* context)
{
    while(selectors_list) {

        for(size_t i = 0; i < selectors_list->entries_list_length; i++)
        {
            mycss_selectors_entries_list_t *entries = &selectors_list->entries_list[i];
            mycss_selectors_serialization_chain(selectors, entries->entry, callback, context);
            
            if((i + 1) != selectors_list->entries_list_length)
                callback(", ", 2, context);
        }
        
        if(selectors_list->declaration_entry) {
            callback(" {", 2, context);
            mycss_declaration_serialization_entries(selectors->ref_entry, selectors_list->declaration_entry, callback, context);
            callback("}", 1, context);
        }
        
        if(selectors_list->flags == MyCSS_SELECTORS_FLAGS_SELECTOR_BAD) {
            callback("^BAD_SELECTOR_LIST", 18, context);
        }
        
        if(selectors_list->next)
            callback("\n", 1, context);
        
        selectors_list = selectors_list->next;
    }
    
    return true;
}

bool mycss_selectors_serialization_selector(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector,
                                            mycore_callback_serialize_f callback, void* context)
{
    switch(selector->type) {
        case MyCSS_SELECTORS_TYPE_ELEMENT: {
            if(selector->ns_entry)
                mycss_namespace_serialization_entry(selectors->ref_entry->ns, selector->ns_entry, callback, context, true);
            
            if(selector->key)
                callback(selector->key->data, selector->key->length, context);
            
            break;
        }
        case MyCSS_SELECTORS_TYPE_ATTRIBUTE: {
            callback("[", 1, context);
            
            if(selector->ns_entry)
                mycss_namespace_serialization_entry(selectors->ref_entry->ns, selector->ns_entry, callback, context, true);
            
            if(selector->key)
                callback(selector->key->data, selector->key->length, context);
            
            if(selector->value == NULL) {
                callback("]", 1, context);
                break;
            }
            
            /* match value: =, |=, ~=... */
            callback(" ", 1, context);
            
            const char *match_name = mycss_selectors_resource_matcher_names_map[ mycss_selector_value_attribute(selector->value)->match ];
            callback(match_name, strlen(match_name), context);
            
            callback(" ", 1, context);
            
            /* value */
            if(mycss_selector_value_attribute(selector->value)->value) {
                mycore_string_t *str_value = mycss_selector_value_attribute(selector->value)->value;
                callback(str_value->data, str_value->length, context);
            }
            
            /* modificator */
            if(mycss_selector_value_attribute(selector->value)->mod & MyCSS_SELECTORS_MOD_I) {
                callback(" i", 2, context);
            }
            
            callback("]", 1, context);
            break;
        }
        case MyCSS_SELECTORS_TYPE_ID: {
            if(selector->key) {
                callback("#", 1, context);
                callback(selector->key->data, selector->key->length, context);
            }
            
            break;
        }
        case MyCSS_SELECTORS_TYPE_CLASS: {
            if(selector->key) {
                callback(".", 1, context);
                callback(selector->key->data, selector->key->length, context);
            }
            
            break;
        }
        case MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION: {
            if(selector->key) {
                callback(":", 1, context);
                callback(selector->key->data, selector->key->length, context);
            }
            
            callback("(", 1, context);

            switch (selector->sub_type) {
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CONTAINS:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_HAS:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CURRENT:
                    if(selector->value)
                        mycss_selectors_serialization_list(selectors, selector->value, callback, context);
                    
                    break;
                    
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_CHILD:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_CHILD:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_COLUMN:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_COLUMN:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_OF_TYPE:
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_OF_TYPE:
                    if(selector->value) {
                        mycss_an_plus_b_serialization(selector->value, callback, context);
                        
                        if(mycss_selector_value_an_plus_b(selector->value)->of) {
                            callback(" of ", 4, context);
                            mycss_selectors_serialization_list(selectors, mycss_selector_value_an_plus_b(selector->value)->of, callback, context);
                        }
                    }
                    
                    break;
                    
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DROP: {
                    mycss_selectors_function_drop_type_t drop_val = mycss_selector_value_drop(selector->value);
                    
                    if(drop_val & MyCSS_SELECTORS_FUNCTION_DROP_TYPE_ACTIVE) {
                        callback("active", 6, context);
                        
                        if(drop_val != MyCSS_SELECTORS_FUNCTION_DROP_TYPE_ACTIVE)
                            callback(" || ", 4, context);
                    }
                    
                    if(drop_val & MyCSS_SELECTORS_FUNCTION_DROP_TYPE_VALID) {
                        callback("valid", 5, context);
                        
                        if(drop_val & MyCSS_SELECTORS_FUNCTION_DROP_TYPE_INVALID)
                            callback(" || ", 4, context);
                    }
                    
                    if(drop_val & MyCSS_SELECTORS_FUNCTION_DROP_TYPE_INVALID)
                        callback("invalid", 7, context);
                    
                    break;
                }
                    
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DIR:
                {
                    if(selector->value) {
                        mycore_string_t *str_fname = mycss_selector_value_string(selector->value);
                        callback(str_fname->data, str_fname->length, context);
                    }
                    
                    break;
                }
                    
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LANG: {
                    if(selector->value) {
                        mycss_selectors_value_lang_t *lang = mycss_selector_value_lang(selector->value);
                        
                        while(lang) {
                            callback(lang->str.data, lang->str.length, context);
                            
                            if(lang->next)
                                callback(", ", 2, context);
                            
                            lang = lang->next;
                        }
                        
                    }
                    
                    break;
                }
                    
                case MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNKNOWN:
                    callback("^UST", 4, context);
                    break;
                    
                default:
                    break;
            }
            
            callback(")", 1, context);
            break;
        }
            
        case MyCSS_SELECTORS_TYPE_PSEUDO_CLASS: {
            callback(":", 1, context);
            
            if(selector->key)
                callback(selector->key->data, selector->key->length, context);
            
            break;
        }
            
        case MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT: {
            callback("::", 2, context);
            
            if(selector->key)
                callback(selector->key->data, selector->key->length, context);
            
            break;
        }
            
        default: {
            if(selector->key)
                callback(selector->key->data, selector->key->length, context);
            
            callback("^U", 2, context);
            break;
        }
    };
    
    if(selector->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)
        callback("^B", 2, context);
    
    return true;
}


