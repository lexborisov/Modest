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

#ifndef MyHTML_MyCSS_SELECTORS_PARSER_H
#define MyHTML_MyCSS_SELECTORS_PARSER_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/entry.h>
#include <mycss/namespace/myosi.h>
#include <mycss/namespace/init.h>
#include <mycss/selectors/myosi.h>
#include <mycss/selectors/value.h>
#include <mycss/selectors/function.h>
#include <mycss/selectors/pseudo.h>

void mycss_selectors_parser_selector_begin(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_ident_type(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_ident_attr(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_namespace_ident(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_namespace_attr(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_after_namespace(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_id(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_class(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_value(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_end(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_modifier(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_class(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_class_function(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_class_function_end(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_element(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_element_function(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_selector_pseudo_element_function_end(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_expectations_error(mycss_entry_t* entry, mycss_token_t* token);
void mycss_selectors_parser_bad_token(mycss_entry_t* entry, mycss_token_t* token);

/* for set parent selector bad status if child selector is bad*/
void mycss_selectors_parser_check_and_set_bad_parent_selector(mycss_entry_t* entry, mycss_selectors_list_t* selectors_list);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_PARSER_H */
