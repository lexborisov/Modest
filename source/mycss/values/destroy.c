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


