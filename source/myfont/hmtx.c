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

#include "myfont/hmtx.h"

void myfont_load_table_hmtx(struct myfont_font *mf)
{
    uint16_t num_metrics = htons(mf->table_hhea.numberOfHMetrics);
    
    myfont_long_hor_metric_t *lhor_metric = (myfont_long_hor_metric_t *)malloc(sizeof(myfont_long_hor_metric_t) * num_metrics);
    
    fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_hmtx], SEEK_SET);
    fread(lhor_metric, sizeof(myfont_long_hor_metric_t), num_metrics, mf->file_h);
    
    mf->table_hmtx.hMetrics = lhor_metric;
    mf->table_hmtx.leftSideBearing = NULL;
}

