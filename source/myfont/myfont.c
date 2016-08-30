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

#include "myfont/myfont.h"

const char myfont_table_name[][5] = {
    "cmap", "head", "hhea", "hmtx", "maxp", "name",
    "OS/2", "post", "cvt ", "fpgm", "glyf", "loca",
    "prep", "CFF ", "VORG", "EBDT", "EBLC", "EBSC",
    "BASE", "GDEF", "GPOS", "GSUB", "JSTF", "DSIG",
    "gasp", "hdmx", "kern", "LTSH", "PCLT", "VDMX",
    "vhea", "vmtx"
};

myfont_font_t * myfont_create(void)
{
    myfont_font_t *mf = (myfont_font_t *)malloc(sizeof(myfont_font_t));
    
    memset(mf->cache.tables_offset, 0, sizeof(uint32_t) * MyFONT_TKEY_LAST_KEY);
    memset(&mf->header, 0, sizeof(myfont_header_t));
    
    mf->file_path = NULL;
    mf->file_h = NULL;
    
    return mf;
}

void myfont_clean(myfont_font_t *mf)
{
    memset(mf->cache.tables_offset, 0, sizeof(uint32_t) * MyFONT_TKEY_LAST_KEY);
    memset(&mf->header, 0, sizeof(myfont_header_t));
    
    if(mf->file_h)
        fclose(mf->file_h);
    
    mf->file_path = NULL;
    mf->file_h = NULL;
}

myfont_font_t * myfont_destroy(myfont_font_t *mf)
{
    if(mf->file_h)
        fclose(mf->file_h);
    
    if(mf)
        free(mf);
    
    return NULL;
}

void myfont_load(myfont_font_t *mf, const char *filepath)
{
    FILE *fh = fopen(filepath, "rb");
    
    fseek(fh, 0L, SEEK_END);
    long file_size = ftell(fh);
    fseek(fh, 0L, SEEK_SET);
    
    if(file_size > 0)
        mf->file_size = (size_t)file_size;
    
    fread(&mf->header, sizeof(myfont_header_t), 1, fh);
    
    myfont_table_t table = {0};
    uint16_t i;
    
    for(i = 0; i < htons(mf->header.numTables); i++)
    {
        fread(&table, sizeof(myfont_table_t), 1, fh);
        
        switch(table.tag) {
            case MyFONT_TABLE_TYPE_cmap: mf->cache.tables_offset[ MyFONT_TKEY_cmap ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_head: mf->cache.tables_offset[ MyFONT_TKEY_head ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_hhea: mf->cache.tables_offset[ MyFONT_TKEY_hhea ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_hmtx: mf->cache.tables_offset[ MyFONT_TKEY_hmtx ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_maxp: mf->cache.tables_offset[ MyFONT_TKEY_maxp ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_name: mf->cache.tables_offset[ MyFONT_TKEY_name ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_OS_2: mf->cache.tables_offset[ MyFONT_TKEY_OS_2 ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_post: mf->cache.tables_offset[ MyFONT_TKEY_post ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_cvt:  mf->cache.tables_offset[ MyFONT_TKEY_cvt  ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_fpgm: mf->cache.tables_offset[ MyFONT_TKEY_fpgm ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_glyf: mf->cache.tables_offset[ MyFONT_TKEY_glyf ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_loca: mf->cache.tables_offset[ MyFONT_TKEY_loca ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_prep: mf->cache.tables_offset[ MyFONT_TKEY_prep ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_gasp: mf->cache.tables_offset[ MyFONT_TKEY_gasp ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_CFF:  mf->cache.tables_offset[ MyFONT_TKEY_CFF  ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_VORG: mf->cache.tables_offset[ MyFONT_TKEY_VORG ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_SVG:  mf->cache.tables_offset[ MyFONT_TKEY_SVG  ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_EBDT: mf->cache.tables_offset[ MyFONT_TKEY_EBDT ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_EBLC: mf->cache.tables_offset[ MyFONT_TKEY_EBLC ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_EBSC: mf->cache.tables_offset[ MyFONT_TKEY_EBSC ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_CBDT: mf->cache.tables_offset[ MyFONT_TKEY_CBDT ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_CBLC: mf->cache.tables_offset[ MyFONT_TKEY_CBLC ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_BASE: mf->cache.tables_offset[ MyFONT_TKEY_BASE ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_GDEF: mf->cache.tables_offset[ MyFONT_TKEY_GDEF ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_GPOS: mf->cache.tables_offset[ MyFONT_TKEY_GPOS ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_GSUB: mf->cache.tables_offset[ MyFONT_TKEY_GSUB ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_JSTF: mf->cache.tables_offset[ MyFONT_TKEY_JSTF ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_MATH: mf->cache.tables_offset[ MyFONT_TKEY_MATH ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_DSIG: mf->cache.tables_offset[ MyFONT_TKEY_DSIG ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_hdmx: mf->cache.tables_offset[ MyFONT_TKEY_hdmx ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_kern: mf->cache.tables_offset[ MyFONT_TKEY_kern ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_LTSH: mf->cache.tables_offset[ MyFONT_TKEY_LTSH ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_PCLT: mf->cache.tables_offset[ MyFONT_TKEY_PCLT ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_VDMX: mf->cache.tables_offset[ MyFONT_TKEY_VDMX ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_vhea: mf->cache.tables_offset[ MyFONT_TKEY_vhea ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_vmtx: mf->cache.tables_offset[ MyFONT_TKEY_vmtx ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_COLR: mf->cache.tables_offset[ MyFONT_TKEY_COLR ] = ntohl(table.offset); break;
            case MyFONT_TABLE_TYPE_CPAL: mf->cache.tables_offset[ MyFONT_TKEY_CPAL ] = ntohl(table.offset); break;
            default:
                break;
        };
    }
    
    mf->file_h = fh;
    mf->file_path = filepath;
    
    myfont_load_table_cmap(mf);
    myfont_load_table_head(mf);
    myfont_load_table_name(mf);
    myfont_load_table_os_2(mf);
    myfont_load_table_maxp(mf);
    myfont_load_table_hhea(mf);
    myfont_load_table_hmtx(mf);
    myfont_load_table_glyf(mf);
    myfont_load_table_vhea(mf);
    myfont_load_table_vmtx(mf);
    myfont_load_table_pclt(mf);
    myfont_load_table_loca(mf);
}

myfont_status_t myfont_load_table(myfont_font_t *mf, void *table, size_t size, enum myfont_table_key tkey)
{
    if(mf->cache.tables_offset[tkey] == 0)
        return MyFONT_STATUS_NOT_FOUND;
    
    fseek(mf->file_h, mf->cache.tables_offset[tkey], SEEK_SET);
    fread(table, size, 1, mf->file_h);
    
    return MyFONT_STATUS_OK;
}

void myfont_font_print_exists_table(myfont_font_t *mf, FILE *file)
{
    size_t i;
    for(i = 0; i < MyFONT_TKEY_LAST_KEY; i++)
    {
        if(!mf->cache.tables_offset[i])
            continue;
        
        fprintf(file, "%s = %u\n", myfont_table_name[i], mf->cache.tables_offset[i]);
    }
}

// metrics
float myfont_metrics_baseline(myfont_font_t *mf, float font_size)
{
    uint16_t baseline = ntohs(mf->table_os_2.usWinAscent);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)baseline * font_size / ((float)reso);
    
    return fsize;
}

float myfont_metrics_ascent(myfont_font_t *mf, float font_size)
{
    return 0.0f;
}

float myfont_metrics_descent(myfont_font_t *mf, float font_size)
{
    float baseline = myfont_metrics_baseline(mf, font_size);
    uint16_t descent = ntohs(mf->table_os_2.usWinDescent);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)descent * font_size / ((float)reso);
    
    return (baseline + fsize);
}

float myfont_metrics_ascender(myfont_font_t *mf, float font_size)
{
    float baseline = myfont_metrics_baseline(mf, font_size);
    int16_t ascender = ntohs(mf->table_os_2.sTypoAscender);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)ascender * font_size / ((float)reso);
    
    return (baseline - fsize);
}

float myfont_metrics_descender(myfont_font_t *mf, float font_size)
{
    float baseline = myfont_metrics_baseline(mf, font_size);
    int16_t descender = ntohs(mf->table_os_2.sTypoDescender);
    
    if(descender < 0.0f)
        descender = -descender;
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)descender * font_size / ((float)reso);
    
    return (baseline + fsize);
}

float myfont_metrics_x_height(myfont_font_t *mf, float font_size)
{
    float baseline = myfont_metrics_baseline(mf, font_size);
    
    int16_t xheight = 0;
    
    if(myfont_table_version_major(mf->table_os_2.version) > 1)
    {
        if(mf->table_os_2.sxHeight)
            xheight = mf->table_os_2.sxHeight;
    }
    
    if(xheight == 0 && mf->table_pclt.xHeight)
        xheight = (int16_t)mf->table_pclt.xHeight;
    
    if(xheight == 0)
    {
        uint16_t glyph_index = myfont_glyph_index_by_code(mf, (unsigned long)('x'));
        
        if(glyph_index)
        {
            myfont_table_glyph_t glyph;
            myfont_glyf_load(mf, &glyph, glyph_index);
            
            xheight = glyph.head.yMax;
        }
    }
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)(ntohs(xheight)) * font_size / (float)(reso);
    
    return (baseline - fsize);
}

float myfont_metrics_cap_height(myfont_font_t *mf, float font_size)
{
    float baseline = myfont_metrics_baseline(mf, font_size);
    
    int16_t cap_height = 0;
    
    if(myfont_table_version_major(mf->table_os_2.version) > 1)
    {
        if(mf->table_os_2.sCapHeight)
            cap_height = mf->table_os_2.sCapHeight;
    }
    
    if(cap_height == 0 && mf->table_pclt.capHeight)
        cap_height = (int16_t)mf->table_pclt.capHeight;
    
    if(cap_height == 0)
    {
        uint16_t glyph_index = myfont_glyph_index_by_code(mf, (unsigned long)('H'));
        
        if(glyph_index)
        {
            myfont_table_glyph_t glyph;
            myfont_glyf_load(mf, &glyph, glyph_index);
            
            cap_height = glyph.head.yMax;
        }
    }
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)(ntohs(cap_height)) * font_size / (float)(reso);
    
    return (baseline - fsize);
}

// width, height and ...
float myfont_char_width(myfont_font_t *mf, unsigned long char_code, float font_size)
{
    uint16_t glyph_index = myfont_glyph_index_by_code(mf, char_code);
    uint16_t num_metrics = ntohs(mf->table_hhea.numberOfHMetrics);
    
    if(num_metrics == 0)
        return 0.0f;
    
    if(glyph_index > num_metrics)
        glyph_index = num_metrics - 1;
    
    uint16_t width = ntohs(mf->table_hmtx.hMetrics[glyph_index].advanceWidth);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)width * font_size / ((float)reso);
    
    return fsize;
}

float myfont_char_height(myfont_font_t *mf, unsigned long char_code, float font_size)
{
    uint16_t glyph_index = myfont_glyph_index_by_code(mf, char_code);
    uint16_t num_metrics = ntohs(mf->table_vhea.numOfLongVerMetrics);
    
    if(num_metrics == 0)
    {
        return myfont_font_height(mf, font_size);
    }
    
    if(glyph_index > num_metrics)
        glyph_index = num_metrics - 1;
    
    uint16_t height = ntohs(mf->table_vmtx.vMetrics[glyph_index].advanceHeight);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)height * font_size / ((float)reso);
    
    return fsize;
}

float myfont_font_height(myfont_font_t *mf, float font_size)
{
    int16_t height = ntohs(mf->table_os_2.usWinAscent) + ntohs(mf->table_os_2.usWinDescent);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)height * font_size / ((float)reso);
    
    return fsize;
}

float myfont_font_ascent(myfont_font_t *mf, float font_size)
{
    int16_t ascent = ntohs(mf->table_os_2.usWinAscent);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)ascent * font_size / ((float)reso);
    
    return fsize;
}

float myfont_font_descent(myfont_font_t *mf, float font_size)
{
    int16_t descent = ntohs(mf->table_os_2.usWinDescent);
    
    uint16_t reso = ntohs(mf->table_head.unitsPerEm);
    float fsize = (float)descent * font_size / ((float)reso);
    
    return fsize;
}

int16_t myfont_table_version_major(uint32_t version)
{
    version = htonl(version);
    version >>= 16;
    return (int16_t)version;
}

int16_t myfont_table_version_minor(uint32_t version)
{
    version = htonl(version);
    version <<= 16;
    version >>= 16;
    return (int16_t)version;
}

