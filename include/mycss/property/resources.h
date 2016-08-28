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

#ifndef MyHTML_MyCSS_PROPERTY_RESOURCES_H
#define MyHTML_MyCSS_PROPERTY_RESOURCES_H
#pragma once

#define MyCSS_PROPERTY_STATIC_INDEX_FOR_SEARCH_SIZE 3
#define MyCSS_PROPERTY_VALUE_STATIC_INDEX_FOR_SEARCH_SIZE 5

static const mycss_property_index_static_entry_t mycss_property_index_static_for_search[] = 
{
	{NULL, 0, MyCSS_PROPERTY_TYPE_UNDEF, NULL, 0, 0},
	{"height", 6, MyCSS_PROPERTY_TYPE_HEIGHT, mycss_property_parser_height, 0, 1},
	{NULL, 0, MyCSS_PROPERTY_TYPE_UNDEF, NULL, 0, 0},
	{"width", 5, MyCSS_PROPERTY_TYPE_WIDTH, mycss_property_parser_width, 0, 3},
};

static const mycss_property_value_index_static_entry_t mycss_property_value_index_static_for_search[] = 
{
	{NULL, 0, MyCSS_PROPERTY_VALUE_UNDEF, 0, 0},
	{"inherit", 7, MyCSS_PROPERTY_VALUE_INHERIT, 0, 1},
	{NULL, 0, MyCSS_PROPERTY_VALUE_UNDEF, 0, 0},
	{NULL, 0, MyCSS_PROPERTY_VALUE_UNDEF, 0, 0},
	{"auto", 4, MyCSS_PROPERTY_VALUE_AUTO, 0, 4},
	{NULL, 0, MyCSS_PROPERTY_VALUE_UNDEF, 0, 0},
};

static const char * mycss_property_index_type_name[] = 
{
	"",
	"height",
	"width",
	""
};

static const char * mycss_property_index_type_value[] = 
{
	"",
	"auto",
	"inherit",
	"length",
	"percentage",
	""
};


#endif /* MyHTML_MyCSS_PROPERTY_RESOURCES_H */
