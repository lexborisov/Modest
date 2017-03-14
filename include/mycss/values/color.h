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

#ifndef MyCSS_VALUES_COLOR_H
#define MyCSS_VALUES_COLOR_H
#pragma once

#include <mycss/myosi.h>
#include <mycss/values/values.h>
#include <mycss/values/color_const.h>
#include <mycss/values/color_parser.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mycss_values_color_index_static_entry {
    char* name;
    size_t name_length;
    mycss_values_color_id_t type;
    /*
      8bit = r  , 8bit = g  , 8bit = b
...| (|||| ||||) (|||| ||||) (|||| ||||) [0]
     */
    unsigned long rgb;
    size_t next;
    size_t curr;
}
typedef mycss_values_color_index_static_entry_t;

struct mycss_values_color_function_index_static_entry {
    char* name;
    size_t name_length;
    mycss_values_color_function_id_t type;
    mycss_parser_token_f parser;
    size_t next;
    size_t curr;
}
typedef mycss_values_color_function_index_static_entry_t;

const mycss_values_color_index_static_entry_t * mycss_values_color_index_entry_by_name(const char* name, size_t length);
mycss_values_color_id_t mycss_values_color_id_by_name(const char *name, size_t length);
const char * mycss_values_color_name_by_id(mycss_values_color_id_t color_id, size_t *length);

const mycss_values_color_function_index_static_entry_t * mycss_values_color_function_index_entry_by_name(const char* name, size_t length);
mycss_values_color_function_id_t mycss_values_color_function_id_by_name(const char *name, size_t length);
const char * mycss_values_color_function_name_by_id(mycss_values_color_function_id_t color_function_id, size_t *length);
    
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_VALUES_COLOR_H */


