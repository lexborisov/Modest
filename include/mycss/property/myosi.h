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

#ifndef MyHTML_MyCSS_PROPERTY_MYOSI_H
#define MyHTML_MyCSS_PROPERTY_MYOSI_H
#pragma once

#include <mycss/myosi.h>
#include <mycss/property/const.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mycss_property_index_static_entry {
    const char* name;
    size_t name_length;
    
    mycss_property_type_t type;
    mycss_parser_token_f parser;
    
    size_t next;
    size_t curr;
}
typedef mycss_property_index_static_entry_t;

struct mycss_property_value_index_static_entry {
    const char* name;
    size_t name_length;
    
    mycss_property_value_t type;
    
    size_t next;
    size_t curr;
}
typedef mycss_property_value_index_static_entry_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_MYOSI_H */
