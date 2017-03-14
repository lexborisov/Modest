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

#ifndef MyCSS_VALUES_COLOR_PARSER_H
#define MyCSS_VALUES_COLOR_PARSER_H
#pragma once

#include <mycss/myosi.h>
#include <mycss/values/consume.h>
#include <mycss/values/values.h>

#ifdef __cplusplus
extern "C" {
#endif

bool mycss_values_color_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgba(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_g_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_g_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_b_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_b_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_alpha_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_alpha_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_g_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_g_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_b_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_b_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_before_alpha_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_rgb_alpha_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_values_color_parser_hsl(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsla(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_before_saturation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_saturation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_before_lightness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_lightness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hsl_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_values_color_parser_hex(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str);

bool mycss_values_color_parser_hwb(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_before_whiteness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_whiteness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_before_blackness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_blackness(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_hwb_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_values_color_parser_gray(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_gray_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_values_color_parser_gray_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_VALUES_COLOR_PARSER_H */


