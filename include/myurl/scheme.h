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

#ifndef MyURL_SCHEME_H
#define MyURL_SCHEME_H
#pragma once

#include <myurl/myosi.h>
#include <myurl/scheme_const.h>
#include <mycore/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

enum myurl_scheme_type {
    MyURL_SCHEME_TYPE_UNDEF   = 0x00,
    MyURL_SCHEME_TYPE_SPECIAL = 0x01,
    MyURL_SCHEME_TYPE_LOCAL   = 0x02,
    MyURL_SCHEME_TYPE_HTTP_S  = 0x04,
    MyURL_SCHEME_TYPE_NETWORK = 0x08,
    MyURL_SCHEME_TYPE_FETCH   = 0x10
}
typedef myurl_scheme_type_t;

struct myurl_scheme {
    char* name;
    size_t length;
    size_t port;
    
    myurl_scheme_id_t sid;
    myurl_scheme_type_t type;
}
typedef myurl_scheme_t;

struct myurl_scheme_entry {
    const char* name;
    size_t name_length;
    
    myurl_scheme_id_t m_id;
    size_t port;
    myurl_scheme_type_t type;
    
    size_t next;
    size_t curr;
}
typedef myurl_scheme_entry_t;

void myurl_scheme_clean(myurl_t* url, myurl_scheme_t* scheme);
myurl_scheme_t * myurl_scheme_destroy(myurl_t* url, myurl_scheme_t* scheme, bool self_destroy);

const myurl_scheme_entry_t * myurl_scheme_find_entry(const char* name, size_t length);
myurl_scheme_id_t myurl_scheme_id_by_name(const char *name, size_t length);

mystatus_t myurl_scheme_copy(myurl_t* url, myurl_scheme_t* from, myurl_scheme_t* to);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_SCHEME_H */
