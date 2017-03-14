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

#ifndef MODEST_H
#define MODEST_H
#pragma once

#include "modest/myosi.h"
#include "modest/layer/layer.h"
#include "mycore/utils/mcobject.h"
#include "mycore/utils/mcobject_async.h"
#include "mycore/utils/mchar_async.h"
#include "mycore/utils/avl_tree.h"

#ifdef __cplusplus
extern "C" {
#endif

struct modest {
    mcobject_async_t* mnode_obj;
    size_t mnode_node_id;
    
    mcobject_async_t* mstylesheet_obj;
    size_t mstylesheet_node_id;
    
    mchar_async_t* mstyle_type_obj;
    size_t mstyle_type_node_id;
    
    mcobject_t* mraw_style_declaration_obj;
    
    modest_layout_t* layout;
    
    mycore_utils_avl_tree_t* style_avl_tree;
    
    /* refs */
    myhtml_tree_t* myhtml_tree;
    mycss_entry_t* mycss_entry;
};


modest_t * modest_create(void);
mystatus_t modest_init(modest_t* modest);
void modest_clean(modest_t* modest);
modest_t * modest_destroy(modest_t* modest, bool self_destroy);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_H */
