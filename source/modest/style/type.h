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

#ifndef MODEST_STYLE_TYPE_H
#define MODEST_STYLE_TYPE_H
#pragma once

#include "modest/myosi.h"
#include "modest/modest.h"
#include "mycss/declaration/myosi.h"
#include "mycore/utils/mchar_async.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct modest_style_type_length modest_style_type_length_t;
typedef struct modest_style_type_display modest_style_type_display_t;

struct modest_style_type_length {
    float value;
};

struct modest_style_type_display {
    mycss_property_display_t value;
};


void * modest_style_type_create(modest_t* modest, size_t size);
mystatus_t modest_style_type_init(modest_t* modest, void *data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_TYPE_H */
