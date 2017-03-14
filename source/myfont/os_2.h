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

#ifndef MyFONT_OS_2_H
#define MyFONT_OS_2_H
#pragma once

#include "myfont/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

enum myfont_table_os_2_panose {
    MyFONT_PANOSE_panose_bFamilyType = 0,
    MyFONT_PANOSE_bSerifStyle        = 1,
    MyFONT_PANOSE_bWeight            = 2,
    MyFONT_PANOSE_bProportion        = 3,
    MyFONT_PANOSE_bContrast          = 4,
    MyFONT_PANOSE_bStrokeVariation   = 5,
    MyFONT_PANOSE_bArmStyle          = 6,
    MyFONT_PANOSE_bLetterform        = 7,
    MyFONT_PANOSE_bMidline           = 8,
    MyFONT_PANOSE_bXHeight           = 9,
    MyFONT_PANOSE_last               = 10
}
typedef myfont_table_os_2_panose_t;

struct myfont_table_os_2 {
    uint16_t version;
    int16_t	 xAvgCharWidth;
    uint16_t usWeightClass;
    uint16_t usWidthClass;
    int16_t  fsType;
    int16_t  ySubscriptXSize;
    int16_t  ySubscriptYSize;
    int16_t  ySubscriptXOffset;
    int16_t  ySubscriptYOffset;
    int16_t  ySuperscriptXSize;
    int16_t  ySuperscriptYSize;
    int16_t  ySuperscriptXOffset;
    int16_t  ySuperscriptYOffset;
    int16_t  yStrikeoutSize;
    int16_t  yStrikeoutPosition;
    int16_t  sFamilyClass;
    uint8_t  panose[10];
    uint32_t ulUnicodeRange1;
    uint32_t ulUnicodeRange2;
    uint32_t ulUnicodeRange3;
    uint32_t ulUnicodeRange4;
    int8_t   achVendID[4];
    uint16_t fsSelection;
    uint16_t usFirstCharIndex;
    uint16_t usLastCharIndex;
    int16_t  sTypoAscender;
    int16_t  sTypoDescender;
    int16_t  sTypoLineGap;
    uint16_t usWinAscent;
    uint16_t usWinDescent;
    uint32_t ulCodePageRange1;
    uint32_t ulCodePageRange2;
    int16_t  sxHeight;
    int16_t  sCapHeight;
    uint16_t usDefaultChar;
    uint16_t usBreakChar;
    uint16_t usMaxContext;
    uint16_t usLowerOpticalPointSize;
    uint16_t usUpperOpticalPointSize;
}
typedef myfont_table_os_2_t;

#include "myfont/myfont.h"

struct myfont_font;

mystatus_t myfont_load_table_os_2(myfont_font_t* mf, uint8_t* data, size_t data_size);

int8_t myfont_os_2_panose(myfont_font_t* mf, myfont_table_os_2_panose_t id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_OS_2_H */
