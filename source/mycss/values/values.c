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

#include "mycss/values/values.h"
#include "mycss/entry.h"

void * mycss_values_create(mycss_entry_t* entry, size_t size)
{
    void *value = mchar_async_malloc(entry->mchar, entry->mchar_value_node_id, size);
    memset(value, 0, size);
    
    return value;
}

void * mycss_values_destroy(mycss_entry_t* entry, void* value)
{
    if(value == NULL)
        return NULL;
    
    mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
    return NULL;
}

void * mycss_values_clone(mycss_entry_t* entry, void* value)
{
    size_t size = mchar_async_get_size_by_data(value);
    
    void *new_value = mycss_values_create(entry, size);
    memcpy(new_value, value, size);
    
    return new_value;
}

void mycss_values_entry_set(mycss_entry_t* entry, void** value)
{
    entry->values = value;
}

void * mycss_values_entry(mycss_entry_t* entry)
{
    return (*entry->values);
}


