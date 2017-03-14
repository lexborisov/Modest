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

#ifndef MyFONT_GLYF_H
#define MyFONT_GLYF_H
#pragma once

#include <myfont/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

enum myfont_table_glyf_composite_flags {
    MyFONT_GLYF_ARG_1_AND_2_ARE_WORDS      = 0x0001,
    MyFONT_GLYF_ARGS_ARE_XY_VALUES         = 0x0002,
    MyFONT_GLYF_ROUND_XY_TO_GRID           = 0x0004,
    MyFONT_GLYF_WE_HAVE_A_SCALE            = 0x0008,
    MyFONT_GLYF_RESERVED                   = 0x0010,
    MyFONT_GLYF_MORE_COMPONENTS            = 0x0020,
    MyFONT_GLYF_WE_HAVE_AN_X_AND_Y_SCALE   = 0x0040,
    MyFONT_GLYF_WE_HAVE_A_TWO_BY_TWO       = 0x0080,
    MyFONT_GLYF_WE_HAVE_INSTRUCTIONS       = 0x0100,
    MyFONT_GLYF_USE_MY_METRICS             = 0x0200,
    MyFONT_GLYF_OVERLAP_COMPOUND           = 0x0400,
    MyFONT_GLYF_SCALED_COMPONENT_OFFSET    = 0x0800,
    MyFONT_GLYF_UNSCALED_COMPONENT_OFFSET  = 0x1000
};

struct myfont_table_composite_glyph {
    uint16_t flags;
    uint16_t glyphIndex;
    int16_t  argument1;
    int16_t  argument2;
}
typedef myfont_table_composite_glyph_t;

enum myfont_table_glyf_simple_flags {
    MyFONT_GLYF_SML_FLAGS_onCurve         = 0x001,
    MyFONT_GLYF_SML_FLAGS_x_ShortVector   = 0x002,
    MyFONT_GLYF_SML_FLAGS_y_ShortVector   = 0x004,
    MyFONT_GLYF_SML_FLAGS_repeat          = 0x008,
    MyFONT_GLYF_SML_FLAGS_p_x_ShortVector = 0x010,
    MyFONT_GLYF_SML_FLAGS_p_y_ShortVector = 0x020,
    MyFONT_GLYF_SML_FLAGS_reserved_1      = 0x040,
    MyFONT_GLYF_SML_FLAGS_reserved_2      = 0x080,
    MyFONT_GLYF_SML_FLAGS_last            = 0x100
};

struct myfont_table_simple_glyph {
    uint16_t *endPtsOfContours;
    uint16_t instructionLength;
    uint8_t  *instructions;
    uint8_t  *flags;
    int16_t  *xCoordinates;
    int16_t  *yCoordinates;
}
typedef myfont_table_simple_glyph_t;

struct myfont_table_glyf_head {
    int16_t numberOfContours;
    int16_t xMin;
    int16_t yMin;
    int16_t xMax;
    int16_t yMax;
}
typedef myfont_table_glyf_head_t;

struct myfont_table_glyph {
    myfont_table_glyf_head_t head;
    myfont_table_simple_glyph_t simple;
    uint16_t pointCount;
}
typedef myfont_table_glyph_t;

struct myfont_table_glyf {
    myfont_table_glyph_t *cache;
}
typedef myfont_table_glyf_t;

#include <myfont/myfont.h>

struct myfont_font;

mystatus_t myfont_load_table_glyf(myfont_font_t *mf, uint8_t* data, size_t data_size);

mystatus_t myfont_glyf_load(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t* data, size_t data_size, uint16_t glyph_index);
mystatus_t myfont_glyf_load_data(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t* data, size_t data_size, uint32_t offset);
mystatus_t myfont_glyf_load_simple(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset);
mystatus_t myfont_glyf_load_simple_flags(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset);
mystatus_t myfont_glyf_load_simple_coordinates(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_GLYF_H */
