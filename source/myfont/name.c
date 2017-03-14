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

#include "myfont/name.h"

mystatus_t myfont_load_table_name(myfont_font_t *mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_name, 0, sizeof(myfont_table_name_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_name] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_name_t *tname = &mf->table_name;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_name];
    uint32_t pos = table_offset + 6;
    
    if(pos > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    
    tname->format = myfont_read_u16(&data);
    tname->count = myfont_read_u16(&data);
    tname->stringOffset = myfont_read_u16(&data);
    
    pos = pos + (tname->count * 12);
    if(pos > data_size) {
        tname->count = 0;
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    }
    
    myfont_record_t *record = (myfont_record_t *)myfont_calloc(mf, tname->count, sizeof(myfont_record_t));
    
    if(record == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    for(uint16_t i = 0; i < tname->count; i++) {
        record[i].platformID = myfont_read_u16(&data);
        record[i].encodingID = myfont_read_u16(&data);
        record[i].languageID =myfont_read_u16(&data);
        record[i].nameID = myfont_read_u16(&data);
        record[i].length = myfont_read_u16(&data);
        record[i].offset = myfont_read_u16(&data);
    }
    
    tname->nameRecord = record;
    
    if(tname->format == 1)
    {
        pos += 2;
        if(pos > data_size)
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        
        tname->langTagCount = myfont_read_u16(&data);
        
        pos = pos + (tname->langTagCount * 4);
        if(pos > data_size) {
            tname->langTagCount = 0;
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        }
        
        myfont_ltag_record_t *lang_record = (myfont_ltag_record_t *)myfont_calloc(mf, tname->langTagCount, sizeof(myfont_ltag_record_t));
        
        if(lang_record == NULL)
            return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
        
        for(uint16_t i = 0; i < tname->count; i++) {
            lang_record[i].length = myfont_read_u16(&data);
            lang_record[i].offset = myfont_read_u16(&data);
        }
        
        tname->langTagRecord = lang_record;
    }
    
    return MyFONT_STATUS_OK;
}

