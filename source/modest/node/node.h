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

#ifndef MODEST_NODE_NODE_H
#define MODEST_NODE_NODE_H
#pragma once

#include "modest/myosi.h"
#include "modest/modest.h"
#include "modest/style/raw.h"
#include "modest/layer/layer.h"

#ifdef __cplusplus
extern "C" {
#endif

struct modest_node {
    modest_style_sheet_t* stylesheet;
    modest_style_raw_t* raw_style;
    modest_layer_t* layer;
};

modest_node_t * modest_node_create(modest_t* modest);
modest_status_t modest_node_init(modest_t* modest, modest_node_t *mnode);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_NODE_NODE_H */
