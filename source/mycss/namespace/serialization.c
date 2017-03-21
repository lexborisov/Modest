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

#include "mycss/namespace/serialization.h"

void mycss_namespace_serialization_stylesheet(mycss_namespace_stylesheet_t* ns_stylesheet, mycore_callback_serialize_f callback, void* context)
{
    mycss_namespace_entry_t* ns_entry = ns_stylesheet->entry_first;
    
    while(ns_entry) {
        callback("@namespace", 10, context);
        
        if(ns_entry->name && ns_entry->name->length) {
            callback(ns_entry->name->data, ns_entry->name->length, context);
        }
        
        if(ns_entry->url && ns_entry->url->length) {
            callback("\"", 1, context);
            callback(ns_entry->url->data, ns_entry->url->length, context);
            callback("\"", 1, context);
        }
        
        callback(";", 1, context);
        
        ns_entry = ns_entry->next;
    }
}

void mycss_namespace_serialization_entry(mycss_namespace_t* ns, mycss_namespace_entry_t* ns_entry, mycore_callback_serialize_f callback, void* context, bool with_vbar)
{
    if(ns_entry->name && ns_entry->name->length) {
        callback(ns_entry->name->data, ns_entry->name->length, context);
    }
    else if(ns_entry->ns_id == MyHTML_NAMESPACE_ANY)
        return;
    else if(ns_entry->ns_id == MyHTML_NAMESPACE_UNDEF) {
        /* some print */
    }
    else {
        if(ns_entry->ns_id < MyHTML_NAMESPACE_LAST_ENTRY) {
            callback("<default=", 9, context);
            
            const char *ns_name = myhtml_namespace_name_by_id(ns_entry->ns_id, NULL);
            callback(ns_name, strlen(ns_name), context);
            
            callback(">", 1, context);
        }
        else {
            callback("<default>", 9, context);
        }
    }
    
    if(with_vbar)
        callback("|", 1, context);
}

