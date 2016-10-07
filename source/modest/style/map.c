/*
 Copyright (C) 2016 Alexander Borisov
 
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

#include "modest/style/map.h"
#include "modest/style/map_resource.h"

void modest_style_map_collate_declaration(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec)
{
    if(thr_dec->entry == NULL || thr_dec->entry->type >= MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        return;
    
    modest_style_map_static_collate_declaration[ thr_dec->entry->type ](node, thr_dec);
}

void modest_style_map_collate_declaration_undef(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec)
{
    
}

void modest_style_map_collate_declaration_height(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec)
{
//    modest_node_t *m_node = (modest_node_t*)node->data;
//    
//    if(modest_finder_thread_spec_is_up(&thr_dec->raw_spec, &m_node->stylesheet->height.raw.spec)) {
//        m_node->stylesheet->height.raw.declaration = thr_dec->entry;
//        m_node->stylesheet->height.raw.spec = thr_dec->raw_spec;
//    }
}

void modest_style_map_collate_declaration_width(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec)
{
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(modest_finder_thread_spec_is_up(&thr_dec->raw_spec, &m_node->stylesheet->width.raw.spec)) {
        m_node->stylesheet->width.raw.declaration = thr_dec->entry;
        m_node->stylesheet->width.raw.spec = thr_dec->raw_spec;
    }
}


