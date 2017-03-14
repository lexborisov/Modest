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

#ifndef MyCSS_STACK_H
#define MyCSS_STACK_H
#pragma once

#include "mycss/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mycss_stack_entry {
    void *value;
    mycss_parser_token_f parser;
}
typedef mycss_stack_entry_t;

struct mycss_stack {
    mycss_stack_entry_t* entries;
    size_t entries_length;
    size_t entries_size;
}
typedef mycss_stack_t;

mycss_stack_t * mycss_stack_create(void);
mystatus_t mycss_stack_init(mycss_stack_t *stack, size_t size);
void mycss_stack_clean(mycss_stack_t *stack);
mycss_stack_t * mycss_stack_destroy(mycss_stack_t *stack, bool self_destroy);

mystatus_t mycss_stack_push(mycss_stack_t *stack, void* value, mycss_parser_token_f parser);
mycss_stack_entry_t * mycss_stack_pop(mycss_stack_t *stack);
mycss_stack_entry_t * mycss_stack_current(mycss_stack_t *stack);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_STACK_H */
