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

#include "myfont/head.h"

void myfont_load_table_head(struct myfont_font *mf)
{
    fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_head], SEEK_SET);
    
    fread(&mf->table_head        , sizeof(uint32_t), 4, mf->file_h);
    fread(&mf->table_head.flags  , sizeof(uint16_t), 2, mf->file_h);
    fread(mf->table_head.created , sizeof(uint32_t), 2, mf->file_h);
    fread(mf->table_head.modified, sizeof(uint32_t), 2, mf->file_h);
    fread(&mf->table_head.xMin   , sizeof(int16_t) , 9, mf->file_h);
}

float myfont_head_yMax_pixel(struct myfont_font *mf, float font_size)
{
    int16_t yMax = ntohs(mf->table_head.yMax);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)yMax * font_size / ((float)reso);
    
    return fsize;
}