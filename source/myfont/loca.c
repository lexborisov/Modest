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

#include "myfont/loca.h"

void myfont_load_table_loca(struct myfont_font *mf)
{
    if(mf->cache.tables_offset[MyFONT_TKEY_loca])
    {
        uint16_t numGlyph = ntohs(mf->table_maxp.numGlyphs);
        
        if(numGlyph)
        {
            numGlyph++;
            
            if(mf->table_head.indexToLocFormat)
            {
                mf->table_loca.long_offsets = (uint32_t *)malloc(sizeof(uint32_t) * numGlyph);
                
                fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_loca], SEEK_SET);
                fread(mf->table_loca.long_offsets, sizeof(uint32_t), numGlyph, mf->file_h);
                
                mf->table_loca.short_offsets = NULL;
            }
            else
            {
                mf->table_loca.short_offsets = (uint16_t *)malloc(sizeof(uint16_t) * numGlyph);
                
                fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_loca], SEEK_SET);
                fread(mf->table_loca.short_offsets, sizeof(uint16_t) , numGlyph, mf->file_h);
                
                mf->table_loca.long_offsets = NULL;
            }
        }
        else
        {
            mf->table_loca.short_offsets = NULL;
            mf->table_loca.long_offsets = NULL;
            
        }
    }
}

uint32_t myfont_loca_get_offset(struct myfont_font *mf, uint16_t glyph_index)
{
    //uint16_t numGlyph = ntohs(mf->table_maxp.numGlyphs);
    
    if(mf->table_head.indexToLocFormat)
    {
        return ntohl(mf->table_loca.long_offsets[glyph_index]);
    }
    else
    {
        return ntohs(mf->table_loca.short_offsets[glyph_index]);
    }
    
    return 0;
}


