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

#ifndef MyHTML_MyCSS_CONVERT_H
#define MyHTML_MyCSS_CONVERT_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycss/entry.h"
#include "myhtml/mystring.h"

const char * mycss_convert_split_dimension_string(mycore_string_t* str, double* value, bool* is_float);

size_t mycss_convert_data_to_integer(const char* data, size_t size, long* return_num);
size_t mycss_convert_data_to_double(const char *data, size_t size, double *return_num, bool* is_float);
size_t mycss_convert_unicode_range_to_codepoint(const char *data, size_t size, size_t *start, size_t *end);
size_t mycss_convert_hex_to_codepoint(const char *data, size_t size, size_t *codepoint, unsigned int max_consumed);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_CONVERT_H */
