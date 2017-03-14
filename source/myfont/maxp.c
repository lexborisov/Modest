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

#include "myfont/maxp.h"

mystatus_t myfont_load_table_maxp(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_maxp, 0, sizeof(myfont_table_maxp_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_maxp] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_maxp_t *tmaxp = &mf->table_maxp;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_maxp];
    
    if((table_offset + 4) > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    tmaxp->version = myfont_read_u32_as_net(&data);
    
    if(myfont_table_version_major(tmaxp->version) == 1)
    {
        if((table_offset + 4 + 28) > data_size)
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        
        tmaxp->numGlyphs = myfont_read_u16(&data);
        tmaxp->maxPoints = myfont_read_u16(&data);
        tmaxp->maxContours = myfont_read_u16(&data);
        tmaxp->maxCompositePoints = myfont_read_u16(&data);
        tmaxp->maxCompositeContours = myfont_read_u16(&data);
        tmaxp->maxZones = myfont_read_u16(&data);
        tmaxp->maxTwilightPoints = myfont_read_u16(&data);
        tmaxp->maxStorage = myfont_read_u16(&data);
        tmaxp->maxFunctionDefs = myfont_read_u16(&data);
        tmaxp->maxInstructionDefs = myfont_read_u16(&data);
        tmaxp->maxStackElements = myfont_read_u16(&data);
        tmaxp->maxSizeOfInstructions = myfont_read_u16(&data);
        tmaxp->maxComponentElements = myfont_read_u16(&data);
        tmaxp->maxComponentDepth = myfont_read_u16(&data);
    }
    else {
        if((table_offset + 4 + 2) > data_size)
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        
        tmaxp->numGlyphs = myfont_read_u16(&data);
    }
    
    return MyFONT_STATUS_OK;
}


