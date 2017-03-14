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

#ifndef MODEST_RENDER_TREE_H
#define MODEST_RENDER_TREE_H
#pragma once

typedef struct modest_render_tree modest_render_tree_t;

#include "modest/modest.h"
#include "mycore/utils/mcobject.h"
#include "modest/render/tree_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct modest_render_tree {
    mcobject_t* mc_nodes;
};

modest_render_tree_t * modest_render_tree_create(void);
mystatus_t modest_render_tree_init(modest_render_tree_t* render_tree);
void modest_render_tree_clean_all(modest_render_tree_t* render_tree);
modest_render_tree_t * modest_render_tree_destroy(modest_render_tree_t* render_tree, bool self_destroy);

void modest_render_tree_serialization(myhtml_tree_t* html_tree, modest_render_tree_t* tree,
                                      modest_render_tree_node_t* scope_node, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_RENDER_TREE_H */
