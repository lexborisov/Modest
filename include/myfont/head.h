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

#ifndef MyFONT_HEAD_H
#define MyFONT_HEAD_H
#pragma once

#include <myfont/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

struct myfont_table_head {
    uint32_t version;
    uint32_t fontRevision;
    uint32_t checkSumAdjustment;
    uint32_t magicNumber;
    uint16_t flags;
    uint16_t unitsPerEm;
    uint32_t created[2];  // 64bit
    uint32_t modified[2]; // 64bit
    int16_t  xMin;
    int16_t  yMin;
    int16_t  xMax;
    int16_t  yMax;
    uint16_t macStyle;
    uint16_t lowestRecPPEM;
    int16_t  fontDirectionHint;
    int16_t  indexToLocFormat;
    int16_t  glyphDataFormat;
}
typedef myfont_table_head_t;

#include <myfont/myfont.h>

struct myfont_font;

mystatus_t myfont_load_table_head(myfont_font_t *mf, uint8_t* data, size_t data_size);

float myfont_head_yMax_pixel(myfont_font_t *mf, float font_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_HEAD_H */
