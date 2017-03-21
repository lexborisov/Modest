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

#ifndef MyCSS_VALUES_IMAGE_H
#define MyCSS_VALUES_IMAGE_H
#pragma once

#include "mycss/myosi.h"
#include "mycss/values/values.h"
#include "mycss/property/parser.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void * (*mycss_values_image_obejct_f)(mycss_entry_t* entry, mycss_values_image_t* image);

struct mycss_values_image_function_index_static_entry {
    char* name;
    size_t name_length;
    mycss_property_value_t type;
    mycss_parser_token_f parser;
    mycss_values_image_obejct_f obj_creator;
    size_t next;
    size_t curr;
}
typedef mycss_values_image_function_index_static_entry_t;

const mycss_values_image_function_index_static_entry_t * mycss_values_image_index_entry_by_name(const char* name, size_t length);
mycss_property_value_t mycss_values_image_id_by_name(const char *name, size_t length);

void * mycss_values_image_creator_url(mycss_entry_t* entry, mycss_values_image_t* image);
void * mycss_values_image_creator_function_image(mycss_entry_t* entry, mycss_values_image_t* image);
void * mycss_values_image_creator_image_set(mycss_entry_t* entry, mycss_values_image_t* image);
void * mycss_values_image_creator_element(mycss_entry_t* entry, mycss_values_image_t* image);
void * mycss_values_image_creator_cross_fade(mycss_entry_t* entry, mycss_values_image_t* image);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_VALUES_IMAGE_H */
