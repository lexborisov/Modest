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

#include "modest/render/tree.h"

modest_render_tree_t * modest_render_tree_create(void)
{
    return mycore_calloc(1, sizeof(modest_render_tree_t));
}

mystatus_t modest_render_tree_init(modest_render_tree_t* render_tree)
{
    render_tree->mc_nodes = mcobject_create();
    if(render_tree->mc_nodes == NULL)
        return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    
    mystatus_t myhtml_status = mcobject_init(render_tree->mc_nodes, 1024, sizeof(modest_render_tree_node_t));
    if(myhtml_status)
        return MODEST_STATUS_ERROR;
    
    return MODEST_STATUS_OK;
}

void modest_render_tree_clean_all(modest_render_tree_t* render_tree)
{
    memset(render_tree, 0, sizeof(modest_render_tree_t));
}

modest_render_tree_t * modest_render_tree_destroy(modest_render_tree_t* render_tree, bool self_destroy)
{
    if(render_tree == NULL)
        return NULL;
    
    render_tree->mc_nodes = mcobject_destroy(render_tree->mc_nodes, true);
    
    if(self_destroy) {
        mycore_free(render_tree);
        return NULL;
    }
    
    return render_tree;
}

void modest_render_tree_serialization(myhtml_tree_t* html_tree, modest_render_tree_t* tree,
                                      modest_render_tree_node_t* scope_node, mycore_callback_serialize_f callback, void* context)
{
    modest_render_tree_node_t* node = scope_node;
    size_t depth = 0;
    
    while(node) {
        for(size_t i = 0; i < depth; i++)
            callback("\t", 1, context);
        
        modest_render_tree_node_serialization(html_tree, node, callback, context);
        callback("\n", 1, context);
        
        if(node->child) {
            depth++;
            node = node->child;
        }
        else {
            while(node != scope_node && node->next == NULL) {
                depth--;
                node = node->parent;
            }
            
            if(node == scope_node)
                break;
            
            node = node->next;
        }
    }
    
    
}


