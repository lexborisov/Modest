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

#ifndef MyHTML_MyCSS_VALUES_SERIALIZATION_H
#define MyHTML_MyCSS_VALUES_SERIALIZATION_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/values/values.h>
#include <mycss/values/color.h>
#include <mycss/property/const.h>

void mycss_values_serialization_string(mycore_string_t* str, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_number(mycss_values_number_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_length(mycss_values_length_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_angle(mycss_values_angle_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_resolution(mycss_values_resolution_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_percentage(mycss_values_percentage_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_type_length_percentage(mycss_values_type_length_percentage_entry_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_color(mycss_values_color_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_color_alpha(mycss_values_color_alpha_value_t* value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_text_decoration_line(mycss_values_text_decoration_line_t value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_text_decoration_skip(mycss_values_text_decoration_skip_t value, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_url(mycss_values_url_t* url, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_image(mycss_values_image_t* image, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_background_size_entry(mycss_values_background_size_entry_t* bg_size_entry, mycore_callback_serialize_f callback, void* context);
void mycss_values_serialization_border(mycss_values_border_t* border, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_VALUES_SERIALIZATION_H */
