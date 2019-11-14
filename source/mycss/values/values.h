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

#ifndef MyHTML_MyCSS_VALUES_VALUES_H
#define MyHTML_MyCSS_VALUES_VALUES_H
#pragma once

#include "mycss/myosi.h"
#include "mycss/values/units.h"
#include "mycss/values/color_const.h"
#include "mycss/property/const.h"
#include "mycore/utils/mchar_async.h"
#include "myhtml/mystring.h"
#include "mycss/declaration/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mycss_values_gradient_side_or_corner mycss_values_gradient_side_or_corner_t;
typedef struct mycss_values_gradient_linear mycss_values_gradient_linear_t;

typedef struct mycss_values_cross_fade_mixing_image mycss_values_cross_fade_mixing_image_t;
typedef struct mycss_values_cross_fade_final_image mycss_values_cross_fade_final_image_t;
typedef struct mycss_values_cross_fade mycss_values_cross_fade_t;

typedef struct mycss_values_image_image_set_option mycss_values_image_image_set_option_t;
typedef struct mycss_values_image_image_set mycss_values_image_image_set_t;
typedef struct mycss_values_image_image mycss_values_image_image_t;
typedef struct mycss_values_image_list mycss_values_image_list_t;
typedef struct mycss_values_image mycss_values_image_t;

typedef struct mycss_values_url mycss_values_url_t;
typedef struct mycss_values_element mycss_values_element_t;

typedef struct mycss_values_text_decoration mycss_values_text_decoration_t;

typedef struct mycss_values_color_alpha_value mycss_values_color_alpha_value_t;
typedef struct mycss_values_color_hue_value mycss_values_color_hue_value_t;
typedef struct mycss_values_color_hsla mycss_values_color_hsla_t;
typedef struct mycss_values_color_hwb mycss_values_color_hwb_t;
typedef struct mycss_values_color_gray mycss_values_color_gray_t;
typedef struct mycss_values_color_rgba_number mycss_values_color_rgba_number_t;
typedef struct mycss_values_color_rgba_percentage mycss_values_color_rgba_percentage_t;
typedef struct mycss_values_color mycss_values_color_t;

typedef struct mycss_values_background_repeat_list mycss_values_background_repeat_list_t;
typedef struct mycss_values_background_repeat mycss_values_background_repeat_t;
typedef struct mycss_values_background_position mycss_values_background_position_t;
typedef struct mycss_values_background_size_list mycss_values_background_size_list_t;
typedef struct mycss_values_background_size_entry mycss_values_background_size_entry_t;
typedef struct mycss_values_background mycss_values_background_t;

typedef struct mycss_values_border mycss_values_border_t;

typedef struct mycss_values_color_stop mycss_values_color_stop_t;
typedef struct mycss_values_color_stop_list mycss_values_color_stop_list_t;

typedef struct mycss_values_font_family_entry mycss_values_font_family_entry_t;
typedef struct mycss_values_font_family mycss_values_font_family_t;
typedef struct mycss_values_font mycss_values_font_t;

typedef struct mycss_values_type_length_percentage_entry mycss_values_type_length_percentage_entry_t;
typedef struct mycss_values_type_list mycss_values_type_list_t;
typedef struct mycss_values_shorthand_two_type mycss_values_shorthand_two_type_t;
typedef struct mycss_values_shorthand_four mycss_values_shorthand_four_t;
typedef struct mycss_values_shorthand_two mycss_values_shorthand_two_t;
typedef struct mycss_values_percentage mycss_values_percentage_t;
typedef struct mycss_values_length mycss_values_length_t;
typedef struct mycss_values_number mycss_values_number_t;
typedef struct mycss_values_angle mycss_values_angle_t;
typedef struct mycss_values_resolution mycss_values_resolution_t;
typedef struct mycss_values_custom_ident mycss_values_custom_ident_t;

struct mycss_values_shorthand_two_type {
    void* one;
    void* two;
    
    unsigned int type_one;
    unsigned int type_two;
};

struct mycss_values_shorthand_four {
    mycss_declaration_entry_t* one;
    mycss_declaration_entry_t* two;
    mycss_declaration_entry_t* three;
    mycss_declaration_entry_t* four;
};

struct mycss_values_shorthand_two {
    mycss_declaration_entry_t* one;
    mycss_declaration_entry_t* two;
};

struct mycss_values_type_list {
    unsigned int* entries;
    size_t entries_length;
};

union mycss_values_type_length_percentage_union {
    mycss_values_percentage_t* percentage;
    mycss_values_length_t* length;
};
    
struct mycss_values_type_length_percentage_entry {
    union mycss_values_type_length_percentage_union value;
    unsigned int type;
};

struct mycss_values_number {
    union {
        int i;
        float f;
    } value;
    
    bool is_float;
};

struct mycss_values_length {
    union {
        int i;
        float f;
    } value;
    
    bool is_float;
    
    mycss_units_type_t type;
};

struct mycss_values_percentage {
    union {
        int i;
        float f;
    } value;
    
    bool is_float;
};

struct mycss_values_angle {
    union {
        int i;
        float f;
    } value;
    
    bool is_float;
    mycss_units_type_t type;
};

struct mycss_values_resolution {
    union {
        int i;
        float f;
    } value;
    
    bool is_float;
    mycss_units_type_t type;
};

struct mycss_values_custom_ident {
    mycore_string_t str;
};

/*
 Color
 */
enum mycss_values_color_type {
    MyCSS_VALUES_COLOR_TYPE_UNDEF        = 0x00,
    MyCSS_VALUES_COLOR_TYPE_RGB          = 0x01,
    MyCSS_VALUES_COLOR_TYPE_RGBA         = 0x02,
    MyCSS_VALUES_COLOR_TYPE_HSL          = 0x03,
    MyCSS_VALUES_COLOR_TYPE_HSLA         = 0x04,
    MyCSS_VALUES_COLOR_TYPE_HWB          = 0x05,
    MyCSS_VALUES_COLOR_TYPE_GRAY         = 0x06,
    MyCSS_VALUES_COLOR_TYPE_DEVICE_CMYK  = 0x07,
    MyCSS_VALUES_COLOR_TYPE_MOD          = 0x08,
    MyCSS_VALUES_COLOR_TYPE_HEX          = 0x09,
    MyCSS_VALUES_COLOR_TYPE_NAMED        = 0x0a,
    MyCSS_VALUES_COLOR_TYPE_CURRENTCOLOR = 0x0b,
}
typedef mycss_values_color_type_t;

enum mycss_values_color_type_value {
    MyCSS_VALUES_COLOR_TYPE_VALUE_UNDEF      = 0x00,
    MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER     = 0x01,
    MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE = 0x02,
    MyCSS_VALUES_COLOR_TYPE_VALUE_ANGLE      = 0x03,
    MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_8      = 0x04,
    MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_6      = 0x05,
    MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_4      = 0x06,
    MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_3      = 0x07,
}
typedef mycss_values_color_type_value_t;

struct mycss_values_color_alpha_value {
    union {
        mycss_values_number_t number;
        mycss_values_percentage_t percentage;
    } value;
    
    mycss_values_color_type_value_t type_value;
};

struct mycss_values_color_hue_value {
    union {
        mycss_values_number_t number;
        mycss_values_angle_t angle;
    } value;
    
    mycss_values_color_type_value_t type_value;
};

struct mycss_values_color_hsla {
    mycss_values_color_hue_value_t hue;
    mycss_values_percentage_t saturation;
    mycss_values_percentage_t lightness;
    mycss_values_color_alpha_value_t alpha;
};

struct mycss_values_color_hwb {
    mycss_values_color_hue_value_t hue;
    mycss_values_percentage_t saturation;
    mycss_values_percentage_t lightness;
    mycss_values_color_alpha_value_t alpha;
};

struct mycss_values_color_gray {
    mycss_values_number_t number;
    mycss_values_color_alpha_value_t alpha;
};

struct mycss_values_color_rgba_number {
    mycss_values_number_t r;
    mycss_values_number_t g;
    mycss_values_number_t b;
    mycss_values_color_alpha_value_t alpha;
};

struct mycss_values_color_rgba_percentage {
    mycss_values_percentage_t r;
    mycss_values_percentage_t g;
    mycss_values_percentage_t b;
    mycss_values_color_alpha_value_t alpha;
};

struct mycss_values_color {
    union {
        mycss_values_color_rgba_number_t hex;
        mycss_values_color_rgba_number_t rgba_number;
        mycss_values_color_rgba_percentage_t rgba_percentage;
        mycss_values_color_hsla_t hsla;
        mycss_values_color_hwb_t hwb;
        mycss_values_color_gray_t gray;
        mycss_values_color_id_t name_id;
    } value;
    
    mycss_values_color_type_t type;
    mycss_values_color_type_value_t type_value;
};

struct mycss_values_color_stop {
    mycss_values_color_t color;
    mycss_values_percentage_t* percentage;
};

struct mycss_values_color_stop_list {
    mycss_values_color_stop_t* entries;
    size_t entries_length;
};

/*
 URL
 */
struct mycss_values_url {
    mycore_string_t str;
};

/*
 Element
 */
struct mycss_values_element {
    mycss_values_custom_ident_t custom_ident;
    mycss_property_value_t type;
};

/*
 Image
 */
struct mycss_values_image {
    union {
        mycss_values_url_t* url;
        mycss_values_image_image_t* ii;
        mycss_values_image_image_set_t* ii_set;
        mycss_values_element_t* element;
        mycss_values_cross_fade_t* cross_fade;
    } value;
    
    mycss_property_value_t type;
};

struct mycss_values_image_list {
    mycss_values_image_t* images;
    size_t images_length;
};

/* image() */
struct mycss_values_image_image {
    mycore_string_t* str;
    mycss_values_image_t* image;
    mycss_values_color_t* color;
};

/* image-set() */
struct mycss_values_image_image_set_option {
    mycore_string_t* str;
    mycss_values_image_t* image;
    mycss_values_resolution_t* resolution;
};

struct mycss_values_image_image_set {
    mycss_values_image_image_set_option_t* options;
    size_t options_length;
};

/*
 Cross fade
 */
struct mycss_values_cross_fade_mixing_image {
    mycss_values_percentage_t* percentage;
    mycss_values_image_t* image;
};

struct mycss_values_cross_fade_final_image {
    mycss_values_image_t* image;
    mycss_values_color_t* color;
};

struct mycss_values_cross_fade {
    mycss_values_cross_fade_mixing_image_t mixing_image;
    mycss_values_cross_fade_final_image_t final_image;
};

/* Not yet */
/*
 Gradients
 */
/* linear gradient */
enum mycss_values_gradient_side_or_corner_type {
    MyCSS_VALUES_GRADIENT_SIDE_OR_CORNER_TYPE_UNDEF  = 0x00,
    MyCSS_VALUES_GRADIENT_SIDE_OR_CORNER_TYPE_LEFT   = 0x01,
    MyCSS_VALUES_GRADIENT_SIDE_OR_CORNER_TYPE_RIGHT  = 0x02,
    MyCSS_VALUES_GRADIENT_SIDE_OR_CORNER_TYPE_TOP    = 0x04,
    MyCSS_VALUES_GRADIENT_SIDE_OR_CORNER_TYPE_BOTTOM = 0x08
}
typedef mycss_values_gradient_side_or_corner_type_t;

struct mycss_values_gradient_side_or_corner {
    mycss_values_gradient_side_or_corner_type_t side;
    mycss_values_gradient_side_or_corner_type_t corner;
};

struct mycss_values_gradient_linear {
    union {
        mycss_values_angle_t angle;
        mycss_values_gradient_side_or_corner_t side_or_corner;
    } value;
    
    mycss_values_color_stop_list_t color_stop_list;
};

/* radial gradient */
// ...

/*
 Font
 */
enum mycss_values_font_family_type {
    MyCSS_VALUES_FONT_FAMILY_TYPE_UNDEF    = 0x00,
    MyCSS_VALUES_FONT_FAMILY_TYPE_NAME     = 0x01,
    MyCSS_VALUES_FONT_FAMILY_TYPE_GENERIC  = 0x02,
}
typedef mycss_values_font_family_type_t;

struct mycss_values_font_family_entry {
    union {
        mycore_string_t str;
        mycss_property_font_family_t prop_type;
    } value;
    
    mycss_values_font_family_type_t type;
};

struct mycss_values_font_family {
    mycss_values_font_family_entry_t* entries;
    size_t entries_length;
};

struct mycss_values_font {
    mycss_declaration_entry_t* style;
    mycss_declaration_entry_t* weight;
    mycss_declaration_entry_t* stretch;
    mycss_declaration_entry_t* size;
    mycss_declaration_entry_t* family;
    mycss_declaration_entry_t* line_height;
};

/*
 Decoration
 */
enum mycss_values_text_decoration_line {
    MyCSS_VALUES_TEXT_DECORATION_LINE_UNDEF        = 0x00,
    MyCSS_VALUES_TEXT_DECORATION_LINE_UNDERLINE    = 0x01,
    MyCSS_VALUES_TEXT_DECORATION_LINE_OVERLINE     = 0x02,
    MyCSS_VALUES_TEXT_DECORATION_LINE_LINE_THROUGH = 0x04,
    MyCSS_VALUES_TEXT_DECORATION_LINE_BLINK        = 0x08
}
typedef mycss_values_text_decoration_line_t;

enum mycss_values_text_decoration_skip {
    MyCSS_VALUES_TEXT_DECORATION_SKIP_UNDEF          = 0x00,
    MyCSS_VALUES_TEXT_DECORATION_SKIP_OBJECTS        = 0x01,
    MyCSS_VALUES_TEXT_DECORATION_SKIP_SPACES         = 0x02,
    MyCSS_VALUES_TEXT_DECORATION_SKIP_INK            = 0x04,
    MyCSS_VALUES_TEXT_DECORATION_SKIP_EDGES          = 0x08,
    MyCSS_VALUES_TEXT_DECORATION_SKIP_BOX_DECORATION = 0x10
}
typedef mycss_values_text_decoration_skip_t;

struct mycss_values_text_decoration {
    mycss_declaration_entry_t* line;
    mycss_declaration_entry_t* style;
    mycss_declaration_entry_t* color;
};

/*
 Border
 */
struct mycss_values_border {
    mycss_declaration_entry_t* width;
    mycss_declaration_entry_t* style;
    mycss_declaration_entry_t* color;
};

/*
 Background
 */
struct mycss_values_background {
    mycss_declaration_entry_t* image;
    mycss_declaration_entry_t* position;
    mycss_declaration_entry_t* size;
    mycss_declaration_entry_t* repeat;
    mycss_declaration_entry_t* attachment;
    mycss_declaration_entry_t* origin;
    mycss_declaration_entry_t* clip;
    mycss_declaration_entry_t* color;
};


struct mycss_values_background_repeat {
    mycss_property_background_t horizontal;
    mycss_property_background_t vertical;
};

struct mycss_values_background_repeat_list {
    mycss_values_background_repeat_t* entries;
    size_t entries_length;
};

struct mycss_values_background_position {
    mycss_values_type_length_percentage_entry_t one;
    mycss_values_type_length_percentage_entry_t two;
    mycss_values_type_length_percentage_entry_t three;
    mycss_values_type_length_percentage_entry_t four;
};

struct mycss_values_background_size_entry {
    unsigned int scale;
    mycss_values_type_length_percentage_entry_t* width;
    mycss_values_type_length_percentage_entry_t* height;
};

struct mycss_values_background_size_list {
    mycss_values_background_size_entry_t* entries;
    size_t entries_length;
};

void * mycss_values_create(mycss_entry_t* entry, size_t size);
void * mycss_values_destroy(mycss_entry_t* entry, void* value);
void * mycss_values_realloc(mycss_entry_t* entry, void* value, size_t old_size, size_t up_to);
void * mycss_values_clone(mycss_entry_t* entry, void* value);

void * mycss_values_entry(mycss_entry_t* entry);
void mycss_values_entry_set(mycss_entry_t* entry, void** value);

unsigned int * mycss_values_type_list_add_entry(mycss_entry_t* entry, mycss_values_type_list_t *list);
mycss_values_image_t * mycss_values_image_list_add_entry(mycss_entry_t* entry, mycss_values_image_list_t *bg_image);
mycss_values_background_repeat_t * mycss_values_background_repeat_list_add_entry(mycss_entry_t* entry, mycss_values_background_repeat_list_t *list);
mycss_values_background_size_entry_t * mycss_values_background_size_list_add_entry(mycss_entry_t* entry, mycss_values_background_size_list_t *list);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_VALUES_VALUES_H */
