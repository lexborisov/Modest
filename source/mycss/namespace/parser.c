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

#include "mycss/namespace/parser.h"


void mycss_namespace_parser_begin(mycss_entry_t* entry)
{
    mycss_namespace_entry_t *ns_entry = mycss_namespace_entry_create(entry->ns);
    mycss_namespace_entry_clean(ns_entry);
    
    mycss_namespace_entry_append_to_current(entry->ns, ns_entry);
}

void mycss_namespace_parser_name(mycss_entry_t* entry, mycss_token_t* token)
{
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    entry->ns->entry_last->name = str;
}

void mycss_namespace_parser_url(mycss_entry_t* entry, mycss_token_t* token)
{
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    mycss_token_data_to_string(entry, token, str, true, false);
    
    entry->ns->entry_last->url = str;
}

void mycss_namespace_parser_end(mycss_entry_t* entry, mycss_token_t* token)
{
    mycss_namespace_entry_t *ns_entry = entry->ns->entry_last;
    
    mycore_string_t *str_url = entry->ns->entry_last->url;
    ns_entry->ns_id = myhtml_namespace_id_by_url(str_url->data, str_url->length);
    
    if(ns_entry->name) {
        mycore_string_t *str = ns_entry->name;
        
        ns_entry->mctree_id = mctree_insert(entry->ns->ns_stylesheet->name_tree, str->data, str->length, (void*)ns_entry, NULL);
        
        if(str_url->length && ns_entry->ns_id == MyHTML_NAMESPACE_UNDEF)
            ns_entry->ns_id = MyHTML_NAMESPACE_LAST_ENTRY + (myhtml_namespace_t)ns_entry->mctree_id;
        
        return;
    }
    
    mycss_namespace_stylesheet_append_default(entry->ns->ns_stylesheet, ns_entry);
    ns_entry->mctree_id = mctree_insert(entry->ns->ns_stylesheet->name_tree, " ", 1, (void*)ns_entry, NULL);
    
    if(str_url->length && ns_entry->ns_id == MyHTML_NAMESPACE_UNDEF)
        ns_entry->ns_id = MyHTML_NAMESPACE_LAST_ENTRY + (myhtml_namespace_t)ns_entry->mctree_id;
}

void mycss_namespace_parser_expectations_error(mycss_entry_t* entry, mycss_token_t* token)
{
    if(entry->ns->entry_last == NULL)
        return;
    
    mycss_namespace_entry_t *ns_entry = entry->ns->entry_last;
    mycss_namespace_entry_destroy(ns_entry, entry, false);
    
    if(ns_entry->prev) {
        entry->ns->entry_last = ns_entry->prev;
        entry->ns->entry_last->next = NULL;
    }
    else {
        entry->ns->entry_last = NULL;
    }
    
    mcobject_free(entry->ns->mcobject_entries, ns_entry);
}


