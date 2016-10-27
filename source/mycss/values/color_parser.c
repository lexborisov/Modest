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

#include "mycss/values/color_parser.h"
#include "myhtml/utils/resources.h"

bool mycss_values_color_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_values_color_parser_find_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    entry->parser = entry->parser_switch;
    
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS)
        return true;
    
    return false;
}

static void mycss_values_color_parser_set_percentage_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_percentage_t *color_rgb)
{
    myhtml_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str.data, str.length, &return_num, &color_rgb->is_float);
    
    if(color_rgb->is_float)
        color_rgb->f = (float)return_num;
    else
        color_rgb->i = (int)return_num;
    
    myhtml_string_destroy(&str, false);
}

static void mycss_values_color_parser_set_number_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_number_t *color_rgb)
{
    myhtml_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str.data, str.length, &return_num, &color_rgb->is_float);
    
    if(color_rgb->is_float)
        color_rgb->f = (float)return_num;
    else
        color_rgb->i = (int)return_num;
    
    myhtml_string_destroy(&str, false);
}

static bool mycss_values_color_parser_set_angle_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_angle_t *angle)
{
    myhtml_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    bool is_float;
    double return_num;
    
    size_t consume_length = mycss_convert_data_to_double(str.data, str.length, &return_num, &is_float);
    mycss_units_type_t type = mycss_units_type_by_name(&str.data[consume_length], (str.length - consume_length));
    
    myhtml_string_destroy(&str, false);
    
    switch (type) {
        case MyCSS_UNIT_TYPE_DEG:
        case MyCSS_UNIT_TYPE_GRAD:
        case MyCSS_UNIT_TYPE_RAD:
        case MyCSS_UNIT_TYPE_TURN:
            break;
            
        default:
            return false;
    }
    
    if(is_float)
        angle->f = (float)return_num;
    else
        angle->i = (int)return_num;
    
    angle->is_float = is_float;
    angle->type = type;
    
    return true;
}

static bool mycss_values_color_parser_rgb_full(mycss_entry_t* entry, mycss_token_t* token, mycss_values_color_t *color)
{
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE)
    {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->rgba_percentage.r);
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
        entry->parser = mycss_values_color_parser_rgb_before_g_percentage;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->rgba_number.r);
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
        entry->parser = mycss_values_color_parser_rgb_before_g_number;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_values_color_parser_rgb(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    color->type = MyCSS_VALUES_COLOR_TYPE_RGB;
    
    return mycss_values_color_parser_rgb_full(entry, token, color);
}

bool mycss_values_color_parser_rgba(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    color->type = MyCSS_VALUES_COLOR_TYPE_RGBA;
    
    return mycss_values_color_parser_rgb_full(entry, token, color);
}

/*
 * For percentage type
 */
bool mycss_values_color_parser_rgb_before_g_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_g_percentage;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_rgb_g_percentage;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_g_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->rgba_percentage.g);
    
    entry->parser = mycss_values_color_parser_rgb_before_b_percentage;
    
    return true;
}

bool mycss_values_color_parser_rgb_before_b_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_b_percentage;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_rgb_b_percentage;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_b_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->rgba_percentage.b);
    
    entry->parser = mycss_values_color_parser_rgb_before_alpha_percentage;
    return true;
}

bool mycss_values_color_parser_rgb_before_alpha_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_alpha_percentage;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            entry->parser = entry->parser_switch;
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_rgb_alpha_percentage;
                return true;
            }
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_alpha_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->rgba_percentage.alpha.percentage);
        color->rgba_percentage.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->rgba_percentage.alpha.number);
        color->rgba_percentage.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}

/*
 * For number type
 */
bool mycss_values_color_parser_rgb_before_g_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_g_number;
            return true;
            
        case MyCSS_TOKEN_TYPE_NUMBER:
            entry->parser = mycss_values_color_parser_rgb_g_number;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_g_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_number_value(entry, token, &color->rgba_number.g);
    
    entry->parser = mycss_values_color_parser_rgb_before_b_number;
    return true;
}

bool mycss_values_color_parser_rgb_before_b_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_b_number;
            return true;
            
        case MyCSS_TOKEN_TYPE_NUMBER:
            entry->parser = mycss_values_color_parser_rgb_b_number;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_b_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_number_value(entry, token, &color->rgba_number.b);
    
    entry->parser = mycss_values_color_parser_rgb_before_alpha_number;
    return true;
}

bool mycss_values_color_parser_rgb_before_alpha_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_rgb_alpha_number;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            entry->parser = entry->parser_switch;
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_rgb_alpha_number;
                return true;
            }
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_rgb_alpha_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->rgba_number.alpha.percentage);
        color->rgba_number.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->rgba_number.alpha.number);
        color->rgba_number.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}

/*
 * HSL and HSLA
 */
static bool mycss_values_color_parser_hsla_full(mycss_entry_t* entry, mycss_token_t* token, mycss_values_color_t *color)
{
    if(token->type == MyCSS_TOKEN_TYPE_DIMENSION) {
        if(mycss_values_color_parser_set_angle_value(entry, token, &color->hsla.hue.angle) == false) {
            entry->parser = entry->parser_switch;
            return false;
        }
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_ANGLE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->hsla.hue.number);
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_hsl_before_saturation;
    return true;
}

bool mycss_values_color_parser_hsl(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    color->type = MyCSS_VALUES_COLOR_TYPE_HSL;
    
    return mycss_values_color_parser_hsla_full(entry, token, color);
}

bool mycss_values_color_parser_hsla(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    color->type = MyCSS_VALUES_COLOR_TYPE_HSLA;
    
    return mycss_values_color_parser_hsla_full(entry, token, color);
}

bool mycss_values_color_parser_hsl_before_saturation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hsl_saturation;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_hsl_saturation;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hsl_saturation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->hsla.saturation);
    
    entry->parser = mycss_values_color_parser_hsl_before_lightness;
    return true;
}

bool mycss_values_color_parser_hsl_before_lightness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hsl_lightness;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_hsl_lightness;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hsl_lightness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->hsla.lightness);
    
    entry->parser = mycss_values_color_parser_hsl_before_alpha;
    return true;
}

bool mycss_values_color_parser_hsl_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hsl_alpha;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            entry->parser = entry->parser_switch;
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_hsl_alpha;
                return true;
            }
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hsl_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->hsla.alpha.percentage);
        color->hsla.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->hsla.alpha.number);
        color->hsla.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}

/*
 * HEX
 */
static unsigned int mycss_values_color_parser_hex_get_by_two(unsigned char* u_data)
{
    return (myhtml_string_chars_hex_map[ u_data[0] ] << 4) | myhtml_string_chars_hex_map[ u_data[1] ];
}

bool mycss_values_color_parser_hex(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_HASH)
        return true;
        
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned char *u_data = (unsigned char*)str->data;
    mycss_values_color_t *color = (mycss_values_color_t*)mycss_values_create(entry, sizeof(mycss_values_color_t));
    
    switch (str->length) {
        case 6:
            color->hex.r.i = (int)mycss_values_color_parser_hex_get_by_two(u_data);
            color->hex.g.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[2]);
            color->hex.b.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[4]);
            color->hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_UNDEF;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_6;
            break;
        case 8:
            color->hex.r.i = (int)mycss_values_color_parser_hex_get_by_two(u_data);
            color->hex.g.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[2]);
            color->hex.b.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[4]);
            
            color->hex.alpha.number.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[6]);
            color->hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_8;
            break;
        case 3:
            color->hex.r.i = (int)(myhtml_string_chars_hex_map[ u_data[0] ]);
            color->hex.r.i = (color->hex.r.i << 4) | color->hex.r.i;
            
            color->hex.g.i = (int)(myhtml_string_chars_hex_map[ u_data[1] ]);
            color->hex.g.i = (color->hex.g.i << 4) | color->hex.g.i;
            
            color->hex.b.i = (int)(myhtml_string_chars_hex_map[ u_data[2] ]);
            color->hex.b.i = (color->hex.b.i << 4) | color->hex.b.i;
            
            color->hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_UNDEF;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_3;
            break;
        case 4:
            color->hex.r.i = (int)(myhtml_string_chars_hex_map[ u_data[0] ]);
            color->hex.r.i = (color->hex.r.i << 4) | color->hex.r.i;
            
            color->hex.g.i = (int)(myhtml_string_chars_hex_map[ u_data[1] ]);
            color->hex.g.i = (color->hex.g.i << 4) | color->hex.g.i;
            
            color->hex.b.i = (int)(myhtml_string_chars_hex_map[ u_data[2] ]);
            color->hex.b.i = (color->hex.b.i << 4) | color->hex.b.i;
            
            color->hex.alpha.number.i = (int)(myhtml_string_chars_hex_map[ u_data[3] ]);
            color->hex.alpha.number.i = (color->hex.alpha.number.i << 4) | color->hex.alpha.number.i;
            color->hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_4;
            break;
            
        default:
            mycss_values_destroy(entry, (void*)color);
            
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            return false;
    }
    
    color->type = MyCSS_VALUES_COLOR_TYPE_HEX;
    
    *value = color;
    *value_type = MyCSS_PROPERTY_VALUE__COLOR;
    
    return true;
}

/*
 * HWB
 */
static bool mycss_values_color_parser_hwb_hue(mycss_entry_t* entry, mycss_token_t* token, mycss_values_color_t *color)
{
    if(token->type == MyCSS_TOKEN_TYPE_DIMENSION) {
        if(mycss_values_color_parser_set_angle_value(entry, token, &color->hwb.hue.angle) == false) {
            entry->parser = entry->parser_switch;
            return false;
        }
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_ANGLE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->hwb.hue.number);
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_hwb_before_whiteness;
    return true;
}

bool mycss_values_color_parser_hwb(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    color->type = MyCSS_VALUES_COLOR_TYPE_HWB;
    
    return mycss_values_color_parser_hwb_hue(entry, token, color);
}

bool mycss_values_color_parser_hwb_before_whiteness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hwb_whiteness;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_hwb_whiteness;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hwb_whiteness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->hwb.saturation);
    
    entry->parser = mycss_values_color_parser_hwb_before_blackness;
    return true;
}

bool mycss_values_color_parser_hwb_before_blackness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hwb_blackness;
            return true;
            
        case MyCSS_TOKEN_TYPE_PERCENTAGE:
            entry->parser = mycss_values_color_parser_hwb_blackness;
            return false;
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hwb_blackness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->hwb.lightness);
    
    entry->parser = mycss_values_color_parser_hwb_before_alpha;
    return true;
}

bool mycss_values_color_parser_hwb_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_hwb_alpha;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            entry->parser = entry->parser_switch;
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_hwb_alpha;
                return true;
            }
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_hwb_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->hwb.alpha.percentage);
        color->hwb.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->hwb.alpha.number);
        color->hwb.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}

/*
 * Gray
 */
bool mycss_values_color_parser_gray(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->gray.number);
        color->type = MyCSS_VALUES_COLOR_TYPE_GRAY;
        
        entry->parser = mycss_values_color_parser_gray_before_alpha;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_values_color_parser_gray_before_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_values_color_parser_gray_alpha;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            entry->parser = entry->parser_switch;
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_gray_alpha;
                return true;
            }
            
        default:
            entry->parser = entry->parser_switch;
            return false;
    }
}

bool mycss_values_color_parser_gray_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->gray.alpha.percentage);
        color->gray.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->gray.alpha.number);
        color->gray.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        entry->parser = entry->parser_switch;
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}


