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

bool mycss_property_shared_number(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_NUMBER)
        return false;
    
    mycss_values_length_t *length = mycss_values_create(entry, sizeof(mycss_values_length_t));
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str->data, str->length, &return_num, &length->is_float);
    
    if(length->is_float)
        length->f = (float)return_num;
    else
        length->i = (int)return_num;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__NUMBER;
    
    return true;
}

bool mycss_property_shared_length(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
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
        length->f = (float)return_num;
    else
        length->i = (int)return_num;
    
    length->is_float = is_float;
    length->type = type;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__LENGTH;
    
    return true;
}

bool mycss_property_shared_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_PERCENTAGE)
        return false;
    
    mycss_values_percentage_t *length = mycss_values_create(entry, sizeof(mycss_values_length_t));
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    double return_num;
    mycss_convert_data_to_double(str->data, str->length, &return_num, &length->is_float);
    
    if(length->is_float)
        length->f = (float)return_num;
    else
        length->i = (int)return_num;
    
    *value = length;
    *value_type = MyCSS_PROPERTY_VALUE__PERCENTAGE;
    
    return true;
}

bool mycss_property_shared_length_percentage(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    return mycss_property_shared_length(entry, token, value, value_type, str) ||
    mycss_property_shared_percentage(entry, token, value, value_type, str);
}

bool mycss_property_shared_default(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, myhtml_string_t* str)
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

unsigned int mycss_property_shared_get_value_type(mycss_entry_t* entry, mycss_token_t* token, myhtml_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return MyCSS_PROPERTY_TYPE_UNDEF;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    return mycss_property_value_type_by_name(str->data, str->length);
}

bool mycss_property_shared_by_value_type(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, unsigned int check_type, myhtml_string_t* str)
{
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    if(check_type != mycss_property_value_type_by_name(str->data, str->length)) {
        *value_type = check_type;
        return true;
    }
    
    return false;
}

bool mycss_property_shared_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_WIDTH_AVAILABLE:
        case MyCSS_PROPERTY_WIDTH_MIN_CONTENT:
        case MyCSS_PROPERTY_WIDTH_MAX_CONTENT:
        case MyCSS_PROPERTY_WIDTH_FIT_CONTENT:
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

bool mycss_property_shared_height(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, value, value_type, str))
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return false;
    
    if(str->data == NULL)
        mycss_token_data_to_string(entry, token, str, true, false);
    
    *value_type = mycss_property_value_type_by_name(str->data, str->length);
    
    switch (*value_type) {
        case MyCSS_PROPERTY_HEIGHT_AVAILABLE:
        case MyCSS_PROPERTY_HEIGHT_MIN_CONTENT:
        case MyCSS_PROPERTY_HEIGHT_MAX_CONTENT:
        case MyCSS_PROPERTY_HEIGHT_FIT_CONTENT:
        case MyCSS_PROPERTY_HEIGHT_AUTO:
        case MyCSS_PROPERTY_HEIGHT_COMPLEX:
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

bool mycss_property_shared_line_width(mycss_entry_t* entry, mycss_token_t* token, void** value, unsigned int* value_type, myhtml_string_t* str)
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

bool mycss_property_shared_line_style(mycss_entry_t* entry, mycss_token_t* token, unsigned int* value_type, myhtml_string_t* str)
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

void mycss_property_shared_destroy_string(myhtml_string_t* str)
{
    myhtml_string_destroy(str, false);
}




