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

#ifndef MyHTML_MyCSS_SELECTORS_FUNCTION_PARSER_H
#define MyHTML_MyCSS_SELECTORS_FUNCTION_PARSER_H
#pragma once

#define MyCSS_SELECTORS_FUNCTION_NAME_STATIC_SIZE 57

#ifdef __cplusplus
extern "C" {
#endif
    
#include <mycss/entry.h>
#include <mycss/selectors/myosi.h>

bool mycss_selectors_function_parser_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_unknown_parser(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_not_or_matches_or_current_parser(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_has(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_contains(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_nth_with_selectors(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_nth_with_selectors_need_of(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_nth_with_selectors_need_of_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_nth_without_selectors(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_nth_without_selectors_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_drop(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_drop_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_drop_after_column(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_dir(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_dir_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_selectors_function_parser_lang(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_lang_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_function_parser_lang_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_FUNCTION_PARSER_H */
