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

#include "mycss/property/shared.h"

bool mycss_property_shared_switch_to_find_important(mycss_entry_t* entry)
{
    entry->parser = mycss_declaration_state_colon_before_important;
    return true;
}

bool mycss_property_shared_switch_to_parse_error(mycss_entry_t* entry)
{
    entry->parser = mycss_declaration_state_parse_error;
    return false;
}

bool mycss_property_shared_check_declaration_end(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_SEMICOLON) {
        entry->parser = mycss_declaration_state_data;
        return true;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_DELIM && *token->data == '!') {
        entry->parser = mycss_declaration_state_colon_important;
        return true;
    }
    else if(token->type == entry->declaration->ending_token) {
        mycss_entry_parser_list_pop(entry);
        mycss_declaration_parser_end(entry, token);
        
        return true;
    }
    
    return false;
}

bool mycss_property_shared_number(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER)
        return false;
    
    mycss_values_length_t *length = mycss_values_create(entry, sizeof(mycss_values_length_t));
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str->data, str->length, &return_num, &length->is_float);
    
    if(length->is_float)
        length->value.f = (float)return_num;
    else
        length->value.i = (int)return_num;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__NUMBER;
    
    return true;
}

bool mycss_property_shared_length(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_DIMENSION && token->type != MyCSS_TOKEN_TYPE_NUMBER)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num; bool is_float;
    size_t consume_length = mycss_convert_data_to_double(str->data, str->length, &return_num, &is_float);
    
    mycss_units_type_t type = mycss_units_type_by_name(&str->data[consume_length], (str->length - consume_length));
    
    if(type == MyCSS_UNIT_TYPE_UNDEF)
        if(is_float == true || (long)return_num != 0)
            return false;
    
    mycss_values_length_t *length = mycss_values_create(entry, sizeof(mycss_values_length_t));
    
    if(is_float)
        length->value.f = (float)return_num;
    else
        length->value.i = (int)return_num;
    
    length->is_float = is_float;
    length->type = type;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__LENGTH;
    
    return true;
}

bool mycss_property_shared_resolution(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_DIMENSION)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num; bool is_float;
    size_t consume_length = mycss_convert_data_to_double(str->data, str->length, &return_num, &is_float);
    
    mycss_units_type_t type = mycss_units_type_by_name(&str->data[consume_length], (str->length - consume_length));
    
    switch (type) {
        case MyCSS_UNIT_TYPE_DPI:
        case MyCSS_UNIT_TYPE_DPCM:
        case MyCSS_UNIT_TYPE_DPPX:
            break;
            
        default:
            return false;
    }
    
    mycss_values_resolution_t *resolution = mycss_values_create(entry, sizeof(mycss_values_resolution_t));
    
    if(is_float)
        resolution->value.f = (float)return_num;
    else
        resolution->value.i = (int)return_num;
    
    resolution->is_float = is_float;
    resolution->type = type;
    
    *value = resolution;
    *value_type = MyCSS_PROPERTY_VALUE__RESOLUTION;
    
    return true;
}

bool mycss_property_shared_custom_ident(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(*value) {
        mycss_values_custom_ident_t *custom_ident = *value;
        mycss_token_data_to_string(entry, token, &custom_ident->str, true, false);
        
        if(value_type)
            *value_type = MyCSS_PROPERTY_VALUE__CUSTOM_IDENT;
    }
    else {
        mycss_values_custom_ident_t *custom_ident = mycss_values_create(entry, sizeof(mycss_values_custom_ident_t));
        mycss_token_data_to_string(entry, token, &custom_ident->str, true, false);
        
        *value = custom_ident;
        
        if(value_type)
            *value_type = MyCSS_PROPERTY_VALUE__CUSTOM_IDENT;
    }
    
    return true;
}

bool mycss_property_shared_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE)
        return false;
    
    mycss_values_percentage_t *length = mycss_values_create(entry, sizeof(mycss_values_length_t));
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str->data, str->length, &return_num, &length->is_float);
    
    if(length->is_float)
        length->value.f = (float)return_num;
    else
        length->value.i = (int)return_num;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__PERCENTAGE;
    
    return true;
}

bool mycss_property_shared_length_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    return mycss_property_shared_length(entry, token, value, value_type, str) ||
    mycss_property_shared_percentage(entry, token, value, value_type, str);
}

bool mycss_property_shared_color(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str, bool* parser_changed)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_FUNCTION:
        {
            if(str->data == NULL)
                mycss_token_data_to_string(entry, token, str, true, false);
            
            const mycss_values_color_function_index_static_entry_t *color_entry =
                mycss_values_color_function_index_entry_by_name(str->data, str->length);
            
            if(color_entry) {
                *value = mycss_values_create(entry, sizeof(mycss_values_color_t));
                *value_type = MyCSS_PROPERTY_VALUE__COLOR;
                
                *parser_changed = true;
                entry->parser = color_entry->parser;
                
                return true;
            }
            
            break;
        }
            
        case MyCSS_TOKEN_TYPE_IDENT:
        {
            if(str->data == NULL)
                mycss_token_data_to_string(entry, token, str, true, false);
            
            const mycss_values_color_index_static_entry_t *color_entry =
                mycss_values_color_index_entry_by_name(str->data, str->length);
            
            if(color_entry) {
                mycss_values_color_t *color = mycss_values_create(entry, sizeof(mycss_values_color_t));
                
                color->value.name_id = color_entry->type;
                color->type          = MyCSS_VALUES_COLOR_TYPE_NAMED;
                
                *value = color;
                *value_type = MyCSS_PROPERTY_VALUE__COLOR;
                return true;
            }
            
            break;
        }
            
        case MyCSS_TOKEN_TYPE_HASH: {
            return mycss_values_color_parser_hex(entry, token, value, value_type, str);
        }
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_text_decoration_skip(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value,
                                                unsigned int* value_type, mycore_string_t* str, bool with_global)
{
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned int text_dec_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (text_dec_type) {
        case MyCSS_PROPERTY_TEXT_DECORATION_SKIP_OBJECTS:
            if(*value & MyCSS_VALUES_TEXT_DECORATION_SKIP_OBJECTS)
                return false;
            
            *value |= MyCSS_VALUES_TEXT_DECORATION_SKIP_OBJECTS;
            
            entry->parser = mycss_property_parser_text_decoration_skip_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_SKIP_SPACES:
            if(*value & MyCSS_VALUES_TEXT_DECORATION_SKIP_SPACES)
                return false;
            
            *value |= MyCSS_VALUES_TEXT_DECORATION_SKIP_SPACES;
            
            entry->parser = mycss_property_parser_text_decoration_skip_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_SKIP_INK:
            if(*value & MyCSS_VALUES_TEXT_DECORATION_SKIP_INK)
                return false;
            
            *value |= MyCSS_VALUES_TEXT_DECORATION_SKIP_INK;
            
            entry->parser = mycss_property_parser_text_decoration_skip_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_SKIP_EDGES:
            if(*value & MyCSS_VALUES_TEXT_DECORATION_SKIP_EDGES)
                return false;
            
            *value |= MyCSS_VALUES_TEXT_DECORATION_SKIP_EDGES;
            
            entry->parser = mycss_property_parser_text_decoration_skip_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_SKIP_BOX_DECORATION:
            if(*value & MyCSS_VALUES_TEXT_DECORATION_SKIP_BOX_DECORATION)
                return false;
            
            *value |= MyCSS_VALUES_TEXT_DECORATION_SKIP_BOX_DECORATION;
            
            entry->parser = mycss_property_parser_text_decoration_skip_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            if(with_global) {
                *value_type = text_dec_type;
                return true;
            }
            
            break;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_text_decoration_line(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value,
                                                unsigned int* value_type, mycore_string_t* str, bool with_global)
{
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned int text_dec_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (text_dec_type) {
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_UNDERLINE:
            *value |= MyCSS_VALUES_TEXT_DECORATION_LINE_UNDERLINE;
            
            entry->parser = mycss_property_parser_text_decoration_line_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_OVERLINE:
            *value |= MyCSS_VALUES_TEXT_DECORATION_LINE_OVERLINE;
            
            entry->parser = mycss_property_parser_text_decoration_line_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_LINE_THROUGH:
            *value |= MyCSS_VALUES_TEXT_DECORATION_LINE_LINE_THROUGH;
            
            entry->parser = mycss_property_parser_text_decoration_line_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_BLINK:
            *value |= MyCSS_VALUES_TEXT_DECORATION_LINE_BLINK;
            
            entry->parser = mycss_property_parser_text_decoration_line_not_none;
            return true;
            
        case MyCSS_PROPERTY_TEXT_DECORATION_LINE_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            if(with_global) {
                *value_type = text_dec_type;
                return true;
            }
            /* fall through */
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_text_decoration_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned int valye_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (valye_type) {
        case MyCSS_PROPERTY_TEXT_DECORATION_STYLE_SOLID:
        case MyCSS_PROPERTY_TEXT_DECORATION_STYLE_DOUBLE:
        case MyCSS_PROPERTY_TEXT_DECORATION_STYLE_DOTTED:
        case MyCSS_PROPERTY_TEXT_DECORATION_STYLE_DASHED:
        case MyCSS_PROPERTY_TEXT_DECORATION_STYLE_WAVY:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            *value_type = valye_type;
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_default(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            break;
            
        default:
            *value_type = MyCSS_PROPERTY_TYPE_UNDEF;
            return false;
    }
    
    return true;
}

unsigned int mycss_property_shared_get_value_type(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return MyCSS_PROPERTY_TYPE_UNDEF;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    return mycss_property_value_type_by_name(str->data, str->length);
}

bool mycss_property_shared_by_value_type(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, unsigned int check_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(check_type == mycss_property_value_type_by_name(str->data, str->length)) {
        *value_type = check_type;
        return true;
    }
    
    return false;
}

bool mycss_property_shared_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_WIDTH_AUTO:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            break;
            
        default:
            *value_type = MyCSS_PROPERTY_TYPE_UNDEF;
            return false;
    }
    
    return true;
}

bool mycss_property_shared_height(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_HEIGHT_AUTO:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            break;
            
        default:
            *value_type = MyCSS_PROPERTY_TYPE_UNDEF;
            return false;
    }
    
    return true;
}

bool mycss_property_shared_line_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BORDER_WIDTH_THIN:
        case MyCSS_PROPERTY_BORDER_WIDTH_MEDIUM:
        case MyCSS_PROPERTY_BORDER_WIDTH_THICK:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            break;
            
        default:
            *value_type = MyCSS_PROPERTY_TYPE_UNDEF;
            return false;
    }
    
    return true;
}

bool mycss_property_shared_line_height(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str) ||
       mycss_property_shared_number(entry, token, value, value_type, str))
    {
        return true;
    }
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_LINE_HEIGHT_NORMAL:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_line_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BORDER_STYLE_NONE:
        case MyCSS_PROPERTY_BORDER_STYLE_HIDDEN:
        case MyCSS_PROPERTY_BORDER_STYLE_DOTTED:
        case MyCSS_PROPERTY_BORDER_STYLE_DASHED:
        case MyCSS_PROPERTY_BORDER_STYLE_SOLID:
        case MyCSS_PROPERTY_BORDER_STYLE_DOUBLE:
        case MyCSS_PROPERTY_BORDER_STYLE_GROOVE:
        case MyCSS_PROPERTY_BORDER_STYLE_RIDGE:
        case MyCSS_PROPERTY_BORDER_STYLE_INSET:
        case MyCSS_PROPERTY_BORDER_STYLE_OUTSET:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            break;
            
        default:
            *value_type = MyCSS_PROPERTY_TYPE_UNDEF;
            return false;
    }
    
    return true;
}

void mycss_property_shared_destroy_string(mycore_string_t* str)
{
    mycore_string_destroy(str, false);
}

bool mycss_property_shared_font_ends(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_FONT_CAPTION:
        case MyCSS_PROPERTY_FONT_ICON:
        case MyCSS_PROPERTY_FONT_MENU:
        case MyCSS_PROPERTY_FONT_MESSAGE_BOX:
        case MyCSS_PROPERTY_FONT_SMALL_CAPTION:
        case MyCSS_PROPERTY_FONT_STATUS_BAR:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

static mycss_values_font_family_entry_t * mycss_property_shared_font_family_check(mycss_entry_t* entry, void** value)
{
    if(*value == NULL)
        *value = mycss_values_create(entry, sizeof(mycss_values_font_family_t));
    
    mycss_values_font_family_t *font_family = *value;
    
    if(font_family->entries) {
        font_family->entries = mycss_values_realloc(entry, font_family->entries,
                                                    (sizeof(mycss_values_font_family_entry_t) * font_family->entries_length),
                                                    sizeof(mycss_values_font_family_entry_t));
    }
    else
        font_family->entries = mycss_values_create(entry, sizeof(mycss_values_font_family_entry_t));
    
    mycss_values_font_family_entry_t *ff_entry = &font_family->entries[font_family->entries_length];
    font_family->entries_length++;
    
    return ff_entry;
}

bool mycss_property_shared_font_family(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, bool* dont_destroy_str, mycore_string_t* str)
{
    *dont_destroy_str = false;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT && token->type != MyCSS_TOKEN_TYPE_STRING)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    unsigned int family_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (family_type) {
        case MyCSS_PROPERTY_FONT_FAMILY_SERIF:
        case MyCSS_PROPERTY_FONT_FAMILY_SANS_SERIF:
        case MyCSS_PROPERTY_FONT_FAMILY_CURSIVE:
        case MyCSS_PROPERTY_FONT_FAMILY_FANTASY:
        case MyCSS_PROPERTY_FONT_FAMILY_MONOSPACE: {
            mycss_values_font_family_entry_t *ff_entry = mycss_property_shared_font_family_check(entry, value);
            
            ff_entry->type = MyCSS_VALUES_FONT_FAMILY_TYPE_GENERIC;
            ff_entry->value.prop_type = family_type;
            
            return true;
        }
            
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET: {
            if(*value)
                return false;
            
            switch (*value_type) {
                case MyCSS_PROPERTY_VALUE_INHERIT:
                case MyCSS_PROPERTY_VALUE_INITIAL:
                case MyCSS_PROPERTY_VALUE_UNSET:
                    return false;
                    
                default:
                    *value_type = family_type;
                    return true;
            }
        }
            
        default: {
            mycss_values_font_family_entry_t *ff_entry = mycss_property_shared_font_family_check(entry, value);
            
            ff_entry->type = MyCSS_VALUES_FONT_FAMILY_TYPE_NAME;
            ff_entry->value.str = *str;
            
            *dont_destroy_str = true;
            return true;
        }
    }
}

bool mycss_property_shared_font_weight(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT && token->type != MyCSS_TOKEN_TYPE_NUMBER)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_FONT_WEIGHT_NORMAL:
        case MyCSS_PROPERTY_FONT_WEIGHT_BOLD:
        case MyCSS_PROPERTY_FONT_WEIGHT_BOLDER:
        case MyCSS_PROPERTY_FONT_WEIGHT_LIGHTER:
        case MyCSS_PROPERTY_FONT_WEIGHT_100:
        case MyCSS_PROPERTY_FONT_WEIGHT_200:
        case MyCSS_PROPERTY_FONT_WEIGHT_300:
        case MyCSS_PROPERTY_FONT_WEIGHT_400:
        case MyCSS_PROPERTY_FONT_WEIGHT_500:
        case MyCSS_PROPERTY_FONT_WEIGHT_600:
        case MyCSS_PROPERTY_FONT_WEIGHT_700:
        case MyCSS_PROPERTY_FONT_WEIGHT_800:
        case MyCSS_PROPERTY_FONT_WEIGHT_900:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_font_size(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_FONT_SIZE_XX_SMALL:
        case MyCSS_PROPERTY_FONT_SIZE_X_SMALL:
        case MyCSS_PROPERTY_FONT_SIZE_SMALL:
        case MyCSS_PROPERTY_FONT_SIZE_MEDIUM:
        case MyCSS_PROPERTY_FONT_SIZE_LARGE:
        case MyCSS_PROPERTY_FONT_SIZE_X_LARGE:
        case MyCSS_PROPERTY_FONT_SIZE_XX_LARGE:
        case MyCSS_PROPERTY_FONT_SIZE_LARGER:
        case MyCSS_PROPERTY_FONT_SIZE_SMALLER:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_font_stretch(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_FONT_STRETCH_NORMAL:
        case MyCSS_PROPERTY_FONT_STRETCH_ULTRA_CONDENSED:
        case MyCSS_PROPERTY_FONT_STRETCH_EXTRA_CONDENSED:
        case MyCSS_PROPERTY_FONT_STRETCH_CONDENSED:
        case MyCSS_PROPERTY_FONT_STRETCH_SEMI_CONDENSED:
        case MyCSS_PROPERTY_FONT_STRETCH_SEMI_EXPANDED:
        case MyCSS_PROPERTY_FONT_STRETCH_EXPANDED:
        case MyCSS_PROPERTY_FONT_STRETCH_EXTRA_EXPANDED:
        case MyCSS_PROPERTY_FONT_STRETCH_ULTRA_EXPANDED:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_font_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_FONT_STYLE_NORMAL:
        case MyCSS_PROPERTY_FONT_STYLE_ITALIC:
        case MyCSS_PROPERTY_FONT_STYLE_OBLIQUE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return true;
            
        default:
            break;
    }
    
    return false;
}

bool mycss_property_shared_url(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type == MyCSS_TOKEN_TYPE_URL)
    {
        mycore_string_t *new_str = mycss_values_create(entry, sizeof(mycore_string_t));
        mycss_token_data_to_string(entry, token, new_str, true, false);
        
        *value = new_str;
        *value_type = MyCSS_PROPERTY_VALUE__URL;
        
        return true;
    }
    
    if(token->type != MyCSS_TOKEN_TYPE_FUNCTION)
        return false;
    
    if(str->length != 3)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(mycore_strcasecmp(str->data, "url"))
        return false;
    
    entry->parser = mycss_property_parser_url_string;
    *value_type = MyCSS_PROPERTY_VALUE__URL;
    
    return true;
}

bool mycss_property_shared_image(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str, bool* parser_changed)
{
    if(token->type == MyCSS_TOKEN_TYPE_URL)
    {
        mycss_values_image_t *image;
        
        if(*value)
            image = *value;
        else
            *value = image = mycss_values_create(entry, sizeof(mycss_values_image_t));
        
        image->type = MyCSS_PROPERTY_VALUE__URL;
        mycss_values_url_t *url = mycss_values_image_creator_url(entry, image);
        
        *value_type = MyCSS_PROPERTY_VALUE__IMAGE;
        
        mycss_token_data_to_string(entry, token, &url->str, true, false);
        return true;
    }
    
    if(token->type != MyCSS_TOKEN_TYPE_FUNCTION)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    const mycss_values_image_function_index_static_entry_t *func_entry = mycss_values_image_index_entry_by_name(str->data, str->length);
    
    if(func_entry == NULL || func_entry->type == MyCSS_PROPERTY_VALUE_UNDEF)
        return false;
    
    mycss_values_image_t *image;
    
    if(*value)
        image = *value;
    else
        *value = image = mycss_values_create(entry, sizeof(mycss_values_image_t));
    
    image->type = func_entry->type;
    
    *value_type = MyCSS_PROPERTY_VALUE__IMAGE;
    func_entry->obj_creator(entry, image);
    
    *parser_changed = true;
    entry->parser = func_entry->parser;
    
    return true;
}

bool mycss_property_shared_background_repeat_one(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_REPEAT_X:
        case MyCSS_PROPERTY_BACKGROUND_REPEAT_Y:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_background_repeat_two(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_REPEAT:
        case MyCSS_PROPERTY_BACKGROUND_SPACE:
        case MyCSS_PROPERTY_BACKGROUND_ROUND:
        case MyCSS_PROPERTY_BACKGROUND_NO_REPEAT:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_background_attachment(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_ATTACHMENT_FIXED:
        case MyCSS_PROPERTY_BACKGROUND_ATTACHMENT_LOCAL:
        case MyCSS_PROPERTY_BACKGROUND_ATTACHMENT_SCROLL:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_background_position(mycss_entry_t* entry, mycss_token_t* token, void* value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
        case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
        case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
        case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
        case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_background_clip(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_CLIP_BORDER_BOX:
        case MyCSS_PROPERTY_BACKGROUND_CLIP_PADDING_BOX:
        case MyCSS_PROPERTY_BACKGROUND_CLIP_CONTENT_BOX:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}

bool mycss_property_shared_background_size(mycss_entry_t* entry, mycss_token_t* token, void* value, unsigned int* value_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO:
        case MyCSS_PROPERTY_BACKGROUND_SIZE_COVER:
        case MyCSS_PROPERTY_BACKGROUND_SIZE_CONTAIN:
            return true;
            
        default:
            *value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return false;
}








bool mycss_property_shared_function_image(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_FUNCTION)
        return false;
    
    if(str->length != 5)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(mycore_strcasecmp(str->data, "image"))
        return false;
    
    entry->parser = NULL;
    *value_type = MyCSS_PROPERTY_VALUE__URL;
    
    return true;
}

bool mycss_property_shared_function_image_set(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_FUNCTION)
        return false;
    
    if(str->length != 9)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(mycore_strcasecmp(str->data, "image-set"))
        return false;
    
    entry->parser = NULL;
    *value_type = MyCSS_PROPERTY_VALUE__URL;
    
    return true;
}

bool mycss_property_shared_element(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, mycore_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_FUNCTION)
        return false;
    
    if(str->length != 10)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(mycore_strcasecmp(str->data, "cross-fade"))
        return false;
    
    entry->parser = NULL;
    *value_type = MyCSS_PROPERTY_VALUE__URL;
    
    return true;
}


