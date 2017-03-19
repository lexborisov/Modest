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

#ifndef MyCSS_VALUES_IMAGE_RESOURCES_H
#define MyCSS_VALUES_IMAGE_RESOURCES_H
#pragma once

#define MyCSS_IMAGE_FUNCTION_STATIC_INDEX_FOR_SEARCH_SIZE 13

static const mycss_values_image_function_index_static_entry_t mycss_values_image_function_index_static_for_search[] = 
{
	{NULL, 0, 0, 0, 0, 0, 0},
	{"url", 3, MyCSS_PROPERTY_VALUE__URL, mycss_property_parser_url_string, mycss_values_image_creator_url, 0, 1},
	{NULL, 0, 0, 0, 0, 0, 0},
	{NULL, 0, 0, 0, 0, 0, 0},
	{NULL, 0, 0, 0, 0, 0, 0},
	{"image-set", 9, MyCSS_PROPERTY_VALUE__IMAGE_SET_FUNCTION, mycss_property_parser_image_function_image_set, mycss_values_image_creator_image_set, 0, 5},
	{NULL, 0, 0, 0, 0, 0, 0},
	{NULL, 0, 0, 0, 0, 0, 0},
	{"cross-fade", 10, MyCSS_PROPERTY_VALUE__CROSS_FADE_FUNCTION, mycss_property_parser_image_function_cross_fade, mycss_values_image_creator_cross_fade, 0, 8},
	{NULL, 0, 0, 0, 0, 0, 0},
	{NULL, 0, 0, 0, 0, 0, 0},
	{NULL, 0, 0, 0, 0, 0, 0},
	{"image", 5, MyCSS_PROPERTY_VALUE__IMAGE_FUNCTION, mycss_property_parser_image_function_image, mycss_values_image_creator_function_image, 0, 12},
	{"string", 6, MyCSS_PROPERTY_VALUE__ELEMENT_FUNCTION, mycss_property_parser_image_function_string, mycss_values_image_creator_element, 0, 13},
};




#endif /* MyCSS_VALUES_IMAGE_RESOURCES_H */
