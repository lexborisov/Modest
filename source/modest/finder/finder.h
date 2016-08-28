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

#ifndef MODEST_FINDER_FINDER_H
#define MODEST_FINDER_FINDER_H
#pragma once

#include "modest/finder/myosi.h"
#include "modest/finder/type.h"
#include "mycss/selectors/myosi.h"
#include "mycss/selectors/list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*modest_finder_selector_type_f)(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector);
typedef myhtml_tree_node_t * (*modest_finder_selector_combinator_f)(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector);

/* init */
modest_finder_t * modest_finder_create(void);
modest_status_t modest_finder_init(modest_finder_t* finder, myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet);
void modest_finder_clean(modest_finder_t* finder);
modest_finder_t * modest_finder_destroy(modest_finder_t* finder, bool self_destroy);

/* simple api */
modest_finder_t * modest_finder_create_simple(myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet);

/* callbacks */
void modest_finder_callback_found_with_collection(modest_finder_t* finder, myhtml_tree_node_t* node, void* ctx);
void modest_finder_callback_found_with_bool(modest_finder_t* finder, myhtml_tree_node_t* node, void* ctx);

/* base api */
void modest_finder_begin(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
modest_finder_t * modest_finder_by_stylesheet(myhtml_tree_t* myhtml_tree, mycss_stylesheet_t *stylesheet, myhtml_collection_t** collection, myhtml_tree_node_t* base_node, mycss_selectors_list_t* selector_list);
myhtml_collection_t * modest_finder_by_selectors_list(modest_finder_t* finder, mycss_selectors_list_t *sel_list, myhtml_tree_node_t* base_node, myhtml_collection_t* collection);

/* process */
myhtml_tree_node_t * modest_finder_node_combinator_begin(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_descendant(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_next_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_following_sibling(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);
myhtml_tree_node_t * modest_finder_node_combinator_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_FINDER_H */
