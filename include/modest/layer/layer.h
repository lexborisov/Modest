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

#ifndef MODEST_LAYER_LAYER_H
#define MODEST_LAYER_LAYER_H
#pragma once

#include <modest/myosi.h>
#include <mycore/utils/mcobject.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct modest_layer modest_layer_t;
typedef struct modest_layout modest_layout_t;

struct modest_layer {
    
    
    /* navigation */
    modest_layer_t* next;
    modest_layer_t* prev;
    modest_layer_t* child;
    modest_layer_t* parent;
};

struct modest_layout {
    mcobject_t* mc_nodes;
};

modest_layout_t * modest_layers_create(void);
mystatus_t modest_layers_init(modest_layout_t* layout);
void modest_layers_clean_all(modest_layout_t* layout);
modest_layout_t * modest_layers_destroy(modest_layout_t* layout, bool self_destroy);

modest_layer_t * modest_layer_create(modest_layout_t* layout);
void modest_layer_clean(modest_layer_t* layer);
modest_layer_t * modest_layer_destroy(modest_layout_t* layout, modest_layer_t* layer);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_LAYER_LAYER_H */
