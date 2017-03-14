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
#include "myurl/parser.h"
#include "myurl/resources.h"
#include "mycore/utils/resources.h"

static size_t myurl_parser_skip_control_and_space_leading(const char* url, size_t url_size)
{
    size_t i;
    const unsigned char *u_url = (const unsigned char*)url;
    
    for(i = 0; i < url_size; i++) {
        /* control */
        if(u_url[i] >  0x1F &&
           /* space */
           u_url[i] != 0x20 &&
           /* tab */
           u_url[i] != 0x09 &&
           /* new line */
           u_url[i] != 0x0A && u_url[i] != 0x0D)
        {
            break;
        }
    }
    
    return i;
}

static size_t myurl_parser_skip_control_and_space_trailing(const char* url, size_t url_size)
{
    size_t origin_size = url_size;
    const unsigned char *u_url = (const unsigned char*)url;
    
    while(url_size) {
        url_size--;
        
        if(u_url[url_size] > 0x1F && u_url[url_size] != 0x20) {
            url_size++;
            break;
        }
    }
    
    return (origin_size - url_size);
}

static size_t myurl_parser_skip_newline_and_tab_set(unsigned char* u_data, size_t data_size)
{
    size_t offset = 0;
    for(size_t i = 0; i < data_size; i++)
    {
        if(u_data[i] == 0x09 || u_data[i] == 0x0A)
        {
            u_data[(i - offset)] = u_data[ (i + 1) ];
            offset++;
        }
        else
            u_data[(i - offset)] = u_data[i];
    }
    
    u_data[ (data_size - offset) ] = '\0';
    return (data_size - offset);
}

static size_t myurl_parser_skip_newline_and_tab(myurl_t* url, const char* data, size_t data_size)
{
    const unsigned char *u_data = (const unsigned char*)data;
    
    for(size_t i = 0; i < data_size; i++) {
        if(u_data[i] == 0x09 || u_data[i] == 0x0A)
        {
            url->copy = myurl_utils_data_copy(url, data, data_size);
            
            if(url->copy)
                return (i + myurl_parser_skip_newline_and_tab_set((unsigned char*)(&url->copy[i]), (data_size - i)));
            
            return 0;
        }
    }
    
    return data_size;
}

size_t myurl_parser_begin(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_size)
{
    // add check syntax violation
    size_t data_length = myurl_parser_skip_control_and_space_leading(data, data_size);
    data_size -= myurl_parser_skip_control_and_space_trailing(data, data_size);
    
    data_size = myurl_parser_skip_newline_and_tab(url, &data[data_length], data_size);
    
    url->state = myurl_parser_state_scheme_start;
    
    if(url->copy) {
        data = url->copy;
        data_length = 0;
    }
    
    if(data_size == 0) {
        if(data_length)
            data_length = 0;
        
        /* parse end */
        myurl_state_f prev_state = myurl_parser_state_undef;
        
        while(data_length == data_size && url->state != prev_state)
        {
            prev_state = url->state;
            data_length = url->state(url, url_entry, url_base, data, data_length, data_size);
        }
        
        if(url->copy) {
            url->callback_free(url->copy, url->callback_ctx);
        }
        
        return data_length;
    }
    
    while(data_length < data_size)
    {
        while(data_length < data_size) {
            data_length = url->state(url, url_entry, url_base, data, data_length, data_size);
        }
        
        /* parse end */
        myurl_state_f prev_state = myurl_parser_state_undef;
        
        while(data_length == data_size && url->state != prev_state)
        {
            prev_state = url->state;
            data_length = url->state(url, url_entry, url_base, data, data_length, data_size);
        }
        
        if(data_length >= data_size)
            break;
    }
    
    if(url->copy) {
        url->callback_free(url->copy, url->callback_ctx);
    }
    
    return data_length;
}

size_t myurl_parser_state_undef(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * ~s~cheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_scheme_start(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(data_length < data_size && myurl_parser_alpha(data[data_length])) {
        url->state = myurl_parser_state_scheme;
        url->begin = data_length;
        
        data_length++;
    }
    else if(url->state_override == NULL) {
        url->state = myurl_parser_state_no_scheme;
    }
    else {
        // syntax violation, stop parsing
        url_entry->status = MyURL_STATUS_FAILURE_SCHEME_START;
        return (data_size + 1);
    }
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * ~scheme~:[//[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_scheme(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* END OF FILE */
    if(data_length >= data_size) {
        /* 3 */
        if(url->state_override == NULL) {
            url->begin  = 0;
            url->state = myurl_parser_state_no_scheme;
            
            return myurl_parser_skip_control_and_space_leading(data, data_size);
        }
        
        return myurl_parser_state_undef(url, url_entry, url_base, data, data_length, data_size);
    }
    
    while(data_length < data_size)
    {
        /* 1 and 4 */
        if(myurl_parser_alphanumeric(data[data_length]) == false &&
           data[data_length] != '+' && data[data_length] != '-' && data[data_length] != '.')
        {
            /* 2 */
            if(data[data_length] == ':')
            {
                const myurl_scheme_entry_t *scheme = myurl_scheme_find_entry(&data[url->begin], (data_length - url->begin));
                myurl_scheme_t *url_entry_scheme = &url_entry->scheme;
                
                /* 2.1 */
                if(url->state_override)
                {
                    if(scheme == NULL) {
                        if(url_entry_scheme->type & MyURL_SCHEME_TYPE_SPECIAL)
                        {
                            url->state = url->state_override;
                            return (data_length + 1); // skip ':'
                        }
                    }
                    else if((url_entry_scheme->type & MyURL_SCHEME_TYPE_SPECIAL) !=
                            (scheme->type & MyURL_SCHEME_TYPE_SPECIAL))
                    {
                        url->state = url->state_override;
                        return (data_length + 1); // skip ':'
                    }
                }
                
                memset(url_entry_scheme, 0, sizeof(myurl_scheme_t));
                
                /* 2.2 */
                if(scheme == NULL) {
                    if(url_entry_scheme->name)
                        url->callback_free(url_entry_scheme->name, url->callback_ctx);
                    
                    url_entry_scheme->length = (data_length - url->begin);
                    url_entry_scheme->name = myurl_utils_data_copy(url, &data[url->begin], url_entry_scheme->length);
                    
                    if(url_entry_scheme->name == NULL) {
                        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                        return (data_size + 1);
                    }
                }
                else {
                    url_entry_scheme->name = myurl_utils_data_copy(url, scheme->name, scheme->name_length);
                    if(url_entry_scheme->name == NULL) {
                        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                        return (data_size + 1);
                    }
                    
                    url_entry_scheme->length = scheme->name_length;
                    url_entry_scheme->port   = scheme->port;
                    url_entry_scheme->sid    = scheme->m_id;
                    url_entry_scheme->type   = scheme->type;
                }
                
                /* 2.3 */
                url->begin = 0;
                
                data_length++; // skip ':'
                
                /* 2.4 */
                if(url->state_override) {
                    url->state = url->state_override;
                    return data_length;
                }
                
                /* 2.5 */
                if(url_entry_scheme->sid == MyURL_SCHEME_ID_FILE)
                {
                    /* 2.5.1 */
                    if(((data_length + 1) < data_size) &&
                       mycore_strncmp((const char*)(&data[data_length]), "//", 2))
                    {
                        // parse error
                    }
                    
                    /* 2.5.2 */
                    url->state = myurl_parser_state_file;
                }
                /* 2.6 */
                else if((url_entry_scheme->type & MyURL_SCHEME_TYPE_SPECIAL) &&
                        url_base != NULL && url_base->scheme.sid == url_entry_scheme->sid && url_base->scheme.type == url_entry_scheme->type)
                {
                    url->state = myurl_parser_state_special_relative_or_authority;
                }
                /* 2.7 */
                else if(url_entry_scheme->type & MyURL_SCHEME_TYPE_SPECIAL) {
                    url->state = myurl_parser_state_special_authority_slashes;
                }
                /* 2.8 */
                else if(data_length < data_size && data[data_length] == '/') {
                    url->state = myurl_parser_state_path_or_authority;
                    data_length++;
                }
                /* 2.9 */
                else {
                    url_entry->flags |= MyURL_FLAGS_CANNOT_BE_BASE_URL;
                    url->state = myurl_parser_state_cannot_be_a_base_URL_path;
                }
                
                return data_length;
            }
            /* 3 */
            else if(url->state_override == NULL) {
                url->begin  = 0;
                url->state = myurl_parser_state_no_scheme;
                
                return myurl_parser_skip_control_and_space_leading(data, data_size);
            }
            
            /* 4 */
            // syntax violation, return failure
            url_entry->status = MyURL_STATUS_FAILURE_SCHEME_STATE;
            return (data_size + 1);
        }
        
        data_length++;
    }
    
    if(url->state_override == NULL) {
        url->begin  = 0;
        url->state = myurl_parser_state_no_scheme;
        
        return myurl_parser_skip_control_and_space_leading(data, data_size);
    }
    
    /* 4 */
    // syntax violation, return failure
    url_entry->status = MyURL_STATUS_FAILURE_SCHEME_STATE;
    return (data_size + 1);
}

/*
 * //[user:password@]host[:port][/]path[?query][#fragment]
 * ~/~/[user:password@]host[:port][/]path[?query][#fragment]
 */
size_t myurl_parser_state_no_scheme(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1 */
    if(url_base == NULL || ((url_base->flags & MyURL_FLAGS_CANNOT_BE_BASE_URL) &&
       (data_length >= data_size || data[data_length] != '#')))
    {
        // syntax violation, return failure
        url_entry->status = MyURL_STATUS_FAILURE_NO_SCHEME_BASE_NULL_OR_NOT_HASH;
        return (data_size + 1);
    }
    
    /* 2 */
    if((url_base->flags & MyURL_FLAGS_CANNOT_BE_BASE_URL) && data_length < data_size && data[data_length] == '#')
    {
        if(myurl_scheme_copy(url, &url_base->scheme, &url_entry->scheme) != MyURL_STATUS_OK ||
           myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK ||
           myurl_parser_copy_attr(url, url_base, url_entry, query) != MyURL_STATUS_OK)
        {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
        
        url_entry->query_length = url_base->query_length;
        url_entry->flags |= MyURL_FLAGS_CANNOT_BE_BASE_URL;
        
        if(url_entry->fragment)
            url_entry->fragment = url->callback_free(url_entry->fragment, url->callback_ctx);
        
        url->state = myurl_parser_state_fragment;
        
        return (data_length + 1); // skip '#'
    }
    
    /* 3 */
    if(url_base->scheme.sid != MyURL_SCHEME_ID_FILE)
        url->state = myurl_parser_state_relative;
    else
        url->state = myurl_parser_state_file;
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[~//~[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_special_relative_or_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if((data_length + 1) < data_size && data[data_length] == '/' && data[(data_length + 1)] == '/')
    {
        url->state = myurl_parser_state_special_authority_ignore_slashes;
        data_length += 2;
    }
    else {
        // parse error
        url->state = myurl_parser_state_relative;
    }
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[~//~[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_path_or_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(data_length < data_size && data[data_length] == '/') {
        url->state = myurl_parser_state_authority;
        data_length++;
    }
    else {
        url->state = myurl_parser_state_path;
    }
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//[user:password@]host[:port]][/]path~~[?query][#fragment]
 */
size_t myurl_parser_state_relative(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(myurl_scheme_copy(url, &url_base->scheme, &url_entry->scheme) != MyURL_STATUS_OK) {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    /* END OF FILE */
    if(data_length >= data_size)
        return myurl_parser_state_relative_end(url, url_entry, url_base, data, data_length, data_size);
    
    switch (data[data_length]) {
        case '/':
            url->state = myurl_parser_state_relative_slash;
            break;
            
        case '?':
            if(myurl_parser_copy_attr(url, url_base, url_entry, username) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, password) != MyURL_STATUS_OK ||
               myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            url_entry->port = url_base->port;
            url_entry->port_is_set = url_base->port_is_set;
            
            myurl_utils_data_set_empty(url, &url_entry->query, &url_entry->query_length);
            
            url->state = myurl_parser_state_query;
            break;
            
        case '#':
            if(myurl_parser_copy_attr(url, url_base, url_entry, username) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, password) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, query) != MyURL_STATUS_OK ||
               myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            url_entry->port = url_base->port;
            url_entry->port_is_set = url_base->port_is_set;
            
            myurl_utils_data_set_empty(url, &url_entry->fragment, &url_entry->fragment_length);
            
            url->state = myurl_parser_state_fragment;
            break;
            
        default:
            if((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && data[data_length] == '\\')
            {
                // parse error
                url->state = myurl_parser_state_relative_slash;
                break;
            }
            
            if(myurl_parser_copy_attr(url, url_base, url_entry, username) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, password) != MyURL_STATUS_OK ||
               myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            myurl_path_pop(&url_entry->path);
            
            url_entry->port = url_base->port;
            url_entry->port_is_set = url_base->port_is_set;
            
            url->state = myurl_parser_state_path;
            return data_length;
    }
    
    return (data_length + 1);
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_relative_slash(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(data_length < data_size)
    {
        if((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && (data[data_length] == '/' || data[data_length] == '\\'))
        {
            if(data[data_length] == '\\') {
                // parse error
            }
            
            url->state = myurl_parser_state_special_authority_ignore_slashes;
            return (data_length + 1);
        }
        else if(data[data_length] == '/') {
            url->state = myurl_parser_state_authority;
            return (data_length + 1);
        }
    }
    
    if(myurl_parser_copy_attr(url, url_base, url_entry, username) != MyURL_STATUS_OK ||
       myurl_parser_copy_attr(url, url_base, url_entry, password) != MyURL_STATUS_OK ||
       myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK)
    {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    url_entry->port = url_base->port;
    url->state = myurl_parser_state_path;
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_special_authority_slashes(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if((data_length + 1) < data_size && data[data_length] == '/' && data[(data_length + 1)] == '/') {
        data_length += 2;
    }
    else {
        // parse error
    }
    
    url->state = myurl_parser_state_special_authority_ignore_slashes;
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//~~[user:password@]host[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_special_authority_ignore_slashes(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* END OF FILE */
    if(data_length >= data_size) {
        url->begin = 0;
        url->state = myurl_parser_state_authority;
        return data_length;
    }
    
    while(data_length < data_size) {
        if(data[data_length] != '/' && data[data_length] != '\\')
        {
            url->state = myurl_parser_state_authority;
            break;
        }
        else {
            // parse error
        }
        
        data_length++;
    }
    
    return data_length;
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//[~u~ser:password@]host[:port]][/]path[?query][#fragment]
 */
static char * myurl_parser_state_authority_copy_value(myurl_t* url, myurl_entry_t* url_entry, const char* data, size_t data_length, bool is_password)
{
    size_t length;
    char *in_hex_val = myurl_utils_percent_encode(url, data, data_length, myurl_resources_static_map_userinfo, &length);
    
    if(in_hex_val == NULL) {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }
    
    if(is_password) {
        if(myurl_parser_append_buffer(url, in_hex_val, 0, length, url_entry->password)) {
            url->callback_free(in_hex_val, url->callback_ctx);
            
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return NULL;
        }
    }
    else {
        if(myurl_parser_append_buffer(url, in_hex_val, 0, length, url_entry->username)) {
            url->callback_free(in_hex_val, url->callback_ctx);
            
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return NULL;
        }
    }
    
    url->callback_free(in_hex_val, url->callback_ctx);
    
    return url_entry->username;
}

size_t myurl_parser_state_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    bool passwordTokenSeenFlag = false;
    
    while(data_length < data_size) {
        /* 1 */
        if(data[data_length] == '@')
        {
            /* find last at '@' */
            size_t i = data_length;
            while(i < data_size)
            {
                if(data[i] == '@')
                    data_length = i;
                
                i++;
            }
            
            /* 1.1 */
            // parse error
            
            /* 1.2, 1.3 */
            url_entry->flags |= MyURL_FLAGS_AT;
            
            /* 1.4 */
            i = url->begin;
            while(i < data_length)
            {
                if(data[i] == ':') {
                    passwordTokenSeenFlag = true;
                    
                    if(myurl_parser_state_authority_copy_value(url, url_entry, &data[ url->begin ], (i - url->begin), false) == NULL)
                        return (data_size + 1);
                    
                    url->begin = i = i + 1;
                    break;
                }
                
                i++;
            }
            
            if(passwordTokenSeenFlag) {
                if(myurl_parser_state_authority_copy_value(url, url_entry, &data[ url->begin ], (data_length - url->begin), true) == NULL)
                    return (data_size + 1);
            }
            else {
                if(myurl_parser_state_authority_copy_value(url, url_entry, &data[ url->begin ], (data_length - url->begin), false) == NULL)
                    return (data_size + 1);
            }
            
            url->begin = (data_length + 1);
        }
        else if((data[data_length] == '/' || data[data_length] == '?' || data[data_length] == '#') ||
                ((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && data[data_length] == '\\'))
        {
            return myurl_parser_state_authority_end(url, url_entry, url_base, data, data_length, data_size);
        }
        
        data_length++;
    }
    
    /* END OF FILE */
    return myurl_parser_state_authority_end(url, url_entry, url_base, data, data_length, data_size);
}

/*
 * scheme:[//[user:password@]host[:port]][/]path[?query][#fragment]
 * scheme:[//[user:password@]~host~[:port]][/]path[?query][#fragment]
 */
size_t myurl_parser_state_host_hostname(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if(url->state_override && url_entry->scheme.sid == MyURL_SCHEME_ID_FILE) {
            url->state = myurl_parser_state_file_host;
            return data_length;
        }
        
        /* 2 */
        if(data[data_length] == ':' && (url_entry->flags & MyURL_FLAGS_BRACKET) == 0) {
            /* 2.1 */
            if((data_length - url->begin) == 0) {
                // parse error
                url_entry->status = MyURL_STATUS_FAILURE_UNEXPECTED_ENDING;
                return (data_size + 1);
            }
            
            /* 1.2 and 1.3 */
            if(myurl_host_parser(url, &url_entry->host, &data[url->begin], (data_length - url->begin),
                                      (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL)))
            {
                url_entry->status = MyURL_STATUS_FAILURE_BAD_HOSTNAME;
                return (data_size + 1);
            }
            
            /* 1.4 */
            data_length++;
            url->begin = 0;
            
            /* 1.5 */
            if(url->state_override == myurl_parser_state_host_hostname) {
                return data_size;
            }
            
            url->state = myurl_parser_state_port;
            
            return data_length;
        }
        
        /* 3 */
        else if((data[data_length] == '/' || data[data_length] == '?' || data[data_length] == '#') ||
                ((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && data[data_length] == '\\'))
        {
            return myurl_parser_state_host_hostname_end(url, url_entry, url_base, data, data_length, data_size);
        }
        else if(data[data_length] == '[') {
            url_entry->flags |= MyURL_FLAGS_BRACKET;
        }
        else if(data[data_length] == ']') {
            url_entry->flags ^= (url_entry->flags & MyURL_FLAGS_BRACKET);
        }
        
        data_length++;
    }
    
    /* END OF FILE */
    return myurl_parser_state_host_hostname_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_port(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if(myurl_parser_digit(data[data_length]) == 0)
        {
            /* 2 */
            if((data[data_length] == '/' || data[data_length] == '?' || data[data_length] == '#') ||
               ((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && data[data_length] == '\\') ||
               url->state_override)
            {
                return myurl_parser_state_port_end(url, url_entry, url_base, data, data_length, data_size);
            }
            
            url_entry->status = MyURL_STATUS_FAILURE_BAD_PORT;
            return (data_size + 1);
        }
        
        data_length++;
    }
    
    // EOF code point
    return myurl_parser_state_port_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_file(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1 */
    if(url_entry->scheme.sid != MyURL_SCHEME_ID_FILE)
        {
        const myurl_scheme_entry_t *scheme = myurl_scheme_find_entry("file", 4);
        if(scheme) {
            url_entry->scheme.name = myurl_utils_data_copy(url, scheme->name, scheme->name_length);
            if(url_entry->scheme.name == NULL) {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            url_entry->scheme.length = scheme->name_length;
            url_entry->scheme.port   = scheme->port;
            url_entry->scheme.sid    = scheme->m_id;
            url_entry->scheme.type   = scheme->type;
        }
        else {
            url_entry->status = MyURL_STATUS_FAILURE_SCHEME_STATE;
            return (data_size + 1);
        }
    }
    
    /* 2 */
    if(data_length < data_size && (data[data_length] == '/' || data[data_length] == '\\')) {
        //if(data[data_length] == '\\') {
        //    // parse error
        //}
        
        url->state = myurl_parser_state_file_slash;
        return (data_length + 1);
    }
    
    
    /* 3 */
    if(url_base && url_base->scheme.sid == MyURL_SCHEME_ID_FILE) {
        /* END OF FILE */
        if(data_length >= data_size)
            return myurl_parser_state_file_end(url, url_entry, url_base, data, data_length, data_size);
        
        if(data[data_length] == '?') {
            if(myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, query) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            myurl_utils_data_set_empty(url, &url_entry->query, &url_entry->query_length);
            
            url->state = myurl_parser_state_query;
            return (data_length + 1);
        }
        
        if(data[data_length] == '#') {
            if(myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK ||
               myurl_parser_copy_attr(url, url_base, url_entry, query) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            myurl_utils_data_set_empty(url, &url_entry->fragment, &url_entry->fragment_length);
            
            url->state = myurl_parser_state_fragment;
            return (data_length + 1);
        }
        
        /* 3.1 */
        size_t sec_rem = data_length + 2;
        if(
           /* c and the first code point of remaining are not a Windows drive letter */
           (myurl_utils_is_windows_drive_letter(data, data_length, data_size)) ||
           
           /* remaining consists of one code point */
           (sec_rem == data_size) ||
           
           /* remaining’s second code point is not "/", "\", "?", or "#" */
           (
                sec_rem < data_size &&
                (data[sec_rem] != '/' && data[sec_rem] != '/' && data[sec_rem] != '?' && data[sec_rem] != '#')
           ))
        {
            if(myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
               myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK)
            {
                url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
                return (data_size + 1);
            }
            
            myurl_path_shorten(&url_entry->path, url_entry->scheme.sid);
        }
        //else {
        //    // parse error
        //}
    }
    
    /* 4 */
    url->state = myurl_parser_state_path;
    return data_length;
}

size_t myurl_parser_state_file_slash(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1 */
    if(data_length < data_size && (data[data_length] == '/' || data[data_length] == '\\')) {
        //if(data[data_length] == '\\') {
        //    // parse error
        //}
        
        url->state = myurl_parser_state_file_host;
        return (data_length + 1);
    }
    
    /* 2 */
    if(url_base && url_base->scheme.sid == MyURL_SCHEME_ID_FILE && url_base->path.list &&
       myurl_utils_is_windows_drive_letter(url_base->path.list->data, 0, url_base->path.list->length))
    {
        /* 2.1 */
        if(myurl_path_append(url, &url_entry->path, url_base->path.list->data, url_base->path.list->length) == NULL) {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
    }
    
    /* 2.2 */
    url->state = myurl_parser_state_path;
    
    return data_length;
}

size_t myurl_parser_state_file_host(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if((data[data_length] == '/' || data[data_length] == '\\' || data[data_length] == '?' || data[data_length] == '#')) {
            return myurl_parser_state_file_host_end(url, url_entry, url_base, data, data_length, data_size);
        }
        
        data_length++;
    }
    
    // EOF code point
    return myurl_parser_state_file_host_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_path_start(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1 */
    if(url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) {
        /* 1.1 */
//        if(data[data_length] == '\\') {
//            // parse error
//            
//        }
        
        /* 1.2 */
        url->state = myurl_parser_state_path;
        url->begin = 0;
        
        /* 1.2 */
        if(data_length >= data_size || (data[data_length] != '/' && data[data_length] != '\\')) {
            return data_length;
        }
        
        return data_length + 1;
    }
    
    /* 4 */
    if(data_length >= data_size)
        return data_length;
    
    /* 2, 3 */
    if(url->state_override == NULL)
    {
        if(data[data_length] == '?') {
            myurl_utils_data_set_empty(url, &url_entry->query, &url_entry->query_length);
            
            url->state = myurl_parser_state_query;
            return (data_length + 1);
        }
        else if(data[data_length] == '#') {
            myurl_utils_data_set_empty(url, &url_entry->fragment, &url_entry->fragment_length);
            
            url->state = myurl_parser_state_fragment;
            return (data_length + 1);
        }
    }
    
    /* 4 */
    url->state = myurl_parser_state_path;
    
    if(data[data_length] != '/')
        return data_length;
    
    return (data_length + 1);
}

size_t myurl_parser_state_path(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if(
           (data[data_length] == '/') ||
           (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL && data[data_length] == '\\') ||
           (url->state_override == NULL && (data[data_length] == '?' || data[data_length] == '#'))
           )
        {
            data_length = myurl_parser_state_path_end(url, url_entry, url_base, data, data_length, data_size);
            
            if(url->state != myurl_parser_state_path)
                return data_length;
            
            url->begin = data_length;
        }
        else
            data_length++;
        
        /* 2 */
        /* 2.1 */
        // If c is not a URL code point and not "%", validation error.
        //if(data[data_length] == '%') {
        //    // parse error
        //}
        
        /* 2.2 */
        //if((data_length + 2) < data_size && data[data_length] == '%' &&
        //   (mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 1)] ] == 0xff ||
        //    mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 2)] ] == 0xff))
        //{
        //    // parse error
        //}
    }
    
    return myurl_parser_state_path_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_cannot_be_a_base_URL_path(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if(data[data_length] == '?')
        {
            /* 3.3 */
            if(url->begin < data_length) {
                myurl_parser_state_cannot_be_a_base_URL_path_end(url, url_entry, url_base, data, data_length, data_size);
                
                if(url_entry->status)
                    return (data_size + 1);
            }
            
            myurl_utils_data_set_empty(url, &url_entry->query, &url_entry->query_length);
            
            url->state = myurl_parser_state_query;
            url->begin = 0;
            
            return (data_length + 1);
        }
        
        /* 2 */
        if(data[data_length] == '#')
        {
            /* 3.3 */
            if(url->begin < data_length) {
                myurl_parser_state_cannot_be_a_base_URL_path_end(url, url_entry, url_base, data, data_length, data_size);
                
                if(url_entry->status)
                    return (data_size + 1);
            }
            
            myurl_utils_data_set_empty(url, &url_entry->fragment, &url_entry->fragment_length);
            
            url->state = myurl_parser_state_fragment;
            url->begin = 0;
            
            return (data_length + 1);
        }
        
        /* 3 */
        /* 3.1 */
        // TODO: If c is not EOF code point, not a URL code point, and not "%", validation error.
        //if(data[data_length] == '%') {
        //    // parse error
        //}
        
        /* 3.2 */
        //if((data_length + 2) < data_size && data[data_length] == '%' &&
        //   (mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 1)] ] == 0xff ||
        //    mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 2)] ] == 0xff))
        //{
        //    // parse error
        //}
        
        data_length++;
    }
    
    return myurl_parser_state_cannot_be_a_base_URL_path_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_query(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin == 0)
        url->begin = data_length;
    
    while(data_length < data_size)
    {
        /* 1 */
        if(url->state_override == NULL && data[data_length] == '#')
        {
            return myurl_parser_state_query_end(url, url_entry, url_base, data, data_length, data_size);
        }
        
        /* 2 */
        // TODO: If c is not a URL code point and not "%", validation error.
        //if(data[data_length] == '%') {
        //    // parse error
        //}
        
        /* 2.2 */
        //if((data_length + 2) < data_size && data[data_length] == '%' &&
        //   (mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 1)] ] == 0xff ||
        //    mycore_string_chars_hex_map[ (unsigned char)data[(data_length + 2)] ] == 0xff))
        //{
        //    // parse error
        //}
        
        data_length++;
    }
    
    // EOF code point
    return myurl_parser_state_query_end(url, url_entry, url_base, data, data_length, data_size);
}

size_t myurl_parser_state_fragment(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1.2, 1.3 */
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url, &data[ data_length ], (data_size - data_length),
                                                   myurl_resources_static_map_C0, &buffer_length);
    
    if(buffer == NULL) {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    url_entry->fragment = buffer;
    url_entry->fragment_length = buffer_length;
    
    return (data_size + 1);
}


