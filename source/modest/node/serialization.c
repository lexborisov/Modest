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

void modest_node_raw_serialization_declaration(mycss_entry_t* mycss_entry, mycss_declaration_entry_t* decl, mycss_property_type_t property_type, mycss_callback_serialization_f callback, void* context, bool* is_use)
{
    if(decl) {
        if(is_use && *is_use) {
            callback(" ", 1, context);
        }
        
        mycss_declaration_serialization_entry_by_type(mycss_entry, decl, property_type, callback, context);
        callback(";", 1, context);
        
        if(is_use && *is_use == false) {
            *is_use = true;
        }
    }
}

bool modest_node_raw_serialization(mycss_entry_t* mycss_entry, modest_node_t* mnode, mycss_callback_serialization_f callback, void* context)
{
    bool is_use = false;
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, width), MyCSS_PROPERTY_TYPE_WIDTH, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, height), MyCSS_PROPERTY_TYPE_HEIGHT, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_top), MyCSS_PROPERTY_TYPE_PADDING_TOP, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_right), MyCSS_PROPERTY_TYPE_PADDING_RIGHT, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_bottom), MyCSS_PROPERTY_TYPE_PADDING_BOTTOM, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, padding_left), MyCSS_PROPERTY_TYPE_PADDING_LEFT, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_top), MyCSS_PROPERTY_TYPE_MARGIN_TOP, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_right), MyCSS_PROPERTY_TYPE_MARGIN_RIGHT, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_bottom), MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, margin_left), MyCSS_PROPERTY_TYPE_MARGIN_LEFT, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, display), MyCSS_PROPERTY_TYPE_DISPLAY, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_top_width), MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_right_width), MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_bottom_width), MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_left_width), MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_top_style), MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_right_style), MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_bottom_style), MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, border_left_style), MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, box_sizing), MyCSS_PROPERTY_TYPE_BOX_SIZING, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, vertical_align), MyCSS_PROPERTY_TYPE_VERTICAL_ALIGN, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, line_height), MyCSS_PROPERTY_TYPE_LINE_HEIGHT, callback, context, &is_use);
    
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, text_decoration_line), MyCSS_PROPERTY_TYPE_TEXT_DECORATION_LINE, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, text_decoration_style), MyCSS_PROPERTY_TYPE_TEXT_DECORATION_STYLE, callback, context, &is_use);
    modest_node_raw_serialization_declaration(mycss_entry, modest_node_raw_property(mnode, text_decoration_skip), MyCSS_PROPERTY_TYPE_TEXT_DECORATION_SKIP, callback, context, &is_use);
    
    return true;
}


