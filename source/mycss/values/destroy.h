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

#ifndef MyCSS_VALUES_DESTROY_H
#define MyCSS_VALUES_DESTROY_H
#pragma once

#include "mycss/values/values.h"
#include "mycss/declaration/entry.h"

#ifdef __cplusplus
extern "C" {
#endif

mycss_values_shorthand_two_type_t * mycss_values_destroy_shorthand_two_type(mycss_entry_t* entry, mycss_values_shorthand_two_type_t* value, bool self_destroy);
mycss_values_shorthand_four_t * mycss_values_destroy_shorthand_four(mycss_entry_t* entry, mycss_values_shorthand_four_t* value, bool self_destroy);
mycss_values_shorthand_two_t * mycss_values_destroy_shorthand_two(mycss_entry_t* entry, mycss_values_shorthand_two_t* value, bool self_destroy);
mycss_values_number_t * mycss_values_destroy_number(mycss_entry_t* entry, mycss_values_number_t* value, bool self_destroy);
mycss_values_length_t * mycss_values_destroy_length(mycss_entry_t* entry, mycss_values_length_t* value, bool self_destroy);
mycss_values_percentage_t * mycss_values_destroy_percentage(mycss_entry_t* entry, mycss_values_percentage_t* value, bool self_destroy);
mycss_values_angle_t * mycss_values_destroy_angle(mycss_entry_t* entry, mycss_values_angle_t* value, bool self_destroy);
mycss_values_resolution_t * mycss_values_destroy_resolution(mycss_entry_t* entry, mycss_values_resolution_t* value, bool self_destroy);
mycss_values_type_list_t * mycss_values_destroy_type_list(mycss_entry_t* entry, mycss_values_type_list_t* value, bool self_destroy);

/* Color */
mycss_values_color_alpha_value_t * mycss_values_destroy_color_alpha_value(mycss_entry_t* entry, mycss_values_color_alpha_value_t* value, bool self_destroy);
mycss_values_color_hue_value_t * mycss_values_destroy_color_hue_value(mycss_entry_t* entry, mycss_values_color_hue_value_t* value, bool self_destroy);
mycss_values_color_hsla_t * mycss_values_destroy_color_hsla(mycss_entry_t* entry, mycss_values_color_hsla_t* value, bool self_destroy);
mycss_values_color_hwb_t * mycss_values_destroy_color_hwb(mycss_entry_t* entry, mycss_values_color_hwb_t* value, bool self_destroy);
mycss_values_color_gray_t * mycss_values_destroy_color_gray(mycss_entry_t* entry, mycss_values_color_gray_t* value, bool self_destroy);
mycss_values_color_rgba_number_t * mycss_values_destroy_color_rgba_number(mycss_entry_t* entry, mycss_values_color_rgba_number_t* value, bool self_destroy);
mycss_values_color_rgba_percentage_t * mycss_values_destroy_color_rgba_percentage(mycss_entry_t* entry, mycss_values_color_rgba_percentage_t* value, bool self_destroy);
mycss_values_color_t * mycss_values_destroy_color(mycss_entry_t* entry, mycss_values_color_t* value, bool self_destroy);

/* Font */
mycss_values_font_family_entry_t * mycss_values_destroy_font_family_entry(mycss_entry_t* entry, mycss_values_font_family_entry_t* value, bool self_destroy);
mycss_values_font_family_t * mycss_values_destroy_font_family(mycss_entry_t* entry, mycss_values_font_family_t* value, bool self_destroy);
mycss_values_font_t * mycss_values_destroy_font(mycss_entry_t* entry, mycss_values_font_t* value, bool self_destroy);

/* Text Decoration */
mycss_values_text_decoration_t * mycss_values_destroy_text_decoration(mycss_entry_t* entry, mycss_values_text_decoration_t* value, bool self_destroy);

/* Image */
mycss_values_image_t * mycss_values_destroy_image(mycss_entry_t* entry, mycss_values_image_t* image, bool self_destroy);
mycss_values_image_image_t * mycss_values_destroy_image_image(mycss_entry_t* entry, mycss_values_image_image_t* value, bool self_destroy);
mycss_values_image_image_set_t * mycss_values_destroy_image_image_set(mycss_entry_t* entry, mycss_values_image_image_set_t* value, bool self_destroy);
mycss_values_element_t * mycss_values_destroy_element(mycss_entry_t* entry, mycss_values_element_t* value, bool self_destroy);
mycss_values_cross_fade_t * mycss_values_destroy_cross_fade(mycss_entry_t* entry, mycss_values_cross_fade_t* value, bool self_destroy);
mycss_values_image_list_t * mycss_values_destroy_image_list(mycss_entry_t* entry, mycss_values_image_list_t* value, bool self_destroy);
    
/* Background */
mycss_values_background_t * mycss_values_destroy_background(mycss_entry_t* entry, mycss_values_background_t* value, bool self_destroy);
mycss_values_background_repeat_list_t * mycss_values_destroy_background_repeat(mycss_entry_t* entry, mycss_values_background_repeat_list_t* value, bool self_destroy);
mycss_values_background_position_t * mycss_values_destroy_background_position(mycss_entry_t* entry, mycss_values_background_position_t* value, bool self_destroy);
mycss_values_background_size_list_t * mycss_values_destroy_background_size(mycss_entry_t* entry, mycss_values_background_size_list_t* value, bool self_destroy);

/* Border */
mycss_values_border_t * mycss_values_destroy_border(mycss_entry_t* entry, mycss_values_border_t* value, bool self_destroy);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_VALUES_DESTROY_H */
