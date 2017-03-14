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

#ifndef MODEST_FINDER_THREAD_H
#define MODEST_FINDER_THREAD_H
#pragma once

#include <modest/modest.h>
#include <modest/node/node.h>
#include <modest/style/type.h>
#include <modest/style/map.h>
#include <modest/finder/myosi.h>
#include <modest/finder/finder.h>

#include <mycore/mythread.h>
#include <mycore/utils/mcobject_async.h>

#include <mycss/declaration/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

struct modest_finder_thread_declaration {
    mycss_declaration_entry_t* entry;
    modest_style_raw_specificity_t raw_spec;
    
    struct modest_finder_thread_declaration* next;
    struct modest_finder_thread_declaration* prev;
};

struct modest_finder_thread_entry {
    myhtml_tree_node_t* node;
    
    modest_finder_thread_declaration_t* declaration;
    modest_finder_thread_declaration_t* declaration_last;
    
    struct modest_finder_thread_entry* next;
    struct modest_finder_thread_entry* prev;
};

struct modest_finder_thread_context {
    modest_finder_thread_entry_t* entry;
    modest_finder_thread_entry_t* entry_last;
    size_t entry_node_id;
    size_t declaration_node_id;
};

struct modest_finder_thread {
    modest_finder_thread_context_t* context_list;
    size_t context_list_size;
    
    mythread_t *thread;
    
    mcobject_async_t* entry_obj;
    mcobject_async_t* declaration_obj;
    
    /* refs */
    modest_finder_t* finder;
    myhtml_tree_node_t* base_node;
    mycss_selectors_list_t* selector_list;
};

struct modest_finder_thread_found_context {
    modest_finder_thread_t* finder_thread;
    modest_finder_thread_context_t* context;
};


modest_finder_thread_t * modest_finder_thread_create(void);
mystatus_t modest_finder_thread_init(modest_finder_t* finder, modest_finder_thread_t* finder_thread, size_t thread_count);
void modest_finder_thread_clean(modest_finder_thread_t* finder_thread, bool self_destroy);
modest_finder_thread_t * modest_finder_thread_destroy(modest_finder_thread_t* finder_thread, bool self_destroy);

mystatus_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread, myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list);

#ifndef MyCORE_BUILD_WITHOUT_THREADS
void modest_finder_thread_wait_for_all_done(modest_finder_thread_t* finder_thread);
#endif

bool modest_finder_thread_spec_is_up(modest_style_raw_specificity_t* spec_f, modest_style_raw_specificity_t* spec_t);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* thread_h */
