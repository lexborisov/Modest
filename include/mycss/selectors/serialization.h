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

#ifndef MyHTML_MyCSS_SELECTORS_SERIALIZATION_H
#define MyHTML_MyCSS_SELECTORS_SERIALIZATION_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/selectors/myosi.h>
#include <mycss/namespace/serialization.h>
#include <mycss/declaration/serialization.h>

void mycss_selectors_serialization_chain(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, mycore_callback_serialize_f callback, void* context);
bool mycss_selectors_serialization_list(mycss_selectors_t* selectors, mycss_selectors_list_t* selectors_list, mycore_callback_serialize_f callback, void* context);
bool mycss_selectors_serialization_selector(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_SERIALIZATION_H */
