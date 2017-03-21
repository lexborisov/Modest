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
#include "myhtml/serialization.h"

void myurl_serialization_host(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    switch (url_entry->host.type) {
        case MyURL_HOST_TYPE_DOMAIN:
            callback(url_entry->host.value.domain.value, url_entry->host.value.domain.length, ctx);
            break;
            
        case MyURL_HOST_TYPE_IPv4: {
            char digit_buffer[6];
            char buffer[17] = {0};
            
            size_t ipv4_length = 12 + 4;
            size_t digit_size = 0;
            
            unsigned int n = url_entry->host.value.ipv.pieces[0];
            
            for(size_t i = 0; i < 4; i++)
            {
                digit_size = myurl_convert_integer_to_data_without_check_buffer(n % 256, digit_buffer);
                
                if(digit_size <= ipv4_length) {
                    ipv4_length -= digit_size;
                    
                    memcpy(&buffer[ipv4_length], digit_buffer, sizeof(char) * digit_size);
                }
                
                if(ipv4_length && i != 3) {
                    ipv4_length--;
                    buffer[ipv4_length] = '.';
                }
                
                n = (unsigned int)floor((double)n / 256.0f);
            }
            
            callback(&buffer[ipv4_length], (16 - ipv4_length), ctx);
            break;
        }
            
        case MyURL_HOST_TYPE_IPv6: {
            callback("[", 1, ctx);
            
            /* 1 */
            unsigned int *pieces = url_entry->host.value.ipv.pieces;
            unsigned int *compress_pointer = NULL;
            
            char buffer[128] = {0};
            
            /* 2, 3 */
            for(size_t i = 0; i < 7; i++) {
                if(pieces[i] == 0 && pieces[(i + 1)] == 0) {
                    compress_pointer = &pieces[i];
                    break;
                }
            }
            
            /* 4 */
            for(size_t i = 0; i < 8; i++) {
                /* 4.1 */
                if(compress_pointer == &pieces[i]) {
                    
                    
                    if(i == 0)
                        callback("::", 2, ctx);
                    else
                        callback(":", 1, ctx);
                    
                    i++;
                    while(i < 8) {
                        if(pieces[i] != 0) {
                            i--;
                            break;
                        }
                        
                        i++;
                    }
                }
                else {
                    /* 4.2 */
                    size_t len = myurl_convert_integer_to_hex_data_without_check_buffer((long)pieces[i], buffer);
                    callback(buffer, len, ctx);
                    
                    /* 4.3 */
                    if(i != 7)
                        callback(":", 1, ctx);
                }
            }
            
            callback("]", 1, ctx);
            
            break;
        }
            
        case MyURL_HOST_TYPE_OPAQUE:
            callback(url_entry->host.value.opaque.value, url_entry->host.value.opaque.length, ctx);
            break;
            
        default:
            break;
    }
}

void myurl_serialization_authority(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    if(url_entry->username_length || url_entry->password_length) {
        callback(url_entry->username, url_entry->username_length, ctx);
        
        if(url_entry->password_length) {
            callback(":", 1, ctx);
            callback(url_entry->password, url_entry->password_length, ctx);
        }
    }
}

void myurl_serialization_auth_host_port(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    callback("//", 2, ctx);
    
    if(url_entry->username_length || url_entry->password_length) {
        myurl_serialization_authority(url_entry, callback, ctx);
        callback("@", 1, ctx);
    }
    
    myurl_serialization_host(url_entry, callback, ctx);
    
    if(url_entry->port_is_set) {
        callback(":", 1, ctx);
        
        char return_str[128] = {0};
        size_t length = myurl_convert_integer_to_data_without_check_buffer((long)url_entry->port, return_str);
        
        callback(return_str, length, ctx);
    }
}

void myurl_serialization_path(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    if(url_entry->flags & MyURL_FLAGS_CANNOT_BE_BASE_URL) {
        callback(url_entry->path.list[0].data, url_entry->path.list[0].length, ctx);
    }
    else {
        for(size_t i = 0; i < url_entry->path.length; i++) {
            callback("/", 1, ctx);
            callback(url_entry->path.list[i].data, url_entry->path.list[i].length, ctx);
        }
    }
}

void myurl_serialization_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    if(url_entry->fragment && url_entry->fragment_length)
        callback(url_entry->fragment, url_entry->fragment_length, ctx);
}

void myurl_serialization_without_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    if(url_entry->scheme.name)
        callback(url_entry->scheme.name, url_entry->scheme.length, ctx);
    
    callback(":", 1, ctx);
    
    if(url_entry->host.type) {
        myurl_serialization_auth_host_port(url_entry, callback, ctx);
    }
    else if(url_entry->scheme.sid == MyURL_SCHEME_ID_FILE) {
        callback("//", 2, ctx);
    }
    
    myurl_serialization_path(url_entry, callback, ctx);
    
    if(url_entry->query != NULL) {
        callback("?", 1, ctx);
        
        if(url_entry->query_length)
            callback(url_entry->query, url_entry->query_length, ctx);
    }
}

void myurl_serialization_with_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx)
{
    myurl_serialization_without_fragment(url_entry, callback, ctx);
    
    if(url_entry->fragment != NULL) {
        callback("#", 1, ctx);
        
        if(url_entry->fragment_length)
            callback(url_entry->fragment, url_entry->fragment_length, ctx);
    }
}

void myurl_serialization(myurl_entry_t* url_entry, bool exclude_fragment_flag, mycore_callback_serialize_f callback, void* ctx)
{
    if(exclude_fragment_flag)
        myurl_serialization_without_fragment(url_entry, callback, ctx);
    else
        myurl_serialization_with_fragment(url_entry, callback, ctx);
}


