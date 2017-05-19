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

#ifndef MyCSS_SYNTAX_ENDING_H
#define MyCSS_SYNTAX_ENDING_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycss/mycss.h"
#include "mycss/entry.h"

bool mycss_syntax_endings_list_of_rules_return(mycss_entry_t* entry, mycss_token_t* token);
bool mycss_syntax_endings_list_of_rules_qualified_rule_left_qb(mycss_entry_t* entry, mycss_token_t* token);
bool mycss_syntax_endings_list_of_rules_at_rule_qb(mycss_entry_t* entry, mycss_token_t* token);
bool mycss_syntax_endings_component_value_and_simple_block_left_curly_bracket(mycss_entry_t* entry, mycss_token_t* token);
bool mycss_syntax_endings_component_value_and_simple_block_left_square_bracket(mycss_entry_t* entry, mycss_token_t* token);
bool mycss_syntax_endings_component_value_and_simple_block_left_parenthesis(mycss_entry_t* entry, mycss_token_t* token);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_SYNTAX_ENDING_H */
