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

#ifndef MyURL_SERIALIZATION_H
#define MyURL_SERIALIZATION_H
#pragma once

#include <math.h>

#include "myurl/myosi.h"
#include "myurl/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

void myurl_serialization_authority(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_host(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_auth_host_port(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_path(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_with_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization_without_fragment(myurl_entry_t* url_entry, mycore_callback_serialize_f callback, void* ctx);
void myurl_serialization(myurl_entry_t* url_entry, bool exclude_fragment_flag, mycore_callback_serialize_f callback, void* ctx);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_SERIALIZATION_H */
