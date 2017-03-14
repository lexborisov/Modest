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

#ifndef MyHTML_MyCSS_DECLARATION_MYOSI_H
#define MyHTML_MyCSS_DECLARATION_MYOSI_H
#pragma once

#include "mycss/myosi.h"
#include "mycss/stack.h"
#include "mycss/values/units.h"
#include "mycss/property/myosi.h"
#include "mycore/utils/mcobject.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mycss_declaration_entry mycss_declaration_entry_t;
typedef struct mycss_declaration mycss_declaration_t;

typedef mycss_declaration_entry_t * (*mycss_callback_declaration_destroy_f)(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy);

enum mycss_declaration_flags {
    MyCSS_DECLARATION_FLAGS_UNDEF     = 0x00,
    MyCSS_DECLARATION_FLAGS_BAD       = 0x01,
    MyCSS_DECLARATION_FLAGS_READ_ONLY = 0x02
}
typedef mycss_declaration_flags_t;

struct mycss_declaration {
    mycss_entry_t* ref_entry;
    
    mycss_declaration_entry_t** entry;
    mycss_declaration_entry_t*  entry_last;
    
    mycss_stack_t* stack;
    
    mycss_token_type_t ending_token;
    
    mcobject_t* mcobject_entries;      /* for a dec entries */
    mcobject_t* mcobject_list;         /* for a dec list */
};

struct mycss_declaration_entry {
    mycss_property_type_t type;
    
    unsigned int value_type;
    void* value;
    
    bool is_important;
    mycss_declaration_flags_t flags;
    
    mycss_declaration_entry_t* next;
    mycss_declaration_entry_t* prev;
};


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_DECLARATION_MYOSI_H */
