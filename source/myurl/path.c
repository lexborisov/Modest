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

#include "myurl/path.h"
#include "myurl/url.h"

myurl_path_t * myurl_path_create(myurl_t* url)
{
    myurl_path_t *path = url->callback_malloc(sizeof(myurl_path_t), url->callback_ctx);
    
    if(path)
        memset(path, 0, sizeof(myurl_path_t));
    
    return path;
}

mystatus_t myurl_path_init(myurl_t* url, myurl_path_t* path, size_t begin_size)
{
    if(begin_size == 0)
        return MyURL_STATUS_ERROR;
    
    path->length = 0;
    path->size   = begin_size;
    path->list   = url->callback_malloc(sizeof(myurl_path_entry_t) * path->size, url->callback_ctx);
    
    if(path->list == NULL)
        return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    
    memset(path->list, 0, sizeof(myurl_path_entry_t) * path->size);
    
    return MyURL_STATUS_OK;
}

void myurl_path_clean(myurl_t* url, myurl_path_t* path)
{
    for(size_t i = 0; i < path->length; i++) {
        if(path->list[i].data) {
            url->callback_free(path->list[i].data, url->callback_ctx);
        }
    }
    
    path->length = 0;
}

myurl_path_entry_t * myurl_path_entry_destroy(myurl_t* url, myurl_path_entry_t* path, bool destroy_self)
{
    if(path == NULL)
        return NULL;
    
    if(path->data)
        url->callback_free(path->data, url->callback_ctx);
    
    if(destroy_self) {
        url->callback_free(path, url->callback_ctx);
        return NULL;
    }
    
    return path;
}

myurl_path_t * myurl_path_destroy(myurl_t* url, myurl_path_t* path, bool destroy_self)
{
    if(path == NULL)
        return NULL;
    
    if(path->list) {
        myurl_path_clean(url, path);
        url->callback_free(path->list, url->callback_ctx);
    }
    
    if(destroy_self && path) {
        return url->callback_free(path, url->callback_ctx);
    }
    
    return path;
}

myurl_path_entry_t * myurl_path_append(myurl_t* url, myurl_path_t* path, const char* data, size_t length)
{
    if(path->length >= path->size) {
        size_t new_size = path->length + 1024;
        
        myurl_path_entry_t *tmp = url->callback_realloc(path->list, sizeof(myurl_path_entry_t) * new_size, url->callback_ctx);
        
        if(tmp) {
            memset(&tmp[path->length], 0, sizeof(myurl_path_entry_t) * (new_size - path->length));
            
            path->list = tmp;
            path->size = new_size;
        }
        else
            return NULL;
    }
    
    myurl_path_entry_t *entry = &path->list[ path->length ];
    path->length++;
    
    if(length) {
        entry->data = url->callback_malloc(sizeof(char) * length, url->callback_ctx);
        
        if(entry->data == NULL)
            return NULL;
        
        memcpy(entry->data, data, sizeof(char) * length);
    }
    else
        entry->data = NULL;
    
    entry->length = length;
    return entry;
}

myurl_path_entry_t * myurl_path_push(myurl_t* url, myurl_path_t* path, char* data, size_t length)
{
    if(path->length >= path->size) {
        size_t new_size = path->length + 32;
        
        myurl_path_entry_t *tmp = url->callback_realloc(path->list, sizeof(myurl_path_entry_t) * new_size, url->callback_ctx);
        
        if(tmp) {
            memset(&tmp[path->length], 0, sizeof(myurl_path_entry_t) * (new_size - path->length));
            
            path->list = tmp;
            path->size = new_size;
        }
        else
            return NULL;
    }
    
    myurl_path_entry_t *entry = &path->list[ path->length ];
    path->length++;

    entry->data = data;
    entry->length = length;
    
    return entry;
}

myurl_path_entry_t * myurl_path_push_to_index(myurl_t* url, myurl_path_t* path, size_t index, char* data, size_t length)
{
    if(index >= path->size) {
        myurl_path_entry_t *tmp = url->callback_realloc(path->list, sizeof(myurl_path_entry_t) * index, url->callback_ctx);
        
        if(tmp) {
            memset(&tmp[path->length], 0, sizeof(myurl_path_entry_t) * (index - path->length));
            
            path->list = tmp;
            path->size = index;
        }
        else
            return NULL;
    }
    
    if(index > path->length)
        path->length = index;
    
    if(path->list[ index ].data)
        url->callback_free(path->list[ index ].data, url->callback_ctx);
    
    path->list[ index ].data = data;
    path->list[ index ].length = length;
    
    return &path->list[ index ];
}

myurl_path_entry_t * myurl_path_current(myurl_path_t* path)
{
    if(path->length == 0)
        return NULL;
    
    return &path->list[ (path->length - 1) ];
}

myurl_path_entry_t * myurl_path_pop(myurl_path_t* path)
{
    if(path->length == 0)
        return NULL;
    
    path->length--;
    
    return &path->list[path->length];
}

void myurl_path_remove_by_index(myurl_t* url, myurl_path_t* path, size_t index)
{
    if(path->length == 0 || index >= path->length || path->list == NULL)
        return;
    
    myurl_path_entry_destroy(url, &path->list[index], false);
    
    if((path->length - 1) > index) {
        memmove(&path->list[index], &path->list[index + 1], sizeof(myurl_path_entry_t) * (path->length - (path->length - index)));
    }
    
    path->length--;
}

mystatus_t myurl_path_copy(myurl_t* url, myurl_path_t* path_from, myurl_path_t* path_to)
{
    if(path_from->length >= path_to->size) {
        size_t new_size = path_from->length + 2;
        
        myurl_path_entry_t* tmp = url->callback_realloc(path_to->list, sizeof(myurl_path_entry_t) * new_size, url->callback_ctx);
        
        if(tmp) {
            memset(&tmp[path_to->length], 0, sizeof(myurl_path_entry_t) * (new_size - path_to->length));
            
            path_to->list = tmp;
            path_to->size = new_size;
        }
        else
            return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    myurl_path_entry_t *list_to   = path_to->list;
    myurl_path_entry_t *list_from = path_from->list;
    
    if(path_to->length > path_from->length)
    {
        while(path_to->length > path_from->length) {
            path_to->length--;
            
            if(list_to[path_to->length].data)
                url->callback_free( list_to[path_to->length].data, url->callback_ctx );
        }
    }
    
    path_to->length = path_from->length;
    
    for(size_t i = 0; i < path_from->length; i++)
    {
        if(list_to[i].data)
        {
            if(list_to[i].length < list_from[i].length)
                list_to[i].data = url->callback_realloc(list_to[i].data, (list_from[i].length + 1), url->callback_ctx);
        }
        else {
            list_to[i].data = url->callback_malloc((list_from[i].length + 1), url->callback_ctx);
        }
        
        if(list_to[i].data == NULL)
            return MyURL_STATUS_ERROR_MEMORY_ALLOCATION;
        
        list_to[i].length = list_from[i].length;
        list_to[i].data[ list_to[i].length ] = '\0';
        
        if(list_from[i].length) {
            memcpy(list_to[i].data, list_from[i].data, sizeof(char) * list_from[i].length);
        }
    }
    
    return MyURL_STATUS_OK;
}

void myurl_path_shorten(myurl_path_t* path, myurl_scheme_id_t scheme_id)
{
    if(path->length == 0)
        return;
    
    if(scheme_id == MyURL_SCHEME_ID_FILE) {
        if(path->length == 1 && myurl_utils_is_windows_drive_letter(path->list[0].data, 0, path->list[0].length))
            return;
    }
    
    myurl_path_pop(path);
}



