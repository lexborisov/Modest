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

#ifndef MODEST_STYLE_SHEET_H
#define MODEST_STYLE_SHEET_H
#pragma once

#include <modest/myosi.h>
#include <modest/modest.h>
#include <modest/style/type.h>

#ifdef __cplusplus
extern "C" {
#endif

struct modest_style_sheet {
    modest_style_type_length_t width;
    modest_style_type_length_t height;
    
    modest_style_type_length_t padding_top;
    modest_style_type_length_t padding_right;
    modest_style_type_length_t padding_bottom;
    modest_style_type_length_t padding_left;
    
    modest_style_type_length_t margin_top;
    modest_style_type_length_t margin_right;
    modest_style_type_length_t margin_bottom;
    modest_style_type_length_t margin_left;
    
    modest_style_type_display_t display;
    
    modest_style_type_length_t border_top_width;
    modest_style_type_length_t border_right_width;
    modest_style_type_length_t border_bottom_width;
    modest_style_type_length_t border_left_width;
};

modest_style_sheet_t * modest_style_sheet_create(modest_t* modest);
mystatus_t modest_style_sheet_init(modest_t* modest, modest_style_sheet_t* m_stylesheet);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_SHEET_H */
