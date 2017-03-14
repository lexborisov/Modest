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

#ifndef MODEST_FINDER_TYPE_H
#define MODEST_FINDER_TYPE_H
#pragma once

#include <modest/finder/myosi.h>
#include <modest/finder/finder.h>
#include <modest/finder/pseudo_class.h>
#include <modest/finder/match.h>
#include <myhtml/tree.h>
#include <mycore/utils.h>
#include <mycss/selectors/value.h>

#ifdef __cplusplus
extern "C" {
#endif

bool modest_finder_selector_type_undef(modest_finder_t* finder, myhtml_tree_node_t* node,
                                       mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_element(modest_finder_t* finder, myhtml_tree_node_t* node,
                                         mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_id(modest_finder_t* finder, myhtml_tree_node_t* node,
                                    mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_class(modest_finder_t* finder, myhtml_tree_node_t* node,
                                       mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_attribute(modest_finder_t* finder, myhtml_tree_node_t* node,
                                           mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_pseudo_class_function(modest_finder_t* finder, myhtml_tree_node_t* node,
                                                       mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_pseudo_class(modest_finder_t* finder, myhtml_tree_node_t* node,
                                              mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_pseudo_element_function(modest_finder_t* finder, myhtml_tree_node_t* node,
                                                         mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);

bool modest_finder_selector_type_pseudo_element(modest_finder_t* finder, myhtml_tree_node_t* node,
                                                mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_TYPE_H */
