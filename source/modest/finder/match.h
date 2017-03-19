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

#ifndef MODEST_FINDER_MATCH_H
#define MODEST_FINDER_MATCH_H
#pragma once

#include "myhtml/myosi.h"
#include "myhtml/tree.h"

#ifdef __cplusplus
extern "C" {
#endif

bool modest_finder_match_attribute_only_key(myhtml_token_attr_t* attr, const char* key, size_t key_len);
bool modest_finder_match_attribute_eq(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);
bool modest_finder_match_attribute_ws(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);
bool modest_finder_match_attribute_begin(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);
bool modest_finder_match_attribute_end(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);
bool modest_finder_match_attribute_sub(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);
bool modest_finder_match_attribute_hsp(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_MATCH_H */
