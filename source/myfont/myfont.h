/*
 Copyright (C) 2016 Alexander Borisov
 
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

#ifndef MyFONT_MyFONT_H
#define MyFONT_MyFONT_H
#pragma once

#include "myfont/myosi.h"
#include "myfont/cmap.h"
#include "myfont/head.h"
#include "myfont/name.h"
#include "myfont/os_2.h"
#include "myfont/maxp.h"
#include "myfont/hhea.h"
#include "myfont/hmtx.h"
#include "myfont/glyf.h"
#include "myfont/vhea.h"
#include "myfont/vmtx.h"
#include "myfont/pclt.h"
#include "myfont/loca.h"

// base
#pragma pack(push, 1)
struct myfont_header {
    int32_t  version;
    uint16_t numTables;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
}
typedef myfont_header_t;

struct myfont_table {
    uint32_t tag;
    uint32_t checkSum;
    uint32_t offset;
    uint32_t length;
}
typedef myfont_table_t;
#pragma pack(pop)

struct myfont_cache {
    uint32_t tables_offset[MyFONT_TKEY_LAST_KEY];
}
typedef myfont_cache_t;

struct myfont_font {
    myfont_header_t     header;
    myfont_cache_t      cache;
    
    myfont_table_cmap_t table_cmap;
    myfont_table_head_t table_head;
    myfont_table_name_t table_name;
    myfont_table_os_2_t table_os_2;
    myfont_table_maxp_t table_maxp;
    myfont_table_hhea_t table_hhea;
    myfont_table_hmtx_t table_hmtx;
    myfont_table_glyf_t table_glyf;
    myfont_table_vmtx_t table_vmtx;
    myfont_table_vhea_t table_vhea;
    myfont_table_pclt_t table_pclt;
    myfont_table_loca_t table_loca;
    
    const char *file_path;
    FILE       *file_h;
    size_t      file_size;
};

myfont_font_t * myfont_create(void);
void myfont_clean(myfont_font_t *mf);
myfont_font_t * myfont_destroy(myfont_font_t *mf);

void myfont_load(myfont_font_t *mf, const char *filepath);

void myfont_font_print_exists_table(myfont_font_t *mf, FILE *file);

float myfont_metrics_baseline(myfont_font_t *mf, float font_size);
float myfont_metrics_ascent(myfont_font_t *mf, float font_size);
float myfont_metrics_descent(myfont_font_t *mf, float font_size);
float myfont_metrics_ascender(myfont_font_t *mf, float font_size);
float myfont_metrics_descender(myfont_font_t *mf, float font_size);
float myfont_metrics_x_height(myfont_font_t *mf, float font_size);
float myfont_metrics_cap_height(myfont_font_t *mf, float font_size);

float myfont_char_width(myfont_font_t *mf, unsigned long char_code, float font_size);
float myfont_char_height(myfont_font_t *mf, unsigned long char_code, float font_size);
float myfont_font_height(myfont_font_t *mf, float font_size);
float myfont_font_ascent(myfont_font_t *mf, float font_size);
float myfont_font_descent(myfont_font_t *mf, float font_size);

myfont_status_t myfont_load_table(myfont_font_t *mf, void *table, size_t size, enum myfont_table_key tkey);

int16_t myfont_table_version_major(uint32_t version);
int16_t myfont_table_version_minor(uint32_t version);

#endif /* MyFONT_MyFONT_H */
