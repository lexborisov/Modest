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

#include "modest/node/node.h"
#include "modest/style/sheet.h"

modest_node_t * modest_node_create(modest_t* modest)
{
    modest_node_t* mnode = (modest_node_t*)mcobject_async_malloc(modest->mnode_obj, modest->mnode_node_id, NULL);
    
    if(mnode == NULL)
        return NULL;
    
    memset(mnode, 0, sizeof(modest_node_t));
    
    return mnode;
}

mystatus_t modest_node_init(modest_t* modest, modest_node_t *mnode)
{
    mnode->stylesheet = modest_style_sheet_create(modest);
    if(mnode->stylesheet == NULL)
        return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    
    mystatus_t status = modest_style_sheet_init(modest, mnode->stylesheet);
    if(status)
        return MODEST_STATUS_ERROR;
    
    return MODEST_STATUS_OK;
}

#ifdef MODEST_NODE_FULL_RAW

mycss_declaration_entry_t * modest_node_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type)
{
    if(mnode->raw_declaration[ type ])
        return mnode->raw_declaration[ type ]->declaration;
    
    return NULL;
}

modest_style_raw_declaration_t * modest_node_raw_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type)
{
    return mnode->raw_declaration[ type ];
}

void modest_node_raw_declaration_set_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type, modest_style_raw_declaration_t *raw_declr)
{
    mnode->raw_declaration[ type ] = raw_declr;
}

#else

mycss_declaration_entry_t * modest_node_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type)
{
    mycore_utils_avl_tree_node_t *find_node = mycore_utils_avl_tree_search_by_type(modest->style_avl_tree, mnode->avl_tree_node, type);
    
    if(find_node)
        return ((modest_style_raw_declaration_t*)find_node->value)->declaration;
    
    return NULL;
}

modest_style_raw_declaration_t * modest_node_raw_declaration_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type)
{
    mycore_utils_avl_tree_node_t *find_node = mycore_utils_avl_tree_search_by_type(modest->style_avl_tree, mnode->avl_tree_node, type);
    return (find_node ? find_node->value : NULL);
}

void modest_node_raw_declaration_set_by_type(modest_t* modest, modest_node_t *mnode, mycss_property_type_t type, modest_style_raw_declaration_t *raw_declr)
{
    mycore_utils_avl_tree_add(modest->style_avl_tree, &mnode->avl_tree_node, type, raw_declr);
}

#endif /* MODEST_NODE_FULL_RAW */


