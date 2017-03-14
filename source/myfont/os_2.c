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

#include "myfont/os_2.h"

mystatus_t myfont_load_table_os_2(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_os_2, 0, sizeof(myfont_table_os_2_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_OS_2] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_os_2_t *tos_2 = &mf->table_os_2;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_OS_2];
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    uint32_t pos = table_offset + 32 + 10 + 16 + 4 + 16;
    
    if(pos > data_size)
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    tos_2->version = myfont_read_u16(&data);
    tos_2->xAvgCharWidth = myfont_read_16(&data);
    tos_2->usWeightClass = myfont_read_u16(&data);
    tos_2->usWidthClass = myfont_read_u16(&data);
    tos_2->fsType = myfont_read_16(&data);
    tos_2->ySubscriptXSize = myfont_read_16(&data);
    tos_2->ySubscriptYSize = myfont_read_16(&data);
    tos_2->ySubscriptXOffset = myfont_read_16(&data);
    tos_2->ySubscriptYOffset = myfont_read_16(&data);
    tos_2->ySuperscriptXSize = myfont_read_16(&data);
    tos_2->ySuperscriptYSize = myfont_read_16(&data);
    tos_2->ySuperscriptXOffset = myfont_read_16(&data);
    tos_2->ySuperscriptYOffset = myfont_read_16(&data);
    tos_2->yStrikeoutSize = myfont_read_16(&data);
    tos_2->yStrikeoutPosition = myfont_read_16(&data);
    tos_2->sFamilyClass = myfont_read_16(&data);
    
    memcpy(tos_2->panose, data, 10);
    data += 10;
    
    tos_2->ulUnicodeRange1 = myfont_read_u32(&data);
    tos_2->ulUnicodeRange2 = myfont_read_u32(&data);
    tos_2->ulUnicodeRange3 = myfont_read_u32(&data);
    tos_2->ulUnicodeRange4 = myfont_read_u32(&data);
    
    memcpy(tos_2->achVendID, data, 4);
    data += 4;
    
    tos_2->fsSelection = myfont_read_u16(&data);
    tos_2->usFirstCharIndex = myfont_read_u16(&data);
    tos_2->usLastCharIndex = myfont_read_u16(&data);
    tos_2->sTypoAscender = myfont_read_16(&data);
    tos_2->sTypoDescender = myfont_read_16(&data);
    tos_2->sTypoLineGap = myfont_read_16(&data);
    tos_2->usWinAscent = myfont_read_u16(&data);
    tos_2->usWinDescent = myfont_read_u16(&data);
    
    switch (tos_2->version) {
        case 1:
            pos += 8;
            if(pos > data_size)
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            
            tos_2->ulCodePageRange1 = myfont_read_u32(&data);
            tos_2->ulCodePageRange2 = myfont_read_u32(&data);
            
            break;
        case 2:
        case 3:
        case 4:
            pos += 18;
            if(pos > data_size)
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            
            tos_2->ulCodePageRange1 = myfont_read_u32(&data);
            tos_2->ulCodePageRange2 = myfont_read_u32(&data);
            tos_2->sxHeight = myfont_read_16(&data);
            tos_2->sCapHeight = myfont_read_16(&data);
            tos_2->usDefaultChar = myfont_read_u16(&data);
            tos_2->usBreakChar = myfont_read_u16(&data);
            tos_2->usMaxContext = myfont_read_u16(&data);
            
            break;
        case 5:
            pos += 22;
            if(pos > data_size)
                return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
            
            tos_2->ulCodePageRange1 = myfont_read_u32(&data);
            tos_2->ulCodePageRange2 = myfont_read_u32(&data);
            tos_2->sxHeight = myfont_read_16(&data);
            tos_2->sCapHeight = myfont_read_16(&data);
            tos_2->usDefaultChar = myfont_read_u16(&data);
            tos_2->usBreakChar = myfont_read_u16(&data);
            tos_2->usMaxContext = myfont_read_u16(&data);
            tos_2->usLowerOpticalPointSize = myfont_read_u16(&data);
            tos_2->usUpperOpticalPointSize = myfont_read_u16(&data);
            
            break;
        default:
            break;
    }
    
    return MyFONT_STATUS_OK;
}

int8_t myfont_os_2_panose(myfont_font_t *mf, myfont_table_os_2_panose_t id)
{
    return mf->table_os_2.panose[id];
}


