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

#ifndef MyHTML_MyCSS_SELECTORS_PSEUDO_H
#define MyHTML_MyCSS_SELECTORS_PSEUDO_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/selectors/myosi.h"

struct mycss_selectots_pseudo_begin_entry {
    const char* name;
    size_t length;
    
    int sub_type;
    
    size_t next;
    size_t curr;
}
typedef mycss_selectots_pseudo_begin_entry_t;


mycss_selectors_sub_type_pseudo_class_t mycss_pseudo_class_by_name(const char *name, size_t length);
mycss_selectors_sub_type_pseudo_element_t mycss_pseudo_element_by_name(const char *name, size_t length);
const mycss_selectots_pseudo_begin_entry_t * mycss_pseudo_begin_entry_by_name(const char* name, size_t length, size_t static_size, const mycss_selectots_pseudo_begin_entry_t* pseudo);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_PSEUDO_H */
