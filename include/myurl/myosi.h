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

#ifndef MyURL_MYOSI_H
#define MyURL_MYOSI_H
#pragma once

#include <myhtml/myosi.h>

#define MyURL_VERSION_MAJOR 0
#define MyURL_VERSION_MINOR 1
#define MyURL_VERSION_PATCH 0

#define MyURL_VERSION_STRING MyCORE_STR(MyURL_VERSION_MAJOR) MyCORE_STR(.) MyCORE_STR(MyURL_VERSION_MINOR) MyCORE_STR(.) MyCORE_STR(MyURL_VERSION_PATCH)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct myhtml_url myurl_t;
typedef struct myurl_entry myurl_entry_t;

typedef size_t (*myurl_state_f)(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
typedef void (*myurl_callback_serialization_func_f)(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
    
typedef void * (*myurl_callback_malloc_f)(size_t size, void *ctx);
typedef void * (*myurl_callback_realloc_f)(void* value, size_t size, void *ctx);
typedef void * (*myurl_callback_free_f)(void* value, void *ctx);

enum myurl_flags {
    MyURL_FLAGS_UNDEF              = 0x00,
    MyURL_FLAGS_AT                 = 0x01,
    MyURL_FLAGS_BRACKET            = 0x02,
    MyURL_FLAGS_CANNOT_BE_BASE_URL = 0x04
}
typedef myurl_flags_t;

/*
 See all senments of statuses in modest/myosi.h
 for myurl 038888..0388ff; MyURL_STATUS_OK == 0x000000
*/
enum myurl_status {
    MyURL_STATUS_OK                                      = 0x000000,
    MyURL_STATUS_ERROR                                   = 0x038888,
    MyURL_STATUS_ERROR_MEMORY_ALLOCATION                 = 0x038889,
    MyURL_STATUS_FAILURE_SCHEME_START                    = 0x03888a,
    MyURL_STATUS_FAILURE_SCHEME_STATE                    = 0x03888b,
    MyURL_STATUS_FAILURE_NO_SCHEME_BASE_NULL_OR_NOT_HASH = 0x03888c,
    MyURL_STATUS_FAILURE_AUTHORITY_HOST_AFTER_AUTH       = 0x03888d,
    MyURL_STATUS_FAILURE_UNEXPECTED_ENDING               = 0x03888e,
    MyURL_STATUS_FAILURE_BAD_HOSTNAME                    = 0x03888f,
    MyURL_STATUS_FAILURE_BAD_PORT                        = 0x038890,
    MyURL_STATUS_LAST_SEGMENT_ENTRY                      = 0x0388ff
}
typedef myurl_status_t;

void * myurl_callback_malloc(size_t size, void* ctx);
void * myurl_callback_realloc(void* value, size_t size, void* ctx);
void * myurl_callback_free(void* value, void* ctx);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_MYOSI_H */
