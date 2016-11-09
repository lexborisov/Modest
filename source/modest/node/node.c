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

modest_status_t modest_node_init(modest_t* modest, modest_node_t *mnode)
{
    mnode->stylesheet = modest_style_sheet_create(modest);
    if(mnode->stylesheet == NULL)
        return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    
    modest_status_t status = modest_style_sheet_init(modest, mnode->stylesheet);
    if(status)
        return MODEST_STATUS_ERROR;
    
    mnode->raw_style = modest_style_raw_create(modest);
    if(mnode->raw_style == NULL)
        return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    
    status = modest_style_raw_init(modest, mnode->raw_style);
    if(status)
        return MODEST_STATUS_ERROR;
    
    return MODEST_STATUS_OK;
}


