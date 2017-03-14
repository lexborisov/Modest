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

#include "myfont/glyf.h"

mystatus_t myfont_load_table_glyf(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_glyf, 0, sizeof(myfont_table_glyf_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_glyf] == 0)
        return MyFONT_STATUS_OK;
    
    if(mf->table_maxp.numGlyphs == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_glyph_t *glyphs = (myfont_table_glyph_t*)myfont_calloc(mf, mf->table_maxp.numGlyphs, sizeof(myfont_table_glyph_t));
    
    if(glyphs == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    for(uint16_t i = 0; i < mf->table_maxp.numGlyphs; i++)
    {
        uint32_t offset = mf->cache.tables_offset[MyFONT_TKEY_glyf] + mf->table_loca.offsets[i];
        mystatus_t status = myfont_glyf_load_data(mf, &glyphs[i], font_data, data_size, offset);
        
        if(status)
            return status;
    }
    
    mf->table_glyf.cache = glyphs;
    
    return MyFONT_STATUS_OK;
}

mystatus_t myfont_glyf_load(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t* font_data, size_t data_size, uint16_t glyph_index)
{
    memset(glyph, 0, sizeof(myfont_table_glyph_t));
    
    if(mf->table_maxp.numGlyphs == 0)
        return MyFONT_STATUS_OK;
    
    uint16_t offset = myfont_loca_get_offset(mf, glyph_index);
    offset += mf->cache.tables_offset[MyFONT_TKEY_glyf];
    
    return myfont_glyf_load_data(mf, glyph, font_data, data_size, offset);
}

mystatus_t myfont_glyf_load_data(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t* font_data, size_t data_size, uint32_t offset)
{
    memset(&glyph->head, 0, sizeof(myfont_table_glyf_head_t));
    
    /* get current data */
    uint8_t *data = &font_data[offset];
    
    // load head
    offset += 10;
    if(offset > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    glyph->head.numberOfContours = myfont_read_16(&data);
    glyph->head.xMin = myfont_read_16(&data);
    glyph->head.yMin = myfont_read_16(&data);
    glyph->head.xMax = myfont_read_16(&data);
    glyph->head.yMax = myfont_read_16(&data);
    
    if(glyph->head.numberOfContours > 0)
        return myfont_glyf_load_simple(mf, glyph, data, data_size, offset);
    
    return MyFONT_STATUS_OK;
}

mystatus_t myfont_glyf_load_simple(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset)
{
    uint16_t *endPtsOfContours = (uint16_t *)myfont_calloc(mf, glyph->head.numberOfContours, sizeof(uint16_t));
    
    if(endPtsOfContours == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    offset = offset + (glyph->head.numberOfContours * 2) + 2;
    
    if(offset > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    for(uint16_t i = 0; i < glyph->head.numberOfContours; i++) {
        endPtsOfContours[i] = myfont_read_u16(&data);
    }
    
    glyph->simple.endPtsOfContours = endPtsOfContours;
    glyph->simple.instructionLength = myfont_read_u16(&data);
    glyph->pointCount = endPtsOfContours[(glyph->head.numberOfContours - 1)] + 1;
    
    /* instruction */
    offset += glyph->simple.instructionLength;
    if(offset > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    if(glyph->simple.instructionLength) {
        glyph->simple.instructions = (uint8_t *)myfont_calloc(mf, glyph->simple.instructionLength, sizeof(uint8_t));
        
        if(glyph->simple.instructions == NULL)
            return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
        
        memcpy(glyph->simple.instructions, data, glyph->simple.instructionLength);
        data += glyph->simple.instructionLength;
    }
    
    return myfont_glyf_load_simple_flags(mf, glyph, data, data_size, offset);
}

mystatus_t myfont_glyf_load_simple_flags(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset)
{
    uint8_t *flags = (uint8_t *)myfont_calloc(mf, glyph->pointCount, sizeof(uint8_t));
    
    if(flags == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    uint16_t i = 0;
    while(i < glyph->pointCount)
    {
        if(offset >= data_size) {
            myfont_free(mf, flags);
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        }
        
        flags[i] = myfont_read_u8(&data); offset++;
        
        if(flags[i] & MyFONT_GLYF_SML_FLAGS_repeat)
        {
            if(offset >= data_size) {
                myfont_free(mf, flags);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            uint8_t repeat = myfont_read_u8(&data); offset++;
            uint8_t curr = flags[i];
            
            if(repeat > (glyph->pointCount - i)) {
                myfont_free(mf, flags);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            while(repeat--) {
                i++;
                
                flags[i] = curr;
            }
        }
        
        i++;
    }
    
    glyph->simple.flags = flags;
    
    return myfont_glyf_load_simple_coordinates(mf, glyph, data, data_size, offset);
}

mystatus_t myfont_glyf_load_simple_coordinates(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint8_t *data, size_t data_size, uint32_t offset)
{
    /* alloc resources */
    int16_t *xCoordinates = (int16_t *)myfont_calloc(mf, glyph->pointCount, sizeof(int16_t));
    if(xCoordinates == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    int16_t *yCoordinates = (int16_t *)myfont_calloc(mf, glyph->pointCount, sizeof(int16_t));
    if(yCoordinates == NULL) {
        myfont_free(mf, xCoordinates);
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    uint8_t *flags = glyph->simple.flags;
    
    int32_t in_before = 0;
    
    for(uint16_t i = 0; i < glyph->pointCount; i++)
    {
        if(flags[i] & MyFONT_GLYF_SML_FLAGS_x_ShortVector)
        {
            if(offset >= data_size) {
                myfont_free(mf, xCoordinates);
                myfont_free(mf, yCoordinates);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            if(flags[i] & MyFONT_GLYF_SML_FLAGS_p_x_ShortVector) {
                xCoordinates[i] = in_before + myfont_read_u8(&data); offset++;
            }
            else {
                xCoordinates[i] = in_before - myfont_read_u8(&data); offset++;
            }
        }
        else
        {
            offset++;
            
            if(offset >= data_size) {
                myfont_free(mf, xCoordinates);
                myfont_free(mf, yCoordinates);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            if(flags[i] & MyFONT_GLYF_SML_FLAGS_p_x_ShortVector) {
                xCoordinates[i] = in_before;
            }
            else {
                xCoordinates[i] = in_before + myfont_read_16(&data); offset++;
            }
        }
        
        in_before = xCoordinates[i];
    }
    
    in_before = 0;
    
    for(uint16_t i = 0; i < glyph->pointCount; i++)
    {
        if(flags[i] & MyFONT_GLYF_SML_FLAGS_y_ShortVector)
        {
            if(offset >= data_size) {
                myfont_free(mf, xCoordinates);
                myfont_free(mf, yCoordinates);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            if(flags[i] & MyFONT_GLYF_SML_FLAGS_p_y_ShortVector) {
                yCoordinates[i] = in_before + myfont_read_u8(&data); offset++;
            }
            else {
                yCoordinates[i] = in_before - myfont_read_u8(&data); offset++;
            }
        }
        else {
            offset++;
            
            if(offset >= data_size) {
                myfont_free(mf, xCoordinates);
                myfont_free(mf, yCoordinates);
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            }
            
            if(flags[i] & MyFONT_GLYF_SML_FLAGS_p_y_ShortVector) {
                yCoordinates[i] = in_before;
            }
            else {
                yCoordinates[i] = in_before + myfont_read_16(&data); offset += 2;
            }
        }
        
        in_before = yCoordinates[i];
    }
    
    glyph->simple.xCoordinates = xCoordinates;
    glyph->simple.yCoordinates = yCoordinates;
    
    return MyFONT_STATUS_OK;
}


