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

#include "myurl/url.h"
#include "myurl/scheme.h"
#include "myurl/scheme_resources.h"
#include "mycore/utils/resources.h"

void myurl_scheme_clean(myurl_t* url, myurl_scheme_t* scheme)
{
    if(scheme->name)
        url->callback_free(scheme->name, url->callback_ctx);
    
    memset(scheme, 0, sizeof(myurl_scheme_t));
}

myurl_scheme_t * myurl_scheme_destroy(myurl_t* url, myurl_scheme_t* scheme, bool self_destroy)
{
    if(scheme == NULL)
        return NULL;
    
    if(scheme->name)
        url->callback_free(scheme->name, url->callback_ctx);
    
    if(self_destroy) {
        url->callback_free(scheme, url->callback_ctx);
        return NULL;
    }
    
    return scheme;
}

const myurl_scheme_entry_t * myurl_scheme_find_entry(const char* name, size_t length)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyURL_SCHEME_STATIC_INDEX_LENGTH) + 1;
    
    while (myurl_scheme_entry_static_index[idx].name)
    {
        if(myurl_scheme_entry_static_index[idx].name_length == length) {
            if(mycore_strncasecmp(myurl_scheme_entry_static_index[idx].name, name, length) == 0)
                return &myurl_scheme_entry_static_index[idx];
            
            if(myurl_scheme_entry_static_index[idx].next)
                idx = myurl_scheme_entry_static_index[idx].next;
            else
                return NULL;
        }
        else if(myurl_scheme_entry_static_index[idx].name_length > length) {
            return NULL;
        }
        else {
            idx = myurl_scheme_entry_static_index[idx].next;
        }
    }
    
    return NULL;
}

myurl_scheme_id_t myurl_scheme_id_by_name(const char *name, size_t length)
{
    const myurl_scheme_entry_t *entry = myurl_scheme_find_entry(name, length);
    
    if(entry)
        return entry->m_id;
    
    return MyURL_SCHEME_ID_UNDEF;
}

mystatus_t myurl_scheme_copy(myurl_t* url, myurl_scheme_t* from, myurl_scheme_t* to)
{
    memcpy(to, from, sizeof(myurl_scheme_t));
    
    if(from->name) {
        to->name = myurl_utils_data_copy(url, from->name, from->length);
        
        if(to->name == NULL) {
            return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        }
    }
    
    return MyURL_STATUS_OK;
}


