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

#include "mycss/property/parser.h"

bool mycss_property_parser_destroy_string(mycore_string_t* str, bool return_value)
{
    mycss_property_shared_destroy_string(str);
    return return_value;
}

bool mycss_property_parser_switcher_to_find_important(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    entry->parser = mycss_declaration_state_colon_before_important;
    return true;
}

/////////////////////////////////////////////////////////
//// CSS Property
////
/////////////////////////////////////////////////////////
bool mycss_property_parser_undef(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

/* width height */
bool mycss_property_parser_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_width(entry, token, &declr_entry->value, &declr_entry->value_type, &str)) {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_height(entry, token, &declr_entry->value, &declr_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_max_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    if(str.data == NULL)
        mycss_token_data_to_string(entry, token, &str, true, false);
    
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_MAX_WIDTH_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            dec_entry->value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_max_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_max_width(entry, token, last_response);
}

bool mycss_property_parser_min_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_min_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_min_width(entry, token, last_response);
}

/* padding */
mycss_declaration_entry_t * mycss_property_parser_padding_shared(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str)
{
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_length_percentage(entry, token, &value, &value_type, str) ||
       mycss_property_shared_default(entry, token, &value_type, str))
    {
        mycss_declaration_entry_t* decl = mycss_declaration_entry_create(entry->declaration, NULL);
        
        decl->value = value;
        decl->value_type = value_type;
        
        return decl;
    }
    
    return NULL;
}

bool mycss_property_parser_padding(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
    
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(value->one == NULL)
    {
        if((value->one = mycss_property_parser_padding_shared(entry, token, &str))) {
            value->one->type = MyCSS_PROPERTY_TYPE_PADDING_TOP;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_padding_shared(entry, token, &str))) {
            value->two->type = MyCSS_PROPERTY_TYPE_PADDING_RIGHT;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_padding_shared(entry, token, &str))) {
            value->three->type = MyCSS_PROPERTY_TYPE_PADDING_BOTTOM;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_padding_shared(entry, token, &str))) {
            value->four->type = MyCSS_PROPERTY_TYPE_PADDING_LEFT;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_padding_X(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_padding_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

/* padding logical */
bool mycss_property_parser_padding_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

bool mycss_property_parser_padding_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_padding_X(entry, token, last_response);
}

/* margin */
mycss_declaration_entry_t * mycss_property_parser_margin_shared(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str)
{
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_length_percentage(entry, token, &value, &value_type, str) ||
       mycss_property_shared_default(entry, token, &value_type, str) ||
       mycss_property_shared_by_value_type(entry, token, &value_type, MyCSS_PROPERTY_MARGIN_AUTO, str))
    {
        mycss_declaration_entry_t* decl = mycss_declaration_entry_create(entry->declaration, NULL);
        
        decl->value = value;
        decl->value_type = value_type;
        
        return decl;
    }
    
    return NULL;
}

bool mycss_property_parser_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
    
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(value->one == NULL)
    {
        if((value->one = mycss_property_parser_margin_shared(entry, token, &str))) {
            value->one->type = MyCSS_PROPERTY_TYPE_MARGIN_TOP;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_margin_shared(entry, token, &str))) {
            value->two->type = MyCSS_PROPERTY_TYPE_MARGIN_RIGHT;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_margin_shared(entry, token, &str))) {
            value->three->type = MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_margin_shared(entry, token, &str))) {
            value->four->type = MyCSS_PROPERTY_TYPE_MARGIN_LEFT;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_margin_X(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str) ||
       mycss_property_shared_by_value_type(entry, token, &dec_entry->value_type, MyCSS_PROPERTY_MARGIN_AUTO, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_margin_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

/* margin logical */
bool mycss_property_parser_margin_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

bool mycss_property_parser_margin_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_margin_X(entry, token, last_response);
}

/* display */
bool mycss_property_parser_display(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    
    if(token->type == MyCSS_TOKEN_TYPE_IDENT)
    {
        mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
        mycss_token_data_to_string(entry, token, &str, true, false);
        
        dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
        
        switch (dec_entry->value_type) {
            case MyCSS_PROPERTY_DISPLAY_BLOCK:
            case MyCSS_PROPERTY_DISPLAY_CONTENTS:
            case MyCSS_PROPERTY_DISPLAY_FLEX:
            case MyCSS_PROPERTY_DISPLAY_FLOW:
            case MyCSS_PROPERTY_DISPLAY_FLOW_ROOT:
            case MyCSS_PROPERTY_DISPLAY_GRID:
            case MyCSS_PROPERTY_DISPLAY_INLINE:
            case MyCSS_PROPERTY_DISPLAY_INLINE_BLOCK:
            case MyCSS_PROPERTY_DISPLAY_INLINE_FLEX:
            case MyCSS_PROPERTY_DISPLAY_INLINE_GRID:
            case MyCSS_PROPERTY_DISPLAY_INLINE_LIST_ITEM:
            case MyCSS_PROPERTY_DISPLAY_INLINE_TABLE:
            case MyCSS_PROPERTY_DISPLAY_LIST_ITEM:
            case MyCSS_PROPERTY_DISPLAY_NONE:
            case MyCSS_PROPERTY_DISPLAY_RUBY:
            case MyCSS_PROPERTY_DISPLAY_RUBY_BASE:
            case MyCSS_PROPERTY_DISPLAY_RUBY_BASE_CONTAINER:
            case MyCSS_PROPERTY_DISPLAY_RUBY_TEXT:
            case MyCSS_PROPERTY_DISPLAY_RUBY_TEXT_CONTAINER:
            case MyCSS_PROPERTY_DISPLAY_RUN_IN:
            case MyCSS_PROPERTY_DISPLAY_TABLE:
            case MyCSS_PROPERTY_DISPLAY_TABLE_CAPTION:
            case MyCSS_PROPERTY_DISPLAY_TABLE_CELL:
            case MyCSS_PROPERTY_DISPLAY_TABLE_COLUMN:
            case MyCSS_PROPERTY_DISPLAY_TABLE_COLUMN_GROUP:
            case MyCSS_PROPERTY_DISPLAY_TABLE_FOOTER_GROUP:
            case MyCSS_PROPERTY_DISPLAY_TABLE_HEADER_GROUP:
            case MyCSS_PROPERTY_DISPLAY_TABLE_ROW:
            case MyCSS_PROPERTY_DISPLAY_TABLE_ROW_GROUP:
                break;
                
            default:
                if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str) == false) {
                    dec_entry->value_type = MyCSS_PROPERTY_TYPE_UNDEF;
                    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
                }
                break;
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
}

/* border */
mycss_declaration_entry_t * mycss_property_parser_border_width_shared(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str)
{
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_line_width(entry, token, &value, &value_type, str))
    {
        mycss_declaration_entry_t* decl = mycss_declaration_entry_create(entry->declaration, NULL);
        
        decl->value = value;
        decl->value_type = value_type;
        
        return decl;
    }
    
    return NULL;
}

static mycss_declaration_entry_t * mycss_property_parser_border_color_shared(mycss_entry_t* entry, mycss_token_t* token,
                                                                             mycore_string_t* str, mycss_parser_token_f return_parser,
                                                                             unsigned int type)
{
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_color(entry, token, &value, &value_type, str, &parser_changed))
    {
        mycss_declaration_entry_t* step_dec_entry = mycss_declaration_entry_create(entry->declaration, NULL);
        
        step_dec_entry->type       = type;
        step_dec_entry->value      = value;
        step_dec_entry->value_type = value_type;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, entry->declaration->entry_last->value, return_parser);
            entry->declaration->entry_last->value = step_dec_entry->value;
        }
        
        return step_dec_entry;
    }
    
    return NULL;
}

mycss_declaration_entry_t * mycss_property_parser_border_style_shared(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str)
{
    unsigned int value_type = 0;
    
    if(mycss_property_shared_line_style(entry, token, &value_type, str))
    {
        mycss_declaration_entry_t* decl = mycss_declaration_entry_create(entry->declaration, NULL);
        decl->value_type = value_type;
        
        return decl;
    }
    
    return NULL;
}

bool mycss_property_parser_border_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    entry->parser = mycss_property_parser_border_top;
    return false;
}

bool mycss_property_parser_border(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top(entry, token, last_response);
}

bool mycss_property_parser_border_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    unsigned int value_type = 0;
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_default(entry, token, &value_type, &str))
    {
        if(dec_entry->value == NULL) {
            dec_entry->value_type = value_type;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_border_t));
    
    mycss_declaration_entry_t* shared_declr;
    mycss_values_border_t *border = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(border == NULL || (border->style == NULL && border->width == NULL && border->color == NULL))
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if((shared_declr = mycss_property_parser_border_width_shared(entry, token, &str))) {
        if(border->width)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        border->width = shared_declr;
        border->width->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if((shared_declr = mycss_property_parser_border_style_shared(entry, token, &str))) {
        if(border->style)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        border->style = shared_declr;
        border->style->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(border->color == NULL) {
        if((shared_declr = mycss_property_parser_border_color_shared(entry, token, &str,
                                                                    mycss_property_parser_border_after,
                                                                    MyCSS_PROPERTY_TYPE_BORDER_TOP_COLOR)))
        {
            border->color = shared_declr;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top(entry, token, last_response);
}

bool mycss_property_parser_border_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top(entry, token, last_response);
}

bool mycss_property_parser_border_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top(entry, token, last_response);
}

/* border logical */
bool mycss_property_parser_border_block_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border(entry, token, last_response);
}

bool mycss_property_parser_border_block_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border(entry, token, last_response);
}

bool mycss_property_parser_border_inline_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border(entry, token, last_response);
}

bool mycss_property_parser_border_inline_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border(entry, token, last_response);
}

/* border width */
bool mycss_property_parser_border_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
    
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(value->one == NULL)
    {
        if((value->one = mycss_property_parser_border_width_shared(entry, token, &str))) {
            value->one->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_border_width_shared(entry, token, &str))) {
            value->two->type = MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_border_width_shared(entry, token, &str))) {
            value->three->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_border_width_shared(entry, token, &str))) {
            value->four->type = MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_top_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_line_width(entry, token, &declr_entry->value, &declr_entry->value_type, &str)) {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_right_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_width(entry, token, last_response);
}

bool mycss_property_parser_border_bottom_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_width(entry, token, last_response);
}

bool mycss_property_parser_border_left_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_width(entry, token, last_response);
}

/* border width logical */
bool mycss_property_parser_border_block_start_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_width(entry, token, last_response);
}

bool mycss_property_parser_border_block_end_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_width(entry, token, last_response);
}

bool mycss_property_parser_border_inline_start_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_width(entry, token, last_response);
}

bool mycss_property_parser_border_inline_end_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_width(entry, token, last_response);
}

/* border style */
bool mycss_property_parser_border_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
    
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(value->one == NULL)
    {
        if((value->one = mycss_property_parser_border_style_shared(entry, token, &str))) {
            value->one->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_border_style_shared(entry, token, &str))) {
            value->two->type = MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_border_style_shared(entry, token, &str))) {
            value->three->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_border_style_shared(entry, token, &str))) {
            value->four->type = MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_top_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_line_style(entry, token, &declr_entry->value_type, &str)) {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_right_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_style(entry, token, last_response);
}

bool mycss_property_parser_border_bottom_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_style(entry, token, last_response);
}

bool mycss_property_parser_border_left_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_style(entry, token, last_response);
}

/* border style logical */
bool mycss_property_parser_border_block_start_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_style(entry, token, last_response);
}

bool mycss_property_parser_border_block_end_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_style(entry, token, last_response);
}

bool mycss_property_parser_border_inline_start_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_style(entry, token, last_response);
}

bool mycss_property_parser_border_inline_end_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_style(entry, token, last_response);
}

/* border radius */
static mycss_declaration_entry_t * mycss_property_parser_border_radius_shared(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str, bool is_first)
{
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_length_percentage(entry, token, &value, &value_type, str))
    {
        mycss_declaration_entry_t* decl = mycss_declaration_entry_create(entry->declaration, NULL);
        
        mycss_values_shorthand_two_type_t *short_two_type = mycss_values_create(entry, sizeof(mycss_values_shorthand_two_type_t));
        
        if(is_first) {
            short_two_type->one = value;
            short_two_type->type_one = value_type;
        }
        else {
            short_two_type->two = value;
            short_two_type->type_two = value_type;
        }
        
        decl->value = short_two_type;
        return decl;
    }
    
    return NULL;
}

static bool mycss_property_parser_border_radius_two_shared(mycss_entry_t* entry, mycss_token_t* token,
                                                    mycss_values_shorthand_two_type_t *short_two_type, mycore_string_t* str)
{
    if(mycss_property_shared_length_percentage(entry, token, &short_two_type->two, &short_two_type->type_two, str)) {
        return true;
    }
    
    return false;
}

bool mycss_property_parser_border_radius_two(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(((mycss_values_shorthand_two_type_t*)(value->one->value))->two == NULL)
    {
        if(mycss_property_parser_border_radius_two_shared(entry, token, value->one->value, &str))
            return mycss_property_parser_destroy_string(&str, true);
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_border_radius_shared(entry, token, &str, false))) {
            value->two->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_RIGHT_RADIUS;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(((mycss_values_shorthand_two_type_t*)(value->two->value))->two == NULL)
    {
        if(mycss_property_parser_border_radius_two_shared(entry, token, value->two->value, &str))
            return mycss_property_parser_destroy_string(&str, true);
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_border_radius_shared(entry, token, &str, false))) {
            value->three->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_RIGHT_RADIUS;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(((mycss_values_shorthand_two_type_t*)(value->three->value))->two == NULL)
    {
        if(mycss_property_parser_border_radius_two_shared(entry, token, value->three->value, &str))
            return mycss_property_parser_destroy_string(&str, true);
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_border_radius_shared(entry, token, &str, false))) {
            value->four->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_LEFT_RADIUS;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    else if(((mycss_values_shorthand_two_type_t*)(value->four->value))->two == NULL)
    {
        if(mycss_property_parser_border_radius_two_shared(entry, token, value->four->value, &str))
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

static bool mycss_property_parser_border_radius_wait_two(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_DELIM && *token->data == '/') {
        entry->parser = mycss_property_parser_border_radius_two;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
    
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(value->one == NULL)
    {
        if((value->one = mycss_property_parser_border_radius_shared(entry, token, &str, true))) {
            value->one->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_LEFT_RADIUS;
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        unsigned int value_type = 0;
        
        if(mycss_property_shared_default(entry, token, &value_type, &str)) {
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    else if(value->two == NULL)
    {
        if((value->two = mycss_property_parser_border_radius_shared(entry, token, &str, true))) {
            value->two->type = MyCSS_PROPERTY_TYPE_BORDER_TOP_RIGHT_RADIUS;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL)
    {
        if((value->three = mycss_property_parser_border_radius_shared(entry, token, &str, true))) {
            value->three->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_RIGHT_RADIUS;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL)
    {
        if((value->four = mycss_property_parser_border_radius_shared(entry, token, &str, true))) {
            value->four->type = MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_LEFT_RADIUS;
            
            entry->parser = mycss_property_parser_border_radius_wait_two;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_DELIM && *token->data == '/') {
        if(value->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        entry->parser = mycss_property_parser_border_radius_two;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_short_two_type(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_shorthand_two_type_t));
    
    mycss_values_shorthand_two_type_t *short_two_type = dec_entry->value;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        if(short_two_type->one == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
        
        return true;
    }
    
    mycore_string_t str = {0};
    
    if(short_two_type->one == NULL)
    {
        if(mycss_property_shared_length_percentage(entry, token, &short_two_type->one, &short_two_type->type_one, &str) ||
           mycss_property_shared_default(entry, token, &short_two_type->type_one, &str))
        {
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(short_two_type->two == NULL)
    {
        if(mycss_property_shared_length_percentage(entry, token, &short_two_type->two, &short_two_type->type_two, &str) ||
           mycss_property_shared_default(entry, token, &short_two_type->type_two, &str))
        {
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_top_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_short_two_type(entry, token);
}

bool mycss_property_parser_border_top_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_right_radius(entry, token, last_response);
}

bool mycss_property_parser_border_bottom_right_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_right_radius(entry, token, last_response);
}

bool mycss_property_parser_border_bottom_left_radius(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_border_top_right_radius(entry, token, last_response);
}

/* border color */
bool mycss_property_parser_border_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    mycss_values_shorthand_four_t *value = dec_entry->value;
    
    if(value == NULL)
    {
        unsigned int value_type = 0;
        if(mycss_property_shared_default(entry, token, &value_type, &str))
        {
            dec_entry->value_type = value_type;
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        }
        
        mycss_declaration_entry_t* shared_declr;
        dec_entry->value = value = mycss_values_create(entry, sizeof(mycss_values_shorthand_four_t));
        
        if((shared_declr = mycss_property_parser_border_color_shared(entry, token, &str, mycss_property_parser_border_color_after,
                                                                     MyCSS_PROPERTY_TYPE_BORDER_TOP_COLOR)))
        {
            value->one = shared_declr;
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->two == NULL) {
        if((value->two = mycss_property_parser_border_color_shared(entry, token, &str, mycss_property_parser_border_color_after,
                                                                   MyCSS_PROPERTY_TYPE_BORDER_RIGHT_COLOR)))
        {
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->three == NULL) {
        if((value->three = mycss_property_parser_border_color_shared(entry, token, &str, mycss_property_parser_border_color_after,
                                                                     MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_COLOR)))
        {
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    else if(value->four == NULL) {
        if((value->four = mycss_property_parser_border_color_shared(entry, token, &str, mycss_property_parser_border_color_after,
                                                                    MyCSS_PROPERTY_TYPE_BORDER_LEFT_COLOR)))
        {
            return mycss_property_parser_destroy_string(&str, true);
        }
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_border_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    entry->parser = mycss_property_parser_border_color;
    return false;
}

bool mycss_property_parser_border_top_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_right_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_bottom_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_left_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

/* border color logical */
bool mycss_property_parser_border_block_start_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_block_end_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_inline_start_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

bool mycss_property_parser_border_inline_end_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}

/* box sizing */
bool mycss_property_parser_box_sizing(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycore_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_BOX_SIZING_CONTENT_BOX:
        case MyCSS_PROPERTY_BOX_SIZING_BORDER_BOX:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* vertical align */
bool mycss_property_parser_vertical_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    if(str.data == NULL)
        mycss_token_data_to_string(entry, token, &str, true, false);
    
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_VERTICAL_ALIGN_BASELINE:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_SUB:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_SUPER:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_TOP:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_TEXT_TOP:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_MIDDLE:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_BOTTOM:
        case MyCSS_PROPERTY_VERTICAL_ALIGN_TEXT_BOTTOM:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* line height */
bool mycss_property_parser_line_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_line_height(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* color */
bool mycss_property_parser_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    bool parser_changed = false;
    
    dec_entry->value = NULL;
    
    if(mycss_property_shared_color(entry, token, &dec_entry->value, &dec_entry->value_type, &str, &parser_changed))
    {
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, NULL, mycss_property_parser_color_after);
            return true;
        }
        
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

/* position */
bool mycss_property_parser_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_POSITION_STATIC:
        case MyCSS_PROPERTY_POSITION_RELATIVE:
        case MyCSS_PROPERTY_POSITION_ABSOLUTE:
        case MyCSS_PROPERTY_POSITION_STICKY:
        case MyCSS_PROPERTY_POSITION_FIXED:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* z-index */
bool mycss_property_parser_z_index(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_number(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    if(str.data == NULL)
        mycss_token_data_to_string(entry, token, &str, true, false);
    
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_Z_INDEX_AUTO:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            dec_entry->value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* Cursor */
bool mycss_property_parser_cursor(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_CURSOR_AUTO:
        case MyCSS_PROPERTY_CURSOR_DEFAULT:
        case MyCSS_PROPERTY_CURSOR_NONE:
        case MyCSS_PROPERTY_CURSOR_CONTEXT_MENU:
        case MyCSS_PROPERTY_CURSOR_HELP:
        case MyCSS_PROPERTY_CURSOR_POINTER:
        case MyCSS_PROPERTY_CURSOR_PROGRESS:
        case MyCSS_PROPERTY_CURSOR_WAIT:
        case MyCSS_PROPERTY_CURSOR_CELL:
        case MyCSS_PROPERTY_CURSOR_CROSSHAIR:
        case MyCSS_PROPERTY_CURSOR_TEXT:
        case MyCSS_PROPERTY_CURSOR_VERTICAL_TEXT:
        case MyCSS_PROPERTY_CURSOR_ALIAS:
        case MyCSS_PROPERTY_CURSOR_COPY:
        case MyCSS_PROPERTY_CURSOR_MOVE:
        case MyCSS_PROPERTY_CURSOR_NO_DROP:
        case MyCSS_PROPERTY_CURSOR_NOT_ALLOWED:
        case MyCSS_PROPERTY_CURSOR_GRAB:
        case MyCSS_PROPERTY_CURSOR_GRABBING:
        case MyCSS_PROPERTY_CURSOR_E_RESIZE:
        case MyCSS_PROPERTY_CURSOR_N_RESIZE:
        case MyCSS_PROPERTY_CURSOR_NE_RESIZE:
        case MyCSS_PROPERTY_CURSOR_NW_RESIZE:
        case MyCSS_PROPERTY_CURSOR_S_RESIZE:
        case MyCSS_PROPERTY_CURSOR_SE_RESIZE:
        case MyCSS_PROPERTY_CURSOR_SW_RESIZE:
        case MyCSS_PROPERTY_CURSOR_W_RESIZE:
        case MyCSS_PROPERTY_CURSOR_EW_RESIZE:
        case MyCSS_PROPERTY_CURSOR_NS_RESIZE:
        case MyCSS_PROPERTY_CURSOR_NESW_RESIZE:
        case MyCSS_PROPERTY_CURSOR_NWSE_RESIZE:
        case MyCSS_PROPERTY_CURSOR_COL_RESIZE:
        case MyCSS_PROPERTY_CURSOR_ROW_RESIZE:
        case MyCSS_PROPERTY_CURSOR_ALL_SCROLL:
        case MyCSS_PROPERTY_CURSOR_ZOOM_IN:
        case MyCSS_PROPERTY_CURSOR_ZOOM_OUT:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* float */
bool mycss_property_parser_float(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_FLOAT_LEFT:
        case MyCSS_PROPERTY_FLOAT_RIGHT:
        case MyCSS_PROPERTY_FLOAT_TOP:
        case MyCSS_PROPERTY_FLOAT_BOTTOM:
        case MyCSS_PROPERTY_FLOAT_START:
        case MyCSS_PROPERTY_FLOAT_END:
        case MyCSS_PROPERTY_FLOAT_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_float_displace(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_FLOAT_DISPLACE_LINE:
        case MyCSS_PROPERTY_FLOAT_DISPLACE_INDENT:
        case MyCSS_PROPERTY_FLOAT_DISPLACE_BLOCK:
        case MyCSS_PROPERTY_FLOAT_DISPLACE_BLOCK_WITHIN_PAGE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* top right bottom left */
bool mycss_property_parser_top(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    if(str.data == NULL)
        mycss_token_data_to_string(entry, token, &str, true, false);
    
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_VALUE_AUTO:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            dec_entry->value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_top(entry, token, last_response);
}

bool mycss_property_parser_bottom(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_top(entry, token, last_response);
}

bool mycss_property_parser_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_top(entry, token, last_response);
}

/* clear */
bool mycss_property_parser_clear(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_CLEAR_LEFT:
        case MyCSS_PROPERTY_CLEAR_RIGHT:
        case MyCSS_PROPERTY_CLEAR_BOTH:
        case MyCSS_PROPERTY_CLEAR_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_clear_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_CLEAR_AFTER_NONE:
        case MyCSS_PROPERTY_CLEAR_AFTER_LEFT:
        case MyCSS_PROPERTY_CLEAR_AFTER_RIGHT:
        case MyCSS_PROPERTY_CLEAR_AFTER_TOP:
        case MyCSS_PROPERTY_CLEAR_AFTER_BOTTOM:
        case MyCSS_PROPERTY_CLEAR_AFTER_INSIDE:
        case MyCSS_PROPERTY_CLEAR_AFTER_OUTSIDE:
        case MyCSS_PROPERTY_CLEAR_AFTER_START:
        case MyCSS_PROPERTY_CLEAR_AFTER_END:
        case MyCSS_PROPERTY_CLEAR_AFTER_BOTH:
        case MyCSS_PROPERTY_CLEAR_AFTER_DESCENDANTS:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* overflow */
bool mycss_property_parser_overflow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_OVERFLOW_VISIBLE:
        case MyCSS_PROPERTY_OVERFLOW_HIDDEN:
        case MyCSS_PROPERTY_OVERFLOW_SCROLL:
        case MyCSS_PROPERTY_OVERFLOW_AUTO:
        case MyCSS_PROPERTY_OVERFLOW_NO_DISPLAY:
        case MyCSS_PROPERTY_OVERFLOW_NO_CONTENT:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_overflow_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_OVERFLOW_WRAP_NORMAL:
        case MyCSS_PROPERTY_OVERFLOW_WRAP_BREAK_WORD:
        case MyCSS_PROPERTY_OVERFLOW_WRAP_BREAK_SPACES:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_overflow_x(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_overflow(entry, token, last_response);
}

bool mycss_property_parser_overflow_y(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_overflow(entry, token, last_response);
}

/* visibility */
bool mycss_property_parser_visibility(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_VISIBILITY_VISIBLE:
        case MyCSS_PROPERTY_VISIBILITY_HIDDEN:
        case MyCSS_PROPERTY_VISIBILITY_COLLAPSE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* font */
bool mycss_property_parser_font_weight(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_font_weight(entry, token, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_font_size(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_size_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_number(entry, token, &dec_entry->value, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    if(str.data == NULL)
        mycss_token_data_to_string(entry, token, &str, true, false);
    
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_FONT_SIZE_ADJUST_NONE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            dec_entry->value_type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_stretch(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_font_stretch(entry, token, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_font_style(entry, token, &dec_entry->value_type, &str))
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

static bool mycss_property_parser_font_family_wait_comma_or_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE )
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_font_family;
        return true;
    }
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycore_string_t str = {0}; bool dont_destroy_str;
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_font_family(entry, token, &dec_entry->value, &dec_entry->value_type, &dont_destroy_str, &str)) {
        if(dont_destroy_str == false)
            mycss_property_shared_destroy_string(&str);
        
        entry->parser = mycss_property_parser_font_family_wait_comma_or_end;
        return true;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Font
 */
bool mycss_property_parser_font_step_wait_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

static bool mycss_property_parser_font_step_wait_family_comma_or_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE )
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_font_step_wait_family;
        return true;
    }
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_step_wait_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycore_string_t str = {0};
    mycss_values_font_t *font = (mycss_values_font_t*)dec_entry->value;
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool dont_destroy_str;
    
    if(font->family) {
        value = font->family->value;
        value_type = font->family->value_type;
    }
    
    if(mycss_property_shared_font_family(entry, token, &value, &value_type, &dont_destroy_str, &str)) {
        if(dont_destroy_str == false)
            mycss_property_shared_destroy_string(&str);
        
        if(font->family == NULL) {
            font->family = mycss_declaration_entry_create(entry->declaration, NULL);
            
            font->family->type = MyCSS_PROPERTY_TYPE_FONT_FAMILY;
            font->family->value = value;
            font->family->value_type = value_type;
        }
        
        entry->parser = mycss_property_parser_font_step_wait_family_comma_or_end;
        return true;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_step_wait_line_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    mycore_string_t str = {0};
    mycss_values_font_t *font = (mycss_values_font_t*)dec_entry->value;
    
    if(mycss_property_shared_line_height(entry, token, &value, &value_type, &str)) {
        font->line_height = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->line_height->type = MyCSS_PROPERTY_TYPE_LINE_HEIGHT;
        font->line_height->value = value;
        font->line_height->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_wait_family;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_step_after_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_DELIM) {
        if(*token->data == '/') {
            entry->parser = mycss_property_parser_font_step_wait_line_height;
            return true;
        }
        
        return mycss_property_shared_switch_to_parse_error(entry);
    }
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool dont_destroy_str;
    
    mycore_string_t str = {0};
    mycss_values_font_t *font = (mycss_values_font_t*)dec_entry->value;
    
    if(mycss_property_shared_font_family(entry, token, &value, &value_type, &dont_destroy_str, &str)) {
        if(dont_destroy_str == false)
            mycss_property_shared_destroy_string(&str);
        
        font->family = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->family->type = MyCSS_PROPERTY_TYPE_FONT_FAMILY;
        font->family->value = value;
        font->family->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_wait_family_comma_or_end;
        return true;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font_step_one(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    mycss_values_font_t *font = (mycss_values_font_t*)dec_entry->value;
    
    if(mycss_property_shared_font_style(entry, token, &value_type, &str))
    {
        if(font->style)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        font->style = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->style->type = MyCSS_PROPERTY_TYPE_FONT_STYLE;
        font->style->value_type = value_type;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_font_weight(entry, token, &value_type, &str)) {
        if(font->weight)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        font->weight = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->weight->type = MyCSS_PROPERTY_TYPE_FONT_WEIGHT;
        font->weight->value_type = value_type;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_font_stretch(entry, token, &value_type, &str)) {
        if(font->stretch)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        font->stretch = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->stretch->type = MyCSS_PROPERTY_TYPE_FONT_STRETCH;
        font->stretch->value_type = value_type;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* <‘font-size’> [ / <‘line-height’> ]? <‘font-family’>  */
    if(mycss_property_shared_font_size(entry, token, &value, &value_type, &str)) {
        font->size = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->size->type = MyCSS_PROPERTY_TYPE_FONT_SIZE;
        font->size->value = value;
        font->size->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_after_size;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    bool dont_destroy_str;
    
    if(mycss_property_shared_font_family(entry, token, &value, &value_type, &dont_destroy_str, &str)) {
        if(dont_destroy_str == false)
            mycss_property_shared_destroy_string(&str);
        
        font->family = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->family->type = MyCSS_PROPERTY_TYPE_FONT_FAMILY;
        font->family->value = value;
        font->family->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_wait_family_comma_or_end;
        return true;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_font(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_font_t));
    
    if(dec_entry->value == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    mycss_values_font_t *font = (mycss_values_font_t*)dec_entry->value;
    
    /* caption | icon | menu | message-box | small-caption | status-bar */
    if(mycss_property_shared_font_ends(entry, token, &value_type, &str)) {
        dec_entry->value_type = value_type;
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    /* [ <‘font-style’> || <font-variant-css21> || <‘font-weight’> || <‘font-stretch’> ]? */
    if(mycss_property_shared_font_style(entry, token, &value_type, &str))
    {
        font->style = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->style->type = MyCSS_PROPERTY_TYPE_FONT_STYLE;
        font->style->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_one;
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_font_weight(entry, token, &value_type, &str)) {
        font->weight = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->weight->type = MyCSS_PROPERTY_TYPE_FONT_STYLE;
        font->weight->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_one;
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_font_stretch(entry, token, &value_type, &str)) {
        font->stretch = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->stretch->type = MyCSS_PROPERTY_TYPE_FONT_STYLE;
        font->stretch->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_one;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* <‘font-size’> [ / <‘line-height’> ]? <‘font-family’>  */
    if(mycss_property_shared_font_size(entry, token, &value, &value_type, &str)) {
        font->size = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->size->type = MyCSS_PROPERTY_TYPE_FONT_STYLE;
        font->size->value = value;
        font->size->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_after_size;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    bool dont_destroy_str;
    
    if(mycss_property_shared_font_family(entry, token, &value, &value_type, &dont_destroy_str, &str)) {
        if(dont_destroy_str == false)
            mycss_property_shared_destroy_string(&str);
        
        font->family = mycss_declaration_entry_create(entry->declaration, NULL);
        
        font->family->type = MyCSS_PROPERTY_TYPE_FONT_FAMILY;
        font->family->value = value;
        font->family->value_type = value_type;
        
        entry->parser = mycss_property_parser_font_step_wait_family_comma_or_end;
        return true;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* text align */
bool mycss_property_parser_text_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_ALIGN_START:
        case MyCSS_PROPERTY_TEXT_ALIGN_END:
        case MyCSS_PROPERTY_TEXT_ALIGN_LEFT:
        case MyCSS_PROPERTY_TEXT_ALIGN_RIGHT:
        case MyCSS_PROPERTY_TEXT_ALIGN_CENTER:
        case MyCSS_PROPERTY_TEXT_ALIGN_JUSTIFY:
        case MyCSS_PROPERTY_TEXT_ALIGN_MATCH_PARENT:
        case MyCSS_PROPERTY_TEXT_ALIGN_JUSTIFY_ALL:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_align_all(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_START:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_END:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_LEFT:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_RIGHT:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_CENTER:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_JUSTIFY:
        case MyCSS_PROPERTY_TEXT_ALIGN_ALL_MATCH_PARENT:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_align_last(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_AUTO:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_START:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_END:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_LEFT:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_RIGHT:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_CENTER:
        case MyCSS_PROPERTY_TEXT_ALIGN_LAST_JUSTIFY:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* text-transform */
bool mycss_property_parser_white_space(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_WHITE_SPACE_NORMAL:
        case MyCSS_PROPERTY_WHITE_SPACE_PRE:
        case MyCSS_PROPERTY_WHITE_SPACE_NOWRAP:
        case MyCSS_PROPERTY_WHITE_SPACE_PRE_WRAP:
        case MyCSS_PROPERTY_WHITE_SPACE_PRE_LINE:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_transform(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_TRANSFORM_NONE:
        case MyCSS_PROPERTY_TEXT_TRANSFORM_CAPITALIZE:
        case MyCSS_PROPERTY_TEXT_TRANSFORM_UPPERCASE:
        case MyCSS_PROPERTY_TEXT_TRANSFORM_LOWERCASE:
        case MyCSS_PROPERTY_TEXT_TRANSFORM_FULL_WIDTH:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_word_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_WORD_BREAK_NORMAL:
        case MyCSS_PROPERTY_WORD_BREAK_KEEP_ALL:
        case MyCSS_PROPERTY_WORD_BREAK_BREAK_ALL:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_line_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_LINE_BREAK_AUTO:
        case MyCSS_PROPERTY_LINE_BREAK_LOOSE:
        case MyCSS_PROPERTY_LINE_BREAK_NORMAL:
        case MyCSS_PROPERTY_LINE_BREAK_STRICT:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_tab_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_number(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_length(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_hyphens(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_HYPHENS_NONE:
        case MyCSS_PROPERTY_HYPHENS_MANUAL:
        case MyCSS_PROPERTY_HYPHENS_AUTO:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_word_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_overflow_wrap(entry, token, last_response);
}

bool mycss_property_parser_text_justify(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_JUSTIFY_AUTO:
        case MyCSS_PROPERTY_TEXT_JUSTIFY_NONE:
        case MyCSS_PROPERTY_TEXT_JUSTIFY_INTER_WORD:
        case MyCSS_PROPERTY_TEXT_JUSTIFY_INTER_CHARACTER:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_word_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length_percentage(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_by_value_type(entry, token, &dec_entry->value_type, MyCSS_PROPERTY_WORD_SPACING_NORMAL, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_letter_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_length(entry, token, &dec_entry->value, &dec_entry->value_type, &str) ||
       mycss_property_shared_by_value_type(entry, token, &dec_entry->value_type, MyCSS_PROPERTY_LETTER_SPACING_NORMAL, &str) ||
       mycss_property_shared_default(entry, token, &dec_entry->value_type, &str))
    {
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_DIRECTION_LTR:
        case MyCSS_PROPERTY_DIRECTION_RTL:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_unicode_bidi(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_UNICODE_BIDI_NORMAL:
        case MyCSS_PROPERTY_UNICODE_BIDI_EMBED:
        case MyCSS_PROPERTY_UNICODE_BIDI_ISOLATE:
        case MyCSS_PROPERTY_UNICODE_BIDI_BIDI_OVERRIDE:
        case MyCSS_PROPERTY_UNICODE_BIDI_ISOLATE_OVERRIDE:
        case MyCSS_PROPERTY_UNICODE_BIDI_PLAINTEXT:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_writing_mode(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_WRITING_MODE_HORIZONTAL_TB:
        case MyCSS_PROPERTY_WRITING_MODE_VERTICAL_LR:
        case MyCSS_PROPERTY_WRITING_MODE_VERTICAL_RL:
        case MyCSS_PROPERTY_WRITING_MODE_SIDEWAYS_LR:
        case MyCSS_PROPERTY_WRITING_MODE_SIDEWAYS_RL:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_orientation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_TEXT_ORIENTATION_MIXED:
        case MyCSS_PROPERTY_TEXT_ORIENTATION_UPRIGHT:
        case MyCSS_PROPERTY_TEXT_ORIENTATION_SIDEWAYS:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_glyph_orientation_vertical(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycss_token_data_to_string(entry, token, &str, true, false);
    dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (dec_entry->value_type) {
        case MyCSS_PROPERTY_GLYPH_ORIENTATION_VERTICAL_AUTO:
        case MyCSS_PROPERTY_GLYPH_ORIENTATION_VERTICAL_0DEG:
        case MyCSS_PROPERTY_GLYPH_ORIENTATION_VERTICAL_90DEG:
        case MyCSS_PROPERTY_GLYPH_ORIENTATION_VERTICAL_0:
        case MyCSS_PROPERTY_GLYPH_ORIENTATION_VERTICAL_90:
            /* default values */
        case MyCSS_PROPERTY_VALUE_INHERIT:
        case MyCSS_PROPERTY_VALUE_INITIAL:
        case MyCSS_PROPERTY_VALUE_UNSET:
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
            
        default:
            break;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* not yet */
bool mycss_property_parser_align_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_align_items(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_align_self(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_delay(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_fill_mode(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_iteration_count(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_name(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_play_state(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_animation_timing_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_appearance(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_backface_visibility(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_bookmark_label(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_bookmark_level(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_bookmark_state(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_collapse(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_image_outset(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_image_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_image_slice(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_image_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_border_spacing(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_short_two_type(entry, token);
}

bool mycss_property_parser_box_decoration_break(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_box_shadow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_box_suppress(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_break_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_break_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_break_inside(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_caption_side(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_caret(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_caret_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_caret_shape(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_color_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_color_interpolation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_color_interpolation_filters(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_color_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_count(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_fill(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_gap(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_rule_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_rule_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_rule_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_span(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_column_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_columns(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_contain(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_continue(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_counter_increment(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_cue(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_cue_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_cue_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_empty_cells(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_fill(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_fill_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_fill_rule(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_basis(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_direction(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_flow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_grow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_shrink(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_flex_wrap(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_feature_settings(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_kerning(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_language_override(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_synthesis(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_alternates(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_caps(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_east_asian(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_ligatures(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_numeric(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_font_variant_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_hanging_punctuation(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_image_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_indent_edge_reset(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_inline_size_step(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_justify_content(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_line_height_step(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_list_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_list_style_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_list_style_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_list_style_type(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_marker(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_marker_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_marker_mid(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_marker_side(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_marker_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_max_lines(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_nav_down(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_nav_left(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_nav_right(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_nav_up(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_offset_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_offset_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_offset_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_offset_start(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_order(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_orphans(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_outline(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_outline_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_outline_offset(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_outline_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_outline_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_pause(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_pause_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_pause_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_perspective(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_perspective_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_presentation_level(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_quotes(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_region_fragment(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_resize(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_rest(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_rest_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_rest_before(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_ruby_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_ruby_merge(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_ruby_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_scroll_padding(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_scroll_snap_align(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_scroll_snap_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_scroll_snap_stop(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_scroll_snap_type(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_shape_image_threshold(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_shape_margin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_shape_outside(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_shape_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_speak(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_speak_as(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_string_set(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_dasharray(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_dashoffset(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_linecap(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_linejoin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_miterlimit(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_opacity(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_stroke_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_table_layout(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_combine_upright(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_emphasis(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_emphasis_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_emphasis_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_emphasis_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_indent(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_overflow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_rendering(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_shadow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_size_adjust(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_underline_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_touch_action(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transform(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transform_box(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transform_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transform_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transition(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transition_delay(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transition_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transition_property(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_transition_timing_function(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_user_select(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_balance(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_duration(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_family(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_pitch(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_range(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_rate(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_stress(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_voice_volume(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_widows(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_will_change(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_wrap_flow(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_wrap_through(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_shared_switch_to_parse_error(entry);
}


