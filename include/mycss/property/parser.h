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

#ifndef MyHTML_MyCSS_PROPERTY_PARSER_H
#define MyHTML_MyCSS_PROPERTY_PARSER_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/property/myosi.h>
#include <mycss/values/consume.h>
#include <mycss/values/values.h>

bool mycss_property_parser_width(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_property_parser_height(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_PARSER_H */
