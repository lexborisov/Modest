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

#include "mycss/values/consume.h"

bool mycss_values_consume_length(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_DIMENSION || token->type == MyCSS_TOKEN_TYPE_NUMBER)
    {
        mycss_values_length_t *value = mycss_values_create(entry, sizeof(mycss_values_length_t));
        
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, false);
        
        double return_num;
        size_t consume_length = mycss_convert_data_to_double(str.data, str.length, &return_num, &value->is_float);
        
        if(token->type == MyCSS_TOKEN_TYPE_DIMENSION) {
            value->type = mycss_units_type_by_name(&str.data[consume_length], (str.length - consume_length));
            mycore_string_destroy(&str, false);
            
            if(value->type == MyCSS_UNIT_TYPE_UNDEF) {
                mycss_values_destroy(entry, value);
                return false;
            }
        }
        else {
            value->type = MyCSS_UNIT_TYPE_UNDEF;
            mycore_string_destroy(&str, false);
        }
        
        if(value->is_float)
            value->value.f = (float)return_num;
        else
            value->value.i = (int)return_num;
        
        *entry->values = value;
    }
    else
        return false;
    
    return true;
}

bool mycss_values_consume_percentage(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_PERCENTAGE)
    {
        mycss_values_percentage_t *value = mycss_values_create(entry, sizeof(mycss_values_length_t));
        
        mycore_string_t str;
        mycss_token_data_to_string(entry, token, &str, true, false);
        
        double return_num;
        mycss_convert_data_to_double(str.data, str.length, &return_num, &value->is_float);
        
        mycore_string_destroy(&str, false);
        
        if(value->is_float)
            value->value.f = (float)return_num;
        else
            value->value.i = (int)return_num;
        
        *entry->values = value;
        
        return true;
    }
    
    return false;
}



