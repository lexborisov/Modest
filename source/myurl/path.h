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

#include "myurl/myosi.h"
#include "myurl/scheme_const.h"
#include "myurl/utils.h"
#include "myhtml/mystring.h"

#ifndef MyURL_PATH_H
#define MyURL_PATH_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct myurl_path_entry {
    char*  data;
    size_t length;
}
typedef myurl_path_entry_t;

struct myurl_path_t {
    myurl_path_entry_t* list;
    size_t length;
    size_t size;
}
typedef myurl_path_t;

myurl_path_t * myurl_path_create(myurl_t* url);
mystatus_t myurl_path_init(myurl_t* url, myurl_path_t* path, size_t begin_size);
void myurl_path_clean(myurl_t* url, myurl_path_t* path);
myurl_path_t * myurl_path_destroy(myurl_t* url, myurl_path_t* path, bool destroy_self);

myurl_path_entry_t * myurl_path_append(myurl_t* url, myurl_path_t* path, const char* data, size_t length);
myurl_path_entry_t * myurl_path_push(myurl_t* url, myurl_path_t* path, char* data, size_t length);
myurl_path_entry_t * myurl_path_push_to_index(myurl_t* url, myurl_path_t* path, size_t index, char* data, size_t length);
myurl_path_entry_t * myurl_path_current(myurl_path_t* path);
myurl_path_entry_t * myurl_path_pop(myurl_path_t* path);
mystatus_t myurl_path_copy(myurl_t* url, myurl_path_t* path_from, myurl_path_t* path_to);

void myurl_path_remove_by_index(myurl_t* url, myurl_path_t* path, size_t index);

void myurl_path_shorten(myurl_path_t* path, myurl_scheme_id_t scheme_id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_PATH_H */
