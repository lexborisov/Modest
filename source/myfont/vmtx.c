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

#include "myfont/vmtx.h"

void myfont_load_table_vmtx(myfont_font_t *mf)
{
    uint16_t num_metrics = htons(mf->table_vhea.numOfLongVerMetrics);
    
    if(num_metrics)
    {
        myfont_long_ver_metric_t *lver_metric = (myfont_long_ver_metric_t *)malloc(sizeof(myfont_long_ver_metric_t) * num_metrics);
        
        fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_vmtx], SEEK_SET);
        fread(lver_metric, sizeof(myfont_long_ver_metric_t), num_metrics, mf->file_h);
        
        mf->table_vmtx.vMetrics = lver_metric;
        
        uint16_t numOfTSB = htons(mf->table_maxp.numGlyphs - mf->table_vhea.numOfLongVerMetrics);
        
        if(numOfTSB)
        {
            int16_t *topSideBearing = (int16_t *)malloc(sizeof(int16_t) * numOfTSB);
            fread(topSideBearing, sizeof(int16_t), numOfTSB, mf->file_h);
            
            mf->table_vmtx.topSideBearing = topSideBearing;
        }
        else {
            mf->table_vmtx.topSideBearing = NULL;
        }
    }
    else
    {
        mf->table_vmtx.vMetrics       = NULL;
        mf->table_vmtx.topSideBearing = NULL;
    }
}


