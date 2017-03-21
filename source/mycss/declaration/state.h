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

#ifndef MyHTML_MyCSS_DECLARATION_DECLARATION_H
#define MyHTML_MyCSS_DECLARATION_DECLARATION_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/declaration/parser.h"

bool mycss_declaration_state_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_declaration_state_data(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_colon_before_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_colon_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_colon_delim_after_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_find_ending(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_parse_error(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_declaration_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_DECLARATION_DECLARATION_H */
