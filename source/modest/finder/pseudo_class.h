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

#ifndef MODEST_FINDER_PSEUDO_CLASS_H
#define MODEST_FINDER_PSEUDO_CLASS_H
#pragma once

#include "modest/finder/myosi.h"
#include "modest/finder/finder.h"

#ifdef __cplusplus
extern "C" {
#endif

bool modest_finder_selector_sub_type_pseudo_class_function_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_dir(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_has(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_lang(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_matches(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_not(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_nth_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_function_contains(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

/* classes */
bool modest_finder_selector_sub_type_pseudo_class_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_active(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_any_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_blank(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_checked(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_default(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_disabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_empty(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_enabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_first_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_first_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_focus(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_future(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_hover(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_in_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_indeterminate(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_invalid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_only_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_only_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_optional(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_out_of_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_past(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_placeholder_shown(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_read_only(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_read_write(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_required(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_root(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_scope(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_target(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_user_error(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_valid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);
bool modest_finder_selector_sub_type_pseudo_class_visited(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_PSEUDO_CLASS_H */
