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

#include "myfont/maxp.h"

void myfont_load_table_maxp(myfont_font_t *mf)
{
    uint32_t version;
    
    fseek(mf->file_h, mf->cache.tables_offset[MyFONT_TKEY_maxp], SEEK_SET);
    fread(&version, sizeof(uint32_t), 1, mf->file_h);
    
    if(myfont_table_version_major(version) == 1)
    {
        myfont_load_table(mf, &mf->table_maxp, sizeof(myfont_table_maxp_t), MyFONT_TKEY_maxp);
    }
    else
    {
        fread(&(mf->table_maxp.numGlyphs), sizeof(uint16_t), 1, mf->file_h);
        
        mf->table_maxp.version               = version;
        mf->table_maxp.maxPoints             = 0;
        mf->table_maxp.maxContours           = 0;
        mf->table_maxp.maxCompositePoints    = 0;
        mf->table_maxp.maxCompositeContours  = 0;
        mf->table_maxp.maxZones              = 0;
        mf->table_maxp.maxTwilightPoints     = 0;
        mf->table_maxp.maxStorage            = 0;
        mf->table_maxp.maxFunctionDefs       = 0;
        mf->table_maxp.maxInstructionDefs    = 0;
        mf->table_maxp.maxStackElements      = 0;
        mf->table_maxp.maxSizeOfInstructions = 0;
        mf->table_maxp.maxComponentElements  = 0;
        mf->table_maxp.maxComponentDepth     = 0;
    }
}

