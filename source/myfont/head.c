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

#include "myfont/head.h"

mystatus_t myfont_load_table_head(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_head, 0, sizeof(myfont_table_head_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_head] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_head_t *thead = &mf->table_head;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_head];
    
    if(data_size < (table_offset + 16 + 4 + 16 + 8 + 4 + 6))
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    /* u32 */
    thead->version = myfont_read_u32(&data);
    thead->fontRevision = myfont_read_u32(&data);
    thead->checkSumAdjustment = myfont_read_u32(&data);
    thead->magicNumber = myfont_read_u32(&data);
    
    /* u16 */
    thead->flags = myfont_read_u16(&data);
    thead->unitsPerEm = myfont_read_u16(&data);
    
    /* u32 */
    thead->created[0] = myfont_read_u32(&data);
    thead->created[1] = myfont_read_u32(&data);
    thead->modified[0] = myfont_read_u32(&data);
    thead->modified[1] = myfont_read_u32(&data);
    
    /* 16 */
    thead->xMin = myfont_read_16(&data);
    thead->yMin = myfont_read_16(&data);
    thead->xMax = myfont_read_16(&data);
    thead->yMax = myfont_read_16(&data);
    
    /* u16 */
    thead->macStyle = myfont_read_u16(&data);
    thead->lowestRecPPEM = myfont_read_u16(&data);
    
    /* 16 */
    thead->fontDirectionHint = myfont_read_16(&data);
    thead->indexToLocFormat = myfont_read_16(&data);
    thead->glyphDataFormat = myfont_read_16(&data);
    
    return MyFONT_STATUS_OK;
}

float myfont_head_yMax_pixel(struct myfont_font *mf, float font_size)
{
    return (float)mf->table_head.yMax * font_size / ((float)mf->table_head.unitsPerEm);
}


