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

#ifndef MODEST_STYLE_MAP_H
#define MODEST_STYLE_MAP_H
#pragma once

#include "modest/myosi.h"
#include "modest/modest.h"
#include "modest/finder/myosi.h"
#include "modest/finder/thread.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*modest_style_map_collate_f)(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);

void modest_style_map_collate_declaration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);

void modest_style_map_collate_declaration_undef(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_for_all(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_MAP_H */
