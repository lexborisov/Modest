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

bool mycss_property_parser_background_position_check(mycss_values_background_position_t *position)
{
    if(position == NULL)
        return false;
    
    if(position->one.type == MyCSS_PROPERTY_VALUE__LENGTH ||
       position->one.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
                return true;
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT ||
       position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        else
                            return false;
                        
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                           position->four.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                           position->four.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                        {
                            return true;
                        }
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                   position->three.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                   position->three.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                {
                    if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                        return true;
                }
                
                return false;
            }
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_VALUE__LENGTH:
                    case MyCSS_PROPERTY_VALUE__PERCENTAGE:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_VALUE__LENGTH:
                    case MyCSS_PROPERTY_VALUE__PERCENTAGE:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_TOP ||
       position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        else
                            return false;
                        
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                           position->four.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                           position->four.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                        {
                            return true;
                        }
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                   position->three.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                   position->three.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                {
                    if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                        return true;
                }
                
                return false;
            }
                
            default:
                return false;
        }
    }
    
    return true;
}


/*
 Background
 */
bool mycss_property_parser_background_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

static bool mycss_property_parser_background_step_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    entry->parser = mycss_property_parser_background;
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        mycss_values_background_t *background = entry->declaration->entry_last->value;
        
        if(background->color)
            return mycss_property_shared_switch_to_parse_error(entry);

        return true;
    }
    
    return false;
}

static bool mycss_property_parser_background_check_position(mycss_entry_t* entry, mycss_values_background_t *background, void* value, unsigned int value_type)
{
    if(background->position == NULL)
        background->position = mycss_declaration_entry_create(entry->declaration, NULL);
    
    if(background->position->value == NULL)
        background->position->value = mycss_values_create(entry, sizeof(mycss_values_background_position_t));
    
    mycss_values_background_position_t *position = (mycss_values_background_position_t*)background->position->value;
    mycss_values_type_length_percentage_entry_t *pos_entry;
    
    if(position->one.type == 0)
        pos_entry = &position->one;
    else if(position->two.type == 0)
        pos_entry = &position->two;
    else if(position->three.type == 0)
        pos_entry = &position->three;
    else if(position->four.type == 0)
        pos_entry = &position->four;
    else
        return false;
    
    pos_entry->type = value_type;
    
    if(value_type == MyCSS_PROPERTY_VALUE__LENGTH)
        pos_entry->value.length = value;
    else if(value_type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
        pos_entry->value.percentage = value;
    
    return true;
}

static bool mycss_property_parser_background_step_size_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    mycss_values_background_t *background = dec_entry->value;
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_size(entry, token, &value, &value_type, &str))
    {
        mycss_values_background_size_list_t *list = background->size->value;
        mycss_values_background_size_entry_t *bg_entry = &list->entries[ (list->entries_length - 1) ];
        
        if(value) {
            bg_entry->height = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->height->value.percentage = value;
            bg_entry->height->type = value_type;
        }
        else if(value_type == MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO)
        {
            bg_entry->height = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->height->type = MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO;
        }
        else
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    entry->parser = mycss_property_parser_background_step_end;
    return false;
}

bool mycss_property_parser_background_step_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    mycss_values_background_t *background = dec_entry->value;
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_size(entry, token, &value, &value_type, &str))
    {
        background->size = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(background->size->value == NULL)
            background->size->value = mycss_values_create(entry, sizeof(mycss_values_background_size_list_t));
        
        mycss_values_background_size_entry_t *bg_entry = mycss_values_background_size_list_add_entry(entry, background->size->value);
        
        if(value) {
            bg_entry->width = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->width->value.percentage = value;
            bg_entry->width->type = value_type;
            
            entry->parser = mycss_property_parser_background_step_size_height;
        }
        else if(value_type == MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO)
        {
            bg_entry->width = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->width->type = MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO;
            
            entry->parser = mycss_property_parser_background_step_size_height;
        }
        else {
            bg_entry->scale = value_type;
            
            entry->parser = mycss_property_parser_background_step_end;
        }
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

static bool mycss_property_parser_background_step_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(token->type == MyCSS_TOKEN_TYPE_DELIM && *token->data == '/') {
        entry->parser = mycss_property_parser_background_step_size;
        return true;
    }
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void* value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_position(entry, token, &value, &value_type, &str))
    {
        mycss_values_background_t *background = dec_entry->value;
        
        if(mycss_property_parser_background_check_position(entry, background, value, value_type))
            return mycss_property_parser_destroy_string(&str, true);
        
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
    }
    
    entry->parser = mycss_property_parser_background_step_end;
    return mycss_property_parser_destroy_string(&str, false);
}

static bool mycss_property_parser_background_step_repeat_wait_two(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    mycss_values_background_t *background = dec_entry->value;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_repeat_two(entry, token, &value_type, &str))
    {
        mycss_values_background_repeat_list_t *list = background->repeat->value;
        
        mycss_values_background_repeat_t *repeat = &list->entries[ (list->entries_length - 1) ];
        repeat->vertical = value_type;
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    entry->parser = mycss_property_parser_background_step_end;
    return mycss_property_parser_destroy_string(&str, false);
}

mycss_values_background_t * mycss_property_parser_background_check_entry(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry)
{
    mycss_values_background_t *background = dec_entry->value;

    return background;
}

bool mycss_property_parser_background(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_values_image_t stat_image;
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void *value = &stat_image;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_background_t));

    /* Image */
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed))
    {
        mycss_values_background_t *background =  dec_entry->value;
        
        if(background->image == NULL)
            background->image = mycss_declaration_entry_create(entry->declaration, NULL);

        if(background->image->value == NULL)
            background->image->value = mycss_values_create(entry, sizeof(mycss_values_image_list_t));
        
        mycss_values_image_t *image = mycss_values_image_list_add_entry(entry, background->image->value);
        *image = stat_image;
        
        if(background->image->value_type == MyCSS_PROPERTY_VALUE_UNDEF)
            background->image->value_type = MyCSS_PROPERTY_VALUE__IMAGE_LIST;
        
        background->image->type = MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, dec_entry->value, mycss_property_parser_background_step_end);
            dec_entry->value = image;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_by_value_type(entry, token, &value_type, MyCSS_PROPERTY_BACKGROUND_IMAGE_NONE, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->image == NULL)
            background->image = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(background->image->value == NULL)
            background->image->value = mycss_values_create(entry, sizeof(mycss_values_image_list_t));
        
        background->image->type = MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE;
        
        mycss_values_image_t *image = mycss_values_image_list_add_entry(entry, background->image->value);
        image->type = MyCSS_PROPERTY_VALUE_NONE;
        
        if(background->image->value_type == MyCSS_PROPERTY_VALUE_UNDEF)
            background->image->value_type = MyCSS_PROPERTY_VALUE__IMAGE_LIST;
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* Position */
    if(mycss_property_shared_background_position(entry, token, &value, &value_type, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->position == NULL)
            background->position = mycss_declaration_entry_create(entry->declaration, NULL);

        background->position->type = MyCSS_PROPERTY_TYPE_BACKGROUND_POSITION;
        
        if(mycss_property_parser_background_check_position(entry, background, value, value_type)) {
            entry->parser = mycss_property_parser_background_step_position;
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
    }
    
    /* Repeat */
    if(mycss_property_shared_background_repeat_one(entry, token, &value_type, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->repeat == NULL)
            background->repeat = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(background->repeat->value == NULL)
            background->repeat->value = mycss_values_create(entry, sizeof(mycss_values_background_repeat_list_t));
        
        background->repeat->type = MyCSS_PROPERTY_TYPE_BACKGROUND_REPEAT;
        
        mycss_values_background_repeat_t *repeat = mycss_values_background_repeat_list_add_entry(entry, background->repeat->value);
        repeat->horizontal = value_type;
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_background_repeat_two(entry, token, &value_type, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->repeat == NULL)
            background->repeat = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(background->repeat->value == NULL)
            background->repeat->value = mycss_values_create(entry, sizeof(mycss_values_background_repeat_list_t));
        
        background->repeat->type = MyCSS_PROPERTY_TYPE_BACKGROUND_REPEAT;
        
        mycss_values_background_repeat_t *repeat = mycss_values_background_repeat_list_add_entry(entry, background->repeat->value);
        repeat->horizontal = value_type;
        
        entry->parser = mycss_property_parser_background_step_repeat_wait_two;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* Color */
    if(mycss_property_shared_color(entry, token, &value, &value_type, &str, &parser_changed))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->color == NULL)
            background->color = mycss_declaration_entry_create(entry->declaration, NULL);
        background->color->type = MyCSS_PROPERTY_TYPE_BACKGROUND_COLOR;
        background->color->value = value;
        background->color->value_type = value_type;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, dec_entry->value, mycss_property_parser_background_step_end);
            dec_entry->value = value;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* Attachment */
    if(mycss_property_shared_background_attachment(entry, token, &value_type, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->attachment == NULL)
            background->attachment = mycss_declaration_entry_create(entry->declaration, NULL);
        
        if(background->attachment->value == NULL)
            background->attachment->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
        
        background->attachment->type = MyCSS_PROPERTY_TYPE_BACKGROUND_ATTACHMENT;
        
        unsigned int *type = mycss_values_type_list_add_entry(entry, background->attachment->value);
        *type = value_type;
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    /* Clip and Origin */
    if(mycss_property_shared_background_clip(entry, token, &value_type, &str))
    {
        mycss_values_background_t *background = mycss_property_parser_background_check_entry(entry, dec_entry);
        
        if(background->clip) {
            if(background->origin == NULL)
                background->origin = mycss_declaration_entry_create(entry->declaration, NULL);
            
            if(background->origin->value == NULL)
                background->origin->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
            
            background->origin->type = MyCSS_PROPERTY_TYPE_BACKGROUND_ORIGIN;
            
            unsigned int *type = mycss_values_type_list_add_entry(entry, background->origin->value);
            *type = value_type;
        }
        else {
            background->clip = mycss_declaration_entry_create(entry->declaration, NULL);
            
            if(background->clip->value == NULL)
                background->clip->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
            
            background->clip->type = MyCSS_PROPERTY_TYPE_BACKGROUND_CLIP;
            
            unsigned int *type = mycss_values_type_list_add_entry(entry, background->clip->value);
            *type = value_type;
        }
        
        entry->parser = mycss_property_parser_background_step_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Attachment
 */
static bool mycss_property_parser_background_attachment_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_attachment;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_background_attachment(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_attachment(entry, token, &value_type, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
        
        unsigned int *type = mycss_values_type_list_add_entry(entry, dec_entry->value);
        *type = value_type;
        
        entry->parser = mycss_property_parser_background_attachment_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Clip
 */
static bool mycss_property_parser_background_clip_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_clip;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_background_clip(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_clip(entry, token, &value_type, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
        
        unsigned int *type = mycss_values_type_list_add_entry(entry, dec_entry->value);
        *type = value_type;
        
        entry->parser = mycss_property_parser_background_clip_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Image
 */
bool mycss_property_parser_background_image_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_image;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_background_image(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_values_image_t stat_image;
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void *value = &stat_image;
    unsigned int value_type = 0;
    bool parser_changed = false;
    
    if(mycss_property_shared_image(entry, token, &value, &value_type, &str, &parser_changed))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_image_list_t));
        
        mycss_values_image_t *image = mycss_values_image_list_add_entry(entry, dec_entry->value);
        *image = stat_image;
        
        if(dec_entry->value_type == MyCSS_PROPERTY_VALUE_UNDEF)
            dec_entry->value_type = MyCSS_PROPERTY_VALUE__IMAGE_LIST;
        
        if(parser_changed) {
            mycss_stack_push(entry->declaration->stack, dec_entry->value, mycss_property_parser_background_image_end);
            dec_entry->value = image;
            
            return mycss_property_parser_destroy_string(&str, true);
        }
        
        entry->parser = mycss_property_parser_background_image_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_by_value_type(entry, token, &value_type, MyCSS_PROPERTY_BACKGROUND_IMAGE_NONE, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_image_list_t));
        
        mycss_values_image_t *image = mycss_values_image_list_add_entry(entry, dec_entry->value);
        image->type = MyCSS_PROPERTY_VALUE_NONE;
        
        if(dec_entry->value_type == MyCSS_PROPERTY_VALUE_UNDEF)
            dec_entry->value_type = MyCSS_PROPERTY_VALUE__IMAGE_LIST;
        
        entry->parser = mycss_property_parser_background_image_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Origin
 */
static bool mycss_property_parser_background_origin_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_origin;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

bool mycss_property_parser_background_origin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_clip(entry, token, &value_type, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_type_list_t));
        
        unsigned int *type = mycss_values_type_list_add_entry(entry, dec_entry->value);
        *type = value_type;
        
        entry->parser = mycss_property_parser_background_origin_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Position
 */
bool mycss_property_parser_background_position(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void* value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_position(entry, token, &value, &value_type, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_background_position_t));
        
        mycss_values_background_position_t *position = (mycss_values_background_position_t*)dec_entry->value;
        mycss_values_type_length_percentage_entry_t *pos_entry;
        
        if(position->one.type == 0)
            pos_entry = &position->one;
        else if(position->two.type == 0)
            pos_entry = &position->two;
        else if(position->three.type == 0)
            pos_entry = &position->three;
        else if(position->four.type == 0)
            pos_entry = &position->four;
        else
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        pos_entry->type = value_type;
        
        if(value_type == MyCSS_PROPERTY_VALUE__LENGTH)
            pos_entry->value.length = value;
        else if(value_type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
            pos_entry->value.percentage = value;
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        
        return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
    }
    
    if(mycss_property_parser_background_position_check(dec_entry->value)) {
        mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
        return false;
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Repeat
 */
static bool mycss_property_parser_background_repeat_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_repeat;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

static bool mycss_property_parser_background_repeat_wait_two(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_repeat;
        return true;
    }
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_repeat_two(entry, token, &value_type, &str))
    {
        mycss_values_background_repeat_list_t *list = dec_entry->value;
        
        mycss_values_background_repeat_t *repeat = &list->entries[ (list->entries_length - 1) ];
        repeat->vertical = value_type;
        
        entry->parser = mycss_property_parser_background_repeat_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

static void mycss_property_parser_background_repeat_create_entry(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry, unsigned int value_type)
{
    if(dec_entry->value == NULL)
        dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_background_repeat_list_t));
    
    mycss_values_background_repeat_t *repeat = mycss_values_background_repeat_list_add_entry(entry, dec_entry->value);
    repeat->horizontal = value_type;
}

bool mycss_property_parser_background_repeat(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_repeat_one(entry, token, &value_type, &str))
    {
        mycss_property_parser_background_repeat_create_entry(entry, dec_entry, value_type);
        
        entry->parser = mycss_property_parser_background_repeat_end;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_background_repeat_two(entry, token, &value_type, &str))
    {
        mycss_property_parser_background_repeat_create_entry(entry, dec_entry, value_type);
        
        entry->parser = mycss_property_parser_background_repeat_wait_two;
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/*
 * Background Size
 */
static bool mycss_property_parser_background_size_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    if(mycss_property_shared_check_declaration_end(entry, token)) {
        return true;
    }
    
    if(token->type == MyCSS_TOKEN_TYPE_COMMA) {
        entry->parser = mycss_property_parser_background_size;
        return true;
    }
    
    return mycss_property_shared_switch_to_parse_error(entry);
}

static bool mycss_property_parser_background_size_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_size(entry, token, &value, &value_type, &str))
    {
        mycss_values_background_size_list_t *list = dec_entry->value;
        mycss_values_background_size_entry_t *bg_entry = &list->entries[ (list->entries_length - 1) ];
        
        if(value) {
            bg_entry->height = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->height->value.percentage = value;
            bg_entry->height->type = value_type;
            
            entry->parser = mycss_property_parser_background_size_end;
        }
        else if(value_type == MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO)
        {
            bg_entry->height = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->height->type = MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO;
            
            entry->parser = mycss_property_parser_background_size_end;
        }
        else
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

bool mycss_property_parser_background_size(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycore_string_t str = {0};
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void *value = NULL;
    unsigned int value_type = 0;
    
    if(mycss_property_shared_background_size(entry, token, &value, &value_type, &str))
    {
        if(dec_entry->value == NULL)
            dec_entry->value = mycss_values_create(entry, sizeof(mycss_values_background_size_list_t));
        
        mycss_values_background_size_entry_t *bg_entry = mycss_values_background_size_list_add_entry(entry, dec_entry->value);
        
        if(value) {
            bg_entry->width = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->width->value.percentage = value;
            bg_entry->width->type = value_type;
            
            entry->parser = mycss_property_parser_background_size_height;
        }
        else if(value_type == MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO)
        {
            bg_entry->width = mycss_values_create(entry, sizeof(mycss_values_type_length_percentage_entry_t));
            bg_entry->width->type = MyCSS_PROPERTY_BACKGROUND_SIZE_AUTO;
            
            entry->parser = mycss_property_parser_background_size_height;
        }
        else {
            bg_entry->scale = value_type;
            
            entry->parser = mycss_property_parser_background_size_end;
        }
        
        return mycss_property_parser_destroy_string(&str, true);
    }
    
    if(mycss_property_shared_default(entry, token, &dec_entry->value_type, &str)) {
        if(dec_entry->value == NULL)
            return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_find_important(entry));
    }
    
    return mycss_property_parser_destroy_string(&str, mycss_property_shared_switch_to_parse_error(entry));
}

/* Color */
bool mycss_property_parser_background_color(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return mycss_property_parser_color(entry, token, last_response);
}


