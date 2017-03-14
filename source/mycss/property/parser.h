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

#ifndef MyHTML_MyCSS_PROPERTY_PARSER_H
#define MyHTML_MyCSS_PROPERTY_PARSER_H
#pragma once

#include "mycss/property/myosi.h"
#include "mycss/property/shared.h"
#include "mycss/values/consume.h"
#include "mycss/values/values.h"
#include "mycss/declaration/entry.h"

#ifdef __cplusplus
extern "C" {
#endif

/* custom added */
bool mycss_property_parser_background_position_check(mycss_values_background_position_t *position);
bool mycss_property_parser_destroy_string(mycore_string_t* str, bool return_value);
bool mycss_property_parser_switcher_to_find_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_line_not_none(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_line_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_skip_not_none(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_skip_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_after_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_after_line(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_url_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_url_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

bool mycss_property_parser_image_function_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_wait_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_set(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_set_resolution(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_image_set_resolution_wait_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_string_wait_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_string_wait_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_cross_fade(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_cross_fade_mixing_after_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_cross_fade_mixing_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_cross_fade_final(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_function_cross_fade_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

/* all generated */
bool mycss_property_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_items(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_align_self(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_delay(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_fill_mode(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_iteration_count(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_name(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_play_state(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_animation_timing_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_appearance(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_backface_visibility(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_attachment(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_clip(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_background_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_bookmark_label(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_bookmark_level(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_bookmark_state(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_end_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_end_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_end_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_start_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_start_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_block_start_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_bottom_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_collapse(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_outset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_slice(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_image_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_end_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_end_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_end_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_start_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_start_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_inline_start_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_left_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_right_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_top_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_border_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_decoration_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_shadow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_sizing(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_box_suppress(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_break_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_break_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_break_inside(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_caption_side(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_caret(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_caret_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_caret_shape(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_clear(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_clear_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color_interpolation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color_interpolation_filters(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_color_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_count(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_fill(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_gap(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_rule_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_rule_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_rule_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_span(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_column_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_columns(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_contain(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_continue(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_counter_increment(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_cue(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_cue_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_cue_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_cursor(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_display(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_empty_cells(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_fill(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_fill_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_fill_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
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
bool mycss_property_parser_glyph_orientation_vertical(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_hanging_punctuation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_hyphens(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_image_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_indent_edge_reset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_inline_size_step(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_justify_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_letter_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_line_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_line_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_line_height_step(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_list_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_list_style_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_list_style_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_list_style_type(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_margin_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_marker(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_marker_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_marker_mid(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_marker_side(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_marker_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_max_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_max_lines(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_max_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_min_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_min_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_nav_down(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_nav_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_nav_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_nav_up(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_offset_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_offset_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_offset_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_offset_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_order(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_orphans(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_outline(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_outline_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_outline_offset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_outline_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_outline_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow_x(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_overflow_y(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_padding_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_pause(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_pause_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_pause_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_perspective(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_perspective_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_presentation_level(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_quotes(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_region_fragment(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_resize(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_rest(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_rest_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_rest_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_ruby_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_ruby_merge(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_ruby_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_scroll_padding(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_scroll_snap_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_scroll_snap_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_scroll_snap_stop(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_scroll_snap_type(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_shape_image_threshold(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_shape_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_shape_outside(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_shape_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_speak(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_speak_as(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_string_set(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_dasharray(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_dashoffset(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_linecap(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_linejoin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_miterlimit(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_stroke_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_tab_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_table_layout(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_align_all(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_align_last(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_combine_upright(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_line(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_skip(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_decoration_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_emphasis(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_emphasis_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_emphasis_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_emphasis_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_indent(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_justify(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_orientation(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_overflow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_shadow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_size_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_transform(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_text_underline_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_touch_action(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transform(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transform_box(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transform_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transform_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transition(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transition_delay(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transition_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transition_property(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_transition_timing_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_unicode_bidi(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_user_select(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_vertical_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_visibility(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_balance(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_pitch(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_range(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_rate(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_stress(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_voice_volume(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_white_space(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_widows(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_will_change(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_word_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_word_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_word_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_wrap_flow(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_wrap_through(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_writing_mode(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_z_index(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_PARSER_H */
