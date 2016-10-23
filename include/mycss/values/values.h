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

#ifndef MyHTML_MyCSS_VALUES_VALUES_H
#define MyHTML_MyCSS_VALUES_VALUES_H
#pragma once

#include <mycss/myosi.h>
#include <mycss/values/units.h>
#include <myhtml/utils/mchar_async.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mycss_values_shorthand_two_type mycss_values_shorthand_two_type_t;
typedef struct mycss_values_shorthand_four mycss_values_shorthand_four_t;
typedef struct mycss_values_shorthand_two mycss_values_shorthand_two_t;
typedef struct mycss_values_percentage mycss_values_percentage_t;
typedef struct mycss_values_length mycss_values_length_t;

struct mycss_values_shorthand_two_type {
    void* one;
    void* two;
    
    unsigned int type_one;
    unsigned int type_two;
};

struct mycss_values_shorthand_four {
    void* one;
    void* two;
    void* three;
    void* four;
};

struct mycss_values_shorthand_two {
    void* one;
    void* two;
};

struct mycss_values_length {
    union {
        int i;
        float f;
    };
    
    bool is_float;
    mycss_units_type_t type;
};

struct mycss_values_percentage {
    union {
        int i;
        float f;
    };
    
    bool is_float;
};

void * mycss_values_create(mycss_entry_t* entry, size_t size);
void * mycss_values_destroy(mycss_entry_t* entry, void* value);

void * mycss_values_clone(mycss_entry_t* entry, void* value);

void * mycss_values_entry(mycss_entry_t* entry);
void mycss_values_entry_set(mycss_entry_t* entry, void** value);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_VALUES_VALUES_H */
