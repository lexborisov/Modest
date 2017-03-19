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
#include "myurl/resources.h"

myurl_t * myurl_create(void)
{
    return mycore_calloc(1, sizeof(myurl_t));
}

mystatus_t myurl_init(myurl_t* url)
{
    url->callback_malloc  = myurl_callback_malloc;
    url->callback_free    = myurl_callback_free;
    url->callback_realloc = myurl_callback_realloc;
    url->callback_ctx     = url;
    
    return MyURL_STATUS_OK;
}

void myurl_clean(myurl_t* url)
{
    memset(url, 0, sizeof(myurl_t));
}

myurl_t * myurl_destroy(myurl_t* url, bool self_destroy)
{
    if(url == NULL)
        return NULL;
    
    if(self_destroy) {
        mycore_free(url);
        return NULL;
    }
    
    return url;
}

/*
 * Entry
 */
myurl_entry_t * myurl_entry_create_and_init(myurl_t* url)
{
    myurl_entry_t *entry = url->callback_malloc(sizeof(myurl_entry_t), url->callback_ctx);
    if(entry == NULL)
        return NULL;
    
    memset(entry, 0, sizeof(myurl_entry_t));
    
    if(myurl_path_init(url, &entry->path, 56) != MyURL_STATUS_OK) {
        return url->callback_free(entry, url->callback_ctx);
    }
    
    entry->url_ref = url;
    
    return entry;
}

void myurl_entry_clean(myurl_entry_t* url_entry)
{
    myurl_t* url = url_entry->url_ref;
    
    if(url_entry->username)
        url->callback_free(url_entry->username, url->callback_ctx);
    
    if(url_entry->password)
        url->callback_free(url_entry->password, url->callback_ctx);
    
    if(url_entry->query)
        url->callback_free(url_entry->query, url->callback_ctx);
    
    if(url_entry->fragment)
        url->callback_free(url_entry->fragment, url->callback_ctx);
    
    myurl_host_destroy(url, &url_entry->host, false);
    myurl_path_destroy(url, &url_entry->path, false);
    myurl_scheme_destroy(url, &url_entry->scheme, false);
    
    memset(url_entry, 0, sizeof(myurl_entry_t));
    
    url_entry->url_ref = url;
}

myurl_entry_t * myurl_entry_destroy(myurl_entry_t* url_entry, bool self_destroy)
{
    if(url_entry == NULL)
        return NULL;
    
    myurl_entry_clean(url_entry);
    
    if(self_destroy) {
        return url_entry->url_ref->callback_free(url_entry, url_entry->url_ref->callback_ctx);
    }
    
    return url_entry;
}

/*
 * The CODE
 */
myurl_entry_t * myurl_parse(myurl_t* url, const char* data_url, size_t data_url_size, myurl_entry_t* base_url, mystatus_t* status)
{
    myurl_entry_t* entry = myurl_entry_create_and_init(url);
    
    if(entry == NULL) {
        if(status)
            *status = MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        
        return NULL;
    }
    
    myurl_parser_begin(url, entry, base_url, data_url, data_url_size);
    
    if(status)
        *status = entry->status;
    
    if(entry->status)
        return myurl_entry_destroy(entry, true);
    
    return entry;
}

/* api */
/* callback */
void myurl_callback_memory_set(myurl_t* url, myurl_callback_malloc_f callback_malloc, myurl_callback_realloc_f callback_realloc, myurl_callback_free_f callback_free, void* ctx)
{
    if(callback_malloc)
        url->callback_malloc = callback_malloc;
    else
        url->callback_malloc = myurl_callback_malloc;
    
    if(callback_realloc)
        url->callback_realloc = callback_realloc;
    else
        url->callback_realloc = myurl_callback_realloc;
    
    if(callback_free)
        url->callback_free = callback_free;
    else
        url->callback_free = myurl_callback_free;
    
    if(ctx)
        url->callback_ctx = ctx;
    else
        url->callback_ctx = url;
}

void * myurl_callback_memory_context(myurl_t* url)
{
    return url->callback_ctx;
}

/* api entry */
/* callback for as_string */
static mystatus_t myurl_entry_host_callback_for_as_string(const char* data, size_t len, void* ctx)
{
    myurl_utils_serialization_ctx_t *obj_ctx = ctx;
    
    if(obj_ctx->error)
        return MyCORE_STATUS_ERROR;
    
    if((obj_ctx->length + len + 1) >= obj_ctx->size) {
        size_t new_size = obj_ctx->length + len + 128;
        
        char *tmp = obj_ctx->url->callback_realloc(obj_ctx->data, sizeof(char) * new_size,
                                                   obj_ctx->url->callback_ctx);
        
        if(tmp) {
            obj_ctx->size = new_size;
            obj_ctx->data = tmp;
        }
        else
            obj_ctx->error = true;
    }
    
    memcpy(&obj_ctx->data[ obj_ctx->length ], data, sizeof(char) * len);
    obj_ctx->length += len;
    
    return MyCORE_STATUS_OK;
}

static char * myurl_as_string(myurl_entry_t* url_entry, size_t *length, myurl_callback_serialization_func_f func)
{
    if(length)
        *length = 0;
    
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    myurl_utils_serialization_ctx_t ctx = {0};
    
    ctx.size = 128;
    ctx.data = url->callback_malloc(sizeof(char) * ctx.size, url->callback_ctx);
    ctx.url  = url;
    
    if(ctx.data == NULL)
        return NULL;
    
    func(url_entry, myurl_entry_host_callback_for_as_string, &ctx);
    
    if(ctx.error) {
        if(ctx.data)
            return url->callback_free(ctx.data, url->callback_ctx);
        
        return NULL;
    }
    
    if(length)
        *length = ctx.length;
    
    ctx.data[ ctx.length ] = '\0';
    
    return ctx.data;
}

mystatus_t myurl_entry_status(myurl_entry_t* url_entry)
{
    return url_entry->status;
}

myurl_flags_t myurl_entry_flags(myurl_entry_t* url_entry)
{
    return url_entry->flags;
}

myurl_t * myurl_entry_url(myurl_entry_t* url_entry)
{
    return url_entry->url_ref;
}

char * myurl_entry_as_string(myurl_entry_t* url_entry, size_t *length)
{
    return myurl_as_string(url_entry, length, myurl_serialization_with_fragment);
}

/* scheme */
myurl_scheme_t * myurl_entry_scheme(myurl_entry_t* url_entry)
{
    return &url_entry->scheme;
}

const char * myurl_entry_scheme_name(myurl_entry_t* url_entry, size_t* length)
{
    if(length)
        *length = url_entry->scheme.length;
    
    return url_entry->scheme.name;
}

unsigned int myurl_entry_scheme_port(myurl_entry_t* url_entry)
{
    return (unsigned int)url_entry->scheme.port;
}

myurl_scheme_id_t myurl_entry_scheme_id(myurl_entry_t* url_entry)
{
    return url_entry->scheme.sid;
}

myurl_scheme_type_t myurl_entry_scheme_type(myurl_entry_t* url_entry)
{
    return url_entry->scheme.type;
}

/* authority */
char * myurl_entry_authority_as_string(myurl_entry_t* url_entry, size_t* length)
{
    return myurl_as_string(url_entry, length, myurl_serialization_authority);
}

const char * myurl_entry_username(myurl_entry_t* url_entry, size_t *length)
{
    if(length)
        *length = url_entry->username_length;
    
    return url_entry->username;
}

const char * myurl_entry_password(myurl_entry_t* url_entry, size_t *length)
{
    if(length)
        *length = url_entry->password_length;
    
    return url_entry->password;
}

/* host */
myurl_host_t * myurl_entry_host(myurl_entry_t* url_entry)
{
    return &url_entry->host;
}

char * myurl_entry_host_as_string(myurl_entry_t* url_entry, size_t *length)
{
    return myurl_as_string(url_entry, length, myurl_serialization_host);
}

myurl_host_type_t myurl_entry_host_type(myurl_entry_t* url_entry)
{
    return url_entry->host.type;
}

const char * myurl_entry_host_domain(myurl_entry_t* url_entry, size_t *length)
{
    if(url_entry->host.type != MyURL_HOST_TYPE_DOMAIN) {
        if(length)
            *length = 0;
        
        return NULL;
    }
        
    if(length)
        *length = url_entry->host.value.domain.length;
    
    return url_entry->host.value.domain.value;
}

const char * myurl_entry_host_opaque(myurl_entry_t* url_entry, size_t *length)
{
    if(url_entry->host.type != MyURL_HOST_TYPE_OPAQUE) {
        if(length)
            *length = 0;
        
        return NULL;
    }
    
    if(length)
        *length = url_entry->host.value.opaque.length;
    
    return url_entry->host.value.opaque.value;
}

unsigned int myurl_entry_host_ipv4(myurl_entry_t* url_entry)
{
    if(url_entry->host.type != MyURL_HOST_TYPE_IPv4)
        return 0;
    
    return url_entry->host.value.ipv.pieces[0];
}

unsigned int * myurl_entry_host_ipv6(myurl_entry_t* url_entry)
{
    if(url_entry->host.type != MyURL_HOST_TYPE_IPv6)
        return NULL;
    
    return url_entry->host.value.ipv.pieces;
}

/* port */
bool myurl_entry_port_is_defined(myurl_entry_t* url_entry)
{
    return url_entry->port_is_set;
}

unsigned int myurl_entry_port(myurl_entry_t* url_entry)
{
    return url_entry->port;
}

/* path */
myurl_path_t * myurl_entry_path(myurl_entry_t* url_entry)
{
    return &url_entry->path;
}

char * myurl_entry_path_as_string(myurl_entry_t* url_entry, size_t* length)
{
    return myurl_as_string(url_entry, length, myurl_serialization_path);
}

size_t myurl_entry_path_length(myurl_entry_t* url_entry)
{
    return url_entry->path.length;
}

const char * myurl_entry_path_entry(myurl_entry_t* url_entry, size_t index, size_t *length)
{
    if(url_entry->path.length < index) {
        if(length)
            *length = 0;
        
        return NULL;
    }
    
    if(length)
        *length = url_entry->path.list[index].length;
    
    return url_entry->path.list[index].data;
}

/* query */
const char * myurl_entry_query(myurl_entry_t* url_entry, size_t *length)
{
    if(length)
        *length = url_entry->query_length;
    
    return url_entry->query;
}

/* fragment */
const char * myurl_entry_fragment(myurl_entry_t* url_entry, size_t *length)
{
    if(length)
        *length = url_entry->fragment_length;
    
    return url_entry->fragment;
}

/* 
 For changes
*/
/* scheme */
const char * myurl_entry_scheme_name_set(myurl_entry_t* url_entry, const char* name, size_t length)
{
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    
    if(myurl_utils_data_copy_set(url, name, length, &url_entry->scheme.name, &url_entry->scheme.length))
        return NULL;
    
    return url_entry->scheme.name;
}

void myurl_entry_scheme_port_set(myurl_entry_t* url_entry, unsigned int port)
{
    url_entry->scheme.port = port;
}

void myurl_entry_scheme_id_set(myurl_entry_t* url_entry, myurl_scheme_id_t sid)
{
    url_entry->scheme.sid = sid;
}

void myurl_entry_scheme_type_set(myurl_entry_t* url_entry, myurl_scheme_type_t type)
{
    url_entry->scheme.type = type;
}

void myurl_entry_scheme_clean(myurl_entry_t* url_entry)
{
    if(url_entry->url_ref)
        myurl_scheme_clean(url_entry->url_ref, &url_entry->scheme);
}

/* authority */
const char * myurl_entry_username_set(myurl_entry_t* url_entry, const char* username, size_t length)
{
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    
    if(myurl_utils_data_copy_set(url, username, length, &url_entry->username, &url_entry->username_length))
        return NULL;
    
    return url_entry->username;
}

const char * myurl_entry_password_set(myurl_entry_t* url_entry, const char* password, size_t length)
{
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    
    if(myurl_utils_data_copy_set(url, password, length, &url_entry->password, &url_entry->password_length))
        return NULL;
    
    return url_entry->password;
}

/* host */
mystatus_t myurl_entry_host_set(myurl_entry_t* url_entry, const char* host, size_t length)
{
    if(url_entry->url_ref == NULL)
        return MyURL_STATUS_ERROR;
    
    myurl_host_t new_host;
    memset(&new_host, 0, sizeof(myurl_host_t));
    
    mystatus_t status = myurl_host_parser(url_entry->url_ref, &new_host, host, length, (url_entry->scheme.type & MyURL_SCHEME_TYPE_SPECIAL));
    
    if(status)
        return status;
    
    myurl_host_clean(url_entry->url_ref, &url_entry->host);
    url_entry->host = new_host;
    
    return status;
}

/* port */
void myurl_entry_port_set(myurl_entry_t* url_entry, unsigned int port)
{
    url_entry->port = port;
    url_entry->port_is_set = true;
}

/* path */
mystatus_t myurl_entry_path_set(myurl_entry_t* url_entry, const char* path, size_t length)
{
    if(url_entry->url_ref == NULL || path == NULL)
        return MyURL_STATUS_ERROR;
    
    mystatus_t status;
    myurl_entry_t *new_entry = myurl_parse(url_entry->url_ref, path, length, url_entry, &status);
    
    if(new_entry) {
        status = myurl_path_copy(url_entry->url_ref, &new_entry->path, &url_entry->path);
        
        myurl_entry_destroy(new_entry, true);
    }
    
    return status;
}

mystatus_t myurl_entry_path_append_entry(myurl_entry_t* url_entry, const char* entry, size_t length)
{
    if(url_entry->url_ref == NULL || entry == NULL)
        return MyURL_STATUS_ERROR;
    
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url_entry->url_ref, entry, length, myurl_resources_static_map_path, &buffer_length);
    
    if(buffer == NULL)
        return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if(myurl_path_push(url_entry->url_ref, &url_entry->path, buffer, buffer_length) == NULL)
        return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    
    return MyURL_STATUS_OK;
}

void myurl_entry_path_pop_entry(myurl_entry_t* url_entry)
{
    myurl_path_pop(&url_entry->path);
}

mystatus_t myurl_entry_path_replace_entry(myurl_entry_t* url_entry, size_t index, const char* entry, size_t length)
{
    if(url_entry->url_ref == NULL || entry == NULL)
        return MyURL_STATUS_ERROR;
    
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url_entry->url_ref, entry, length, myurl_resources_static_map_path, &buffer_length);
    
    if(buffer == NULL)
        return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if(myurl_path_push_to_index(url_entry->url_ref, &url_entry->path, index, buffer, buffer_length) == NULL)
        return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    
    return MyURL_STATUS_OK;
}

void myurl_entry_path_remove_entry(myurl_entry_t* url_entry, size_t index)
{
    if(url_entry->url_ref == NULL)
        return;
    
    myurl_path_remove_by_index(url_entry->url_ref, &url_entry->path, index);
}

void myurl_entry_path_clean(myurl_entry_t* url_entry)
{
    if(url_entry->url_ref == NULL)
        return;
    
    myurl_path_clean(url_entry->url_ref, &url_entry->path);
}

/* query */
const char * myurl_entry_query_set(myurl_entry_t* url_entry, const char* query, size_t length)
{
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url, query, length, myurl_resources_static_map_query_charset, &buffer_length);
    
    if(buffer == NULL)
        return NULL;
    
    if(url_entry->query)
        url->callback_free(url_entry->query, url->callback_ctx);
    
    url_entry->query = buffer;
    url_entry->query_length = buffer_length;
    
    return url_entry->query;
}

/* fragment */
const char * myurl_entry_fragment_set(myurl_entry_t* url_entry, const char* fragment, size_t length)
{
    if(url_entry->url_ref == NULL)
        return NULL;
    
    myurl_t* url = url_entry->url_ref;
    
    size_t buffer_length;
    char *buffer = myurl_utils_percent_encode(url, fragment, length, myurl_resources_static_map_C0, &buffer_length);
    
    if(buffer == NULL)
        return NULL;
    
    if(url_entry->fragment)
        url->callback_free(url_entry->fragment, url->callback_ctx);
    
    url_entry->fragment = buffer;
    url_entry->fragment_length = buffer_length;
    
    return url_entry->fragment;
}

/* for free char* */
void myurl_entry_free_string(myurl_entry_t* url_entry, char* string)
{
    if(url_entry->url_ref == NULL)
        return;
    
    if(string)
        url_entry->url_ref->callback_free(string, url_entry->url_ref->callback_ctx);
}


