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

#ifndef MyHTML_MyCSS_SELECTORS_INIT_H
#define MyHTML_MyCSS_SELECTORS_INIT_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/entry.h>
#include <mycss/selectors/myosi.h>
#include <mycss/selectors/list.h>

mycss_selectors_t * mycss_selectors_create(void);
mystatus_t mycss_selectors_init(mycss_entry_t* entry, mycss_selectors_t* selectors);
void mycss_selectors_clean(mycss_selectors_t* selectors);
mystatus_t mycss_selectors_clean_all(mycss_selectors_t* selectors);
mycss_selectors_t * mycss_selectors_destroy(mycss_selectors_t* selectors, bool self_destroy);

void mycss_selectors_entry_clean(mycss_selectors_entry_t* sel_entry);
mycss_selectors_entry_t * mycss_selectors_entry_destroy(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, bool self_destroy);

void * mycss_selectors_entry_value_destroy(mycss_entry_t* entry, mycss_selectors_entry_t* selector_entry, bool destroy_self);

mycss_selectors_list_t * mycss_selectors_parse(mycss_selectors_t* selectors, myencoding_t encoding, const char* data, size_t data_size, mystatus_t* out_status);
mycss_selectors_list_t * mycss_selectors_parse_by_function(mycss_selectors_t* selectors, mycss_parser_token_f func, myencoding_t encoding, const char* data, size_t data_size, mystatus_t* out_status);

mycss_selectors_entry_t * mycss_selectors_entry_find_first(mycss_selectors_entry_t* selector);

mycss_selectors_entry_t * mycss_selectors_entry_create(mycss_selectors_t* selectors);
    
mycss_selectors_entries_list_t * mycss_selectors_entries_list_create(mycss_selectors_t* selectors);
mycss_selectors_entries_list_t * mycss_selectors_entries_list_add_one(mycss_selectors_t* selectors, mycss_selectors_entries_list_t* entries, size_t current_size);
mycss_selectors_entries_list_t * mycss_selectors_entries_list_destroy(mycss_selectors_t* selectors, mycss_selectors_entries_list_t* entries);

mycss_selectors_entry_t * mycss_selectors_entry(mycss_selectors_t* selectors);
void mycss_selectors_entry_append_to_current(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_INIT_H */
