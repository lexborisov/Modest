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

size_t myurl_parser_state_relative_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(myurl_parser_copy_attr(url, url_base, url_entry, username) != MyURL_STATUS_OK ||
       myurl_parser_copy_attr(url, url_base, url_entry, password) != MyURL_STATUS_OK ||
       myurl_parser_copy_attr(url, url_base, url_entry, query)    != MyURL_STATUS_OK ||
       myurl_host_copy(url, &url_base->host, &url_entry->host)    != MyURL_STATUS_OK ||
       myurl_path_copy(url, &url_base->path, &url_entry->path)    != MyURL_STATUS_OK)
    {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    url_entry->port = url_base->port;
    url_entry->port_is_set = url_base->port_is_set;
    
    return data_size;
}

size_t myurl_parser_state_authority_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if((url_entry->flags & MyURL_FLAGS_AT) && (data_length - url->begin) == 0) {
        // parse error
        url_entry->status = MyURL_STATUS_FAILURE_AUTHORITY_HOST_AFTER_AUTH;
        return (data_size + 1);
    }
    
    data_length -= (data_length - url->begin);
    
    url->state = myurl_parser_state_host_hostname;
    url->begin = 0;
    
    return data_length;
}

size_t myurl_parser_state_host_hostname_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 3.1 */
    if((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) && (data_length - url->begin) == 0) {
        // parse error
        url_entry->status = MyURL_STATUS_FAILURE_UNEXPECTED_ENDING;
        return (data_size + 1);
    }
    
    /* 3.2 */
    if(url->state_override && (data_length - url->begin) == 0 &&
       (myurl_parser_is_includes_credentials(url_entry) || url_entry->port_is_set))
    {
        // parse error
        return (data_size + 1);
    }
    
    /* 3.3 and 3.4 */
    if(myurl_host_parser(url, &url_entry->host, &data[url->begin], (data_length - url->begin),
                              (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL)))
    {
        url_entry->status = MyURL_STATUS_FAILURE_BAD_HOSTNAME;
        return (data_size + 1);
    }
    
    /* 3.6 */
    if(url->state_override)
        return (data_size + 1);
    
    /* 3.5 */
    url->state = myurl_parser_state_port;
    url->begin = 0;
    
    return data_length;
}

size_t myurl_parser_state_port_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 2.1 */
    if((data_length - url->begin))
    {
        size_t len = url->begin;
        unsigned int port = 0;
        
        /* 2.1.1 */
        while(len < data_length)
        {
            if(port > 65535) {
                url_entry->status = MyURL_STATUS_FAILURE_BAD_PORT;
                return (data_size + 1);
            }
            
            port = mycore_string_chars_num_map[ (unsigned char)data[len] ] + port * 10;
            len++;
        }
        
        /* 2.1.3 */
        if(url_entry->scheme.port != port) {
            url_entry->port = port;
            url_entry->port_is_set = true;
        }
    }
    
    /* for all 2.1.4 */
    url->begin = 0;
    
    /* 2.2 */
    if(url->state_override)
        return (data_size + 1);
    
    /* 2.3 */
    url->state = myurl_parser_state_path_start;
    
    return data_length;
}

size_t myurl_parser_state_file_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(myurl_host_copy(url, &url_base->host, &url_entry->host) != MyURL_STATUS_OK ||
       myurl_path_copy(url, &url_base->path, &url_entry->path) != MyURL_STATUS_OK ||
       myurl_parser_copy_attr(url, url_base, url_entry, query) != MyURL_STATUS_OK)
    {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    return data_size;
}

size_t myurl_parser_state_file_host_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1.1 */
    if(url->state_override == NULL && myurl_utils_is_windows_drive_letter(data, url->begin, data_size)) {
        url->state = myurl_parser_state_path;
        return data_length;
    }
    
    /* 1.2 */
    if((data_length <= url->begin)) {
        /* 1.2.1 */
        myurl_host_clean(url, &url_entry->host);
        
        /* 1.2.2 */
        if(url->state_override)
            return (data_size + 1);
        
        /* 1.2.3 */
        url->state = myurl_parser_state_path_start;
        return data_length;
    }
    
    /* 1.3 */
    if(myurl_host_parser(url, &url_entry->host, &data[url->begin], (data_length - url->begin), (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL))) {
        url_entry->status = MyURL_STATUS_FAILURE_BAD_HOSTNAME;
        return (data_size + 1);
    }
    
    /* 1.3.3 */
    if(url_entry->host.type == MyURL_HOST_TYPE_DOMAIN &&
       url_entry->host.value.domain.length == 9 &&
       mycore_strncasecmp("localhost", url_entry->host.value.domain.value, url_entry->host.value.domain.length) == 0)
    {
        myurl_host_clean(url, &url_entry->host);
    }
    
    /* 1.3.5 */
    if(url->state_override)
        return (data_size + 1);
    
    /* 2.1.6 */
    url->begin = 0;
    url->state = myurl_parser_state_path_start;
    
    return data_length;
}

size_t myurl_parser_state_path_start_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    return data_size;
}

size_t myurl_parser_state_path_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1.1 */
    //if(url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL && data[data_length] == '\\') {
    //    // parse error
    //}
    
    /* 1.2 */
    if(myurl_utils_is_double_dot_path_segment(&data[ url->begin ], (data_length - url->begin)))
    {
        myurl_path_shorten(&url_entry->path, url_entry->scheme.sid);
        
        if(data_length >= data_size || (data[data_length] != '/' &&
          (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL && data[data_length] == '\\') == 0))
        {
            if(myurl_path_push(url, &url_entry->path, NULL, 0) == NULL) {
                url_entry->status = MyURL_STATUS_ERROR;
                return (data_size + 1);
            }
        }
    }
    
    /* 1.3 */
    else if(myurl_utils_is_single_dot_path_segment(&data[ url->begin ], (data_length - url->begin)))
    {
        if(data_length >= data_size || (data[data_length] != '/' &&
           (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL && data[data_length] == '\\') == 0))
        {
            if(myurl_path_push(url, &url_entry->path, NULL, 0) == NULL) {
                url_entry->status = MyURL_STATUS_ERROR;
                return (data_size + 1);
            }
        }
    }
    
    /* 1.4 */
    else {
        bool second_replace = false;
        /* 1.4.1 */
        if(url_entry->scheme.sid == MyURL_SCHEME_ID_FILE && url_entry->path.length == 0 &&
           myurl_utils_is_windows_drive_letter(data, url->begin, data_length))
        {
            /* 1.4.1.1 */
            //if(url_entry->host.type != MyURL_HOST_TYPE_UNDEF) {
            //    // parse error
            //}
            
            /* 1.4.1.2 */
            myurl_host_clean(url, &url_entry->host);
            second_replace = true;
        }
        
        /* 1.4.2 */
        size_t buffer_length;
        char *buffer = myurl_utils_percent_encode(url, &data[ url->begin ], (data_length - url->begin),
                                                       myurl_resources_static_map_path, &buffer_length);
        
        if(buffer == NULL) {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
        
        if(myurl_path_push(url, &url_entry->path, buffer, buffer_length) == NULL) {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
        
        /* 1.4.1.2 */
        if(second_replace && buffer_length > 1) {
            buffer[1] = ':';
        }
    }
    
    /* 1.5 */
    url->begin = 0;
    
    if(data_length < data_size) {
        /* 1.6 */
        if(data[data_length] == '?') {
            myurl_utils_data_set_null(url, &url_entry->query, &url_entry->query_length);
            url->state = myurl_parser_state_query;
        }
        /* 1.7 */
        if(data[data_length] == '#') {
            myurl_utils_data_set_null(url, &url_entry->fragment, &url_entry->fragment_length);
            url->state = myurl_parser_state_fragment;
        }
    }
    
    return (data_length + 1);
}

size_t myurl_parser_state_cannot_be_a_base_URL_path_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    if(url->begin < data_length) {
        size_t buffer_length;
        char *buffer = myurl_utils_percent_encode(url, &data[ url->begin ], (data_length - url->begin),
                                                       myurl_resources_static_map_C0, &buffer_length);
        
        if(buffer == NULL) {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
        
        if(myurl_path_push(url, &url_entry->path, buffer, buffer_length) == NULL) {
            url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
            return (data_size + 1);
        }
    }
    
    return (data_size + 1);
}

size_t myurl_parser_state_query_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size)
{
    /* 1.1 */
    if((url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL) == 0 ||
       url_entry->scheme.sid == MyURL_SCHEME_ID_WS ||
       url_entry->scheme.sid == MyURL_SCHEME_ID_WSS)
    {
        url->encoding = MyENCODING_UTF_8;
    }
    
    /* 1.2, 1.3 */
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url, &data[ url->begin ], (data_length - url->begin),
                                                   myurl_resources_static_map_query_charset, &buffer_length);
    
    if(buffer == NULL) {
        url_entry->status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        return (data_size + 1);
    }
    
    url_entry->query = buffer;
    url_entry->query_length = buffer_length;
    
    /* 1.4 */
    url->begin = 0;
    
    /* 1.5 */
    myurl_utils_data_set_null(url, &url_entry->fragment, &url_entry->fragment_length);
    url->state = myurl_parser_state_fragment;
    
    return (data_length + 1);
}


