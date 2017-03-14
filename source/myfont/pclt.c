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

#include "myfont/pclt.h"

mystatus_t myfont_load_table_pclt(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_pclt, 0, sizeof(myfont_table_pclt_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_PCLT] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_pclt_t *tpclt = &mf->table_pclt;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_PCLT];
    
    uint32_t pos = table_offset + 4 + 16 + 16 + 8 + 6 + 4;
    if(pos > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    tpclt->version = myfont_read_u32_as_net(&data);
    
    tpclt->fontNumber = myfont_read_u32(&data);
    tpclt->pitch = myfont_read_u16(&data);
    tpclt->xHeight = myfont_read_u16(&data);
    tpclt->style = myfont_read_u16(&data);
    tpclt->typeFamily = myfont_read_u16(&data);
    tpclt->capHeight = myfont_read_u16(&data);
    tpclt->symbolSet = myfont_read_u16(&data);
    
    memcpy(tpclt->typeface, data, 16);
    data += 16;
    
    memcpy(tpclt->characterComplement, data, 8);
    data += 8;
    
    memcpy(tpclt->fileName, data, 6);
    data += 6;
    
    tpclt->strokeWeight = (char)myfont_read_u8(&data);
    tpclt->widthType = (char)myfont_read_u8(&data);
    tpclt->serifStyle = myfont_read_u8(&data);
    tpclt->reserved = myfont_read_u8(&data);
    
    return MyFONT_STATUS_OK;
}

