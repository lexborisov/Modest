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

#ifndef MyFONT_NAME_H
#define MyFONT_NAME_H
#pragma once

#include <myfont/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

// table name
struct myfont_table_name_record {
    uint16_t  platformID;
    uint16_t  encodingID;
    uint16_t  languageID;
    uint16_t  nameID;
    uint16_t  length;
    uint16_t  offset;
}
typedef myfont_record_t;

struct myfont_lang_tag_record {
    uint16_t  length;
    uint16_t  offset;
}
typedef myfont_ltag_record_t;

struct myfont_table_name {
    uint16_t              format;
    uint16_t              count;
    uint16_t              stringOffset;
    myfont_record_t      *nameRecord;
    uint16_t              langTagCount;
    myfont_ltag_record_t *langTagRecord;
    char                 *str_data;
}
typedef myfont_table_name_t;

#include <myfont/myfont.h>

struct myfont_font;

mystatus_t myfont_load_table_name(myfont_font_t *mf, uint8_t* data, size_t data_size);
    
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_NAME_H */
