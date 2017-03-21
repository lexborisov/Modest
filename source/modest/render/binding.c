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

#include "modest/render/binding.h"

modest_render_tree_node_t * modest_render_binding_create_viewport(modest_t* modest, modest_render_tree_t* render_tree)
{
    modest_render_tree_node_t* render_node = modest_render_tree_node_create_and_init(render_tree);
    render_node->type = MODEST_RENDER_TREE_NODE_TYPE_VIEWPORT;
    
    return render_node;
}

modest_render_tree_node_t * modest_render_binding(modest_t* modest, modest_render_tree_t* render_tree, myhtml_tree_t* html_tree)
{
    myhtml_tree_node_t* html_node = html_tree->node_html;
    myhtml_tree_node_t* html_scope = html_node;
    
    modest_render_tree_node_t *render_root = modest_render_binding_create_viewport(modest, render_tree);
    modest_render_tree_node_t *render_node = render_root;
    
    while(html_node) {
        render_node = modest_layer_binding_node(modest, render_tree, render_node, html_node);
        
        if(render_node == NULL && html_node->next) {
            modest_node_t *m_node = html_node->parent->data;
            render_node = m_node->render_node;
            
            html_node = html_node->next;
        }
        else if(render_node && html_node->child)
            html_node = html_node->child;
        else {
            while(html_node != html_scope && html_node->next == NULL) {
                html_node = html_node->parent;
            }
            
            if(html_node == html_scope)
                break;
            
            modest_node_t *m_node = html_node->parent->data;
            render_node = m_node->render_node;
            
            html_node = html_node->next;
        }
    }
    
    return render_root;
}

modest_render_tree_node_t * modest_layer_binding_node(modest_t* modest, modest_render_tree_t* render_tree,
                                                      modest_render_tree_node_t* render_root, myhtml_tree_node_t* html_node)
{
    if(html_node->data == NULL)
        return NULL;
    
    mycss_declaration_entry_t *display = modest_declaration_by_type(modest, html_node, MyCSS_PROPERTY_TYPE_DISPLAY);
    
    if(display->value_type == MyCSS_PROPERTY_DISPLAY_NONE)
        return NULL;
    
    modest_node_t *m_node = html_node->data;
    
    if(m_node->render_node == NULL) {
        m_node->render_node = modest_render_tree_node_create_and_init(render_tree);
    }
    
    modest_render_tree_node_t* render_node = m_node->render_node;
    modest_render_tree_node_append(render_root, render_node);
    
    render_node->html_node = html_node;
    
    return render_node;
}


