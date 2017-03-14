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

#include "mycss/selectors/pseudo.h"
#include "mycss/selectors/pseudo_resource.h"
#include "mycore/utils/resources.h"

/////////////////////////////////////////////////////////
//// Functions for a find Begin Function
////
/////////////////////////////////////////////////////////
const mycss_selectots_pseudo_begin_entry_t * mycss_pseudo_begin_entry_by_name(const char* name, size_t length, size_t static_size, const mycss_selectots_pseudo_begin_entry_t* pseudo)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % static_size) + 1;
    
    while (pseudo[idx].name)
    {
        if(pseudo[idx].length == length) {
            if(mycore_strncasecmp(pseudo[idx].name, name, length) == 0)
                return &pseudo[idx];
            
            if(pseudo[idx].next)
                idx = pseudo[idx].next;
            else
                return NULL;
        }
        else if(pseudo[idx].length > length) {
            return NULL;
        }
        else {
            idx = pseudo[idx].next;
        }
    }
    
    return NULL;
}

mycss_selectors_sub_type_pseudo_class_t mycss_pseudo_class_by_name(const char *name, size_t length)
{
    const mycss_selectots_pseudo_begin_entry_t *entry = mycss_pseudo_begin_entry_by_name(name, length, MyCSS_SELECTORS_PSEUDO_CLASS_NAME_STATIC_SIZE, mycss_selectors_pseudo_class_begin_map_index);
    
    if(entry)
        return entry->sub_type;
    
    return MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_UNKNOWN;
}

mycss_selectors_sub_type_pseudo_element_t mycss_pseudo_element_by_name(const char *name, size_t length)
{
    const mycss_selectots_pseudo_begin_entry_t *entry = mycss_pseudo_begin_entry_by_name(name, length, MyCSS_SELECTORS_PSEUDO_ELEMENT_NAME_STATIC_SIZE, mycss_selectors_pseudo_element_begin_map_index);
    
    if(entry)
        return entry->sub_type;
    
    return MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_UNKNOWN;
}


