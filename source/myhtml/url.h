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

#ifndef MyHTML_URL_H
#define MyHTML_URL_H
#pragma once

#ifdef __cplusplus
//extern "C" {
#endif
    
#include "myhtml/myosi.h"
#include "myhtml/mystring.h"
#include "myhtml/url/scheme.h"

typedef struct myhtml_url myhtml_url_t;

struct myhtml_url {
    const myhtml_url_scheme_entry_t* scheme;
    
    char* href;
    char* origin;
    char* protocol;
    char* username;
    char* password;
    char* host;
    char* hostname;
    char* port;
    char* pathname;
    char* search;
    char* hash;
    
    mchar_async_t* mchar;
    size_t node_idx;
};

myhtml_status_t myhtml_url_parse(myhtml_url_t* url, mchar_async_t* mchar, size_t node_id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_URL_H */
