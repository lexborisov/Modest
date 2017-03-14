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
 
 By specification https://www.microsoft.com/typography/otspec/otff.htm
*/

#ifndef MyFONT_BASE_H
#define MyFONT_BASE_H
#pragma once

#include <myhtml/myosi.h>

// Required Tables
#define MyFONT_TABLE_TYPE_cmap 1885433187
#define MyFONT_TABLE_TYPE_head 1684104552
#define MyFONT_TABLE_TYPE_hhea 1634035816
#define MyFONT_TABLE_TYPE_hmtx 2020896104
#define MyFONT_TABLE_TYPE_maxp 1886937453
#define MyFONT_TABLE_TYPE_name 1701667182
#define MyFONT_TABLE_TYPE_OS_2 841962319   // OS/2
#define MyFONT_TABLE_TYPE_post 1953722224

// Tables Related to TrueType Outlines
#define MyFONT_TABLE_TYPE_cvt  1953915648
#define MyFONT_TABLE_TYPE_fpgm 1835495526
#define MyFONT_TABLE_TYPE_glyf 1719233639
#define MyFONT_TABLE_TYPE_loca 1633906540
#define MyFONT_TABLE_TYPE_prep 1885696624
#define MyFONT_TABLE_TYPE_gasp 1886609767

// Tables Related to PostScript Outlines
#define MyFONT_TABLE_TYPE_CFF  1179009792
#define MyFONT_TABLE_TYPE_VORG 1196576598

// Tables Related to SVG
#define MyFONT_TABLE_TYPE_SVG  1196839680

// Tables Related to Bitmap Glyphs
#define MyFONT_TABLE_TYPE_EBDT 1413759557
#define MyFONT_TABLE_TYPE_EBLC 1129071173
#define MyFONT_TABLE_TYPE_EBSC 1129529925
#define MyFONT_TABLE_TYPE_CBDT 1413759555
#define MyFONT_TABLE_TYPE_CBLC 1129071171

// Advanced Typographic Tables
#define MyFONT_TABLE_TYPE_BASE 1163084098
#define MyFONT_TABLE_TYPE_GDEF 1178944583
#define MyFONT_TABLE_TYPE_GPOS 1397706823
#define MyFONT_TABLE_TYPE_GSUB 1112888135
#define MyFONT_TABLE_TYPE_JSTF 1179931466
#define MyFONT_TABLE_TYPE_MATH 1213481293

// Other OpenType Tables
#define MyFONT_TABLE_TYPE_DSIG 1195987780
#define MyFONT_TABLE_TYPE_hdmx 2020435048
#define MyFONT_TABLE_TYPE_kern 1852990827
#define MyFONT_TABLE_TYPE_LTSH 1213420620
#define MyFONT_TABLE_TYPE_PCLT 1414284112
#define MyFONT_TABLE_TYPE_VDMX 1481458774
#define MyFONT_TABLE_TYPE_vhea 1634035830
#define MyFONT_TABLE_TYPE_vmtx 2020896118
#define MyFONT_TABLE_TYPE_COLR 1380732739
#define MyFONT_TABLE_TYPE_CPAL 1279348803

#ifdef __cplusplus
extern "C" {
#endif

// base
/*
 Very important!!!
*/
enum myfont_status {
    MyFONT_STATUS_OK                                    = 0x000000,
    MyFONT_STATUS_ERROR_MEMORY_ALLOCATION               = 0x070001,
    MyFONT_STATUS_NOT_FOUND                             = 0x070002,
    MyFONT_STATUS_ERROR_TABLE_BROKEN                    = 0x070003,
    MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING         = 0x070004,
    MyFONT_STATUS_ERROR_TABLE_LACKS_REQUIRED            = 0x070004,
    MyFONT_STATUS_ERROR_FILE_OPEN                       = 0x070030,
    MyFONT_STATUS_ERROR_FILE_SEEK                       = 0x070031,
    MyFONT_STATUS_ERROR_FILE_READ                       = 0x070032,
    MyFONT_STATUS_ERROR_FILE_TELL                       = 0x070033,
    MyFONT_STATUS_ERROR_FILE_CLOSE                      = 0x070034,
    MyFONT_STATUS_ERROR_FILE_TOO_SMALL                  = 0x070035,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CMAP                 = 0x070040,
    MyFONT_STATUS_ERROR_TABLE_LOAD_HEAD                 = 0x070041,
    MyFONT_STATUS_ERROR_TABLE_LOAD_HHEA                 = 0x070042,
    MyFONT_STATUS_ERROR_TABLE_LOAD_HMTX                 = 0x070043,
    MyFONT_STATUS_ERROR_TABLE_LOAD_MAXP                 = 0x070044,
    MyFONT_STATUS_ERROR_TABLE_LOAD_NAME                 = 0x070045,
    MyFONT_STATUS_ERROR_TABLE_LOAD_OS_2                 = 0x070046,
    MyFONT_STATUS_ERROR_TABLE_LOAD_POST                 = 0x070047,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CVT                  = 0x070048,
    MyFONT_STATUS_ERROR_TABLE_LOAD_FPGM                 = 0x070049,
    MyFONT_STATUS_ERROR_TABLE_LOAD_GLYF                 = 0x07004a,
    MyFONT_STATUS_ERROR_TABLE_LOAD_LOCA                 = 0x07004b,
    MyFONT_STATUS_ERROR_TABLE_LOAD_PREP                 = 0x07004c,
    MyFONT_STATUS_ERROR_TABLE_LOAD_GASP                 = 0x07004d,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CFF                  = 0x07004e,
    MyFONT_STATUS_ERROR_TABLE_LOAD_VORG                 = 0x07004f,
    MyFONT_STATUS_ERROR_TABLE_LOAD_SVG                  = 0x070050,
    MyFONT_STATUS_ERROR_TABLE_LOAD_EBDT                 = 0x070051,
    MyFONT_STATUS_ERROR_TABLE_LOAD_EBLC                 = 0x070052,
    MyFONT_STATUS_ERROR_TABLE_LOAD_EBSC                 = 0x070053,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CBDT                 = 0x070054,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CBLC                 = 0x070055,
    MyFONT_STATUS_ERROR_TABLE_LOAD_BASE                 = 0x070056,
    MyFONT_STATUS_ERROR_TABLE_LOAD_GDEF                 = 0x070057,
    MyFONT_STATUS_ERROR_TABLE_LOAD_GPOS                 = 0x070058,
    MyFONT_STATUS_ERROR_TABLE_LOAD_GSUB                 = 0x070059,
    MyFONT_STATUS_ERROR_TABLE_LOAD_JSTF                 = 0x07005a,
    MyFONT_STATUS_ERROR_TABLE_LOAD_MATH                 = 0x07005b,
    MyFONT_STATUS_ERROR_TABLE_LOAD_DSIG                 = 0x07005c,
    MyFONT_STATUS_ERROR_TABLE_LOAD_HDMX                 = 0x07005d,
    MyFONT_STATUS_ERROR_TABLE_LOAD_KERN                 = 0x07005e,
    MyFONT_STATUS_ERROR_TABLE_LOAD_LTSH                 = 0x07005f,
    MyFONT_STATUS_ERROR_TABLE_LOAD_PCLT                 = 0x070060,
    MyFONT_STATUS_ERROR_TABLE_LOAD_VDMX                 = 0x070061,
    MyFONT_STATUS_ERROR_TABLE_LOAD_VHEA                 = 0x070062,
    MyFONT_STATUS_ERROR_TABLE_LOAD_VMTX                 = 0x070063,
    MyFONT_STATUS_ERROR_TABLE_LOAD_COLR                 = 0x070064,
    MyFONT_STATUS_ERROR_TABLE_LOAD_CPAL                 = 0x070065,
    MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND                 = 0x070100,
}
typedef myfont_status_t;

enum myfont_table_key {
    MyFONT_TKEY_cmap = 0x00,
    MyFONT_TKEY_head = 0x01,
    MyFONT_TKEY_hhea = 0x02,
    MyFONT_TKEY_hmtx = 0x03,
    MyFONT_TKEY_maxp = 0x04,
    MyFONT_TKEY_name = 0x05,
    MyFONT_TKEY_OS_2 = 0x06,
    MyFONT_TKEY_post = 0x07,
    MyFONT_TKEY_cvt  = 0x08,
    MyFONT_TKEY_fpgm = 0x09,
    MyFONT_TKEY_glyf = 0x0A,
    MyFONT_TKEY_loca = 0x0B,
    MyFONT_TKEY_prep = 0x0C,
    MyFONT_TKEY_gasp = 0x0D,
    MyFONT_TKEY_CFF  = 0x0E,
    MyFONT_TKEY_VORG = 0x0F,
    MyFONT_TKEY_SVG  = 0x10,
    MyFONT_TKEY_EBDT = 0x11,
    MyFONT_TKEY_EBLC = 0x12,
    MyFONT_TKEY_EBSC = 0x13,
    MyFONT_TKEY_CBDT = 0x14,
    MyFONT_TKEY_CBLC = 0x15,
    MyFONT_TKEY_BASE = 0x16,
    MyFONT_TKEY_GDEF = 0x17,
    MyFONT_TKEY_GPOS = 0x18,
    MyFONT_TKEY_GSUB = 0x19,
    MyFONT_TKEY_JSTF = 0x1A,
    MyFONT_TKEY_MATH = 0x1B,
    MyFONT_TKEY_DSIG = 0x1C,
    MyFONT_TKEY_hdmx = 0x1D,
    MyFONT_TKEY_kern = 0x1E,
    MyFONT_TKEY_LTSH = 0x1F,
    MyFONT_TKEY_PCLT = 0x20,
    MyFONT_TKEY_VDMX = 0x21,
    MyFONT_TKEY_vhea = 0x22,
    MyFONT_TKEY_vmtx = 0x23,
    MyFONT_TKEY_COLR = 0x24,
    MyFONT_TKEY_CPAL = 0x25,
    MyFONT_TKEY_LAST_KEY = 0x26
}
typedef myfont_table_key_t;

/* base struct typedef */
typedef struct myfont_font myfont_font_t;

int8_t myfont_read_8(uint8_t** data);
uint8_t myfont_read_u8(uint8_t** data);

int16_t myfont_read_16(uint8_t** data);
uint16_t myfont_read_u16(uint8_t** data);

int32_t myfont_read_32(uint8_t** data);
uint32_t myfont_read_u32(uint8_t** data);

uint32_t myfont_read_u32_as_net(uint8_t** data);

uint32_t myfont_htonl(uint32_t data);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_BASE_H */


