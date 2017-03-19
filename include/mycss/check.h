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

#ifndef MyHTML_MyCSS_CHECK_H
#define MyHTML_MyCSS_CHECK_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/myosi.h>
#include <mycss/mycss.h>
#include <mycss/entry.h>

bool mycss_check_three_code_points_would_start_identifier(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
bool mycss_check_two_code_points_valid_escape(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
bool mycss_check_three_code_points_would_start_number(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_CHECK_H */
