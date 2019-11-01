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

#include "mycss/declaration/serialization.h"
#include "mycss/declaration/serialization_resources.h"

static void mycss_declaration_serialization_important_if_need(mycss_declaration_entry_t* dec_entry, mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry->is_important) {
        callback(" !important", 11, context);
    }
}

bool mycss_declaration_serialization_entry(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                           mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    mycss_property_serialization_type_name(dec_entry->type, callback, context);
    
    callback(": ", 2, context);
    
    return mycss_declaration_serialization_map_by_type[ dec_entry->type ](entry, dec_entry, callback, context);
}

bool mycss_declaration_serialization_entry_only_value(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                      mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    return mycss_declaration_serialization_map_by_type[ dec_entry->type ](entry, dec_entry, callback, context);
}

bool mycss_declaration_serialization_entry_by_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                   mycss_property_type_t property_type,
                                                   mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL || property_type >= MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        return false;
    
    mycss_property_serialization_type_name(property_type, callback, context);
    
    callback(": ", 2, context);
    
    return mycss_declaration_serialization_map_by_type[ property_type ](entry, dec_entry, callback, context);
}

bool mycss_declaration_serialization_entry_only_value_by_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                              mycss_property_type_t property_type,
                                                              mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL || property_type >= MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        return false;
    
    return mycss_declaration_serialization_map_by_type[ property_type ](entry, dec_entry, callback, context);
}


void mycss_declaration_serialization_entries(mycss_entry_t* entry, mycss_declaration_entry_t* first_dec_entry,
                                             mycore_callback_serialize_f callback, void* context)
{
    if(first_dec_entry == NULL)
        return;
    
    while(first_dec_entry) {
        mycss_declaration_serialization_entry(entry, first_dec_entry, callback, context);
        
        if(first_dec_entry->next)
            callback("; ", 2, context);
        else
            callback(";", 1, context);
        
        first_dec_entry = first_dec_entry->next;
    }
}

bool mycss_declaration_serialization_undef(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                           mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    mycss_property_serialization_value(dec_entry->value_type, dec_entry->value, callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_shorthand_four(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                           mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL || dec_entry->value == NULL)
        return false;
    
    mycss_values_shorthand_four_t *value = (mycss_values_shorthand_four_t*)dec_entry->value;
    mycss_declaration_entry_t *tmp;
    
    if(value->one) {
        tmp = (mycss_declaration_entry_t*)value->one;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    if(value->two) {
        callback(" ", 1, context);
        
        tmp = (mycss_declaration_entry_t*)value->two;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    if(value->three) {
        callback(" ", 1, context);
        
        tmp = (mycss_declaration_entry_t*)value->three;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    if(value->four) {
        callback(" ", 1, context);
        
        tmp = (mycss_declaration_entry_t*)value->four;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_shorthand_two(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                   mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL || dec_entry->value == NULL)
        return false;
    
    mycss_values_shorthand_two_t *shorthand_two = (mycss_values_shorthand_two_t*)dec_entry->value;
    mycss_declaration_entry_t *tmp;
    
    if(shorthand_two->one) {
        tmp = (mycss_declaration_entry_t*)shorthand_two->one;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    if(shorthand_two->two) {
        callback(" ", 1, context);
        
        tmp = (mycss_declaration_entry_t*)shorthand_two->two;
        mycss_property_serialization_value(tmp->value_type, tmp->value, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_shorthand_two_type(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                        mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL || dec_entry->value == NULL)
        return false;
    
    mycss_values_shorthand_two_type_t *short_two_type = (mycss_values_shorthand_two_type_t*)dec_entry->value;
    
    if(short_two_type->one) {
        mycss_property_serialization_value(short_two_type->type_one, short_two_type->one, callback, context);
    }
    
    if(short_two_type->two) {
        callback(" ", 1, context);
        
        mycss_property_serialization_value(short_two_type->type_two, short_two_type->two, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_type_list(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                               mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_type_list_t *list = dec_entry->value;
    
    for(size_t i = 0; i < list->entries_length; i++) {
        if(i)
            callback(", ", 2, context);
        
        mycss_property_serialization_value(list->entries[i], NULL, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_text_decoration(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                     mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_text_decoration_t *text_decoration = (mycss_values_text_decoration_t*)dec_entry->value;
    
    if(text_decoration->line) {
        if(text_decoration->line->value == NULL)
            mycss_property_serialization_value(text_decoration->line->value_type, dec_entry->value, callback, context);
        else
            mycss_values_serialization_text_decoration_line(*((mycss_values_text_decoration_line_t*)text_decoration->line->value), callback, context);
    }
    
    if(text_decoration->style) {
        if(text_decoration->line)
            callback(" ", 1, context);
        
        mycss_property_serialization_value(text_decoration->style->value_type, text_decoration->style->value, callback, context);
    }
    
    if(text_decoration->color) {
        if(text_decoration->line || text_decoration->style)
            callback(" ", 1, context);
        
        mycss_values_serialization_color(text_decoration->color->value, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_font_family(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                 mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_font_family_t* font_family = (mycss_values_font_family_t*)dec_entry->value;
    
    for(size_t i = 0; i < font_family->entries_length; i++)
    {
        if(i)
            callback(", ", 2, context);
        
        if(font_family->entries[i].type == MyCSS_VALUES_FONT_FAMILY_TYPE_GENERIC) {
            mycss_property_serialization_value(font_family->entries[i].value.prop_type, NULL, callback, context);
        }
        else if(font_family->entries[i].type == MyCSS_VALUES_FONT_FAMILY_TYPE_NAME) {
            callback("\"", 1, context);
            mycore_string_t *str = &font_family->entries[i].value.str;
            callback(str->data, str->length, context);
            callback("\"", 1, context);
        }
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    return true;
}

bool mycss_declaration_serialization_font(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                          mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_font_t *font = dec_entry->value;
    bool set_ws = false;
    
    if(font->style) {
        set_ws = true;
        mycss_declaration_serialization_undef(entry, font->style, callback, context);
    }
    
    if(font->weight) {
        if(set_ws == false)
            set_ws = true;
        else
            callback(" ", 1, context);
        
        mycss_declaration_serialization_undef(entry, font->weight, callback, context);
    }
    
    if(font->stretch) {
        if(set_ws == false)
            set_ws = true;
        else
            callback(" ", 1, context);
        
        mycss_declaration_serialization_undef(entry, font->stretch, callback, context);
    }
    
    if(font->size) {
        if(set_ws == false)
            set_ws = true;
        else
            callback(" ", 1, context);
        
        mycss_declaration_serialization_undef(entry, font->size, callback, context);
        
        if(font->line_height) {
            callback(" / ", 3, context);
            mycss_declaration_serialization_undef(entry, font->line_height, callback, context);
        }
    }
    
    if(font->family) {
        if(set_ws == true)
            callback(" ", 1, context);
        
        mycss_declaration_serialization_font_family(entry, font->family, callback, context);
    }
    
    return true;
}

bool mycss_declaration_serialization_border_radius(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                   mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_shorthand_four_t *value = (mycss_values_shorthand_four_t*)dec_entry->value;
    mycss_values_shorthand_two_type_t *short_two_type;
    
    bool o_e = false;
    
    if(value->one && ((mycss_values_shorthand_two_type_t*)(value->one->value))->one) {
        o_e = true;
        short_two_type = value->one->value;
        mycss_property_serialization_value(short_two_type->type_one, short_two_type->one, callback, context);
    }
    
    if(value->two && ((mycss_values_shorthand_two_type_t*)(value->two->value))->one) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        
        short_two_type = value->two->value;
        mycss_property_serialization_value(short_two_type->type_one, short_two_type->one, callback, context);
    }
    
    if(value->three && ((mycss_values_shorthand_two_type_t*)(value->three->value))->one) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        
        short_two_type = value->three->value;
        mycss_property_serialization_value(short_two_type->type_one, short_two_type->one, callback, context);
    }
    
    if(value->four && ((mycss_values_shorthand_two_type_t*)(value->four->value))->one) {
        if(o_e) callback(" ", 1, context);
        
        short_two_type = value->four->value;
        mycss_property_serialization_value(short_two_type->type_one, short_two_type->one, callback, context);
    }
    
    o_e = false;
    
    if(value->one && ((mycss_values_shorthand_two_type_t*)(value->one->value))->two) {
        callback(" / ", 3, context);
        o_e = true;
        
        short_two_type = value->one->value;
        mycss_property_serialization_value(short_two_type->type_two, short_two_type->two, callback, context);
    }
    
    if(value->two && ((mycss_values_shorthand_two_type_t*)(value->two->value))->two) {
        if(o_e == false) callback(" / ", 3, context);
        else callback(" ", 1, context);
        
        o_e = true;
        
        short_two_type = value->two->value;
        mycss_property_serialization_value(short_two_type->type_two, short_two_type->two, callback, context);
    }
    
    if(value->three && ((mycss_values_shorthand_two_type_t*)(value->three->value))->two) {
        if(o_e == false) callback(" / ", 3, context);
        else callback(" ", 1, context);
        
        o_e = true;
        
        short_two_type = value->three->value;
        mycss_property_serialization_value(short_two_type->type_two, short_two_type->two, callback, context);
    }
    
    if(value->four && ((mycss_values_shorthand_two_type_t*)(value->four->value))->two) {
        if(o_e == false) callback(" / ", 3, context);
        else callback(" ", 1, context);
        
        short_two_type = value->four->value;
        mycss_property_serialization_value(short_two_type->type_two, short_two_type->two, callback, context);
    }
    
    return true;
}

bool mycss_declaration_serialization_text_decoration_line(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                        mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_serialization_text_decoration_line(*((mycss_values_text_decoration_line_t*)dec_entry->value), callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_text_decoration_skip(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                          mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_serialization_text_decoration_skip(*((mycss_values_text_decoration_skip_t*)dec_entry->value), callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_background(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;

    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);

    mycss_values_background_t* bg = dec_entry->value;

    bool o_e = false;

    if(bg->color) {
        o_e = true;
        mycss_property_serialization_value(bg->color->value_type, bg->color->value, callback, context);
    }

    if(bg->image) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_declaration_serialization_background_image(entry, bg->image, callback, context);
    }

    if(bg->position) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_declaration_serialization_background_position(entry, bg->position, callback, context);

        if(bg->size) {
            callback(" / ", 3, context);
            mycss_declaration_serialization_background_size(entry, bg->size, callback, context);
        }
    }

    if(bg->repeat) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_declaration_serialization_background_repeat(entry, bg->repeat, callback, context);
    }

    if(bg->attachment) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_declaration_serialization_type_list(entry, bg->attachment, callback, context);
    }

    if(bg->clip) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_declaration_serialization_type_list(entry, bg->clip, callback, context);
    }

    if(bg->origin) {
        if(o_e) callback(" ", 1, context);
        mycss_declaration_serialization_type_list(entry, bg->origin, callback, context);
    }

    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);

    return true;
}

bool mycss_declaration_serialization_background_image(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                      mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_image_list_t *list = dec_entry->value;
    
    for(size_t i = 0; i < list->images_length; i++) {
        if(i)
            callback(", ", 2, context);
        
        mycss_property_serialization_value(MyCSS_PROPERTY_VALUE__IMAGE, &list->images[i], callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_background_repeat(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                       mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_background_repeat_list_t *list = dec_entry->value;
    
    for(size_t i = 0; i < list->entries_length; i++) {
        if(i)
            callback(", ", 2, context);
        
        mycss_property_serialization_value(list->entries[i].horizontal, NULL, callback, context);
        
        if(list->entries[i].vertical) {
            if(list->entries[i].horizontal)
                callback(" ", 1, context);
            
            mycss_property_serialization_value(list->entries[i].vertical, NULL, callback, context);
        }
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_background_position(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                         mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_background_position_t *position = dec_entry->value;
    bool o_e = false;
    
    if(position->one.type) {
        o_e = true;
        mycss_property_serialization_value(position->one.type, position->one.value.length, callback, context);
    }
    
    if(position->two.type) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_property_serialization_value(position->two.type, position->two.value.length, callback, context);
    }
    
    if(position->three.type) {
        if(o_e) callback(" ", 1, context); else o_e = true;
        mycss_property_serialization_value(position->three.type, position->three.value.length, callback, context);
    }
    
    if(position->four.type) {
        if(o_e) callback(" ", 1, context);
        
        mycss_property_serialization_value(position->four.type, position->four.value.length, callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_background_size(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                     mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_background_size_list_t *list = dec_entry->value;
    
    for(size_t i = 0; i < list->entries_length; i++) {
        if(i)
            callback(", ", 2, context);
        
        mycss_values_serialization_background_size_entry(&list->entries[i], callback, context);
    }
    
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_border_x(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                              mycore_callback_serialize_f callback, void* context)
{
    if(dec_entry == NULL)
        return false;
    
    if(dec_entry->value == NULL)
        return mycss_declaration_serialization_undef(entry, dec_entry, callback, context);
    
    mycss_values_serialization_border(dec_entry->value, callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}


