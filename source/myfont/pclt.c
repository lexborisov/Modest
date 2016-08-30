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

#include "myfont/pclt.h"

void myfont_load_table_pclt(struct myfont_font *mf)
{
    if(mf->cache.tables_offset[MyFONT_TKEY_PCLT])
    {
        myfont_load_table(mf, &mf->table_pclt, sizeof(int32_t) * 2, MyFONT_TKEY_PCLT);
        
        fread(&mf->table_pclt.pitch              , sizeof(uint32_t) , 6, mf->file_h);
        fread(&mf->table_pclt.typeface           , sizeof(char)     , 16, mf->file_h);
        fread(mf->table_pclt.characterComplement , sizeof(char)     , 8, mf->file_h);
        fread(&mf->table_pclt.fileName           , sizeof(char)     , 6, mf->file_h);
        fread(&mf->table_pclt.strokeWeight       , sizeof(char)     , 2, mf->file_h);
        fread(&mf->table_pclt.serifStyle         , sizeof(uint8_t)  , 2, mf->file_h);
    }
    else
    {
        memset(&mf->table_pclt.pitch               , 0, sizeof(uint32_t) * 6);
        memset(&mf->table_pclt.typeface            , 0, sizeof(char)     * 16);
        memset(&mf->table_pclt.characterComplement , 0, sizeof(char)     * 8);
        memset(&mf->table_pclt.fileName            , 0, sizeof(char)     * 6);
        memset(&mf->table_pclt.strokeWeight        , 0, sizeof(char)     * 2);
        memset(&mf->table_pclt.serifStyle          , 0, sizeof(uint32_t) * 2);
    }
}

