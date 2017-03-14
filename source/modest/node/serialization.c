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

#include "modest/node/serialization.h"

void modest_node_raw_serialization_declaration(mycss_entry_t* mycss_entry, mycss_declaration_entry_t* decl, mycss_property_type_t property_type, mycore_callback_serialize_f callback, void* context, bool* is_use)
{
    if(decl == NULL)
        return;
    
    if(is_use && *is_use)
        callback(" ", 1, context);
    
    mycss_declaration_serialization_entry_by_type(mycss_entry, decl, property_type, callback, context);
    callback(";", 1, context);
    
    if(is_use && *is_use == false) {
        *is_use = true;
    }
}

//bool modest_node_raw_serialization(mycss_entry_t* mycss_entry, modest_node_t* mnode, mycore_callback_serialize_f callback, void* context)
//{
//    bool is_use = false;
//    
//    for(size_t i = 0; i < MyCSS_PROPERTY_TYPE_LAST_ENTRY; i++) {
//        if(mnode->raw_declaration[i])
//            modest_node_raw_serialization_declaration(mycss_entry, mnode->raw_declaration[i]->declaration, i, callback, context, &is_use);
//    }
//    
//    return is_use;
//}

void modest_node_raw_serialization_callback(mycore_utils_avl_tree_node_t* node, void* context)
{
    modest_node_serialization_context_t *ctx = context;
    
    modest_style_raw_declaration_t *raw_declr = node->value;
    modest_node_raw_serialization_declaration(ctx->modest->mycss_entry, raw_declr->declaration, (mycss_property_type_t)node->type, ctx->callback, ctx->context, &ctx->is_use);
}

bool modest_node_raw_serialization(modest_t* modest, modest_node_t* mnode, mycore_callback_serialize_f callback, void* context)
{
    modest_node_serialization_context_t ctx = {modest, callback, context, 0};
    
    mycore_utils_avl_tree_list_all_nodes(modest->style_avl_tree, mnode->avl_tree_node, modest_node_raw_serialization_callback, &ctx);
    
    return ctx.is_use;
}
