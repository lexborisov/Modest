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

#ifndef MyHTML_MyCSS_NAMESPACE_SERIALIZATION_H
#define MyHTML_MyCSS_NAMESPACE_SERIALIZATION_H
#pragma once

#include "mycss/entry.h"
#include "mycss/namespace/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

void mycss_namespace_serialization_stylesheet(mycss_namespace_stylesheet_t* ns_stylesheet, mycore_callback_serialize_f callback, void* context);
void mycss_namespace_serialization_entry(mycss_namespace_t* ns, mycss_namespace_entry_t* ns_entry, mycore_callback_serialize_f callback, void* context, bool with_vbar);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_NAMESPACE_SERIALIZATION_H */
