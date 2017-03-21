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

#include "modest/layer/layer.h"

modest_layer_t * modest_layer_create(modest_layout_t* layout)
{
    void *layer = mcobject_malloc(layout->mc_nodes, NULL);
    
    if(layer) {
        memset(layer, 0, sizeof(modest_layer_t));
    }
    
    return layer;
}

void modest_layer_clean(modest_layer_t* layer)
{
    memset(layer, 0, sizeof(modest_layer_t));
}

modest_layer_t * modest_layer_destroy(modest_layout_t* layout, modest_layer_t* layer)
{
    mcobject_free(layout->mc_nodes, layer);
    return NULL;
}
