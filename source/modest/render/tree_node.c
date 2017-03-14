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

#include "modest/render/tree_node.h"

modest_render_tree_node_t * modest_render_tree_node_create_and_init(modest_render_tree_t* render_tree)
{
    void *render_node = mcobject_malloc(render_tree->mc_nodes, NULL);
    
    if(render_node) {
        memset(render_node, 0, sizeof(modest_render_tree_node_t));
    }
    
    return render_node;
}

void modest_render_tree_node_clean_all(modest_render_tree_node_t* render_node)
{
    memset(render_node, 0, sizeof(modest_render_tree_node_t));
}

modest_render_tree_node_t * modest_render_tree_node_destroy(modest_render_tree_t* render_tree, modest_render_tree_node_t* render_node, bool self_destroy)
{
    if(render_node == NULL)
        return NULL;
    
    if(self_destroy) {
        mcobject_free(render_tree->mc_nodes, render_node);
        return NULL;
    }
    
    return render_node;
}

void modest_render_tree_node_append(modest_render_tree_node_t* to, modest_render_tree_node_t* node)
{
    if(to->child_last) {
        to->child_last->next = node;
        node->prev = to->child_last;
    }
    else {
        to->child = node;
        node->prev = NULL;
    }
    
    node->parent = to;
    node->next = NULL;
    
    to->child_last = node;
}

void modest_render_tree_node_remove(modest_render_tree_node_t* node)
{
    if(node->parent) {
        if(node->next == NULL)
            node->parent->child_last = node->prev;
        else
            node->next->prev = node->prev;
        
        if(node->prev == NULL)
            node->parent->child = node->next;
        else
            node->prev->next = node->next;
    }
    else {
        if(node->next)
            node->next->prev = node->prev;
        
        if(node->prev)
            node->prev->next = node->next;
    }
}

void modest_render_tree_node_append_after(modest_render_tree_node_t* target, modest_render_tree_node_t* node)
{
    if(target->next) {
        target->next->prev = node;
    }
    else {
        if(target->parent)
            target->parent->child_last = node;
    }
    
    node->next = target->next;
    node->prev = target;
    node->parent = target->parent;
    
    target->next = node;
}

void modest_render_tree_node_append_before(modest_render_tree_node_t* target, modest_render_tree_node_t* node)
{
    if(target->prev) {
        target->prev->next = node;
    }
    else {
        if(target->parent)
            target->parent->child = node;
    }
    
    node->next = target;
    node->prev = target->prev;
    node->parent = target->parent;
    
    target->prev = node;
}

void modest_render_tree_node_serialization(myhtml_tree_t* html_tree, modest_render_tree_node_t* node, mycore_callback_serialize_f callback, void* context)
{
    callback("<", 1, context);
    
    switch (node->type) {
        case MODEST_RENDER_TREE_NODE_TYPE_BLOCK:
            callback("block", 5, context);
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT:
            callback("viewport", 8, context);
            break;
            
        case MODEST_RENDER_TREE_NODE_TYPE_ANONYMOUS:
            callback("anonymous", 9, context);
            break;
            
        default:
            break;
    }
    
    if(node->html_node) {
        size_t tag_length = 0;
        const char *tag_name = myhtml_tag_name_by_id(html_tree, node->html_node->tag_id, &tag_length);
        
        callback(" ", 1, context);
        callback(tag_name, tag_length, context);
    }
    
    callback(">", 1, context);
}


