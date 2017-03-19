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

#ifndef MyFONT_HMTX_H
#define MyFONT_HMTX_H
#pragma once

#include "myfont/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

struct myfont_long_hor_metric {
    uint16_t	advanceWidth;
    int16_t		lsb;
}
typedef myfont_long_hor_metric_t;

// table hhea
struct myfont_table_hmtx {
    myfont_long_hor_metric_t *hMetrics;
    int16_t *leftSideBearing;
}
typedef myfont_table_hmtx_t;

#include "myfont/myfont.h"

struct myfont_font;

mystatus_t myfont_load_table_hmtx(myfont_font_t* mf, uint8_t* data, size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_HMTX_H */
