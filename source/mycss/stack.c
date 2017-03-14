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

#include "mycss/stack.h"

mycss_stack_t * mycss_stack_create(void)
{
    return mycore_calloc(1, sizeof(mycss_stack_t));
}

mystatus_t mycss_stack_init(mycss_stack_t *stack, size_t size)
{
    stack->entries_size   = size;
    stack->entries_length = 0;
    stack->entries = (mycss_stack_entry_t*)mycore_calloc(stack->entries_size, sizeof(mycss_stack_entry_t));
    
    if(stack->entries == NULL)
        return MyCSS_STATUS_ERROR_MEMORY_ALLOCATION;
    
    return MyCSS_STATUS_OK;
}

void mycss_stack_clean(mycss_stack_t *stack)
{
    stack->entries_length = 0;
}

mycss_stack_t * mycss_stack_destroy(mycss_stack_t *stack, bool self_destroy)
{
    if(stack == NULL)
        return NULL;
    
    if(stack->entries) {
        mycore_free(stack->entries);
        stack->entries = NULL;
    }
    
    if(self_destroy) {
        mycore_free(stack);
        return NULL;
    }
    
    return stack;
}

mystatus_t mycss_stack_push(mycss_stack_t *stack, void* value, mycss_parser_token_f parser)
{
    if(stack->entries_length >= stack->entries_size) {
        size_t new_size = stack->entries_length << 1;
        
        mycss_stack_entry_t *entries = (mycss_stack_entry_t*)mycore_realloc(stack->entries,
                                                                            sizeof(mycss_stack_entry_t) * new_size);
        
        if(entries) {
            stack->entries = entries;
            stack->entries_size = new_size;
        }
        else
            return MyCSS_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    stack->entries[ stack->entries_length ].value  = value;
    stack->entries[ stack->entries_length ].parser = parser;
    
    stack->entries_length++;
    
    return MyCSS_STATUS_OK;
}

mycss_stack_entry_t * mycss_stack_pop(mycss_stack_t *stack)
{
    stack->entries_length--;
    return &stack->entries[ stack->entries_length ];
}

mycss_stack_entry_t * mycss_stack_current(mycss_stack_t *stack)
{
    if(stack->entries_length == 0)
        return NULL;
    
    return &stack->entries[ (stack->entries_length - 1) ];
}

