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

#ifndef MyHTML_MyCSS_DECLARATION_SERIALIZATION_H
#define MyHTML_MyCSS_DECLARATION_SERIALIZATION_H
#pragma once

#include <mycss/declaration/myosi.h>
#include <mycss/values/values.h>
#include <mycss/property/init.h>
#include <mycss/property/serialization.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*mycss_declaration_serialization_f)(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
    mycore_callback_serialize_f callback, void* context);

bool mycss_declaration_serialization_entry(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
void mycss_declaration_serialization_entries(mycss_entry_t* entry, mycss_declaration_entry_t* first_dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_entry_only_value(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_entry_by_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycss_property_type_t property_type, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_entry_only_value_by_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycss_property_type_t property_type, mycore_callback_serialize_f callback, void* context);

bool mycss_declaration_serialization_undef(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_shorthand_four(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_shorthand_two(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_shorthand_two_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_type_list(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_border_radius(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_text_decoration(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_text_decoration_line(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_text_decoration_skip(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_font_family(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_font(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_background(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_background_image(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_background_repeat(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_background_position(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_background_size(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);
bool mycss_declaration_serialization_border_x(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_DECLARATION_SERIALIZATION_H */
