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

#ifndef MyHTML_MyCSS_DECLARATION_ENTRY_H
#define MyHTML_MyCSS_DECLARATION_ENTRY_H
#pragma once

#include <mycss/declaration/myosi.h>
#include <mycss/declaration/entry_destroy.h>
#include <mycss/values/values.h>
#include <mycss/property/init.h>

#ifdef __cplusplus
extern "C" {
#endif

mycss_declaration_entry_t * mycss_declaration_entry_create(mycss_declaration_t* declaration, mystatus_t* status);
void mycss_declaration_entry_clean(mycss_declaration_entry_t* entry);
void mycss_declaration_entry_clean_all(mycss_declaration_entry_t* entry);
mycss_declaration_entry_t * mycss_declaration_entry_destroy(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy);

mycss_declaration_entry_t * mycss_declaration_entry(mycss_declaration_t* declaration);
mycss_declaration_entry_t * mycss_declaration_entry_last(mycss_declaration_t* declaration);
mycss_declaration_entry_t * mycss_declaration_entry_clone(mycss_declaration_t* declaration, mycss_declaration_entry_t* dec_entry, bool with_value);
void mycss_declaration_entry_type_set(mycss_declaration_entry_t* dec_entry, mycss_property_type_t type);
void mycss_declaration_entry_important_set(mycss_declaration_entry_t* dec_entry, bool is_important);

void mycss_declaration_entry_append_to_current(mycss_declaration_t* declaration, mycss_declaration_entry_t* dec_entry);
void mycss_declaration_entry_remove(mycss_declaration_t* declaration, mycss_declaration_entry_t* dec_entry);
mycss_declaration_entry_t * mycss_declaration_entry_delete(mycss_declaration_t* declaration, mycss_declaration_entry_t* dec_entry);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_DECLARATION_ENTRY_H */

