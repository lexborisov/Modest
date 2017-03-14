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

mycss_values_image_image_set_option_t * mycss_property_parser_image_function_get_next_option(mycss_entry_t* entry, mycss_values_image_image_set_t *ii_set)
{
    if(ii_set->options == NULL) {
        ii_set->options = mycss_values_create(entry, sizeof(mycss_values_image_image_set_option_t));
        ii_set->options_length = 0;
    }
    else {
        ii_set->options = mycss_values_realloc(entry, ii_set->options,
                                               ii_set->options_length * sizeof(mycss_values_image_image_set_option_t),
                                               sizeof(mycss_values_image_image_set_option_t));
    }
    
    mycss_values_image_image_set_option_t *ii_entry = &ii_set->options[ ii_set->options_length ];
    ii_set->options_length++;
    
    return ii_entry;
}

static void mycss_values_parser_image_switch(mycss_entry_t* entry)
{
    mycss_stack_entry_t *stack_entry = mycss_stack_pop(entry->declaration->stack);
    
    if(stack_entry->value)
        entry->declaration->entry_last->value = stack_entry->value;
    
    entry->parser = stack_entry->parser;
}

/*
 * Image
 */
bool mycss_property_parser_image_function_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_image_image_t *image_image = image->value.ii;
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed)) {
        image_image->image = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_image_wait_comma);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_image_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_STRING)
    {
        mycore_string_t *ns_str = mycss_values_create(entry, sizeof(mycore_string_t));
        mycss_token_data_to_string(entry, token, ns_str, true, false);
        
        image_image->str = ns_str;
        
        entry->parser = mycss_property_parser_image_function_image_wait_comma;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_color(entry, token, &value, &value_type, &str, &parser_changed)) {
        image_image->color = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_image_end);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_image_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_image_wait_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_property_parser_image_function_image_color;
            return true;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
}

bool mycss_property_parser_image_function_image_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_image_image_t *image_image = image->value.ii;
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_color(entry, token, &value, &value_type, &str, &parser_changed)) {
        image_image->color = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_image_end);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_image_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_image_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
}

/*
 * Image-Set
 */
bool mycss_property_parser_image_function_image_set(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_image_image_set_t *ii_set = image->value.ii_set;
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed))
    {
        mycss_values_image_image_set_option_t *ii_entry = mycss_property_parser_image_function_get_next_option(entry, ii_set);
        ii_entry->image = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_image_set_resolution);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_image_set_resolution;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_STRING)
    {
        mycore_string_t *ns_str = mycss_values_create(entry, sizeof(mycore_string_t));
        mycss_token_data_to_string(entry, token, ns_str, true, false);
        
        mycss_values_image_image_set_option_t *ii_entry = mycss_property_parser_image_function_get_next_option(entry, ii_set);
        ii_entry->str = ns_str;
        
        entry->parser = mycss_property_parser_image_function_image_set_resolution;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_image_set_resolution(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_image_image_set_t *ii_set = image->value.ii_set;
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_resolution(entry, token, &value, &value_type, &str))
    {
        mycss_values_image_image_set_option_t *ii_entry = mycss_property_parser_image_function_get_next_option(entry, ii_set);
        ii_entry->resolution = value;
        
        entry->parser = mycss_property_parser_image_function_image_set_resolution_wait_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_image_set_resolution_wait_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        default:
            entry->parser = mycss_property_parser_image_function_image_set;
            return false;
    }
}

/*
 * Element
 */
bool mycss_property_parser_image_function_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_element_t *element = image->value.element;
    
    void *value = &element->custom_ident;
    
    if(mycss_property_shared_custom_ident(entry, token, &value, NULL)) {
        entry->parser = mycss_property_parser_image_function_string_wait_comma;
        return true;
    }
    
    mycss_values_parser_image_switch(entry);
    return false;
}

bool mycss_property_parser_image_function_string_wait_comma(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_property_parser_image_function_string_wait_ident;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
}

bool mycss_property_parser_image_function_string_wait_ident(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        case MyCSS_TOKEN_TYPE_IDENT:
            break;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_element_t *element = image->value.element;
    
    mycore_string_t str = {0};
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    element->type = mycss_property_value_type_by_name(str.data, str.length);
    
    switch (element->type) {
        case MyCSS_PROPERTY_VALUE_FIRST:
        case MyCSS_PROPERTY_VALUE_START:
        case MyCSS_PROPERTY_VALUE_LAST:
        case MyCSS_PROPERTY_VALUE_FIRST_EXCEPT:
            return mycss_property_parser_destroy_string(&str, true);
            
        default:
            element->type = MyCSS_PROPERTY_VALUE_UNDEF;
            break;
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

/*
 * Cross Fade
 */
bool mycss_property_parser_image_function_cross_fade(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_cross_fade_t *cross_fade = image->value.cross_fade;
    
    mycore_string_t str = {0};
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_percentage(entry, token, &value, &value_type, &str)) {
        cross_fade->mixing_image.percentage = value;
        
        entry->parser = mycss_property_parser_image_function_cross_fade_mixing_after_percentage;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed)) {
        cross_fade->mixing_image.image = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_cross_fade_mixing_after);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_cross_fade_mixing_after;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_cross_fade_mixing_after_percentage(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_cross_fade_t *cross_fade = image->value.cross_fade;
    
    mycore_string_t str = {0};
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed)) {
        cross_fade->mixing_image.image = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_cross_fade_mixing_after);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser_switch = mycss_property_parser_image_function_cross_fade_mixing_after;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_cross_fade_mixing_after(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_COMMA:
            entry->parser = mycss_property_parser_image_function_cross_fade_final;
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
}

bool mycss_property_parser_image_function_cross_fade_final(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    
    mycss_values_image_t *image = (mycss_values_image_t*)declr_entry->value;
    mycss_values_cross_fade_t *cross_fade = image->value.cross_fade;
    
    mycore_string_t str = {0};
    
    void *value = NULL;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed)) {
        cross_fade->final_image.image = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_cross_fade_end);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_cross_fade_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_color(entry, token, &value, &value_type, &str, &parser_changed)) {
        cross_fade->final_image.color = value;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, declr_entry->value, mycss_property_parser_image_function_cross_fade_end);
            declr_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_image_function_cross_fade_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    mycss_values_parser_image_switch(entry);
    return mycss_property_parser_destroy_string(&str, false);
}

bool mycss_property_parser_image_function_cross_fade_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_image_switch(entry);
            return true;
            
        default:
            mycss_values_parser_image_switch(entry);
            return false;
    }
}


