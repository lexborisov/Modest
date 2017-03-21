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

#ifndef MyFONT_PCLT_H
#define MyFONT_PCLT_H
#pragma once

#include <myfont/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

// table pclt
struct myfont_table_pclt {
    int32_t  version;
    uint32_t fontNumber;
    uint16_t pitch;
    uint16_t xHeight;
    uint16_t style;
    uint16_t typeFamily;
    uint16_t capHeight;
    uint16_t symbolSet;
    char     typeface[16];
    char     characterComplement[8];
    char     fileName[6];
    char     strokeWeight;
    char     widthType;
    uint8_t  serifStyle;
    uint8_t  reserved;
}
typedef myfont_table_pclt_t;

#include <myfont/myfont.h>

struct myfont_font;

mystatus_t myfont_load_table_pclt(myfont_font_t* mf, uint8_t* data, size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_PCLT_H */
