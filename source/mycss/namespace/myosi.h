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

#ifndef MyHTML_MyCSS_NAMESPACE_MYOSI_H
#define MyHTML_MyCSS_NAMESPACE_MYOSI_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "myhtml/mystring.h"
#include "mycore/utils/mctree.h"
#include "mycore/utils/mcobject.h"

typedef struct mycss_namespace mycss_namespace_t;
typedef struct mycss_namespace_entry mycss_namespace_entry_t;
typedef struct mycss_namespace_stylesheet mycss_namespace_stylesheet_t;

struct mycss_namespace_entry {
    mycore_string_t* name;
    mycore_string_t* url;
    
    myhtml_namespace_t ns_id;
    size_t mctree_id;
    
    mycss_namespace_entry_t* next;
    mycss_namespace_entry_t* prev;
};

struct mycss_namespace_stylesheet {
    mctree_t* name_tree; // tree for namespace names
    
    mycss_namespace_entry_t* entry_first;
    
    mycss_namespace_entry_t* entry_default;
    mycss_namespace_entry_t entry_undef;
    mycss_namespace_entry_t entry_any;
    
    size_t ns_id_counter;
};

struct mycss_namespace {
    mycss_namespace_entry_t** entry;
    mycss_namespace_entry_t*  entry_last;
    
    mycss_namespace_stylesheet_t* ns_stylesheet;
    
    mcobject_t* mcobject_entries;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_NAMESPACE_MYOSI_H */
