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

#include "myfont/cmap.h"

void myfont_table_cmap_format_0(myfont_font_t *mf, myfont_tcmap_entry_t  *entry)
{
    myfont_tcmap_format_0_t *f0 = (myfont_tcmap_format_0_t *)malloc(sizeof(myfont_tcmap_format_0_t));
    
    uint16_t glyphCount = 256;
    
    fread(f0, (sizeof(uint16_t) * 2), 1, mf->file_h);
    fread(f0->glyphIdArray, sizeof(uint8_t), glyphCount, mf->file_h);
    
    entry->header = (void *)f0;
}

void myfont_table_cmap_format_4(myfont_font_t *mf, myfont_tcmap_entry_t *entry)
{
    myfont_tcmap_format_4_t *f4 = (myfont_tcmap_format_4_t *)malloc(sizeof(myfont_tcmap_format_4_t));
    
    fread(f4, MyFONT_TCMAP_FORMAT_4_FIRST_LENGTH, 1, mf->file_h);
    
    uint16_t segCount    = ntohs(f4->segCountX2) / 2;
    uint16_t glyphCount  = ((ntohs(f4->length) - (16L + 8L * segCount )) & 0xffff) / 2;
    
    f4->numGlyphId    = glyphCount;
    f4->endCount      = (uint16_t *)malloc(sizeof(uint16_t) * segCount);
    f4->startCount    = (uint16_t *)malloc(sizeof(uint16_t) * segCount);
    f4->idDelta       = (int16_t  *)malloc(sizeof(int16_t)  * segCount);
    f4->idRangeOffset = (uint16_t *)malloc(sizeof(uint16_t) * segCount);
    f4->glyphIdArray  = (uint16_t *)malloc(sizeof(uint16_t) * glyphCount);
    
    fread(f4->endCount     , sizeof(uint16_t)             , segCount, mf->file_h);
    fread(&f4->reservedPad , sizeof(uint16_t)             , 1, mf->file_h);
    fread(f4->startCount   , sizeof(uint16_t)             , segCount, mf->file_h);
    fread(f4->idDelta      , sizeof(int16_t)              , segCount, mf->file_h);
    fread(f4->idRangeOffset, sizeof(int16_t)              , segCount, mf->file_h);
    fread(f4->glyphIdArray , sizeof(uint16_t)             , glyphCount, mf->file_h);
    
    entry->header = (void *)f4;
}

uint16_t myfont_glyph_index_by_code_format_0(myfont_tcmap_format_0_t *f0, unsigned long char_code)
{
    if(char_code < 256)
        return (uint16_t)f0->glyphIdArray[char_code];
    
    return 0;
}

uint16_t myfont_glyph_index_by_code_format_4(myfont_tcmap_format_4_t *f4, unsigned long char_code)
{
    uint16_t segCount = ntohs(f4->segCountX2) / 2;
    
    uint16_t i;
    
    for(i = 0; i < segCount; i++)
        if(char_code <= ntohs(f4->endCount[i]))
            break;
    
    if(i >= segCount || char_code < ntohs(f4->startCount[i]))
        return 0;
    
    if(f4->idRangeOffset[i] == 0)
    {
        return (char_code + ntohs((uint16_t)f4->idDelta[i])) & 0xFFFF;
    }
    else
    {
        uint16_t index = ntohs(f4->idRangeOffset[i]) / 2 + (char_code - ntohs(f4->startCount[i])) - (segCount - i);
        
        if(index < f4->numGlyphId)
        {
            if(f4->glyphIdArray[index] != 0)
                return (ntohs(f4->glyphIdArray[index]) + ntohs((uint16_t)f4->idDelta[i])) & 0xFFFF;
        }
    }
    
    return 0;
}

uint16_t myfont_glyph_index_by_code(myfont_font_t *mf, unsigned long char_code)
{
    uint16_t i, index = 0, tcout = ntohs(mf->table_cmap.header.numTables);
    
    for(i = 0; i < tcout; i++)
    {
        myfont_tcmap_entry_t *entry = &mf->table_cmap.entries[i];
        
        switch (ntohs(entry->format)) {
            case 0:
                index = myfont_glyph_index_by_code_format_0((myfont_tcmap_format_0_t *)(entry->header), char_code);
                break;
                
            case 4:
                index = myfont_glyph_index_by_code_format_4((myfont_tcmap_format_4_t *)(entry->header), char_code);
                break;
                
            default:
                break;
        };
        
        if(index)
            break;
    }
    
    return index;
}

uint16_t myfont_glyph_index_by_code_on_entry(myfont_tcmap_entry_t *entry, unsigned long char_code)
{
    switch (ntohs(entry->format)) {
        case 0:
            return myfont_glyph_index_by_code_format_0((myfont_tcmap_format_0_t *)(entry->header), char_code);
            
        case 4:
            return myfont_glyph_index_by_code_format_4((myfont_tcmap_format_4_t *)(entry->header), char_code);
            
        default:
            break;
    };
    
    return 0;
}

void myfont_load_table_cmap(myfont_font_t *mf)
{
    myfont_table_cmap_t *tcmap = &mf->table_cmap;
    myfont_load_table(mf, &tcmap->header, sizeof(myfont_tcmap_header_t), MyFONT_TKEY_cmap);
    
    uint16_t tcout = ntohs(tcmap->header.numTables);
    
    if(tcout == 0)
        return;
    
    tcmap->records = (myfont_tcmap_record_t *)malloc(sizeof(myfont_tcmap_record_t) * tcout);
    tcmap->entries = (myfont_tcmap_entry_t *)malloc(sizeof(myfont_tcmap_entry_t) * tcout);
    
    fread(tcmap->records, sizeof(myfont_tcmap_record_t), tcout, mf->file_h);
    
    uint16_t i;
    for(i = 0; i < tcout; i++)
    {
        uint32_t offset = ntohl(tcmap->records[i].offset) + mf->cache.tables_offset[MyFONT_TKEY_cmap];
        fseek(mf->file_h, offset, SEEK_SET);
        
        fread(&tcmap->entries[i].format, sizeof(uint16_t), 1, mf->file_h);
        
        uint16_t hformat = ntohs(tcmap->entries[i].format);
        
        switch (hformat) {
            case 0:
                myfont_table_cmap_format_0(mf, &tcmap->entries[i]);
                break;
                
            case 4:
                myfont_table_cmap_format_4(mf, &tcmap->entries[i]);
                break;
                
            default:
                break;
        }
    }
}


