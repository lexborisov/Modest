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

#ifndef MODEST_RENDER_TREE_NODE_H
#define MODEST_RENDER_TREE_NODE_H
#pragma once

typedef struct modest_render_tree_node modest_render_tree_node_t;

#include "modest/modest.h"
#include "modest/render/tree.h"

#include "myhtml/tree.h"
#include "mycore/utils/mcobject.h"

#ifdef __cplusplus
extern "C" {
#endif

enum modest_render_tree_node_type {
    MODEST_RENDER_TREE_NODE_TYPE_BLOCK     = 0,
    MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT  = 1,
    MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS = 3
}
typedef modest_render_tree_node_type_t;

struct modest_render_tree_node {
    myhtml_tree_node_t* html_node;
    modest_render_tree_node_type_t type;
    
    /* navigation */
    modest_render_tree_node_t* next;
    modest_render_tree_node_t* prev;
    modest_render_tree_node_t* child;
    modest_render_tree_node_t* child_last;
    modest_render_tree_node_t* parent;
};

modest_render_tree_node_t * modest_render_tree_node_create_and_init(modest_render_tree_t* render_tree);
void modest_render_tree_node_clean_all(modest_render_tree_node_t* render_node);
modest_render_tree_node_t * modest_render_tree_node_destroy(modest_render_tree_t* render_tree, modest_render_tree_node_t* render_node, bool self_destroy);

void modest_render_tree_node_append(modest_render_tree_node_t* to, modest_render_tree_node_t* node);
void modest_render_tree_node_remove(modest_render_tree_node_t* node);
void modest_render_tree_node_append_after(modest_render_tree_node_t* target, modest_render_tree_node_t* node);
void modest_render_tree_node_append_before(modest_render_tree_node_t* target, modest_render_tree_node_t* node);

void modest_render_tree_node_serialization(myhtml_tree_t* html_tree, modest_render_tree_node_t* node, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_RENDER_TREE_NODE_H */
