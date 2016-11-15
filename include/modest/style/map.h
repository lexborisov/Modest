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

#ifndef MODEST_STYLE_MAP_H
#define MODEST_STYLE_MAP_H
#pragma once

#include <modest/myosi.h>
#include <modest/modest.h>
#include <modest/finder/myosi.h>
#include <modest/finder/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*modest_style_map_collate_f)(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);

void modest_style_map_collate_declaration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);

void modest_style_map_collate_declaration_undef(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_align_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_align_items(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_align_self(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_delay(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_fill_mode(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_iteration_count(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_name(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_play_state(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_animation_timing_function(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_appearance(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_backface_visibility(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_attachment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_clip(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_repeat(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_background_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_bookmark_label(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_bookmark_level(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_bookmark_state(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_end_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_end_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_end_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_start_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_start_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_block_start_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom_left_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom_right_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_bottom_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_collapse(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_image_outset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_image_repeat(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_image_slice(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_image_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_end_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_end_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_end_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_start_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_start_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_inline_start_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_left_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_left_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_left_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_right_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_right_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_right_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top_left_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top_right_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_top_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_border_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_box_decoration_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_box_shadow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_box_sizing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_box_suppress(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_break_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_break_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_break_inside(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_caption_side(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_caret(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_caret_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_caret_shape(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_clear(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_clear_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_color_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_color_interpolation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_color_interpolation_filters(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_color_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_count(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_fill(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_gap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_rule(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_rule_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_rule_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_rule_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_span(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_column_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_columns(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_contain(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_continue(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_counter_increment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_cue(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_cue_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_cue_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_cursor(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_display(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_empty_cells(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_fill(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_fill_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_fill_rule(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_basis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_flow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_grow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_shrink(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_flex_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_float(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_float_displace(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_family(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_feature_settings(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_kerning(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_language_override(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_size_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_stretch(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_synthesis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_alternates(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_caps(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_east_asian(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_ligatures(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_numeric(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_variant_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_font_weight(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_glyph_orientation_vertical(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_hanging_punctuation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_hyphens(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_image_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_indent_edge_reset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_inline_size_step(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_justify_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_letter_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_line_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_line_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_line_height_step(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_list_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_list_style_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_list_style_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_list_style_type(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_block_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_block_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_inline_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_inline_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_margin_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_marker(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_marker_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_marker_mid(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_marker_side(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_marker_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_max_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_max_lines(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_max_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_min_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_min_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_nav_down(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_nav_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_nav_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_nav_up(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_offset_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_offset_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_offset_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_offset_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_order(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_orphans(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_outline(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_outline_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_outline_offset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_outline_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_outline_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_overflow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_overflow_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_overflow_x(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_overflow_y(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_block_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_block_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_inline_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_inline_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_padding_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_pause(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_pause_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_pause_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_perspective(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_perspective_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_presentation_level(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_quotes(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_region_fragment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_resize(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_rest(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_rest_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_rest_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_ruby_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_ruby_merge(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_ruby_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_scroll_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_scroll_snap_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_scroll_snap_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_scroll_snap_stop(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_scroll_snap_type(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_shape_image_threshold(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_shape_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_shape_outside(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_shape_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_speak(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_speak_as(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_string_set(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_dasharray(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_dashoffset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_linecap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_linejoin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_miterlimit(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_stroke_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_tab_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_table_layout(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_align_all(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_align_last(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_combine_upright(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_decoration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_decoration_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_decoration_line(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_decoration_skip(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_decoration_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_emphasis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_emphasis_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_emphasis_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_emphasis_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_indent(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_justify(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_orientation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_overflow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_shadow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_size_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_transform(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_text_underline_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_touch_action(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transform(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transform_box(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transform_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transform_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transition(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transition_delay(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transition_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transition_property(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_transition_timing_function(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_unicode_bidi(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_user_select(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_vertical_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_visibility(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_balance(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_family(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_pitch(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_range(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_rate(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_stress(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_voice_volume(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_white_space(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_widows(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_will_change(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_word_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_word_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_word_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_wrap_flow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_wrap_through(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_writing_mode(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);
void modest_style_map_collate_declaration_z_index(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_MAP_H */
