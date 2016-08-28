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

void mycss_serialization_length(mycss_values_length_t* value, FILE* fh)
{
    if(value->is_float) {
        fprintf(fh, "%0.4f", value->f);
    }
    else {
        fprintf(fh, "%d", value->i);
    }
    
    if(value->type < MyCSS_UNIT_TYPE_LAST_ENTRY) {
        fprintf(fh, "%s", mycss_units_index_name[ value->type ]);
    }
}

void mycss_serialization_percentage(mycss_values_percentage_t* value, FILE* fh)
{
    if(value->is_float) {
        fprintf(fh, "%0.4f%%", value->f);
    }
    else {
        fprintf(fh, "%d%%", value->i);
    }
}

