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

#include "mycss/values/destroy.h"

mycss_values_shorthand_two_type_t * mycss_values_destroy_shorthand_two_type(mycss_entry_t* entry, mycss_values_shorthand_two_type_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    /* wrong!!! */
//    value->one = mycss_declaration_entry_destroy(entry->declaration, value->one, true);
//    value->two = mycss_declaration_entry_destroy(entry->declaration, value->two, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_shorthand_four_t * mycss_values_destroy_shorthand_four(mycss_entry_t* entry, mycss_values_shorthand_four_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    value->one   = mycss_declaration_entry_destroy(entry->declaration, value->one, true);
    value->two   = mycss_declaration_entry_destroy(entry->declaration, value->two, true);
    value->three = mycss_declaration_entry_destroy(entry->declaration, value->three, true);
    value->four  = mycss_declaration_entry_destroy(entry->declaration, value->four, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_shorthand_two_t * mycss_values_destroy_shorthand_two(mycss_entry_t* entry, mycss_values_shorthand_two_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    value->one   = mycss_declaration_entry_destroy(entry->declaration, value->one, true);
    value->two   = mycss_declaration_entry_destroy(entry->declaration, value->two, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_number_t * mycss_values_destroy_number(mycss_entry_t* entry, mycss_values_number_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_length_t * mycss_values_destroy_length(mycss_entry_t* entry, mycss_values_length_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_percentage_t * mycss_values_destroy_percentage(mycss_entry_t* entry, mycss_values_percentage_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_angle_t * mycss_values_destroy_angle(mycss_entry_t* entry, mycss_values_angle_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_resolution_t * mycss_values_destroy_resolution(mycss_entry_t* entry, mycss_values_resolution_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_type_list_t * mycss_values_destroy_type_list(mycss_entry_t* entry, mycss_values_type_list_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_values_destroy(entry, (void*)value->entries);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Color
 */
mycss_values_color_alpha_value_t * mycss_values_destroy_color_alpha_value(mycss_entry_t* entry, mycss_values_color_alpha_value_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_hue_value_t * mycss_values_destroy_color_hue_value(mycss_entry_t* entry, mycss_values_color_hue_value_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_hsla_t * mycss_values_destroy_color_hsla(mycss_entry_t* entry, mycss_values_color_hsla_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_hwb_t * mycss_values_destroy_color_hwb(mycss_entry_t* entry, mycss_values_color_hwb_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_gray_t * mycss_values_destroy_color_gray(mycss_entry_t* entry, mycss_values_color_gray_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_rgba_number_t * mycss_values_destroy_color_rgba_number(mycss_entry_t* entry, mycss_values_color_rgba_number_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_rgba_percentage_t * mycss_values_destroy_color_rgba_percentage(mycss_entry_t* entry, mycss_values_color_rgba_percentage_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_color_t * mycss_values_destroy_color(mycss_entry_t* entry, mycss_values_color_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Font
 */
mycss_values_font_family_entry_t * mycss_values_destroy_font_family_entry(mycss_entry_t* entry, mycss_values_font_family_entry_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_font_family_t * mycss_values_destroy_font_family(mycss_entry_t* entry, mycss_values_font_family_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    value->entries_length = 0;
    value->entries = mycss_values_destroy(entry, (void*)value->entries);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_font_t * mycss_values_destroy_font(mycss_entry_t* entry, mycss_values_font_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    value->style       = mycss_declaration_entry_destroy(entry->declaration, value->style, true);
    value->weight      = mycss_declaration_entry_destroy(entry->declaration, value->weight, true);
    value->stretch     = mycss_declaration_entry_destroy(entry->declaration, value->stretch, true);
    value->size        = mycss_declaration_entry_destroy(entry->declaration, value->size, true);
    value->family      = mycss_declaration_entry_destroy(entry->declaration, value->family, true);
    value->line_height = mycss_declaration_entry_destroy(entry->declaration, value->line_height, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Text Decoration
 */
mycss_values_text_decoration_t * mycss_values_destroy_text_decoration(mycss_entry_t* entry, mycss_values_text_decoration_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    value->style = mycss_declaration_entry_destroy(entry->declaration, value->style, true);
    value->line  = mycss_declaration_entry_destroy(entry->declaration, value->line, true);
    value->color = mycss_declaration_entry_destroy(entry->declaration, value->color, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * String
 */
mycore_string_t * mycss_values_destroy_string(mycss_entry_t* entry, mycore_string_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycore_string_destroy(value, false);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * URL
 */
mycss_values_url_t * mycss_values_destroy_url(mycss_entry_t* entry, mycss_values_url_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(value->str.data)
        mycss_values_destroy_string(entry, &value->str, false);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Image
 */
mycss_values_image_t * mycss_values_destroy_image(mycss_entry_t* entry, mycss_values_image_t* image, bool self_destroy)
{
    if(image == NULL)
        return NULL;
    
    switch (image->type) {
        case MyCSS_PROPERTY_VALUE__URL:
            image->value.url = mycss_values_destroy_url(entry, image->value.url, true);
            break;
            
        case MyCSS_PROPERTY_VALUE__IMAGE_FUNCTION:
            image->value.ii = mycss_values_destroy_image_image(entry, image->value.ii, true);
            break;
            
        case MyCSS_PROPERTY_VALUE__IMAGE_SET_FUNCTION:
            image->value.ii_set = mycss_values_destroy_image_image_set(entry, image->value.ii_set, true);
            break;
            
        case MyCSS_PROPERTY_VALUE__ELEMENT_FUNCTION:
            image->value.element = mycss_values_destroy_element(entry, image->value.element, true);
            break;
            
        case MyCSS_PROPERTY_VALUE__CROSS_FADE_FUNCTION:
            image->value.cross_fade = mycss_values_destroy_cross_fade(entry, image->value.cross_fade, true);
            break;
            
        default:
            break;
    }
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)image);
        return NULL;
    }
    
    return image;
}

mycss_values_image_image_t * mycss_values_destroy_image_image(mycss_entry_t* entry, mycss_values_image_image_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(value->image)
        mycss_values_destroy_image(entry, value->image, true);
    
    if(value->str)
        mycss_values_destroy_string(entry, value->str, true);
    
    if(value->color)
        mycss_values_destroy_color(entry, value->color, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_image_image_set_t * mycss_values_destroy_image_image_set(mycss_entry_t* entry, mycss_values_image_image_set_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    for(size_t i = 0; i < value->options_length; i++) {
        mycss_values_image_image_set_option_t* option = &value->options[i];
        
        if(option->image)
            mycss_values_destroy_image(entry, option->image, true);
        
        if(option->str)
            mycss_values_destroy_string(entry, option->str, true);
        
        if(option->resolution)
            mycss_values_destroy_resolution(entry, option->resolution, true);
    }
    
    mycss_values_destroy(entry, (void*)value->options);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_element_t * mycss_values_destroy_element(mycss_entry_t* entry, mycss_values_element_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_values_destroy_string(entry, &value->custom_ident.str, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_cross_fade_t * mycss_values_destroy_cross_fade(mycss_entry_t* entry, mycss_values_cross_fade_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(value->mixing_image.image)
        mycss_values_destroy_image(entry, value->mixing_image.image, true);
    
    if(value->mixing_image.percentage)
        mycss_values_destroy_percentage(entry, value->mixing_image.percentage, true);
    
    if(value->final_image.image)
        mycss_values_destroy_image(entry, value->final_image.image, true);
    
    if(value->final_image.color)
        mycss_values_destroy_color(entry, value->final_image.color, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Image List
 */
mycss_values_image_list_t * mycss_values_destroy_image_list(mycss_entry_t* entry, mycss_values_image_list_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    for(size_t i = 0; i < value->images_length; i++) {
        mycss_values_destroy_image(entry, &value->images[i], false);
    }
    
    mycss_values_destroy(entry, (void*)value->images);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

/*
 * Background
 */
mycss_values_background_repeat_list_t * mycss_values_destroy_background_repeat(mycss_entry_t* entry, mycss_values_background_repeat_list_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_values_destroy(entry, (void*)value->entries);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_background_position_t * mycss_values_destroy_background_position(mycss_entry_t* entry, mycss_values_background_position_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(value->one.value.length) {
        mycss_values_destroy(entry, (void*)value->one.value.length);
    }
    
    if(value->two.value.length) {
        mycss_values_destroy(entry, (void*)value->two.value.length);
    }
    
    if(value->three.value.length) {
        mycss_values_destroy(entry, (void*)value->three.value.length);
    }
    
    if(value->four.value.length) {
        mycss_values_destroy(entry, (void*)value->four.value.length);
    }
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_background_size_list_t * mycss_values_destroy_background_size(mycss_entry_t* entry, mycss_values_background_size_list_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    for(size_t i = 0; i < value->entries_length; i++) {
        if(value->entries[i].width) {
            if(value->entries[i].width->value.percentage)
                mycss_values_destroy(entry, (void*)value->entries[i].width->value.percentage);
            
            mycss_values_destroy(entry, (void*)value->entries[i].width);
        }
        
        if(value->entries[i].height) {
            if(value->entries[i].height->value.percentage)
                mycss_values_destroy(entry, (void*)value->entries[i].height->value.percentage);
            
            mycss_values_destroy(entry, (void*)value->entries[i].height);
        }
    }
    
    mycss_values_destroy(entry, (void*)value->entries);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}

mycss_values_background_t * mycss_values_destroy_background(mycss_entry_t* entry, mycss_values_background_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;

    if(value->color)
        mycss_values_destroy_color(entry, value->color->value, true);
    if(value->image)
        mycss_values_destroy_image(entry, value->image->value, true);
    if(value->position)
        mycss_values_destroy_background_position(entry, value->position->value, true);
    if(value->size)
        mycss_values_destroy_background_size(entry, value->size->value, true);
    if(value->repeat)
        mycss_values_destroy_background_repeat(entry, value->repeat->value, true);
    if(value->attachment)
        mycss_values_destroy_type_list(entry, value->attachment->value, true);
    if(value->clip)
        mycss_values_destroy_type_list(entry, value->clip->value, true);
    if(value->origin)
        mycss_values_destroy_type_list(entry, value->origin->value, true);

    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }

    return value;
}

/*
 * Border
 */
mycss_values_border_t * mycss_values_destroy_border(mycss_entry_t* entry, mycss_values_border_t* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(value->width)
        value->width = mycss_declaration_entry_destroy(entry->declaration, value->width, true);
    
    if(value->style)
        value->style = mycss_declaration_entry_destroy(entry->declaration, value->style, true);
    
    if(value->color)
        value->color = mycss_declaration_entry_destroy(entry->declaration, value->color, true);
    
    if(self_destroy) {
        mycss_values_destroy(entry, (void*)value);
        return NULL;
    }
    
    return value;
}


