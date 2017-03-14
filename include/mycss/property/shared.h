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

#ifndef MyHTML_MyCSS_PROPERTY_SHARED_H
#define MyHTML_MyCSS_PROPERTY_SHARED_H
#pragma once

#include <mycss/property/myosi.h>
#include <mycss/values/consume.h>
#include <mycss/values/values.h>
#include <mycss/values/color.h>
#include <mycss/values/image.h>
#include <mycore/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

bool mycss_property_shared_switch_to_find_important(mycss_entry_t* entry);
bool mycss_property_shared_switch_to_parse_error(mycss_entry_t* entry);
bool mycss_property_shared_check_declaration_end(mycss_entry_t* entry, mycss_token_t* token);

bool mycss_property_shared_number(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_length(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_length_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_resolution(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_custom_ident(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type);
bool mycss_property_shared_color(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str, bool* parser_changed);
bool mycss_property_shared_default(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
unsigned int mycss_property_shared_get_value_type(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str);
bool mycss_property_shared_by_value_type(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, unsigned int check_type, mycore_string_t* str);
bool mycss_property_shared_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_height(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_line_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_line_height(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_line_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_text_decoration_skip(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value, unsigned int* value_type, mycore_string_t* str, bool with_global);
bool mycss_property_shared_text_decoration_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_text_decoration_line(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value, unsigned int* value_type, mycore_string_t* str, bool with_global);

bool mycss_property_shared_font_ends(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_font_weight(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_font_size(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_font_stretch(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_font_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_font_family(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, bool *dont_destroy_str, mycore_string_t* str);

bool mycss_property_shared_image(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str, bool* parser_changed);

bool mycss_property_shared_background_repeat_one(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_background_repeat_two(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_background_attachment(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_background_position(mycss_entry_t* entry, mycss_token_t* token, void* value, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_background_clip(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str);
bool mycss_property_shared_background_size(mycss_entry_t* entry, mycss_token_t* token, void* value, unsigned int* value_type, mycore_string_t* str);

void mycss_property_shared_destroy_string(mycore_string_t* str);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_SHARED_H */
