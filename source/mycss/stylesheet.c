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

#include "mycss/stylesheet.h"

mycss_stylesheet_t * mycss_stylesheet_create(void)
{
    return (mycss_stylesheet_t*)mycore_calloc(1, sizeof(mycss_stylesheet_t));
}

mystatus_t mycss_stylesheet_init(mycss_stylesheet_t* stylesheet, mycss_entry_t* entry)
{
    stylesheet->entry = entry;
    
    mystatus_t status = mycss_namespace_stylesheet_init(&stylesheet->ns_stylesheet, entry);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_stylesheet_clean_all(mycss_stylesheet_t* stylesheet)
{
    mystatus_t status = mycss_namespace_stylesheet_clean(&stylesheet->ns_stylesheet, stylesheet->entry);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    memset(stylesheet, 0, sizeof(mycss_stylesheet_t));
    
    return MyCSS_STATUS_OK;
}

mycss_stylesheet_t * mycss_stylesheet_destroy(mycss_stylesheet_t* stylesheet, bool self_destroy)
{
    mycss_namespace_stylesheet_destroy(&stylesheet->ns_stylesheet, stylesheet->entry, false);
    
    if(self_destroy) {
        mycore_free(stylesheet);
        return NULL;
    }
    
    return stylesheet;
}

/* print */
void mycss_stylesheet_serialization(mycss_stylesheet_t* stylesheet, mycore_callback_serialize_f callback, void* context)
{
    mycss_selectors_serialization_list(stylesheet->entry->selectors, stylesheet->sel_list_first, callback, context);
}


