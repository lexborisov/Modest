/*
 Copyright (C) 2016 Alexander Borisov
 
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

#include "modest/myosi.h"
#include "myhtml/myosi.h"
#include "mycss/myosi.h"

#ifdef __cplusplus
//extern "C" {
#endif

struct modest_finder typedef modest_finder_t;

typedef void (*modest_finder_callback_f)(modest_finder_t* finder, myhtml_tree_node_t* node, void* ctx);
typedef bool (*modest_finder_match_f)(myhtml_token_attr_t* attr, const char* key, size_t key_len, const char* value, size_t value_len, bool case_sensitive);

struct modest_finder {
    myhtml_tree_t* tree;
    mycss_stylesheet_t* stylesheet;
    
    modest_finder_callback_f callback_found;
    void* callback_found_ctx;
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_FINDER_MYOSI_H */
