/*
 Copyright (C) 2016 Alexander Borisov
 
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

#ifndef MyHTML_MyCSS_PROPERTY_PARSER_H
#define MyHTML_MyCSS_PROPERTY_PARSER_H
#pragma once

#include "mycss/property/myosi.h"
#include "mycss/property/shared.h"
#include "mycss/values/consume.h"
#include "mycss/values/values.h"

#ifdef __cplusplus
extern "C" {
#endif

bool mycss_property_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_items(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_self(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_attachment(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_clip(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_outset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_slice(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_shadow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_suppress(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_clear(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_clear_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_display(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_basis(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_flow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_grow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_shrink(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_flex_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_float(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_float_displace(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_feature_settings(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_kerning(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_language_override(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_size_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_stretch(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_synthesis(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_alternates(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_caps(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_east_asian(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_ligatures(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_numeric(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_variant_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_font_weight(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_indent_edge_reset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_justify_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_max_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_max_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_min_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_min_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_order(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow_x(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow_y(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_visibility(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_PARSER_H */
