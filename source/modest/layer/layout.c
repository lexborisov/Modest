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

#include "modest/layer/layer.h"

modest_layout_t * modest_layers_create(void)
{
    return myhtml_calloc(1, sizeof(modest_layout_t));
}

modest_status_t modest_layers_init(modest_layout_t* layout)
{
    layout->mc_nodes = mcobject_create();
    if(layout->mc_nodes == NULL)
        return MODEST_STATUS_ERROR_MEMORY_ALLOCATION;
    
    myhtml_status_t myhtml_status = mcobject_init(layout->mc_nodes, 1024, sizeof(modest_layer_t));
    if(myhtml_status)
        return MODEST_STATUS_ERROR;
    
    return MODEST_STATUS_OK;
}

void modest_layers_clean_all(modest_layout_t* layout)
{
    mcobject_clean(layout->mc_nodes);
}

modest_layout_t * modest_layers_destroy(modest_layout_t* layout, bool self_destroy)
{
    if(layout == NULL)
        return NULL;
    
    layout->mc_nodes = mcobject_destroy(layout->mc_nodes, true);
    
    if(self_destroy) {
        myhtml_free(layout);
        return NULL;
    }
    
    return layout;
}


