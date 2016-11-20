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

#ifndef MyCSS_DECLARATION_DEFAULT_ENTRIES_H
#define MyCSS_DECLARATION_DEFAULT_ENTRIES_H
#pragma once

static mycss_declaration_entry_t mycss_declaration_default_entry_undef = {
    MyCSS_PROPERTY_TYPE_UNDEF,
    MyCSS_PROPERTY_VALUE_UNDEF,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_width = {
    MyCSS_PROPERTY_TYPE_WIDTH,
    MyCSS_PROPERTY_VALUE_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_height = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VALUE_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_min_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MIN_WIDTH__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_min_height = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MIN_HEIGHT__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_max_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MAX_WIDTH_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_max_height = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MAX_HEIGHT_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_direction = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_DIRECTION_LTR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_ = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_DIRECTION_LTR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_unicode_bidi = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_UNICODE_BIDI_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_writing_mode = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_WRITING_MODE_HORIZONTAL_TB,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_orientation = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_ORIENTATION_MIXED,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_glyph_orientation_vertical = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TYPE_UNDEF,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_box_sizing = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BOX_SIZING_CONTENT_BOX,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_cursor = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_CURSOR_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_decoration_line = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_DECORATION_LINE_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_decoration_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_DECORATION_COLOR_CURRENTCOLOR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_decoration_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_DECORATION_STYLE_SOLID,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_decoration_skip = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VALUE_UNDEF,
    &(unsigned int){MyCSS_PROPERTY_TEXT_DECORATION_SKIP_OBJECTS},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_transform = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_TRANSFORM_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_white_space = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_WHITE_SPACE_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_tab_size = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VALUE__NUMBER,
    &(mycss_values_number_t){{8}, false},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_word_break = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_WORD_BREAK_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_line_break = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_LINE_BREAK_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_hyphens = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_HYPHENS_MANUAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_overflow_wrap = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_OVERFLOW_WRAP_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_word_wrap = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_WORD_WRAP_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_align = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_ALIGN_START,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_align_all = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_ALIGN_ALL_START,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_align_last = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_ALIGN_LAST_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_text_justify = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TEXT_JUSTIFY_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_word_spacing = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_WORD_SPACING_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_letter_spacing = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_LETTER_SPACING_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_position = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_POSITION_STATIC,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_top = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_TOP_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_right = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_RIGHT_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_bottom = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BOTTOM_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_left = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_LEFT_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_z_index = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_Z_INDEX_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VALUE_UNDEF,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_size = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_origin = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_ORIGIN_PADDING_BOX,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_clip = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_CLIP_BORDER_BOX,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_position = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VALUE_UNDEF,
    &(mycss_values_background_position_t){
        {{(&(mycss_values_percentage_t){{0}, false})}, MyCSS_PROPERTY_VALUE__PERCENTAGE},
        {{(&(mycss_values_percentage_t){{0}, false})}, MyCSS_PROPERTY_VALUE__PERCENTAGE},
        {{NULL}, MyCSS_PROPERTY_VALUE_UNDEF},
        {{NULL}, MyCSS_PROPERTY_VALUE_UNDEF}
    },
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_attachment = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_ATTACHMENT_SCROLL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_repeat = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_REPEAT_REPEAT,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_image = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_IMAGE_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_background_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BACKGROUND_COLOR_TRANSPARENT,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_top_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_TOP_MEDIUM,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_right_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_RIGHT_MEDIUM,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_bottom_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_BOTTOM_MEDIUM,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_left_width = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_LEFT_MEDIUM,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_top_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_TOP_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_right_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_RIGHT_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_bottom_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_BOTTOM_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_left_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_LEFT_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_top_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_TOP_COLOR_CURRENTCOLOR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_right_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_RIGHT_COLOR_CURRENTCOLOR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_bottom_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_BOTTOM_COLOR_CURRENTCOLOR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_left_color = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_LEFT_COLOR_CURRENTCOLOR,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_top_left_radius = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_TOP_LEFT_RADIUS__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_top_right_radius = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_TOP_RIGHT_RADIUS__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_bottom_right_radius = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_border_bottom_left_radius = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_BORDER_BOTTOM_LEFT_RADIUS__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_padding_top = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_PADDING_TOP__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_padding_right = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_PADDING_RIGHT__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_padding_bottom = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_PADDING_BOTTOM__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_padding_left = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_PADDING_LEFT__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_margin_top = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MARGIN_TOP__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_margin_right = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MARGIN_RIGHT__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_margin_bottom = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MARGIN_BOTTOM__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_margin_left = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_MARGIN_LEFT__LENGTH,
    &(mycss_values_length_t){{0}, false, MyCSS_UNIT_TYPE_UNDEF},
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_float = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FLOAT_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_clear = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_CLEAR_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_clear_after = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_CLEAR_AFTER_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_overflow_x = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_OVERFLOW_X_VISIBLE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_overflow_y = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_OVERFLOW_Y_VISIBLE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_visibility = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VISIBILITY_VISIBLE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_float_displace = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FLOAT_DISPLACE_LINE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_display = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_DISPLAY_INLINE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_font_weight = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FONT_WEIGHT_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_font_style = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FONT_STYLE_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_font_size = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FONT_SIZE_MEDIUM,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_font_size_adjust = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_FONT_SIZE_ADJUST_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_line_height = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_LINE_HEIGHT_NORMAL,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t mycss_declaration_default_entry_vertical_align = {
    MyCSS_PROPERTY_TYPE_HEIGHT,
    MyCSS_PROPERTY_VERTICAL_ALIGN_BASELINE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

#endif /* MyCSS_DECLARATION_DEFAULT_ENTRIES_H */
