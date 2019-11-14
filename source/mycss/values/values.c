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

void * mycss_values_realloc(mycss_entry_t* entry, void* value, size_t old_size, size_t up_to)
{
    char *new_value = mchar_async_realloc(entry->mchar, entry->mchar_value_node_id, value, old_size, (up_to + old_size));
    memset(&new_value[old_size], 0, up_to);
    
    return (void*)new_value;
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

unsigned int * mycss_values_type_list_add_entry(mycss_entry_t* entry, mycss_values_type_list_t *list)
{
    if(list->entries == NULL) {
        list->entries = mycss_values_create(entry, sizeof(unsigned int));
        list->entries_length = 0;
    }
    else {
        list->entries = mycss_values_realloc(entry, list->entries,
                                             list->entries_length * sizeof(unsigned int),
                                             sizeof(unsigned int));
    }
    
    unsigned int *type = &list->entries[ list->entries_length ];
    list->entries_length++;
    
    return type;
}

mycss_values_image_t * mycss_values_image_list_add_entry(mycss_entry_t* entry, mycss_values_image_list_t *bg_image)
{
    if(bg_image->images == NULL) {
        bg_image->images = mycss_values_create(entry, sizeof(mycss_values_image_t));
        bg_image->images_length = 0;
    }
    else {
        bg_image->images = mycss_values_realloc(entry, bg_image->images,
                                                bg_image->images_length * sizeof(mycss_values_image_t),
                                                sizeof(mycss_values_image_t));
    }
    
    mycss_values_image_t *image = &bg_image->images[ bg_image->images_length ];
    bg_image->images_length++;
    
    return image;
}

mycss_values_background_repeat_t * mycss_values_background_repeat_list_add_entry(mycss_entry_t* entry, mycss_values_background_repeat_list_t *list)
{
    if(list->entries == NULL) {
        list->entries = mycss_values_create(entry, sizeof(mycss_values_background_repeat_t));
        list->entries_length = 0;
    }
    else {
        list->entries = mycss_values_realloc(entry, list->entries,
                                             list->entries_length * sizeof(mycss_values_background_repeat_t),
                                             sizeof(mycss_values_background_repeat_t));
    }
    
    mycss_values_background_repeat_t *repeat = &list->entries[ list->entries_length ];
    list->entries_length++;
    
    return repeat;
}

mycss_values_background_size_entry_t * mycss_values_background_size_list_add_entry(mycss_entry_t* entry, mycss_values_background_size_list_t *list)
{
    if(list->entries == NULL) {
        list->entries = mycss_values_create(entry, sizeof(mycss_values_background_size_entry_t));
        list->entries_length = 0;
    }
    else {
        list->entries = mycss_values_realloc(entry, list->entries,
                                             list->entries_length * sizeof(mycss_values_background_size_entry_t),
                                             sizeof(mycss_values_background_size_entry_t));
    }
    
    mycss_values_background_size_entry_t *size_entry = &list->entries[ list->entries_length ];
    list->entries_length++;
    
    return size_entry;
}

