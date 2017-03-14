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

#include "modest/modest.h"
#include "modest/style/sheet.h"
#include "modest/style/raw.h"
#include "modest/node/node.h"

modest_t * modest_create(void)
{
    return (modest_t*)mycore_calloc(1, sizeof(modest_t));
}

mystatus_t modest_init(modest_t* modest)
{
    mystatus_t status;
    
    /* Modest nodes */
    modest->mnode_obj = mcobject_async_create();
    if(modest->mnode_obj == NULL)
        return MODEST_STATUS_ERROR_MNODE_CREATE;
    
    mcobject_async_status_t mcstatus = mcobject_async_init(modest->mnode_obj, 128, 1024, sizeof(modest_node_t));
    if(mcstatus)
        return MODEST_STATUS_ERROR_MNODE_INIT;
    
    /* base object node for all modest node objects */
    modest->mnode_node_id = mcobject_async_node_add(modest->mnode_obj, &mcstatus);
    if(mcstatus)
        return MODEST_STATUS_ERROR_MNODE_NODE_ADD;
    
    
    /* Modest stylesheet */
    modest->mstylesheet_obj = mcobject_async_create();
    if(modest->mstylesheet_obj == NULL)
        return MODEST_STATUS_ERROR_STYLESHEET_CREATE;
    
    mcstatus = mcobject_async_init(modest->mstylesheet_obj, 128, 1024, sizeof(modest_style_sheet_t));
    if(mcstatus)
        return MODEST_STATUS_ERROR_STYLESHEET_INIT;
    
    /* base object node for all modest stylesheet objects */
    modest->mstylesheet_node_id = mcobject_async_node_add(modest->mstylesheet_obj, &mcstatus);
    if(mcstatus)
        return MODEST_STATUS_ERROR_STYLESHEET_NODE_ADD;
    
    
    /* Modest style type */
    modest->mstyle_type_obj = mchar_async_create();
    if(modest->mstyle_type_obj == NULL)
        return MODEST_STATUS_ERROR_STYLE_TYPE_CREATE;
    
    if((status = mchar_async_init(modest->mstyle_type_obj, 12, (4096 * 5))))
        return status;
    
    modest->mstyle_type_node_id = mchar_async_node_add(modest->mstyle_type_obj, &status);
    if(status)
        return status;
    
    /* for raw declaration style */
    modest->mraw_style_declaration_obj = mcobject_create();
    if(modest->mraw_style_declaration_obj == NULL)
        return MODEST_STATUS_ERROR_STYLE_DECLARATION_CREATE;
    
    mystatus_t myhtml_status = mcobject_init(modest->mraw_style_declaration_obj, 256, sizeof(modest_style_raw_declaration_t));
    if(myhtml_status)
        return MODEST_STATUS_ERROR_STYLE_DECLARATION_INIT;
    
    
    /* styles tree */
    modest->style_avl_tree = mycore_utils_avl_tree_create();
    if(modest->style_avl_tree == NULL)
        return MODEST_STATUS_ERROR_AVL_TREE_CREATE;
    
    myhtml_status = mycore_utils_avl_tree_init(modest->style_avl_tree);
    if(myhtml_status)
        return MODEST_STATUS_ERROR_AVL_TREE_INIT;
    
    return MODEST_STATUS_OK;
}

void modest_clean(modest_t* modest)
{
    mcobject_async_clean(modest->mnode_obj);
    mcobject_async_clean(modest->mstylesheet_obj);
    mycore_utils_avl_tree_clean(modest->style_avl_tree);
}

modest_t * modest_destroy(modest_t* modest, bool self_destroy)
{
    if(modest == NULL)
        return NULL;
    
    modest->mnode_obj = mcobject_async_destroy(modest->mnode_obj, true);
    modest->mstylesheet_obj = mcobject_async_destroy(modest->mstylesheet_obj, true);
    modest->style_avl_tree = mycore_utils_avl_tree_destroy(modest->style_avl_tree, true);
    
    if(self_destroy) {
        mycore_free(modest);
        return NULL;
    }
    
    return modest;
}


