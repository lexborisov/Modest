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

#include "mycss/values/color_parser.h"
#include "mycore/utils/resources.h"

bool mycss_values_color_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

static void mycss_values_color_parser_switch_parser(mycss_entry_t* entry)
{
    mycss_stack_entry_t *stack_entry = mycss_stack_pop(entry->declaration->stack);
    
    if(stack_entry->value)
        entry->declaration->entry_last->value = stack_entry->value;
    
    entry->parser = stack_entry->parser;
}

static bool mycss_values_color_parser_find_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_values_color_parser_switch_parser(entry);
    
    if(token->type == MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS)
        return true;
    
    return false;
}

static void mycss_values_color_parser_set_percentage_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_percentage_t *color_rgb)
{
    mycore_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str.data, str.length, &return_num, &color_rgb->is_float);
    
    if(color_rgb->is_float)
        color_rgb->value.f = (float)return_num;
    else
        color_rgb->value.i = (int)return_num;
    
    mycore_string_destroy(&str, false);
}

static void mycss_values_color_parser_set_number_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_number_t *color_rgb)
{
    mycore_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str.data, str.length, &return_num, &color_rgb->is_float);
    
    if(color_rgb->is_float)
        color_rgb->value.f = (float)return_num;
    else
        color_rgb->value.i = (int)return_num;
    
    mycore_string_destroy(&str, false);
}

static bool mycss_values_color_parser_set_angle_value(mycss_entry_t* entry, mycss_token_t* token, mycss_values_angle_t *angle)
{
    mycore_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    bool is_float;
    double return_num;
    
    size_t consume_length = mycss_convert_data_to_double(str.data, str.length, &return_num, &is_float);
    mycss_units_type_t type = mycss_units_type_by_name(&str.data[consume_length], (str.length - consume_length));
    
    mycore_string_destroy(&str, false);
    
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
        angle->value.f = (float)return_num;
    else
        angle->value.i = (int)return_num;
    
    angle->is_float = is_float;
    angle->type = type;
    
    return true;
}

static bool mycss_values_color_parser_rgb_full(mycss_entry_t* entry, mycss_token_t* token, mycss_values_color_t *color)
{
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE)
    {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.rgba_percentage.r);
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
        entry->parser = mycss_values_color_parser_rgb_before_g_percentage;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.rgba_number.r);
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
        entry->parser = mycss_values_color_parser_rgb_before_g_number;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_rgb_g_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.rgba_percentage.g);
    
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
            mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.rgba_percentage.b);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_rgb_alpha_percentage;
                return true;
            }
            /* fall through */
            
        default:
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_rgb_alpha_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.rgba_percentage.alpha.value.percentage);
        color->value.rgba_percentage.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.rgba_percentage.alpha.value.number);
        color->value.rgba_percentage.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_rgb_g_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_number_value(entry, token, &color->value.rgba_number.g);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_rgb_b_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_number_value(entry, token, &color->value.rgba_number.b);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_rgb_alpha_number;
                return true;
            }
            /* fall through */
            
        default:
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_rgb_alpha_number(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.rgba_number.alpha.value.percentage);
        color->value.rgba_number.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.rgba_number.alpha.value.number);
        color->value.rgba_number.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
        if(mycss_values_color_parser_set_angle_value(entry, token, &color->value.hsla.hue.value.angle) == false) {
            mycss_values_color_parser_switch_parser(entry);
            return false;
        }
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_ANGLE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.hsla.hue.value.number);
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_hsl_saturation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hsla.saturation);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_hsl_lightness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hsla.lightness);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_hsl_alpha;
                return true;
            }
            /* fall through */
            
        default:
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_hsl_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hsla.alpha.value.percentage);
        color->value.hsla.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.hsla.alpha.value.number);
        color->value.hsla.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
    return (mycore_string_chars_hex_map[ u_data[0] ] << 4) | mycore_string_chars_hex_map[ u_data[1] ];
}

bool mycss_values_color_parser_hex(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_HASH)
        return true;
        
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned char *u_data = (unsigned char*)str->data;
    mycss_values_color_t *color = (mycss_values_color_t*)mycss_values_create(entry, sizeof(mycss_values_color_t));
    
    switch (str->length) {
        case 6:
            color->value.hex.r.value.i = (int)mycss_values_color_parser_hex_get_by_two(u_data);
            color->value.hex.g.value.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[2]);
            color->value.hex.b.value.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[4]);
            color->value.hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_UNDEF;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_6;
            break;
        case 8:
            color->value.hex.r.value.i = (int)mycss_values_color_parser_hex_get_by_two(u_data);
            color->value.hex.g.value.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[2]);
            color->value.hex.b.value.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[4]);
            
            color->value.hex.alpha.value.number.value.i = (int)mycss_values_color_parser_hex_get_by_two(&u_data[6]);
            color->value.hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_8;
            break;
        case 3:
            color->value.hex.r.value.i = (int)(mycore_string_chars_hex_map[ u_data[0] ]);
            color->value.hex.r.value.i = (color->value.hex.r.value.i << 4) | color->value.hex.r.value.i;
            
            color->value.hex.g.value.i = (int)(mycore_string_chars_hex_map[ u_data[1] ]);
            color->value.hex.g.value.i = (color->value.hex.g.value.i << 4) | color->value.hex.g.value.i;
            
            color->value.hex.b.value.i = (int)(mycore_string_chars_hex_map[ u_data[2] ]);
            color->value.hex.b.value.i = (color->value.hex.b.value.i << 4) | color->value.hex.b.value.i;
            
            color->value.hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_UNDEF;
            
            color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_3;
            break;
        case 4:
            color->value.hex.r.value.i = (int)(mycore_string_chars_hex_map[ u_data[0] ]);
            color->value.hex.r.value.i = (color->value.hex.r.value.i << 4) | color->value.hex.r.value.i;
            
            color->value.hex.g.value.i = (int)(mycore_string_chars_hex_map[ u_data[1] ]);
            color->value.hex.g.value.i = (color->value.hex.g.value.i << 4) | color->value.hex.g.value.i;
            
            color->value.hex.b.value.i = (int)(mycore_string_chars_hex_map[ u_data[2] ]);
            color->value.hex.b.value.i = (color->value.hex.b.value.i << 4) | color->value.hex.b.value.i;
            
            color->value.hex.alpha.value.number.value.i = (int)(mycore_string_chars_hex_map[ u_data[3] ]);
            color->value.hex.alpha.value.number.value.i = (color->value.hex.alpha.value.number.value.i << 4) | color->value.hex.alpha.value.number.value.i;
            color->value.hex.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
            
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
        if(mycss_values_color_parser_set_angle_value(entry, token, &color->value.hwb.hue.value.angle) == false) {
            mycss_values_color_parser_switch_parser(entry);
            return false;
        }
        
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_ANGLE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.hwb.hue.value.number);
        color->type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
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
            mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hwb.saturation);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_hwb_blackness(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hwb.lightness);
    
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
            mycss_values_color_parser_switch_parser(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_hwb_alpha;
                return true;
            }
            /* fall through */
            
        default:
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_hwb_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.hwb.alpha.value.percentage);
        color->value.hwb.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.hwb.alpha.value.number);
        color->value.hwb.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.gray.number);
        color->type = MyCSS_VALUES_COLOR_TYPE_GRAY;
        
        entry->parser = mycss_values_color_parser_gray_before_alpha;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
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
            mycss_values_color_parser_switch_parser(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_DELIM:
            if(*token->data == '/') {
                entry->parser = mycss_values_color_parser_gray_alpha;
                return true;
            }
            /* fall through */
            
        default:
            mycss_values_color_parser_switch_parser(entry);
            return false;
    }
}

bool mycss_values_color_parser_gray_alpha(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(declr_entry->value == NULL) {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    mycss_values_color_t *color = declr_entry->value;
    
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE) {
        mycss_values_color_parser_set_percentage_value(entry, token, &color->value.gray.alpha.value.percentage);
        color->value.gray.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        mycss_values_color_parser_set_number_value(entry, token, &color->value.gray.alpha.value.number);
        color->value.gray.alpha.type_value = MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER;
    }
    else {
        mycss_values_color_parser_switch_parser(entry);
        return false;
    }
    
    entry->parser = mycss_values_color_parser_find_end;
    return true;
}


