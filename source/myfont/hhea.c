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

#include "myfont/hhea.h"

mystatus_t myfont_load_table_hhea(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_hhea, 0, sizeof(myfont_table_hhea_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_hhea] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_hhea_t *thhea = &mf->table_hhea;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_hhea];
    
    if(data_size < (table_offset + 8 + 6 + 2 + 22 + 2))
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    thhea->version = myfont_read_u32(&data);
    
    thhea->Ascender = myfont_read_16(&data);
    thhea->Descender = myfont_read_16(&data);
    thhea->LineGap = myfont_read_16(&data);
    
    thhea->advanceWidthMax = myfont_read_u16(&data);
    
    thhea->minLeftSideBearing = myfont_read_16(&data);
    thhea->minRightSideBearing = myfont_read_16(&data);
    thhea->xMaxExtent = myfont_read_16(&data);
    thhea->caretSlopeRise = myfont_read_16(&data);
    thhea->caretSlopeRun = myfont_read_16(&data);
    thhea->caretOffset = myfont_read_16(&data);
    thhea->reserved1 = myfont_read_16(&data);
    thhea->reserved2 = myfont_read_16(&data);
    thhea->reserved3 = myfont_read_16(&data);
    thhea->reserved4 = myfont_read_16(&data);
    thhea->metricDataFormat = myfont_read_16(&data);
    
    thhea->numberOfHMetrics = myfont_read_u16(&data);
    
    return MyFONT_STATUS_OK;
}
