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

#ifndef MODEST_STYLE_MAP_H
#define MODEST_STYLE_MAP_H
#pragma once

#include "modest/myosi.h"
#include "modest/finder/myosi.h"
#include "modest/finder/thread.h"

typedef void (*modest_style_map_collate_f)(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec);

void modest_style_map_collate_declaration(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec);

void modest_style_map_collate_declaration_undef(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec);
void modest_style_map_collate_declaration_height(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec);
void modest_style_map_collate_declaration_width(myhtml_tree_node_t* node, modest_finder_thread_declaration_t* thr_dec);


#endif /* MODEST_STYLE_MAP_H */
