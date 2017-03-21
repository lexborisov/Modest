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

#ifndef MODEST_NODE_NODE_H
#define MODEST_NODE_NODE_H
#pragma once

#include <modest/myosi.h>
#include <modest/modest.h>
#include <modest/style/raw.h>
#include <modest/render/tree_node.h>
#include <mycore/utils/avl_tree.h>

#ifdef __cplusplus
extern "C" {
#endif

struct modest_node {
    modest_style_sheet_t* stylesheet;
#ifndef MODEST_NODE_FULL_RAW
    mycore_utils_avl_tree_node_t *avl_tree_node;
#else
    modest_style_raw_declaration_t * raw_declaration[MyCSS_PROPERTY_TYPE_LAST_ENTRY];
#endif /* MODEST_NODE_FULL_RAW */
    
    modest_render_tree_node_t* render_node;
};

modest_node_t * modest_node_create(modest_t* modest);
mystatus_t modest_node_init(modest_t* modest, modest_node_t *mnode);

mycss_declaration_entry_t * modest_node_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type);

modest_style_raw_declaration_t * modest_node_raw_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type);
void modest_node_raw_declaration_set_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type, modest_style_raw_declaration_t *raw_declr);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_NODE_NODE_H */
