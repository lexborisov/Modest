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

#ifndef MyHTML_MyCSS_NAMESPACE_PARSER_H
#define MyHTML_MyCSS_NAMESPACE_PARSER_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/namespace/myosi.h"
#include "myhtml/mynamespace.h"
#include "mycore/utils/mctree.h"

void mycss_namespace_parser_begin(mycss_entry_t* entry);

void mycss_namespace_parser_name(mycss_entry_t* entry, mycss_token_t* token);
void mycss_namespace_parser_url(mycss_entry_t* entry, mycss_token_t* token);
void mycss_namespace_parser_end(mycss_entry_t* entry, mycss_token_t* token);
void mycss_namespace_parser_expectations_error(mycss_entry_t* entry, mycss_token_t* token);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_NAMESPACE_PARSER_H */
