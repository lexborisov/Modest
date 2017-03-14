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

#include "myfont/cmap.h"

mystatus_t myfont_table_cmap_format_0(myfont_font_t *mf, myfont_tcmap_entry_t *entry, uint8_t* font_data, size_t data_size, size_t offset)
{
    if(data_size < (offset + 260)) {
        entry->header = NULL;
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    }
    
    myfont_tcmap_format_0_t *f0 = (myfont_tcmap_format_0_t*)myfont_calloc(mf, 1, sizeof(myfont_tcmap_format_0_t));
    
    if(f0 == NULL) {
        entry->header = NULL;
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    uint8_t *data = &font_data[offset];
    
    f0->length = myfont_read_u16(&data);
    f0->language = myfont_read_u16(&data);
    
    memcpy(f0->glyphIdArray, data, 256);
    
    entry->header = (void *)f0;
    
    return MyFONT_STATUS_OK;
}

mystatus_t myfont_table_cmap_format_4(myfont_font_t *mf, myfont_tcmap_entry_t *entry, uint8_t* font_data, size_t data_size, size_t offset)
{
    uint8_t *data = &font_data[offset];
    
    myfont_tcmap_format_4_t *f4 = (myfont_tcmap_format_4_t*)myfont_calloc(mf, 1, sizeof(myfont_tcmap_format_4_t));
    
    if(f4 == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    offset += MyFONT_TCMAP_FORMAT_4_FIRST_LENGTH;
    
    if(data_size < offset) {
        myfont_free(mf, f4);
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    }
    
    f4->length        = myfont_read_u16(&data);
    f4->language      = myfont_read_u16(&data);
    f4->segCountX2    = myfont_read_u16(&data);
    f4->searchRange   = myfont_read_u16(&data);
    f4->entrySelector = myfont_read_u16(&data);
    f4->rangeShift    = myfont_read_u16(&data);
    
    f4->segCount      = f4->segCountX2 / 2;
    f4->numGlyphId    = ((f4->length - (16L + 8L * f4->segCount)) & 0xffff) / 2;
    
    offset += sizeof(uint16_t) * (f4->segCount * 5);
    if(data_size < offset)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* init mem */
    if((f4->endCount = (uint16_t *)myfont_calloc(mf, f4->segCount, sizeof(uint16_t))) == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if((f4->startCount = (uint16_t *)myfont_calloc(mf, f4->segCount, sizeof(uint16_t))) == NULL) {
        myfont_free(mf, f4->endCount); f4->endCount = NULL;
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    if((f4->idDelta = (int16_t *)myfont_calloc(mf, f4->segCount, sizeof(int16_t))) == NULL) {
        myfont_free(mf, f4->endCount); f4->endCount = NULL;
        myfont_free(mf, f4->startCount); f4->startCount = NULL;
        
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    if((f4->idRangeOffset = (uint16_t *)myfont_calloc(mf, f4->segCount, sizeof(uint16_t))) == NULL) {
        myfont_free(mf, f4->endCount); f4->endCount = NULL;
        myfont_free(mf, f4->startCount); f4->startCount = NULL;
        myfont_free(mf, f4->idDelta); f4->idDelta = NULL;
        
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    if((f4->glyphIdArray = (uint16_t *)myfont_calloc(mf, f4->numGlyphId, sizeof(uint16_t))) == NULL) {
        myfont_free(mf, f4->endCount); f4->endCount = NULL;
        myfont_free(mf, f4->startCount); f4->startCount = NULL;
        myfont_free(mf, f4->idDelta); f4->idDelta = NULL;
        myfont_free(mf, f4->idRangeOffset); f4->idRangeOffset = NULL;
        
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    /* read data */
    for(uint16_t i = 0; i < f4->segCount; i++) {
        f4->endCount[i] = myfont_read_u16(&data);
    }
    
    f4->reservedPad = myfont_read_u16(&data);
    
    for(uint16_t i = 0; i < f4->segCount; i++) {
        f4->startCount[i] = myfont_read_u16(&data);
    }
    
    for(uint16_t i = 0; i < f4->segCount; i++) {
        f4->idDelta[i] = myfont_read_16(&data);
    }
    
    for(uint16_t i = 0; i < f4->segCount; i++) {
        f4->idRangeOffset[i] = myfont_read_u16(&data);
    }
    
    for(uint16_t i = 0; i < f4->numGlyphId; i++) {
        f4->glyphIdArray[i] = myfont_read_u16(&data);
    }
    
    entry->header = (void *)f4;
    
    return MyFONT_STATUS_OK;
}

uint16_t myfont_glyph_index_by_code_format_0(myfont_tcmap_format_0_t *f0, unsigned long codepoint, mystatus_t* status)
{
    if(status)
        *status = MyFONT_STATUS_OK;
    
    if(codepoint < 256)
        return (uint16_t)f0->glyphIdArray[codepoint];
    
    if(status)
        *status = MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND;
    
    return 0;
}

uint16_t myfont_glyph_index_by_code_format_4(myfont_tcmap_format_4_t *f4, unsigned long codepoint, mystatus_t* status)
{
    uint16_t i;
    
    if(status)
        *status = MyFONT_STATUS_OK;
    
    for(i = 0; i < f4->segCount; i++)
        if(codepoint <= f4->endCount[i])
            break;
    
    if(i >= f4->segCount || codepoint < f4->startCount[i]) {
        if(status)
            *status = MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND;
        
        return 0;
    }
    
    if(f4->idRangeOffset[i] == 0) {
        return (codepoint + (uint16_t)f4->idDelta[i]) & 0xFFFF;
    }
    else {
        uint16_t index = (f4->idRangeOffset[i] / 2) + (codepoint - f4->startCount[i]) - (f4->segCount - i);
        
        if(index < f4->numGlyphId) {
            if(f4->glyphIdArray[index] != 0)
                return (f4->glyphIdArray[index] + (uint16_t)f4->idDelta[i]) & 0xFFFF;
        }
    }
    
    if(status)
        *status = MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND;
    
    return 0;
}

uint16_t myfont_glyph_index_by_codepoint(myfont_font_t *mf, unsigned long codepoint, mystatus_t* status)
{
    uint16_t i, index = 0, tcout = mf->table_cmap.header.numTables;
    mystatus_t mf_status;
    
    for(i = 0; i < tcout; i++)
    {
        myfont_tcmap_entry_t *entry = &mf->table_cmap.entries[i];
        
        switch (entry->format) {
            case 0:
                index = myfont_glyph_index_by_code_format_0((myfont_tcmap_format_0_t *)(entry->header), codepoint, &mf_status);
                break;
                
            case 4:
                index = myfont_glyph_index_by_code_format_4((myfont_tcmap_format_4_t *)(entry->header), codepoint, &mf_status);
                break;
                
            default:
                mf_status = MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND;
                break;
        };
        
        if(mf_status == MyFONT_STATUS_OK) {
            if(status)
                *status = MyFONT_STATUS_OK;
            
            return index;
        }
    }
    
    if(status)
        *status = MyFONT_STATUS_ERROR_GLYPH_NOT_FOUND;
    
    return 0;
}

mystatus_t myfont_load_table_cmap(myfont_font_t *mf, uint8_t* font_data, size_t data_size)
{
    myfont_table_cmap_t *tcmap = &mf->table_cmap;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_cmap];
    
    if(table_offset == 0)
        return MyFONT_STATUS_OK;
    
    if((table_offset + 4) > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    /* get header */
    tcmap->header.version = myfont_read_u16(&data);
    tcmap->header.numTables = myfont_read_u16(&data);
    
    if(tcmap->header.numTables == 0)
        return MyFONT_STATUS_OK;
    
    size_t size_records = sizeof(myfont_tcmap_record_t) * tcmap->header.numTables;
    size_t size_entries = sizeof(myfont_tcmap_entry_t) * tcmap->header.numTables;
    
    if(data_size < (size_records + size_entries))
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    if((tcmap->records = (myfont_tcmap_record_t *)myfont_malloc(mf, size_records)) == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if((tcmap->entries = (myfont_tcmap_entry_t *)myfont_malloc(mf, size_entries)) == NULL) {
        tcmap->records = NULL;
        myfont_free(mf, tcmap->records);
        
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    for(uint16_t i = 0; i < tcmap->header.numTables; i++) {
        tcmap->records[i].platformID = myfont_read_u16(&data);
        tcmap->records[i].encodingID = myfont_read_u16(&data);
        tcmap->records[i].offset = myfont_read_u32(&data);
    }
    
    for(uint16_t i = 0; i < tcmap->header.numTables; i++)
    {
        uint32_t offset = tcmap->records[i].offset + table_offset;
        
        if(data_size <= offset)
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        
        data = &font_data[offset];
        tcmap->entries[i].format = myfont_read_u16(&data);
        
        switch (tcmap->entries[i].format) {
            case 0:
                myfont_table_cmap_format_0(mf, &tcmap->entries[i], font_data, data_size, (offset + 2));
                break;
                
            case 4:
                myfont_table_cmap_format_4(mf, &tcmap->entries[i], font_data, data_size, (offset + 2));
                break;
                
            default:
                break;
        }
    }
    
    return MyFONT_STATUS_OK;
}



