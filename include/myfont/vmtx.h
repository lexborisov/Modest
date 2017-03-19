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

#ifndef MyFONT_VMTX_H
#define MyFONT_VMTX_H
#pragma once

#include <myfont/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

struct myfont_long_ver_metric {
    uint16_t	advanceHeight;
    int16_t		topSideBearing;
}
typedef myfont_long_ver_metric_t;

// table vmtx
struct myfont_table_vmtx {
    myfont_long_ver_metric_t *vMetrics;
    int16_t *topSideBearing;
}
typedef myfont_table_vmtx_t;

#include <myfont/myfont.h>

struct myfont_font;

mystatus_t myfont_load_table_vmtx(myfont_font_t* mf, uint8_t* data, size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_VMTX_H */
