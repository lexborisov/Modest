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

#include "modest/modest.h"

modest_t * modest_create(void)
{
    return (modest_t*)myhtml_calloc(1, sizeof(modest_t));
}

modest_status_t modest_init(modest_t* modest)
{
    /* Modest nodes */
    modest->mnode_obj = mcobject_async_create();
    if(modest->mnode_obj == NULL)
        return MODEST_STATUS_OK;
    
    mcobject_async_status_t mcstatus = mcobject_async_init(modest->mnode_obj, 128, 1024, sizeof(modest_node_t));
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    /* base object node for all modest node objects */
    modest->mnode_node_id = mcobject_async_node_add(modest->mnode_obj, &mcstatus);
    
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    
    /* Modest stylesheet */
    modest->mstylesheet_obj = mcobject_async_create();
    if(modest->mstylesheet_obj == NULL)
        return MODEST_STATUS_OK;
    
    mcstatus = mcobject_async_init(modest->mstylesheet_obj, 128, 1024, sizeof(modest_style_sheet_t));
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    /* base object node for all modest stylesheet objects */
    modest->mstylesheet_node_id = mcobject_async_node_add(modest->mstylesheet_obj, &mcstatus);
    
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    return MODEST_STATUS_OK;
}

void modest_clean(modest_t* modest)
{
    mcobject_async_clean(modest->mnode_obj);
    mcobject_async_clean(modest->mstylesheet_obj);
}

modest_t * modest_destroy(modest_t* modest, bool self_destroy)
{
    if(modest == NULL)
        return NULL;
    
    modest->mnode_obj = mcobject_async_destroy(modest->mnode_obj, true);
    modest->mstylesheet_obj = mcobject_async_destroy(modest->mstylesheet_obj, true);
    
    if(self_destroy) {
        myhtml_free(modest);
        return NULL;
    }
    
    return modest;
}


