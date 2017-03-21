/*
 Copyright (C) 2016-2107 Alexander Borisov
 
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

#ifndef MyURL_H
#define MyURL_H
#pragma once

#include "myurl/myosi.h"
#include "myhtml/mystring.h"
#include "myurl/scheme.h"
#include "myurl/host.h"
#include "myurl/path.h"
#include "myurl/utils.h"
#include "myurl/serialization.h"

#ifdef __cplusplus
extern "C" {
#endif

struct myurl_entry {
    myurl_scheme_t scheme;
    myurl_host_t host;
    myurl_path_t path;
    
    char* username;
    size_t username_length;
    
    char* password;
    size_t password_length;
    
    unsigned int port;
    bool port_is_set;
    
    char* query;
    size_t query_length;
    
    char* fragment;
    size_t fragment_length;
    
    myurl_flags_t flags;
    mystatus_t status;
    
    myurl_t* url_ref;
};

struct myhtml_url {
    /* parser */
    myurl_state_f state;
    myurl_state_f state_override;
    myencoding_t  encoding;
    
    /* memory */
    myurl_callback_malloc_f  callback_malloc;
    myurl_callback_realloc_f callback_realloc;
    myurl_callback_free_f    callback_free;
    void* callback_ctx;
    
    /* work variables */
    size_t begin;
    /* if URL include '\t' or '\n', 
     then buffer copied removing all '\t' and '\n' */
    char *copy;
};

myurl_t * myurl_create(void);
mystatus_t myurl_init(myurl_t* url);
void myurl_clean(myurl_t* url);
myurl_t * myurl_destroy(myurl_t* url, bool self_destroy);

myurl_entry_t * myurl_parse(myurl_t* url, const char* data_url, size_t data_url_size, myurl_entry_t* base_url, mystatus_t* status);

myurl_entry_t * myurl_entry_create_and_init(myurl_t* url);
void myurl_entry_clean(myurl_entry_t* url_entry);
myurl_entry_t * myurl_entry_destroy(myurl_entry_t* url_entry, bool self_destroy);

/* api */
/* callback */
void myurl_callback_memory_set(myurl_t* url, myurl_callback_malloc_f callback_malloc, myurl_callback_realloc_f callback_realloc, myurl_callback_free_f callback_free, void* ctx);
void * myurl_callback_memory_context(myurl_t* url);

/* api entry */
/* for read */
mystatus_t myurl_entry_status(myurl_entry_t* url_entry);
myurl_flags_t myurl_entry_flags(myurl_entry_t* url_entry);
myurl_t * myurl_entry_url(myurl_entry_t* url_entry);

/* don't forget call 'myurl_entry_free_string' after use */
char * myurl_entry_as_string(myurl_entry_t* url_entry, size_t *length);
    
/* scheme */
myurl_scheme_t * myurl_entry_scheme(myurl_entry_t* url_entry);
const char * myurl_entry_scheme_name(myurl_entry_t* url_entry, size_t* length);
unsigned int myurl_entry_scheme_port(myurl_entry_t* url_entry);
myurl_scheme_id_t myurl_entry_scheme_id(myurl_entry_t* url_entry);
myurl_scheme_type_t myurl_entry_scheme_type(myurl_entry_t* url_entry);

/* authority */
/* don't forget call 'myurl_entry_free_string' after use */
char * myurl_entry_authority_as_string(myurl_entry_t* url_entry, size_t* length);

const char * myurl_entry_username(myurl_entry_t* url_entry, size_t* length);
const char * myurl_entry_password(myurl_entry_t* url_entry, size_t* length);

/* host */
myurl_host_t * myurl_entry_host(myurl_entry_t* url_entry);

/* don't forget call 'myurl_entry_free_string' after use */
char * myurl_entry_host_as_string(myurl_entry_t* url_entry, size_t *length);

myurl_host_type_t myurl_entry_host_type(myurl_entry_t* url_entry);
const char * myurl_entry_host_domain(myurl_entry_t* url_entry, size_t* length);
const char * myurl_entry_host_opaque(myurl_entry_t* url_entry, size_t* length);
unsigned int myurl_entry_host_ipv4(myurl_entry_t* url_entry);
unsigned int * myurl_entry_host_ipv6(myurl_entry_t* url_entry);

/* port */
bool myurl_entry_port_is_defined(myurl_entry_t* url_entry);
unsigned int myurl_entry_port(myurl_entry_t* url_entry);

/* path */
myurl_path_t * myurl_entry_path(myurl_entry_t* url_entry);

/* don't forget call 'myurl_entry_free_string' after use */
char * myurl_entry_path_as_string(myurl_entry_t* url_entry, size_t* length);
    
size_t myurl_entry_path_length(myurl_entry_t* url_entry);
const char * myurl_entry_path_entry(myurl_entry_t* url_entry, size_t index, size_t* length);

/* query */
const char * myurl_entry_query(myurl_entry_t* url_entry, size_t* length);

/* fragment */
const char * myurl_entry_fragment(myurl_entry_t* url_entry, size_t* length);

/* 
 For changes 
*/
/* scheme */
const char * myurl_entry_scheme_name_set(myurl_entry_t* url_entry, const char* name, size_t length);
void myurl_entry_scheme_port_set(myurl_entry_t* url_entry, unsigned int port);
void myurl_entry_scheme_id_set(myurl_entry_t* url_entry, myurl_scheme_id_t sid);
void myurl_entry_scheme_type_set(myurl_entry_t* url_entry, myurl_scheme_type_t type);
void myurl_entry_scheme_clean(myurl_entry_t* url_entry);

/* authority */
const char * myurl_entry_username_set(myurl_entry_t* url_entry, const char* username, size_t length);
const char * myurl_entry_password_set(myurl_entry_t* url_entry, const char* password, size_t length);

/* host */
mystatus_t myurl_entry_host_set(myurl_entry_t* url_entry, const char* host, size_t length);

/* port */
void myurl_entry_port_set(myurl_entry_t* url_entry, unsigned int port);

/* path */
mystatus_t myurl_entry_path_set(myurl_entry_t* url_entry, const char* path, size_t length);
mystatus_t myurl_entry_path_append_entry(myurl_entry_t* url_entry, const char* entry, size_t length);
void myurl_entry_path_pop_entry(myurl_entry_t* url_entry);
mystatus_t myurl_entry_path_replace_entry(myurl_entry_t* url_entry, size_t index, const char* entry, size_t length);
void myurl_entry_path_remove_entry(myurl_entry_t* url_entry, size_t index);
void myurl_entry_path_clean(myurl_entry_t* url_entry);

/* query */
const char * myurl_entry_query_set(myurl_entry_t* url_entry, const char* query, size_t length);

/* fragment */
const char * myurl_entry_fragment_set(myurl_entry_t* url_entry, const char* fragment, size_t length);

/* for free resources for char* */
void myurl_entry_free_string(myurl_entry_t* url_entry, char* string);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_H */


