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

static void mycss_values_parser_url_switch(mycss_entry_t* entry)
{
    mycss_stack_entry_t *stack_entry = mycss_stack_pop(entry->declaration->stack);
    
    if(stack_entry->value)
        entry->declaration->entry_last->value = stack_entry->value;
    
    entry->parser = stack_entry->parser;
}

bool mycss_property_parser_url_end(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            return true;
            
        case MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS:
            mycss_values_parser_url_switch(entry);
            return true;
            
        default:
            mycss_values_parser_url_switch(entry);
            return false;
    }
}

bool mycss_property_parser_url_string(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    else if(token->type != MyCSS_TOKEN_TYPE_STRING) {
        mycss_values_parser_url_switch(entry);
        return false;
    }
    
    mycore_string_t *str = mycss_values_create(entry, sizeof(mycore_string_t));
    mycss_token_data_to_string(entry, token, str, true, false);
    
    mycss_declaration_entry_t* declr_entry = entry->declaration->entry_last;
    declr_entry->value = str;
    
    entry->parser = mycss_property_parser_url_end;
    return true;
}


