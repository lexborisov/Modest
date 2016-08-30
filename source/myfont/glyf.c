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

#include "myfont/glyf.h"

void myfont_load_table_glyf(struct myfont_font *mf)
{
    
}

void myfont_glyf_load(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint16_t glyph_index)
{
    uint16_t offset = myfont_loca_get_offset(mf, glyph_index);
    offset += mf->cache.tables_offset[MyFONT_TKEY_glyf];
    
    myfont_glyf_load_data(mf, glyph, offset);
}

void myfont_glyf_load_data(myfont_font_t *mf, myfont_table_glyph_t *glyph, uint16_t offset)
{
    if(offset > 0)
    {
        // load head
        fseek(mf->file_h, offset, SEEK_SET);
        fread(&glyph->head, sizeof(myfont_table_glyf_head_t), 1, mf->file_h);
        
        uint16_t instructionLength;
        uint16_t numberOfContours  = ntohs(glyph->head.numberOfContours);
        uint16_t *endPtsOfContours = (uint16_t *)malloc(sizeof(uint16_t) * numberOfContours);
        
        fread(endPtsOfContours, sizeof(uint16_t), numberOfContours, mf->file_h);
        fread(&instructionLength, sizeof(uint16_t), 1, mf->file_h);
        
        uint16_t pointCount = ntohs(endPtsOfContours[numberOfContours - 1]) + 1;
        
        uint8_t *instructions = (uint8_t *)malloc(sizeof(uint8_t) * instructionLength);
        fread(instructions, sizeof(uint8_t), instructionLength, mf->file_h);
        
        glyph->simple.endPtsOfContours  = endPtsOfContours;
        glyph->simple.instructionLength = instructionLength;
        glyph->simple.instructions      = instructions;
        
        glyph->pointCount = pointCount;
        
        myfont_glyf_load_flags(mf, glyph);
        myfont_glyf_load_coordinates(mf, glyph);
    }
}

void myfont_glyf_load_flags(myfont_font_t *mf, myfont_table_glyph_t *glyph)
{
    uint8_t *flags = (uint8_t *)malloc(sizeof(uint8_t) * myfont_glyf_pointCount(glyph));
    
    uint16_t i, j; uint8_t repeat;
    for(i = 0; i < myfont_glyf_pointCount(glyph); i++)
    {
        flags[i] = fread(flags, sizeof(uint8_t), 1, mf->file_h);
        
        if(flags[i] & MyFONT_GLYF_SML_FLAGS_repeat)
        {
            repeat = fread(flags, sizeof(uint8_t), 1, mf->file_h);
            
            for(j = 0; j < repeat; j++, i++)
                flags[i+1] = flags[i];
        }
    }
    
    glyph->simple.flags = flags;
}

void myfont_glyf_load_coordinates(myfont_font_t *mf, myfont_table_glyph_t *glyph)
{
    int16_t *xCoordinates = (int16_t *)malloc(sizeof(int16_t) * myfont_glyf_pointCount(glyph));
    int16_t *yCoordinates = (int16_t *)malloc(sizeof(int16_t) * myfont_glyf_pointCount(glyph));
    
    uint16_t i;
    int16_t in_before = 0, in_now;
    
    for(i = 0; i < myfont_glyf_pointCount(glyph); i++)
    {
        in_now = 0;
        
        if( myfont_glyf_flags(glyph, i) & 0x02 && myfont_glyf_flags(glyph, i) & 0x10 )
        {
            fread(&in_now, sizeof(uint8_t), 1, mf->file_h);
            xCoordinates[i] = in_before + in_now;
        }
        else if (myfont_glyf_flags(glyph, i) & 0x02 && !(myfont_glyf_flags(glyph, i) & 0x10) )
        {
            fread(&in_now, sizeof(uint8_t), 1, mf->file_h);
            xCoordinates[i] = in_before - in_now;
        }
        else if (!(myfont_glyf_flags(glyph, i) & 0x02) && myfont_glyf_flags(glyph, i) & 0x10 )
        {
            xCoordinates[i] = in_before;
        }
        else
        {
            fread(&in_now, sizeof(int16_t), 1, mf->file_h);
            xCoordinates[i] = in_before + in_now;
        }
        
        in_before = xCoordinates[i];
    }
    
    in_before = 0;
    for(i = 0; i < myfont_glyf_pointCount(glyph); i++)
    {
        in_now = 0;
        
        if(myfont_glyf_flags(glyph, i) & 0x04 && myfont_glyf_flags(glyph, i) & 0x20)
        {
            fread(&in_now, sizeof(uint8_t), 1, mf->file_h);
            yCoordinates[i] = in_before+in_now;
        }
        else if (myfont_glyf_flags(glyph, i) & 0x04 && !(myfont_glyf_flags(glyph, i) & 0x20))
        {
            fread(&in_now, sizeof(uint8_t), 1, mf->file_h);
            yCoordinates[i] = in_before-in_now;
        }
        else if (!(myfont_glyf_flags(glyph, i) & 0x04) && myfont_glyf_flags(glyph, i) & 0x20)
        {
            yCoordinates[i] = in_before;
        }
        else
        {
            fread(&in_now, sizeof(int16_t), 1, mf->file_h);
            yCoordinates[i] = in_before+in_now;
        }
        
        in_before = yCoordinates[i];
    }
    
    glyph->simple.xCoordinates = xCoordinates;
    glyph->simple.yCoordinates = yCoordinates;
}

