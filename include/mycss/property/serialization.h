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

#ifndef MyHTML_MyCSS_PROPERTY_SERIALIZATION_H
#define MyHTML_MyCSS_PROPERTY_SERIALIZATION_H
#pragma once

#include <mycss/property/myosi.h>
#include <mycss/property/init.h>
#include <mycss/values/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

void mycss_property_serialization_type_name(mycss_property_type_t prop_type, mycore_callback_serialize_f callback, void* context);
void mycss_property_serialization_value(unsigned int value_type, void* value, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_SERIALIZATION_H */
