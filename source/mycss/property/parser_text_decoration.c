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

static void mycss_property_parser_text_decoration_parser_switch(mycss_entry_t* entry)
{
    mycss_stack_entry_t *stack_entry = mycss_stack_pop(entry->declaration->stack);
    
    if(stack_entry->value)
        entry->declaration->entry_last = stack_entry->value;
    
    entry->parser = stack_entry->parser;
}

void * mycss_property_destroy_text_decoration(mycss_entry_t* entry, void* value)
{
    if(value == NULL)
        return NULL;
    
    mycss_values_text_decoration_t *text_decoration = (mycss_values_text_decoration_t*)value;
    
    if(text_decoration->color)
        text_decoration->color = mycss_declaration_entry_destroy(entry->declaration, text_decoration->color, true);
    
    if(text_decoration->line)
        text_decoration->color = mycss_declaration_entry_destroy(entry->declaration, text_decoration->line, true);
    
    if(text_decoration->style)
        text_decoration->color = mycss_declaration_entry_destroy(entry->declaration, text_decoration->style, true);
    
    return mycss_values_destroy(entry, text_decoration);
}

bool mycss_property_parser_text_decoration(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    mycss_values_text_decoration_t *text_decoration;
    
    if(dec_entry->value == NULL) {
        text_decoration = (mycss_values_text_decoration_t*)mycss_values_create(entry, sizeof(mycss_values_text_decoration_t));
        dec_entry->value = text_decoration;
        
        if(text_decoration == NULL)
            return mycss_property_shared_switch_to_parse_error(entry);
    }
    else {
        text_decoration = (mycss_values_text_decoration_t*)dec_entry->value;
    }
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        if(text_decoration &&
           text_decoration->color == NULL &&
           text_decoration->style == NULL &&
           text_decoration->line == NULL)
        {
            dec_entry->value = mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_shared_switch_to_parse_error(entry);
        }
        
        return true;
    }
    
    if(text_decoration == NULL)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    dec_entry->value = text_decoration;
    
    void *value = NULL;
    unsigned int line_value = 0;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_text_decoration_style(entry, token, &value_type, &str))
    {
        if(text_decoration->style) {
            mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        }
        
        text_decoration->style = mycss_declaration_entry_create(entry->declaration, NULL);
        
        text_decoration->style->type = MyCSS_PROPERTY_TYPE_TEXT_DECORATION_STYLE;
        text_decoration->style->value_type = value_type;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_color(entry, token, &value, &value_type, &str, &parser_changed))
    {
        if(text_decoration->color) {
            mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        }
        
        text_decoration->color = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, dec_entry->value, mycss_property_parser_text_decoration_after_color);
            entry->declaration->entry_last->value = text_decoration->color->value;
        }
        
        text_decoration->color->value = value;
        text_decoration->color->type = MyCSS_PROPERTY_TYPE_TEXT_DECORATION_COLOR;
        text_decoration->color->value_type = value_type;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    else if(mycss_property_shared_text_decoration_line(entry, token, &line_value, &value_type, &str, true))
    {
        if(text_decoration->line) {
            mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        }
        
        text_decoration->line = mycss_declaration_entry_create(entry->declaration, NULL);
        text_decoration->line->type = MyCSS_PROPERTY_TYPE_TEXT_DECORATION_LINE;
        
        if(line_value) {
            unsigned int *new_value = mycss_values_create(entry, sizeof(unsigned int));
            *new_value = line_value;
            
            text_decoration->line->value = new_value;
            
            mycss_stack_push(entry->declaration->stack, dec_entry, mycss_property_parser_text_decoration_after_line);
            entry->declaration->entry_last = text_decoration->line;
        }
        else {
            text_decoration->line->value_type = value_type;
        }
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_decoration_after_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        mycss_values_text_decoration_t *text_decoration = (mycss_values_text_decoration_t*)dec_entry->value;
        
        if(text_decoration &&
           text_decoration->color == NULL &&
           text_decoration->style == NULL &&
           text_decoration->line == NULL)
        {
            dec_entry->value = mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_shared_switch_to_parse_error(entry);
        }
        
        return true;
    }
    
    entry->parser = mycss_property_parser_text_decoration;
    return false;
}

bool mycss_property_parser_text_decoration_after_line(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
    {
        mycss_values_text_decoration_t *text_decoration = (mycss_values_text_decoration_t*)dec_entry->value;
        
        if(text_decoration &&
           text_decoration->color == NULL &&
           text_decoration->style == NULL &&
           text_decoration->line == NULL)
        {
            dec_entry->value = mycss_property_destroy_text_decoration(entry, text_decoration);
            return mycss_property_shared_switch_to_parse_error(entry);
        }
        
        return true;
    }
    
    entry->parser = mycss_property_parser_text_decoration;
    return false;
}

bool mycss_property_parser_text_decoration_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    bool parser_changed = false;
    
    if(mycss_property_shared_color(entry, token, &dec_entry->value, &dec_entry->value_type, &str, &parser_changed))
    {
        if(parser_changed)
            mycss_stack_push(entry->declaration->stack, NULL, mycss_property_parser_text_decoration_color_after);
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_decoration_color_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    dec_entry->value = mycss_values_destroy(entry, dec_entry->value);
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_decoration_skip(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value = 0;
    
    if(mycss_property_shared_text_decoration_skip(entry, token, &value, &dec_entry->value_type, &str, true)) {
        if(value) {
            unsigned int *new_value = mycss_values_create(entry, sizeof(unsigned int));
            *new_value = value;
            
            dec_entry->value = new_value;
            
            mycss_stack_push(entry->declaration->stack, dec_entry, mycss_property_parser_text_decoration_skip_after);
        }
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_decoration_skip_not_none(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT) {
        mycss_property_parser_text_decoration_parser_switch(entry);
        return false;
    }
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_text_decoration_skip(entry, token, (unsigned int*)dec_entry->value, &dec_entry->value_type, &str, false))
        return mycss_property_parser_destroy_string(&str, true);
    
    mycss_property_parser_text_decoration_parser_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_text_decoration_skip_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value)
        dec_entry->value = mycss_values_destroy(entry, dec_entry->value);
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_text_decoration_style(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_text_decoration_style(entry, token, &dec_entry->value_type, &str))
        mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_decoration_line(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT)
        return mycss_property_shared_switch_to_parse_error(entry);
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value = 0;
    
    if(mycss_property_shared_text_decoration_line(entry, token, &value, &dec_entry->value_type, &str, true))
    {
        if(value) {
            unsigned int *new_value = mycss_values_create(entry, sizeof(unsigned int));
            *new_value = value;
            
            dec_entry->value = new_value;
            
            mycss_stack_push(entry->declaration->stack, dec_entry, mycss_property_parser_text_decoration_line_after);
        }
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_text_decoration_line_not_none(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type != MyCSS_TOKEN_TYPE_IDENT) {
        mycss_property_parser_text_decoration_parser_switch(entry);
        return false;
    }
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(mycss_property_shared_text_decoration_line(entry, token, (unsigned int*)dec_entry->value, &dec_entry->value_type, &str, false))
        return mycss_property_parser_destroy_string(&str, true);
    
    mycss_property_parser_text_decoration_parser_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_text_decoration_line_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(mycss_property_shared_check_declaration_end(entry, token))
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    if(dec_entry->value)
        dec_entry->value = mycss_values_destroy(entry, dec_entry->value);
    
    return mycss_property_shared_switch_to_parse_error(entry);
}


