/*
 Copyright (C) 2016 Alexander Borisov
 
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
    return (modest_finder_t*)myhtml_calloc(1, sizeof(modest_finder_t));
}

modest_status_t modest_finder_init(modest_finder_t* finder, myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet)
{
    finder->tree = myhtml_tree;
    finder->stylesheet = stylesheet;
    
    return MODEST_STATUS_OK;
}

void modest_finder_clean(modest_finder_t* finder)
{
    finder->callback_found = NULL;
    finder->callback_found_ctx = NULL;
}

modest_finder_t * modest_finder_destroy(modest_finder_t* finder, bool self_destroy)
{
    if(finder == NULL)
        return NULL;
    
    if(self_destroy) {
        myhtml_free(finder);
        return NULL;
    }
    
    return finder;
}

modest_finder_t * modest_finder_create_simple(myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet)
{
    modest_finder_t *finder = modest_finder_create();
    
    if(finder == NULL)
        return NULL;
    
    if(modest_finder_init(finder, myhtml_tree, stylesheet) != MyHTML_STATUS_OK)
        return modest_finder_destroy(finder, true);
    
    return finder;
}

void modest_finder_callback_found_set(modest_finder_t* finder, modest_finder_callback_f callback, void* callback_ctx)
{
    finder->callback_found = callback;
    finder->callback_found_ctx = callback_ctx;
}

void modest_finder_callback_found_with_collection(modest_finder_t* finder, myhtml_tree_node_t* node, void* ctx)
{
    myhtml_collection_t* collection = (myhtml_collection_t*)finder->callback_found_ctx;
    
    if(myhtml_collection_check_size(collection, 1, 1024) == MyHTML_STATUS_OK) {
        collection->list[ collection->length ] = node;
        collection->length++;
    }
}

void modest_finder_callback_found_with_bool(modest_finder_t* finder, myhtml_tree_node_t* node, void* ctx)
{
    bool *is = (bool*)ctx;
    
    if(*is == false)
        *is = true;
}

modest_finder_t * modest_finder_by_stylesheet(myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet, myhtml_collection_t** collection, myhtml_tree_node_t* base_node, mycss_selectors_list_t* selector_list)
{
    if(collection == NULL)
        return NULL;
    
    modest_finder_t *finder = modest_finder_create();
    
    if(finder == NULL)
        return NULL;
    
    modest_status_t status = modest_finder_init(finder, myhtml_tree, stylesheet);
    
    if(status != MODEST_STATUS_OK) {
        modest_finder_destroy(finder, true);
        return NULL;
    }
    
    if(*collection == NULL) {
        myhtml_status_t status;
        *collection = myhtml_collection_create(4096, &status);
        
        if(status) {
            modest_finder_destroy(finder, true);
            return NULL;
        }
    }
    else
        myhtml_collection_clean(*collection);
    
    if(base_node == NULL) {
        if(myhtml_tree->node_html)
            base_node = myhtml_tree->node_html;
        else
            return finder;
    }
    
    if(selector_list == NULL) {
        if(stylesheet->sel_list_first)
            selector_list = stylesheet->sel_list_first;
        else
            return finder;
    }
    
    modest_finder_callback_found_set(finder, modest_finder_callback_found_with_collection, *collection);
    
    while(selector_list) {
        for(size_t i = 0; i < selector_list->selector_list_length; i++) {
            modest_finder_node_combinator_begin(finder, base_node, selector_list->selector_list[i]);
        }
        
        selector_list = selector_list->next;
    }
    
    return finder;
}

myhtml_collection_t * modest_finder_by_selectors_list(modest_finder_t* finder, mycss_selectors_list_t *sel_list, myhtml_tree_node_t* base_node, myhtml_collection_t* collection)
{
    if(finder == NULL || sel_list == NULL || base_node == NULL)
        return NULL;
    
    if(collection == NULL) {
        myhtml_status_t status;
        collection = myhtml_collection_create(4096, &status);
        
        if(status)
            return NULL;
    }
    
    modest_finder_callback_found_set(finder, modest_finder_callback_found_with_collection, collection);
    
    for(size_t i = 0; i < sel_list->selector_list_length; i++) {
        modest_finder_node_combinator_begin(finder, base_node, sel_list->selector_list[i]);
    }
    
    return collection;
}

void modest_finder_begin(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    modest_finder_node_combinator_begin(finder, base_node, selector);
}

myhtml_tree_node_t * modest_finder_node_combinator_begin(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector))
        {
            if(selector->next == NULL) {
                if(finder->callback_found)
                    finder->callback_found(finder, node, finder->callback_found_ctx);
            }
            else {
                myhtml_tree_node_t *find_node = modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector->next);
                
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
myhtml_tree_node_t * modest_finder_node_combinator_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id != MyHTML_TAG__TEXT && base_node->tag_id != MyHTML_TAG__COMMENT &&
       modest_finder_static_selector_type_map[selector->type](finder, base_node, selector)) {
        if(selector->next == NULL) {
            if(finder->callback_found)
                finder->callback_found(finder, base_node, finder->callback_found_ctx);
        }
        else {
            modest_finder_static_selector_combinator_map[selector->next->combinator](finder, base_node, selector->next);
        }
    }
    
    return base_node;
}

/* E F or E >> F */
myhtml_tree_node_t * modest_finder_node_combinator_descendant(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector))
        {
            if(selector->next == NULL) {
                if(finder->callback_found)
                    finder->callback_found(finder, node, finder->callback_found_ctx);
            }
            else {
                myhtml_tree_node_t *find_node = modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector->next);
                
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
myhtml_tree_node_t * modest_finder_node_combinator_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector))
        {
            if(selector->next == NULL) {
                if(finder->callback_found)
                    finder->callback_found(finder, node, finder->callback_found_ctx);
            }
            else {
                modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector->next);
            }
        }
        
        node = node->next;
    }
    
    return base_node;
}

/* E + F */
myhtml_tree_node_t * modest_finder_node_combinator_next_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->next;
    
    if(base_node->next) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector))
        {
            if(selector->next == NULL) {
                if(finder->callback_found)
                    finder->callback_found(finder, node, finder->callback_found_ctx);
            }
            else {
                modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector->next);
            }
        }
    }
    
    return base_node;
}

/* E ~ F */
myhtml_tree_node_t * modest_finder_node_combinator_following_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT &&
           modest_finder_static_selector_type_map[selector->type](finder, node, selector))
        {
            if(selector->next == NULL) {
                if(finder->callback_found)
                    finder->callback_found(finder, node, finder->callback_found_ctx);
            }
            else {
                modest_finder_static_selector_combinator_map[selector->next->combinator](finder, node, selector->next);
            }
        }
        
        node = node->next;
    }
    
    return base_node;
}

/* E || F */
myhtml_tree_node_t * modest_finder_node_combinator_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return base_node;
}


