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

#ifndef MyHTML_MyCSS_STYLESHEET_H
#define MyHTML_MyCSS_STYLESHEET_H
#pragma once

#include "mycss/myosi.h"
#include "mycss/entry.h"
#include "mycss/namespace/myosi.h"
#include "mycss/selectors/myosi.h"
#include "mycss/selectors/serialization.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mycss_stylesheet {
    mycss_entry_t* entry; /* refs */
    
    mycss_namespace_stylesheet_t ns_stylesheet;
    mycss_selectors_list_t* sel_list_first;
    
    mycss_stylesheet_t* child;
    mycss_stylesheet_t* parent;
    mycss_stylesheet_t* next;
    mycss_stylesheet_t* prev;
};

mycss_stylesheet_t * mycss_stylesheet_create(void);
mystatus_t mycss_stylesheet_init(mycss_stylesheet_t* stylesheet, mycss_entry_t* entry);
mystatus_t mycss_stylesheet_clean_all(mycss_stylesheet_t* stylesheet);
mycss_stylesheet_t * mycss_stylesheet_destroy(mycss_stylesheet_t* stylesheet, bool self_destroy);

void mycss_stylesheet_serialization(mycss_stylesheet_t* stylesheet, mycore_callback_serialize_f callback, void* context);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* MyHTML_MyCSS_STYLESHEET_H */
