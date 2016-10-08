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

bool mycss_property_shared_length(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_declaration_entry_t* dec_entry = entry->declaration->entry_last;
    
    void *value = NULL;
    mycss_values_entry_set(entry, &value);
    
    if(mycss_values_consume_length(entry, token)) {
        dec_entry->value = value;
        dec_entry->value_type = MyCSS_PROPERTY_WIDTH_LENGTH;
    }
    else if(mycss_values_consume_percentage(entry, token)) {
        dec_entry->value = value;
        dec_entry->value_type = MyCSS_PROPERTY_WIDTH_PERCENTAGE;
    }
    else if(token->type == MyCSS_TOKEN_TYPE_IDENT)
    {
        myhtml_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, false);
        
        dec_entry->value_type = mycss_property_value_type_by_name(str.data, str.length);
        myhtml_string_destroy(&str, false);
        
        if(dec_entry->value_type != MyCSS_PROPERTY_WIDTH_AUTO &&
           dec_entry->value_type != MyCSS_PROPERTY_WIDTH_INHERIT)
        {
            return mycss_property_shared_switch_to_parse_error(entry);
        }
    }
    else {
        return mycss_property_shared_switch_to_parse_error(entry);
    }
    
    return mycss_property_shared_switch_to_find_important(entry);
}

bool mycss_property_shared_line_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    return true;
}


