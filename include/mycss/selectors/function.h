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

#ifndef MyHTML_MyCSS_SELECTORS_FUNCTION_H
#define MyHTML_MyCSS_SELECTORS_FUNCTION_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/entry.h>
#include <mycss/selectors/myosi.h>
#include <mycss/selectors/function_parser.h>

typedef void (*mycss_selectors_function_begin_f)(mycss_entry_t* entry, mycss_selectors_entry_t* selector);

struct mycss_selectors_function_index {
    mycss_parser_token_f parser;
    mycss_parser_token_f switch_parser;
}
typedef mycss_selectors_function_index_t;

struct mycss_selectots_function_begin_entry {
    const char* name;
    size_t length;
    
    mycss_selectors_function_begin_f func;
    
    size_t next;
    size_t curr;
}
typedef mycss_selectots_function_begin_entry_t;

mycss_selectors_function_begin_f mycss_function_begin_by_name(const char *name, size_t length);
const mycss_selectots_function_begin_entry_t * mycss_function_begin_entry_by_name(const char* name, size_t length);

void mycss_selectors_function_begin_nth_child(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_not(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_dir(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_matches(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_lang(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_drop(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_nth_of_type(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_nth_last_column(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_current(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_nth_last_child(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_nth_last_of_type(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_has(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_nth_column(mycss_entry_t* entry, mycss_selectors_entry_t* selector);
void mycss_selectors_function_begin_contains(mycss_entry_t* entry, mycss_selectors_entry_t* selector);

void mycss_selectors_begin_unknown(mycss_entry_t* entry, mycss_selectors_entry_t* selector);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_FUNCTION_H */
