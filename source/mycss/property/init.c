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

#include "mycss/property/init.h"
#include "mycss/property/resources.h"
#include "myhtml/utils/resources.h"

const mycss_property_index_static_entry_t * mycss_property_index_entry_by_name(const char* name, size_t length)
{
    if(length == 0)
        return NULL;
    
    size_t idx = ((myhtml_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   myhtml_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_PROPERTY_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_property_index_static_for_search[idx].name)
    {
        if(mycss_property_index_static_for_search[idx].name_length == length) {
            if(myhtml_strncasecmp(mycss_property_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_property_index_static_for_search[idx];
            
            if(mycss_property_index_static_for_search[idx].next)
                idx = mycss_property_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_property_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_property_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_property_type_t mycss_property_type_by_name(const char *name, size_t length)
{
    const mycss_property_index_static_entry_t *entry = mycss_property_index_entry_by_name(name, length);
    
    if(entry)
        return entry->type;
    
    return MyCSS_PROPERTY_TYPE_UNDEF;
}

const mycss_property_value_index_static_entry_t * mycss_property_value_index_entry_by_name(const char* name, size_t length)
{
    if(length == 0)
        return NULL;
    
    size_t idx = ((myhtml_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   myhtml_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_PROPERTY_VALUE_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_property_value_index_static_for_search[idx].name)
    {
        if(mycss_property_value_index_static_for_search[idx].name_length == length) {
            if(myhtml_strncasecmp(mycss_property_value_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_property_value_index_static_for_search[idx];
            
            if(mycss_property_value_index_static_for_search[idx].next)
                idx = mycss_property_value_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_property_value_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_property_value_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_property_value_t mycss_property_value_type_by_name(const char *name, size_t length)
{
    const mycss_property_value_index_static_entry_t *entry = mycss_property_value_index_entry_by_name(name, length);
    
    if(entry)
        return entry->type;
    
    return MyCSS_PROPERTY_VALUE_UNDEF;
}

void mycss_property_print(mycss_property_type_t prop_type, FILE* fh)
{
    if(prop_type >= MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        return;
    
    fprintf(fh, "%s", mycss_property_index_type_name[prop_type]);
}

void mycss_property_value_print(unsigned int value_type, void* value, FILE* fh)
{
    switch (value_type) {
        case MyCSS_PROPERTY_VALUE_LENGTH:
            mycss_serialization_length(value, fh);
            break;
            
        case MyCSS_PROPERTY_VALUE_PERCENTAGE:
            mycss_serialization_percentage(value, fh);
            break;
            
        default:
        {
            if(value_type >= MyCSS_PROPERTY_VALUE_LAST_ENTRY)
                break;
            
            fprintf(fh, "%s", mycss_property_index_type_value[value_type]);
            
            break;
        }
    }
}


