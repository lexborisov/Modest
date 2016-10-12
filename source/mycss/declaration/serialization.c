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

#include "mycss/declaration/serialization.h"
#include "mycss/declaration/serialization_resources.h"

static void mycss_declaration_serialization_important_if_need(mycss_declaration_entry_t* dec_entry, mycss_callback_serialization_f callback, void* context)
{
    if(dec_entry->is_important) {
        callback(" !important", 11, context);
    }
}

bool mycss_declaration_serialization_entry(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                           mycss_callback_serialization_f callback, void* context)
{
    mycss_property_serialization_type_name(dec_entry->type, callback, context);
    
    callback(": ", 2, context);
    
    return mycss_declaration_serialization_map_by_type[ dec_entry->type ](entry, dec_entry, callback, context);
}

void mycss_declaration_serialization_entries(mycss_entry_t* entry, mycss_declaration_entry_t* first_dec_entry,
                                             mycss_callback_serialization_f callback, void* context)
{
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
                                           mycss_callback_serialization_f callback, void* context)
{
    if(dec_entry->value == NULL)
        return false;
    
    mycss_property_serialization_value(dec_entry->value_type, dec_entry->value, callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}

bool mycss_declaration_serialization_padding(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                           mycss_callback_serialization_f callback, void* context)
{
    if(dec_entry->value == NULL)
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

bool mycss_declaration_serialization_padding_x(mycss_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                               mycss_callback_serialization_f callback, void* context)
{
    if(dec_entry->value == NULL)
        return false;
    
    mycss_property_serialization_value(dec_entry->value_type, dec_entry->value, callback, context);
    mycss_declaration_serialization_important_if_need(dec_entry, callback, context);
    
    return true;
}
