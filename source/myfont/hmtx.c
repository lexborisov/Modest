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

#include "myfont/hmtx.h"

mystatus_t myfont_load_table_hmtx(myfont_font_t* mf, uint8_t* font_data, size_t data_size)
{
    memset(&mf->table_hmtx, 0, sizeof(myfont_table_hmtx_t));
    
    if(mf->cache.tables_offset[MyFONT_TKEY_hmtx] == 0)
        return MyFONT_STATUS_OK;
    
    myfont_table_hmtx_t *thmtx = &mf->table_hmtx;
    const uint32_t table_offset = mf->cache.tables_offset[MyFONT_TKEY_hmtx];
    
    /* get current data */
    uint8_t *data = &font_data[table_offset];
    uint16_t num_metrics = mf->table_hhea.numberOfHMetrics;
    
    if(num_metrics == 0)
        return MyFONT_STATUS_OK;
    
    if(data_size < (table_offset + (num_metrics * 2)))
        return MyFONT_STATUS_ERROR_TABLE_UNEXPECTED_ENDING;
    
    myfont_long_hor_metric_t *lhor_metric = (myfont_long_hor_metric_t *)myfont_calloc(mf, num_metrics, sizeof(myfont_long_hor_metric_t));
    
    if(lhor_metric == NULL)
        return MyFONT_STATUS_ERROR_MEMORY_ALLOCATION;
    
    for(uint16_t i = 0; i < num_metrics; i++) {
        lhor_metric[i].advanceWidth = myfont_read_u16(&data);
        lhor_metric[i].lsb = myfont_read_16(&data);
    }
    
    thmtx->hMetrics = lhor_metric;
    thmtx->leftSideBearing = NULL;
    
    return MyFONT_STATUS_OK;
}

