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

#ifndef MODEST_STYLE_RAW_H
#define MODEST_STYLE_RAW_H
#pragma once

#include <modest/myosi.h>
#include <modest/modest.h>
#include <myhtml/utils/mcobject.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct modest_style_raw modest_style_raw_t;
typedef struct modest_style_raw_declaration modest_style_raw_declaration_t;
typedef struct modest_style_raw_specificity modest_style_raw_specificity_t;

struct modest_style_raw_specificity {
    unsigned int x;
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct modest_style_raw_declaration {
    mycss_declaration_entry_t* declaration;
    modest_style_raw_specificity_t spec;
};

struct modest_style_raw {
    modest_style_raw_declaration_t* width;
    modest_style_raw_declaration_t* height;
    
    modest_style_raw_declaration_t* padding_top;
    modest_style_raw_declaration_t* padding_right;
    modest_style_raw_declaration_t* padding_bottom;
    modest_style_raw_declaration_t* padding_left;
    modest_style_raw_declaration_t* margin_top;
    modest_style_raw_declaration_t* margin_right;
    modest_style_raw_declaration_t* margin_bottom;
    modest_style_raw_declaration_t* margin_left;
    
    modest_style_raw_declaration_t* display;
    
    modest_style_raw_declaration_t* border_top_width;
    modest_style_raw_declaration_t* border_right_width;
    modest_style_raw_declaration_t* border_bottom_width;
    modest_style_raw_declaration_t* border_left_width;
    
    modest_style_raw_declaration_t* border_top_style;
    modest_style_raw_declaration_t* border_right_style;
    modest_style_raw_declaration_t* border_bottom_style;
    modest_style_raw_declaration_t* border_left_style;
    
    modest_style_raw_declaration_t* box_sizing;
    
    modest_style_raw_declaration_t* vertical_align;
    modest_style_raw_declaration_t* line_height;
};

modest_style_raw_t * modest_style_raw_create(modest_t* modest);
modest_status_t modest_style_raw_init(modest_t* modest, modest_style_raw_t* raw_style);

modest_style_raw_declaration_t * modest_style_raw_declaration_create(modest_t* modest);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_RAW_H */
