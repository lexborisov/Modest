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

#ifndef MODEST_FINDER_MYOSI_H
#define MODEST_FINDER_MYOSI_H
#pragma once

#include <modest/myosi.h>
#include <mycss/myosi.h>
#include <mycss/selectors/myosi.h>
#include <mycss/selectors/list.h>

#ifdef __cplusplus
extern "C" {
#endif

struct modest_finder typedef modest_finder_t;

typedef void (*modest_finder_callback_f)(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx);
typedef bool (*modest_finder_match_f)(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);

struct modest_finder {
    void* ctx;
};

typedef struct modest_finder_thread_declaration modest_finder_thread_declaration_t;
typedef struct modest_finder_thread_entry modest_finder_thread_entry_t;
typedef struct modest_finder_thread_context modest_finder_thread_context_t;
typedef struct modest_finder_thread modest_finder_thread_t;
typedef struct modest_finder_thread_found_context modest_finder_thread_found_context_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_MYOSI_H */
