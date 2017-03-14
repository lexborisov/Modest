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

#include "modest/glue.h"

void modest_glue_callback_myhtml_insert_node(myhtml_tree_t* tree, myhtml_tree_node_t* node, void* ctx)
{
    if(node->tag_id == MyHTML_TAG__TEXT)
        return;
    
    modest_t *modest = (modest_t*)ctx;
    
    /* create modest node */
    modest_node_t *m_node = modest_node_create(modest);
    if(m_node == NULL)
        return;
    
    modest_node_init(modest, m_node);
    
    node->data = m_node;
}


