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

#ifndef MyHTML_MyCSS_PROPERTY_INIT_H
#define MyHTML_MyCSS_PROPERTY_INIT_H
#pragma once

#include "mycss/property/myosi.h"
#include "mycss/property/parser.h"
#include "mycss/values/serialization.h"
#include "mycore/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

const mycss_property_index_static_entry_t * mycss_property_index_entry_by_name(const char* name, size_t length);
mycss_property_type_t mycss_property_type_by_name(const char *name, size_t length);

const mycss_property_value_index_static_entry_t * mycss_property_value_index_entry_by_name(const char* name, size_t length);
mycss_property_value_t mycss_property_value_type_by_name(const char *name, size_t length);

void mycss_property_print(mycss_property_type_t prop_type, FILE* fh);
void mycss_property_value_print(unsigned int value_type, void* value, FILE* fh);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_INIT_H */
