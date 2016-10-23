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

#include "modest/node/serialization.h"

void modest_node_raw_serialization_declaration(mycss_entry_t* mycss_entry, mycss_declaration_entry_t* decl, mycss_callback_serialization_f callback, void* context, bool* is_use)
{
    if(decl) {
        if(is_use && *is_use) {
            callback(" ", 1, context);
        }
        
        mycss_declaration_serialization_entry(mycss_entry, decl, callback, context);
        callback(";", 1, context);
        
        if(is_use && *is_use == false) {
            *is_use = true;
        }
    }
}

bool modest_node_raw_serialization(mycss_entry_t* mycss_entry, modest_node_t* mnode, mycss_callback_serialization_f callback, void* context)
{
    bool is_use = false;
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, width), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, height), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_top), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_right), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_bottom), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_left), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_top), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_right), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_bottom), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_left), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, display), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_top_width), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_right_width), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_bottom_width), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_left_width), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_top_style), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_right_style), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_bottom_style), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_left_style), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, box_sizing), callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, vertical_align), callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, line_height), callback, context, &is_use);
    
    return true;
}


