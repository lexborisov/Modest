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

#include "mycss/values/image.h"
#include "mycss/values/image_resources.h"
#include "mycore/utils/resources.h"

const mycss_values_image_function_index_static_entry_t * mycss_values_image_index_entry_by_name(const char* name, size_t length)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_IMAGE_FUNCTION_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_values_image_function_index_static_for_search[idx].name)
    {
        if(mycss_values_image_function_index_static_for_search[idx].name_length == length) {
            if(mycore_strncasecmp(mycss_values_image_function_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_values_image_function_index_static_for_search[idx];
            
            if(mycss_values_image_function_index_static_for_search[idx].next)
                idx = mycss_values_image_function_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_values_image_function_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_values_image_function_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_property_value_t mycss_values_image_id_by_name(const char *name, size_t length)
{
    const mycss_values_image_function_index_static_entry_t *entry = mycss_values_image_index_entry_by_name(name, length);
    
    if(entry)
        return entry->type;
    
    return MyCSS_PROPERTY_VALUE_UNDEF;
}

void * mycss_values_image_creator_url(mycss_entry_t* entry, mycss_values_image_t* image)
{
    image->value.url = mycss_values_create(entry, sizeof(mycss_values_url_t));
    return image->value.url;
}

void * mycss_values_image_creator_function_image(mycss_entry_t* entry, mycss_values_image_t* image)
{
    image->value.ii = mycss_values_create(entry, sizeof(mycss_values_image_image_t));
    return image->value.ii;
}

void * mycss_values_image_creator_image_set(mycss_entry_t* entry, mycss_values_image_t* image)
{
    image->value.ii_set = mycss_values_create(entry, sizeof(mycss_values_image_image_set_t));
    return image->value.ii_set;
}

void * mycss_values_image_creator_element(mycss_entry_t* entry, mycss_values_image_t* image)
{
    image->value.element = mycss_values_create(entry, sizeof(mycss_values_element_t));
    return image->value.element;
}

void * mycss_values_image_creator_cross_fade(mycss_entry_t* entry, mycss_values_image_t* image)
{
    image->value.cross_fade = mycss_values_create(entry, sizeof(mycss_values_cross_fade_t));
    return image->value.cross_fade;
}


