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

#ifndef MyHTML_MyCSS_SELECTORS_STATE_H
#define MyHTML_MyCSS_SELECTORS_STATE_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/selectors/myosi.h"
#include "mycss/selectors/parser.h"
#include "mycore/utils.h"

void mycss_selectors_state_end(mycss_entry_t* entry);
bool mycss_selectors_state_function_skip_all(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* <drop> */
bool mycss_selectors_state_drop(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_drop_component_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
    
/* <combinator> */
bool mycss_selectors_state_combinator(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_combinator_greater_than(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* <complex-selector-list> */
bool mycss_selectors_state_complex_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_complex_selector_list_need_combinator_or_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_complex_selector_list_need_combinator_or_selector_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_complex_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_complex_selector_list_need_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* <compound-selector-list> */
bool mycss_selectors_state_compound_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_compound_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_compound_selector_list_need_selector_or_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_compound_selector_list_comma_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_compound_selector_list_need_ending_or_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* <relative-selector-list> */
bool mycss_selectors_state_relative_selector_list(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_relative_selector_list_need_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_relative_selector_list_need_combinator_or_selector_ws(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* <simple-selector> */
bool mycss_selectors_state_simple_selector_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_left_bracket(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_left_bracket_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_left_bracket_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_left_bracket_ident_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_colon(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_colon_colon(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_colon_colon_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_colon_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_full_stop(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_simple_selector_ident_vertical_bar(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_shared_after_attr_modifier(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_shared_after_attribute_value(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_left_bracket_after_wq_name_attr(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_selectors_state_shared_after_attr_matcher(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_STATE_H */
