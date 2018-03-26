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

#include "modest/finder/finder.h"
#include "modest/finder/resource.h"

modest_finder_t * modest_finder_create(void)
{
    return (modest_finder_t*)mycore_calloc(1, sizeof(modest_finder_t));
}

mystatus_t modest_finder_init(modest_finder_t* finder)
{
    return MODEST_STATUS_OK;
}

void modest_finder_clean(modest_finder_t* finder)
{
    
}

modest_finder_t * modest_finder_destroy(modest_finder_t* finder, bool self_destroy)
{
    if(finder == NULL)
        return NULL;
    
    if(self_destroy) {
        mycore_free(finder);
        return NULL;
    }
    
    return finder;
}

modest_finder_t * modest_finder_create_simple(void)
{
    modest_finder_t *finder = modest_finder_create();
    
    if(finder == NULL)
        return NULL;
    
    if(modest_finder_init(finder) != MODEST_STATUS_OK)
        return modest_finder_destroy(finder, true);
    
    return finder;
}

void modest_finder_callback_found_with_collection(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx)
{
    myhtml_collection_t* collection = (myhtml_collection_t*)ctx;
    
    if(myhtml_collection_check_size(collection, 1, 1024) == MyHTML_STATUS_OK) {
        collection->list[ collection->length ] = node;
        collection->length++;
    }
}

void modest_finder_callback_found_with_bool(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx)
{
    bool *is = (bool*)ctx;
    
    if(*is == false)
        *is = true;
}

void modest_finder_specificity_inc(mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    switch (selector->type) {
        case MyCSS_SELECTORS_TYPE_ID:
            spec->a++;
            break;
            
        case MyCSS_SELECTORS_TYPE_CLASS:
        case MyCSS_SELECTORS_TYPE_ATTRIBUTE:
        case MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION:
        case MyCSS_SELECTORS_TYPE_PSEUDO_CLASS:
            spec->b++;
            break;
            
        case MyCSS_SELECTORS_TYPE_ELEMENT:
        case MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT_FUNCTION:
        case MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT:
            spec->c++;
            break;
        default:
            break;
    }
}

modest_finder_t * modest_finder_by_stylesheet(mycss_stylesheet_t *stylesheet, myhtml_collection_t** collection, myhtml_tree_node_t* base_node)
{
    if(collection == NULL || base_node == NULL || stylesheet == NULL)
        return NULL;
    
    modest_finder_t *finder = modest_finder_create();
    
    if(finder == NULL)
        return NULL;
    
    mystatus_t status = modest_finder_init(finder);
    
    if(status != MODEST_STATUS_OK) {
        modest_finder_destroy(finder, true);
        return NULL;
    }
    
    if(*collection == NULL) {
        mystatus_t status;
        *collection = myhtml_collection_create(4096, &status);
        
        if(status) {
            modest_finder_destroy(finder, true);
            return NULL;
        }
    }
    else
        myhtml_collection_clean(*collection);
    
    mycss_selectors_list_t *selector_list = stylesheet->sel_list_first;
    
    while(selector_list) {
        for(size_t i = 0; i < selector_list->entries_list_length; i++) {
            mycss_selectors_specificity_t spec = selector_list->entries_list[i].specificity;
            
            modest_finder_node_combinator_begin(finder, base_node, selector_list, selector_list->entries_list[i].entry, &spec, modest_finder_callback_found_with_collection, *collection);
        }
        
        selector_list = selector_list->next;
    }
    
    return finder;
}

mystatus_t modest_finder_by_selectors_list(modest_finder_t* finder, myhtml_tree_node_t* scope_node,
                                                mycss_selectors_list_t* selector_list, myhtml_collection_t** collection)
{
    if(finder == NULL || selector_list == NULL || scope_node == NULL || collection == NULL)
        return MODEST_STATUS_ERROR;
    
    if(*collection == NULL) {
        mystatus_t status;
        *collection = myhtml_collection_create(4096, &status);
        
        if(status)
            return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    }

    for(size_t i = 0; i < selector_list->entries_list_length; i++) {
        mycss_selectors_specificity_t spec = selector_list->entries_list[i].specificity;
        
        modest_finder_node_combinator_begin(finder, scope_node, selector_list, selector_list->entries_list[i].entry, &spec,
                                            modest_finder_callback_found_with_collection, *collection);
    }
    
    return MODEST_STATUS_OK;
}

myhtml_tree_node_t * modest_finder_node_combinator_begin(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                         mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                         mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    
    myhtml_tree_node_t *node = base_node;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector, spec))
        {
            if(selector->next == NULL) {
                if(callback_found)
                    callback_found(finder, node, selector_list, selector, spec, ctx);
            }
            else {
                myhtml_tree_node_t *find_node = modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector_list, selector->next, spec, callback_found, ctx);

                if(find_node == NULL) {
                    while(node != base_node && node->next == NULL)
                        node = node->parent;
                    
                    if(node == base_node)
                        break;
                    
                    node = node->next;
                    continue;
                }
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != base_node && node->next == NULL)
                node = node->parent;
            
            if(node == base_node)
                break;
            
            node = node->next;
        }
    }

    return NULL;
}

/* some */
myhtml_tree_node_t * modest_finder_node_combinator_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                         mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                         mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    mycss_selectors_specificity_t match_spec = *spec;
    
    if(base_node->tag_id != MyHTML_TAG__TEXT && base_node->tag_id != MyHTML_TAG__COMMENT &&
       modest_finder_static_selector_type_map[selector->type](finder, base_node, selector, &match_spec)) {
        if(selector->next == NULL) {
            if(callback_found)
                callback_found(finder, base_node, selector_list, selector, &match_spec, ctx);
        }
        else {
            modest_finder_static_selector_combinator_map[selector->next->combinator](finder, base_node, selector_list, selector->next, &match_spec, callback_found, ctx);
        }
    }
    
    return base_node;
}

/* E F or E >> F */
myhtml_tree_node_t * modest_finder_node_combinator_descendant(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                              mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                              mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        mycss_selectors_specificity_t match_spec = *spec;
        
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector, &match_spec))
        {
            if(selector->next == NULL) {
                if(callback_found)
                    callback_found(finder, node, selector_list, selector, &match_spec, ctx);
            }
            else {
                myhtml_tree_node_t *find_node = modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector_list, selector->next, &match_spec, callback_found, ctx);
                
                if(find_node == NULL) {
                    while(node != base_node && node->next == NULL)
                        node = node->parent;
                    
                    if(node == base_node)
                        break;
                    
                    node = node->next;
                    continue;
                }
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != base_node && node->next == NULL)
                node = node->parent;
            
            if(node == base_node)
                break;
            
            node = node->next;
        }
    }
    
    return NULL;
}

/* E > F */
myhtml_tree_node_t * modest_finder_node_combinator_child(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                         mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                         mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        mycss_selectors_specificity_t match_spec = *spec;
        
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector, &match_spec))
        {
            if(selector->next == NULL) {
                if(callback_found)
                    callback_found(finder, node, selector_list ,selector, &match_spec, ctx);
            }
            else {
                modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector_list, selector->next, &match_spec, callback_found, ctx);
            }
        }
        
        node = node->next;
    }
    
    return base_node;
}

/* E + F */
myhtml_tree_node_t * modest_finder_node_combinator_next_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                                mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                                mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
        {
            mycss_selectors_specificity_t match_spec = *spec;
            
            if(modest_finder_static_selector_type_map[selector->type](finder, node, selector, &match_spec)) {
                if(selector->next == NULL) {
                    if(callback_found)
                        callback_found(finder, node, selector_list, selector, &match_spec, ctx);
                }
                else {
                    modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector_list, selector->next, &match_spec, callback_found, ctx);
                }
            }
            
            break;
        }
        
        node = node->next;
    }
    
    return base_node;
}

/* E ~ F */
myhtml_tree_node_t * modest_finder_node_combinator_following_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                                     mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                                     mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        mycss_selectors_specificity_t match_spec = *spec;
        
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector, &match_spec))
        {
            if(selector->next == NULL) {
                if(callback_found)
                    callback_found(finder, node, selector_list, selector, &match_spec, ctx);
            }
            else {
                modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector_list, selector->next, &match_spec, callback_found, ctx);
            }
        }
        
        node = node->next;
    }
    
    return base_node;
}

/* E || F */
myhtml_tree_node_t * modest_finder_node_combinator_column(modest_finder_t* finder, myhtml_tree_node_t* base_node,
                                                          mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector,
                                                          mycss_selectors_specificity_t* spec, modest_finder_callback_f callback_found, void* ctx)
{
    if(selector == NULL)
        return NULL;
    
    return base_node;
}


