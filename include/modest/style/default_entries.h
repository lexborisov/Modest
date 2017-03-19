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

#ifndef MODEST_STYLE_DEFAULT_ENTRIES_H
#define MODEST_STYLE_DEFAULT_ENTRIES_H
#pragma once

static mycss_declaration_entry_t modest_style_default_entry_display_none = {
    MyCSS_PROPERTY_TYPE_DISPLAY,
    MyCSS_PROPERTY_DISPLAY_NONE,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

static mycss_declaration_entry_t modest_style_default_entry_display_block = {
    MyCSS_PROPERTY_TYPE_DISPLAY,
    MyCSS_PROPERTY_DISPLAY_BLOCK,
    NULL,
    false,
    MyCSS_DECLARATION_FLAGS_READ_ONLY,
    NULL, NULL
};

#endif /* MODEST_STYLE_DEFAULT_ENTRIES_H */
