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

#ifndef MyFONT_VHEA_H
#define MyFONT_VHEA_H
#pragma once

#include "myfont/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

// table vhea
struct myfont_table_vhea {
    uint32_t version;
    int16_t  Ascender;
    int16_t  Descender;
    int16_t  LineGap;
    int16_t  advanceHeightMax;
    int16_t  minTopSideBearing;
    int16_t  minBottomSideBearing;
    int16_t  yMaxExtent;
    int16_t  caretSlopeRise;
    int16_t  caretSlopeRun;
    int16_t  caretOffset;
    int16_t  reserved1;
    int16_t  reserved2;
    int16_t  reserved3;
    int16_t  reserved4;
    int16_t  metricDataFormat;
    uint16_t numOfLongVerMetrics;
}
typedef myfont_table_vhea_t;

#include "myfont/myfont.h"

struct myfont_font;

mystatus_t myfont_load_table_vhea(myfont_font_t* mf, uint8_t* data, size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_VHEA_H */
