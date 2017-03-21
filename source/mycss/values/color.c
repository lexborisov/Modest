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

#include "mycss/values/color.h"
#include "mycss/values/color_resources.h"
#include "mycore/utils/resources.h"

const mycss_values_color_index_static_entry_t * mycss_values_color_index_entry_by_name(const char* name, size_t length)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_COLOR_NAME_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_values_color_name_index_static_for_search[idx].name)
    {
        if(mycss_values_color_name_index_static_for_search[idx].name_length == length) {
            if(mycore_strncasecmp(mycss_values_color_name_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_values_color_name_index_static_for_search[idx];
            
            if(mycss_values_color_name_index_static_for_search[idx].next)
                idx = mycss_values_color_name_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_values_color_name_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_values_color_name_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_values_color_id_t mycss_values_color_id_by_name(const char *name, size_t length)
{
    const mycss_values_color_index_static_entry_t *entry = mycss_values_color_index_entry_by_name(name, length);
    
    if(entry)
        return entry->type;
    
    return MyCSS_VALUES_COLOR_ID_UNDEF;
}

const char * mycss_values_color_name_by_id(mycss_values_color_id_t color_id, size_t *length)
{
    if(color_id >= MyCSS_VALUES_COLOR_ID_LAST_ENTRY) {
        if(length)
            *length = 0;
        
        return NULL;
    }
    
    const char *name = mycss_values_color_name_index[color_id];
    
    if(length)
        *length = strlen(name);
    
    return name;
}

const mycss_values_color_function_index_static_entry_t * mycss_values_color_function_index_entry_by_name(const char* name, size_t length)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_COLOR_FUNCTION_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_values_color_function_index_static_for_search[idx].name)
    {
        if(mycss_values_color_function_index_static_for_search[idx].name_length == length) {
            if(mycore_strncasecmp(mycss_values_color_function_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_values_color_function_index_static_for_search[idx];
            
            if(mycss_values_color_function_index_static_for_search[idx].next)
                idx = mycss_values_color_function_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_values_color_function_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_values_color_function_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_values_color_function_id_t mycss_values_color_function_id_by_name(const char *name, size_t length)
{
    const mycss_values_color_function_index_static_entry_t *entry = mycss_values_color_function_index_entry_by_name(name, length);
    
    if(entry)
        return entry->type;
    
    return MyCSS_VALUES_COLOR_FUNCTION_ID_UNDEF;
}

const char * mycss_values_color_function_name_by_id(mycss_values_color_function_id_t color_function_id, size_t *length)
{
    if(color_function_id >= MyCSS_VALUES_COLOR_FUNCTION_ID_LAST_ENTRY) {
        if(length)
            *length = 0;
        
        return NULL;
    }
    
    const char *name = mycss_values_color_function_name_index[color_function_id];
    
    if(length)
        *length = strlen(name);
    
    return name;
}

