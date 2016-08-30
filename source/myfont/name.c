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

#include "myfont/name.h"

void myfont_load_table_name(myfont_font_t *mf)
{
    myfont_table_name_t *table_name = &mf->table_name;
    
    fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_name], SEEK_SET);
    fread(table_name, sizeof(uint16_t) * 3, 1, mf->file_h);
    
    size_t record_size = sizeof(myfont_record_t) * ntohs(table_name->count);
    myfont_record_t *record = (myfont_record_t *)malloc(record_size);
    
    fread(record, record_size, 1, mf->file_h);
    
    table_name->nameRecord = record;
    
    if(ntohs(table_name->format) == 1)
    {
        fread(&table_name->langTagCount, sizeof(uint16_t), 1, mf->file_h);
        
        size_t lang_record_size = sizeof(myfont_ltag_record_t) * ntohs(table_name->langTagCount);
        myfont_ltag_record_t *lang_record = (myfont_ltag_record_t *)malloc(lang_record_size);
        
        fread(lang_record, lang_record_size, 1, mf->file_h);
        
        table_name->langTagRecord = lang_record;
    }
    
    myfont_load_table(mf, table_name, sizeof(myfont_table_hhea_t), MyFONT_TKEY_hhea);
}

