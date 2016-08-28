/*
 Copyright (C) 2015-2016 Alexander Borisov

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA

 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MyHTML_MyCSS_PROPERTY_CONST_H
#define MyHTML_MyCSS_PROPERTY_CONST_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum mycss_property_type {
	MyCSS_PROPERTY_TYPE_UNDEF      = 0x0000,
	MyCSS_PROPERTY_TYPE_HEIGHT     = 0x0001,
	MyCSS_PROPERTY_TYPE_WIDTH      = 0x0002,
	MyCSS_PROPERTY_TYPE_LAST_ENTRY = 0x0003
}
typedef mycss_property_type_t;

enum mycss_property_value {
	MyCSS_PROPERTY_VALUE_UNDEF      = 0x0000,
	MyCSS_PROPERTY_VALUE_AUTO       = 0x0001,
	MyCSS_PROPERTY_VALUE_INHERIT    = 0x0002,
	MyCSS_PROPERTY_VALUE_LENGTH     = 0x0003,
	MyCSS_PROPERTY_VALUE_PERCENTAGE = 0x0004,
	MyCSS_PROPERTY_VALUE_LAST_ENTRY = 0x0005
}
typedef mycss_property_value_t;

enum mycss_property_height {
	MyCSS_PROPERTY_HEIGHT_AUTO       = 0x0001,
	MyCSS_PROPERTY_HEIGHT_INHERIT    = 0x0002,
	MyCSS_PROPERTY_HEIGHT_LENGTH     = 0x0003,
	MyCSS_PROPERTY_HEIGHT_PERCENTAGE = 0x0004
}
typedef mycss_property_height_t;

enum mycss_property_width {
	MyCSS_PROPERTY_WIDTH_AUTO       = 0x0001,
	MyCSS_PROPERTY_WIDTH_INHERIT    = 0x0002,
	MyCSS_PROPERTY_WIDTH_LENGTH     = 0x0003,
	MyCSS_PROPERTY_WIDTH_PERCENTAGE = 0x0004
}
typedef mycss_property_width_t;



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_PROPERTY_CONST_H */


