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

#include "myfont/loca.h"

mystatus_t myfont_load_table_loca(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_loca, 0, sizeof(myfont_table_loca_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_loca] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_loca_t *tloca = &mf->table_loca;
    uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_loca];
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    uint16_t numGlyph = mf->table_maxp.numGlyphs;
    
    if(numGlyph == 0)
        return MyFONT_STATUS_ERROR_TABLE_BROKEN;
    
    numGlyph++;
    
    tloca->offsets = (uint32_t *)myfont_calloc(mf, numGlyph, sizeof(uint32_t));
    
    if(tloca->offsets == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if(mf->table_head.indexToLocFormat)
    {
        if(data_size < (table_offset + (numGlyph * 4))) {
            myfont_free(mf, tloca->offsets);
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        }
        
        for(size_t i = 0; i < numGlyph; i++) {
            tloca->offsets[i] = myfont_read_u32(&data);
        }
    }
    else
    {
        if(data_size < (table_offset + (numGlyph * 2))) {
            myfont_free(mf, tloca->offsets);
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        }
        
        for(size_t i = 0; i < numGlyph; i++) {
            tloca->offsets[i] = myfont_read_u16(&data) * 2;
        }
    }
    
    return MyFONT_STATUS_OK;
}

uint32_t myfont_loca_get_offset(struct myfont_font *mf, uint16_t glyph_index)
{
    if(glyph_index >= mf->table_maxp.numGlyphs)
        return mf->table_loca.offsets[0];
    
    return mf->table_loca.offsets[glyph_index];
}


