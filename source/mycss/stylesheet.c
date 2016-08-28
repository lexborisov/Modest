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

#include "mycss/stylesheet.h"

mycss_stylesheet_t * mycss_stylesheet_create(void)
{
    return (mycss_stylesheet_t*)myhtml_calloc(1, sizeof(mycss_stylesheet_t));
}

mycss_status_t mycss_stylesheet_init(mycss_stylesheet_t* stylesheet, mycss_entry_t* entry)
{
    stylesheet->entry = entry;
    
    mycss_status_t status = mycss_namespace_stylesheet_init(&stylesheet->ns_stylesheet, entry);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    return MyCSS_STATUS_OK;
}

mycss_status_t mycss_stylesheet_clean_all(mycss_stylesheet_t* stylesheet)
{
    mycss_status_t status = mycss_namespace_stylesheet_clean(&stylesheet->ns_stylesheet, stylesheet->entry);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    memset(stylesheet, 0, sizeof(mycss_stylesheet_t));
    
    return MyCSS_STATUS_OK;
}

mycss_stylesheet_t * mycss_stylesheet_destroy(mycss_stylesheet_t* stylesheet, bool self_destroy)
{
    mycss_namespace_stylesheet_destroy(&stylesheet->ns_stylesheet, stylesheet->entry, false);
    
    if(self_destroy) {
        myhtml_free(stylesheet);
        return NULL;
    }
    
    return stylesheet;
}

/* print */
void mycss_stylesheet_print(mycss_stylesheet_t* stylesheet, FILE* fh)
{
    mycss_selectors_print_list(stylesheet->entry->selectors, stylesheet->sel_list_first, fh);
}


