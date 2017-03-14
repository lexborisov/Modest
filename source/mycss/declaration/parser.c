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

#include "mycss/declaration/parser.h"

void mycss_declaration_parser_begin(mycss_entry_t* entry, mycss_token_t* token)
{
    if(entry->declaration->entry == NULL) {
        /* some error */
    }
}

void mycss_declaration_parser_ident(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_declaration_entry_t* dec_entry = mycss_declaration_entry(entry->declaration);
    
    if(dec_entry == NULL || (dec_entry->flags & MyCSS_DECLARATION_FLAGS_BAD) == 0) {
        dec_entry = mycss_declaration_entry_create(entry->declaration, NULL);
        mycss_declaration_entry_append_to_current(entry->declaration, dec_entry);
    }
    else
        mycss_declaration_entry_clean(dec_entry);
    
    mycore_string_t str;
    mycss_token_data_to_string(entry, token, &str, true, false);
    
    const mycss_property_index_static_entry_t *prop_entry = mycss_property_index_entry_by_name(str.data, str.length);
    
    if(prop_entry) {
        dec_entry->type = prop_entry->type;
        
        entry->parser = mycss_declaration_state_ident;
        entry->parser_switch = prop_entry->parser;
    }
    else {
        entry->parser = mycss_declaration_state_parse_error;
    }
    
    mycore_string_destroy(&str, false);
}

void mycss_declaration_parser_end(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_declaration_entry_t* dec_entry = mycss_declaration_entry(entry->declaration);
    
    if(dec_entry && dec_entry->type == MyCSS_PROPERTY_TYPE_UNDEF) {
        if(dec_entry->prev) {
            entry->declaration->entry_last = dec_entry->prev;
            
            dec_entry->prev->next = NULL;
            dec_entry->prev = NULL;
            
            mycss_declaration_entry_destroy(entry->declaration, dec_entry, true);
        }
        else {
            *entry->declaration->entry = NULL;
            entry->declaration->entry_last = NULL;
        }
    }
}


