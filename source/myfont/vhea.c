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

#include "myfont/vhea.h"

mystatus_t myfont_load_table_vhea(myfont_font_t *mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_vhea, 0, sizeof(myfont_table_vhea_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_vhea] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_vhea_t *tvhea = &mf->table_vhea;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_vhea];
    
    if((table_offset + 4 + 32) > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    tvhea->version = myfont_read_u32_as_net(&data);
    tvhea->Ascender = myfont_read_16(&data);
    tvhea->Descender = myfont_read_16(&data);
    tvhea->LineGap = myfont_read_16(&data);
    tvhea->advanceHeightMax = myfont_read_16(&data);
    tvhea->minTopSideBearing = myfont_read_16(&data);
    tvhea->minBottomSideBearing = myfont_read_16(&data);
    tvhea->yMaxExtent = myfont_read_16(&data);
    tvhea->caretSlopeRise = myfont_read_16(&data);
    tvhea->caretSlopeRun = myfont_read_16(&data);
    tvhea->caretOffset = myfont_read_16(&data);
    tvhea->reserved1 = myfont_read_16(&data);
    tvhea->reserved2 = myfont_read_16(&data);
    tvhea->reserved3 = myfont_read_16(&data);
    tvhea->reserved4 = myfont_read_16(&data);
    tvhea->metricDataFormat = myfont_read_16(&data);
    tvhea->numOfLongVerMetrics = myfont_read_u16(&data);
    
    return MyFONT_STATUS_OK;
}


