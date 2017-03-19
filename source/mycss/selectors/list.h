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

#ifndef MyHTML_MyCSS_SELECTORS_LIST_H
#define MyHTML_MyCSS_SELECTORS_LIST_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/selectors/myosi.h"
#include "mycss/declaration/myosi.h"

struct mycss_selectors_entries_list {
    mycss_selectors_entry_t* entry;
    mycss_selectors_specificity_t specificity;
};

struct mycss_selectors_list {
    mycss_selectors_entries_list_t* entries_list;
    size_t entries_list_length;
    
    mycss_declaration_entry_t* declaration_entry;
    
    mycss_selectors_flags_t flags;
    
    mycss_selectors_list_t* parent;
    mycss_selectors_list_t* next;
    mycss_selectors_list_t* prev;
};

mycss_selectors_list_t * mycss_selectors_list_create(mycss_selectors_t* selectors);
void mycss_selectors_list_clean(mycss_selectors_list_t* selector_list);
mycss_selectors_list_t * mycss_selectors_list_destroy(mycss_selectors_t* selectors, mycss_selectors_list_t* selector_list, bool self_destroy);

mycss_selectors_list_t * mycss_selectors_list_append_selector(mycss_selectors_t* selectors, mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector);
mycss_selectors_entry_t * mycss_selectors_list_last_entry(mycss_selectors_list_t* list);
mycss_selectors_entry_t ** mycss_selectors_list_current_chain(mycss_selectors_list_t* list);

void mycss_selectors_list_append_to_current(mycss_selectors_t* selectors, mycss_selectors_list_t* current_list);

bool mycss_selectors_list_destroy_last_empty_selector(mycss_selectors_t* selectors, mycss_selectors_list_t* list, bool destroy_found);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_LIST_H */
