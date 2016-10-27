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

#include "mycss/values/serialization.h"
#include "mycss/values/units_resources.h"
#include "mycss/property/resources_name.h"
#include "myhtml/utils/resources.h"

static void mycss_values_serialization_to_callback(const char* data, size_t len, mycss_callback_serialization_f callback, void* context)
{
    if(len > 0)
        callback(data, len, context);
}

void mycss_values_serialization_number(mycss_values_number_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
}

void mycss_values_serialization_length(mycss_values_length_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    
    if(value->type < MyCSS_UNIT_TYPE_LAST_ENTRY) {
        const char* name = mycss_units_index_name[ value->type ];
        callback(name, strlen(name), context);
    }
}

void mycss_values_serialization_angle(mycss_values_angle_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    
    if(value->type < MyCSS_UNIT_TYPE_LAST_ENTRY) {
        const char* name = mycss_units_index_name[ value->type ];
        callback(name, strlen(name), context);
    }
}

void mycss_values_serialization_percentage(mycss_values_percentage_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f%%", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d%%", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
}

static void mycss_values_serialization_color_hex_one_value(int value, unsigned char* data)
{
    data[0] = myhtml_string_hex_to_char_map[ (unsigned int)(value >> 4) ];
}

static void mycss_values_serialization_color_hex_two_value(int value, unsigned char* data)
{
    data[0] = myhtml_string_hex_to_char_map[ (unsigned int)(value >> 4) ];
    data[1] = myhtml_string_hex_to_char_map[ (unsigned int)((value) ^ ((value >> 4) << 4)) ];
}

void mycss_values_serialization_color(mycss_values_color_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    switch (value->type) {
        case MyCSS_VALUES_COLOR_TYPE_NAMED: {
            size_t length;
            const char *name = mycss_values_color_name_by_id(value->name_id, &length);
            
            mycss_values_serialization_to_callback(name, length, callback, context);
            break;
        }
            
        case MyCSS_VALUES_COLOR_TYPE_RGB:
        case MyCSS_VALUES_COLOR_TYPE_RGBA:
        {
            if(value->type == MyCSS_VALUES_COLOR_TYPE_RGB)
                callback("rgb(", 4, context);
            else
                callback("rgba(", 5, context);
            
            if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE)
            {
                mycss_values_serialization_percentage(&value->rgba_percentage.r, callback, context);
                
                callback(", ", 2, context);
                mycss_values_serialization_percentage(&value->rgba_percentage.g, callback, context);
                
                callback(", ", 2, context);
                mycss_values_serialization_percentage(&value->rgba_percentage.b, callback, context);
                mycss_values_serialization_color_alpha(&value->rgba_percentage.alpha, callback, context);
            }
            else if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER)
            {
                mycss_values_serialization_number(&value->rgba_number.r, callback, context);
                
                callback(", ", 2, context);
                mycss_values_serialization_number(&value->rgba_number.g, callback, context);
                
                callback(", ", 2, context);
                mycss_values_serialization_number(&value->rgba_number.b, callback, context);
                mycss_values_serialization_color_alpha(&value->rgba_number.alpha, callback, context);
            }
            
            callback(")", 1, context);
            
            break;
        }
           
        case MyCSS_VALUES_COLOR_TYPE_HSL:
        case MyCSS_VALUES_COLOR_TYPE_HSLA:
        {
            if(value->type == MyCSS_VALUES_COLOR_TYPE_HSL)
                callback("hsl(", 4, context);
            else
                callback("hsla(", 5, context);
            
            if(value->hsla.hue.type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER) {
                mycss_values_serialization_number(&value->hsla.hue.number, callback, context);
            }
            else {
                mycss_values_serialization_angle(&value->hsla.hue.angle, callback, context);
            }
            
            callback(", ", 2, context);
            mycss_values_serialization_percentage(&value->hsla.saturation, callback, context);
            
            callback(", ", 2, context);
            mycss_values_serialization_percentage(&value->hsla.lightness, callback, context);
            mycss_values_serialization_color_alpha(&value->hsla.alpha, callback, context);
            
            callback(")", 1, context);
            
            break;
        }
            
        case MyCSS_VALUES_COLOR_TYPE_HWB:
        {
            callback("hwb(", 4, context);
            
            if(value->hwb.hue.type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER) {
                mycss_values_serialization_number(&value->hwb.hue.number, callback, context);
            }
            else {
                mycss_values_serialization_angle(&value->hwb.hue.angle, callback, context);
            }
            
            callback(", ", 2, context);
            mycss_values_serialization_percentage(&value->hwb.saturation, callback, context);
            
            callback(", ", 2, context);
            mycss_values_serialization_percentage(&value->hwb.lightness, callback, context);
            mycss_values_serialization_color_alpha(&value->hwb.alpha, callback, context);
            
            callback(")", 1, context);
            
            break;
        }
            
        case MyCSS_VALUES_COLOR_TYPE_GRAY:
        {
            callback("gray(", 5, context);
            
            mycss_values_serialization_number(&value->gray.number, callback, context);
            mycss_values_serialization_color_alpha(&value->gray.alpha, callback, context);
            
            callback(")", 1, context);
            
            break;
        }
            
        case MyCSS_VALUES_COLOR_TYPE_HEX:
        {
            callback("#", 1, context);
            
            if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_8) {
                unsigned char data[9];
                
                mycss_values_serialization_color_hex_two_value(value->hex.r.i, data);
                mycss_values_serialization_color_hex_two_value(value->hex.g.i, &data[2]);
                mycss_values_serialization_color_hex_two_value(value->hex.b.i, &data[4]);
                mycss_values_serialization_color_hex_two_value(value->hex.alpha.number.i, &data[6]);
                
                data[8] = '\0';
                callback((const char*)data, 8, context);
            }
            else if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_6) {
                unsigned char data[7];
                
                mycss_values_serialization_color_hex_two_value(value->hex.r.i, data);
                mycss_values_serialization_color_hex_two_value(value->hex.g.i, &data[2]);
                mycss_values_serialization_color_hex_two_value(value->hex.b.i, &data[4]);
                
                data[6] = '\0';
                callback((const char*)data, 6, context);
            }
            else if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_4) {
                unsigned char data[5];
                
                mycss_values_serialization_color_hex_one_value(value->hex.r.i, data);
                mycss_values_serialization_color_hex_one_value(value->hex.g.i, &data[1]);
                mycss_values_serialization_color_hex_one_value(value->hex.b.i, &data[2]);
                mycss_values_serialization_color_hex_one_value(value->hex.alpha.number.i, &data[3]);
                
                data[4] = '\0';
                callback((const char*)data, 4, context);
            }
            else if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_HEX_3) {
                unsigned char data[4];
                
                mycss_values_serialization_color_hex_one_value(value->hex.r.i, data);
                mycss_values_serialization_color_hex_one_value(value->hex.g.i, &data[1]);
                mycss_values_serialization_color_hex_one_value(value->hex.b.i, &data[2]);
                
                data[3] = '\0';
                callback((const char*)data, 3, context);
            }
            
            break;
        }
            
        default:
            break;
    }
}

void mycss_values_serialization_color_alpha(mycss_values_color_alpha_value_t* value, mycss_callback_serialization_f callback, void* context)
{
    if(value == NULL)
        return;
    
    if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_PERCENTAGE) {
        callback(", ", 2, context);
        mycss_values_serialization_percentage(&value->percentage, callback, context);
    }
    else if(value->type_value == MyCSS_VALUES_COLOR_TYPE_VALUE_NUMBER) {
        callback(", ", 2, context);
        mycss_values_serialization_number(&value->number, callback, context);
    }
}

void mycss_values_serialization_text_decoration_line(mycss_values_text_decoration_line_t value, mycss_callback_serialization_f callback, void* context)
{
    const char *text_value = NULL;
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_LINE_UNDERLINE) {
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_LINE_UNDERLINE];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_LINE_OVERLINE) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_LINE_OVERLINE];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_LINE_LINE_THROUGH) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_LINE_LINE_THROUGH];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_LINE_BLINK) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_LINE_BLINK];
        callback(text_value, strlen(text_value), context);
    }
}

void mycss_values_serialization_text_decoration_skip(mycss_values_text_decoration_skip_t value, mycss_callback_serialization_f callback, void* context)
{
    const char *text_value = NULL;
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_SKIP_OBJECTS) {
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_SKIP_OBJECTS];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_SKIP_SPACES) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_SKIP_SPACES];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_SKIP_INK) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_SKIP_INK];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_SKIP_EDGES) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_SKIP_EDGES];
        callback(text_value, strlen(text_value), context);
    }
    
    if(value & MyCSS_VALUES_TEXT_DECORATION_SKIP_BOX_DECORATION) {
        if(text_value)
            callback(" || ", 4, context);
        
        text_value = mycss_property_index_type_value[MyCSS_PROPERTY_TEXT_DECORATION_SKIP_BOX_DECORATION];
        callback(text_value, strlen(text_value), context);
    }
}



