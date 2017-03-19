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

#include "mycss/values/units.h"
#include "mycss/values/units_resources.h"
#include "mycore/utils/resources.h"

const mycss_units_index_static_entry_t * mycss_units_index_entry_by_name(const char* name, size_t length)
{
    if(length == 0)
        return NULL;
    
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_UNITS_STATIC_INDEX_FOR_SEARCH_SIZE) + 1;
    
    while (mycss_units_index_static_for_search[idx].name)
    {
        if(mycss_units_index_static_for_search[idx].name_length == length) {
            if(mycore_strncasecmp(mycss_units_index_static_for_search[idx].name, name, length) == 0)
                return &mycss_units_index_static_for_search[idx];
            
            if(mycss_units_index_static_for_search[idx].next)
                idx = mycss_units_index_static_for_search[idx].next;
            else
                return NULL;
        }
        else if(mycss_units_index_static_for_search[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = mycss_units_index_static_for_search[idx].next;
        }
    }
    
    return NULL;
}

mycss_units_type_t mycss_units_type_by_name(const char *name, size_t length)
{
    const mycss_units_index_static_entry_t *entry = mycss_units_index_entry_by_name(name, length);
    
    if(entry)
        return entry->unit_type;
    
    return MyCSS_UNIT_TYPE_UNDEF;
}

const char * mycss_units_name_by_type(mycss_units_type_t unit_type)
{
    if(unit_type >= MyCSS_UNIT_TYPE_LAST_ENTRY)
        return NULL;
    
    return mycss_units_index_name[unit_type];
}

