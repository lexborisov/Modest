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

#ifndef MyHTML_MyCSS_NAMESPACE_INIT_H
#define MyHTML_MyCSS_NAMESPACE_INIT_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/namespace/myosi.h>
#include <mycss/entry.h>
#include <myhtml/mynamespace.h>

mycss_namespace_t * mycss_namespace_create(void);
mystatus_t mycss_namespace_init(mycss_entry_t* entry, mycss_namespace_t* ns);
void mycss_namespace_clean(mycss_namespace_t* ns);
mystatus_t mycss_namespace_clean_all(mycss_namespace_t* ns);
mycss_namespace_t * mycss_namespace_destroy(mycss_namespace_t* ns, bool self_destroy);

mystatus_t mycss_namespace_stylesheet_init(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry);
mystatus_t mycss_namespace_stylesheet_clean(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry);
mycss_namespace_stylesheet_t * mycss_namespace_stylesheet_destroy(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry, bool self_destroy);

mystatus_t mycss_namespace_stylesheet_init_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry, const char* url, size_t url_length, myhtml_namespace_t def_ns);
void mycss_namespace_stylesheet_append_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_namespace_entry_t* ns_entry);
void mycss_namespace_stylesheet_destroy_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry);

mycss_namespace_entry_t * mycss_namespace_entry_create(mycss_namespace_t* ns);
void mycss_namespace_entry_clean(mycss_namespace_entry_t* ns_entry);
mycss_namespace_entry_t * mycss_namespace_entry_destroy(mycss_namespace_entry_t* ns_entry, mycss_entry_t* entry, bool self_destroy);

void mycss_namespace_entry_append_to_current(mycss_namespace_t* ns, mycss_namespace_entry_t* ns_entry);

const char * mycss_namespace_name_by_id(mycss_namespace_t* ns, mctree_t* name_tree, size_t ns_id, size_t* length);
mycss_namespace_entry_t * mycss_namespace_entry_by_name(mycss_namespace_t *ns, mctree_t* name_tree, const char* ns_name, size_t length, bool case_insensitive);
const char * mycss_namespace_name_by_entry(mycss_namespace_entry_t* ns_entry, mctree_t* name_tree, size_t* length, bool* is_default);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_NAMESPACE_INIT_H */
