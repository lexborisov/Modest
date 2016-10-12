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

#include "mycss/values/serialization.h"
#include "mycss/values/units_resources.h"

static void mycss_values_serialization_to_callback(const char* data, size_t len, mycss_callback_serialization_f callback, void* context)
{
    if(len > 0)
        callback(data, len, context);
}

void mycss_values_serialization_length(mycss_values_length_t* value, mycss_callback_serialization_f callback, void* context)
{
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    
    if(value->type < MyCSS_UNIT_TYPE_LAST_ENTRY) {
        const char* name = mycss_units_index_name[ value->type ];
        callback(name, strlen(name), context);
    }
}

void mycss_values_serialization_percentage(mycss_values_percentage_t* value, mycss_callback_serialization_f callback, void* context)
{
    char buff[512];
    
    if(value->is_float) {
        int len = snprintf(buff, 512, "%0.4f%%", value->f);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
    else {
        int len = snprintf(buff, 512, "%d%%", value->i);
        mycss_values_serialization_to_callback(buff, len, callback, context);
    }
}


