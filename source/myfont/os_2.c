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

#include "myfont/os_2.h"

void myfont_load_table_os_2(myfont_font_t *mf)
{
    if(mf->cache.tables_offset[MyFONT_TKEY_OS_2])
    {
        myfont_load_table(mf, &mf->table_os_2, sizeof(int16_t) * 16, MyFONT_TKEY_OS_2);
        
        fread(mf->table_os_2.panose           , sizeof(uint8_t) , 10, mf->file_h);
        fread(&mf->table_os_2.ulUnicodeRange1 , sizeof(uint32_t), 4, mf->file_h);
        fread(mf->table_os_2.achVendID        , sizeof(int8_t)  , 4, mf->file_h);
        fread(&mf->table_os_2.fsSelection     , sizeof(int16_t) , 8, mf->file_h);
        
        uint16_t version = myfont_table_version_major(mf->table_os_2.version);
        
        memset(&mf->table_os_2.ulCodePageRange1, 0, sizeof(uint32_t) * 2);
        memset(&mf->table_os_2.sxHeight,         0, sizeof(int16_t)  * 7);
        
        switch (version)
        {
            case 1:
                fread(&mf->table_os_2.ulCodePageRange1, sizeof(uint32_t), 2, mf->file_h);
                break;
            case 2:
                fread(&mf->table_os_2.ulCodePageRange1, sizeof(uint32_t), 2, mf->file_h);
                fread(&mf->table_os_2.sxHeight, sizeof(int16_t), 5, mf->file_h);
                break;
            case 3:
                fread(&mf->table_os_2.ulCodePageRange1, sizeof(uint32_t), 2, mf->file_h);
                fread(&mf->table_os_2.sxHeight, sizeof(int16_t), 5, mf->file_h);
                break;
            case 4:
                fread(&mf->table_os_2.ulCodePageRange1, sizeof(uint32_t), 2, mf->file_h);
                fread(&mf->table_os_2.sxHeight, sizeof(int16_t), 5, mf->file_h);
                break;
            case 5:
                fread(&mf->table_os_2.ulCodePageRange1, sizeof(uint32_t), 2, mf->file_h);
                fread(&mf->table_os_2.sxHeight, sizeof(int16_t), 7, mf->file_h);
                break;
            default:
                break;
        }
    }
    else
    {
        memset(&mf->table_os_2.version         , 0, sizeof(int16_t)  * 16);
        memset(&mf->table_os_2.panose          , 0, sizeof(int8_t)   * 10);
        memset(&mf->table_os_2.ulUnicodeRange1 , 0, sizeof(uint32_t) * 4);
        memset(&mf->table_os_2.achVendID       , 0, sizeof(int8_t)   * 4);
        memset(&mf->table_os_2.achVendID       , 0, sizeof(int16_t)  * 8);
        memset(&mf->table_os_2.ulCodePageRange1, 0, sizeof(uint32_t) * 2);
        memset(&mf->table_os_2.sxHeight        , 0, sizeof(int16_t)  * 7);
    }
}

int8_t myfont_os_2_panose(myfont_font_t *mf, enum myfont_table_os_2_panose id)
{
    return mf->table_os_2.panose[id];
}


