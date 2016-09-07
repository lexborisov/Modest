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
    return (myfont_font_t *)myhtml_calloc(1, sizeof(myfont_font_t));
}

myfont_status_t myfont_init(myfont_font_t *mf)
{
    mf->mchar = mchar_async_create(64, (4096 * 2));
    mf->mchar_node_id = mchar_async_node_add(mf->mchar);
    
    memset(mf->cache.tables_offset, 0, sizeof(uint32_t) * MyFONT_TKEY_LAST_KEY);
    memset(&mf->header, 0, sizeof(myfont_header_t));
    
    mf->file_path = NULL;
    
    return MyFONT_STATUS_OK;
}

void myfont_clean(myfont_font_t *mf)
{
    mchar_async_node_clean(mf->mchar, mf->mchar_node_id);
    
    memset(mf->cache.tables_offset, 0, sizeof(uint32_t) * MyFONT_TKEY_LAST_KEY);
    memset(&mf->header, 0, sizeof(myfont_header_t));
    
    if(mf->file_data) {
        myhtml_free(mf->file_data);
        mf->file_data = NULL;
    }
    
    if(mf->file_path) {
        myhtml_free(mf->file_path);
        mf->file_path = NULL;
    }
    
    memset(mf, 0, sizeof(myfont_font_t));
}

myfont_font_t * myfont_destroy(myfont_font_t *mf, bool self_destroy)
{
    if(mf == NULL)
        return NULL;
    
    mf->mchar = mchar_async_destroy(mf->mchar, 1);
    
    if(mf->file_data) {
        myhtml_free(mf->file_data);
        mf->file_data = NULL;
    }
    
    if(mf->file_path) {
        myhtml_free(mf->file_path);
        mf->file_path = NULL;
    }
    
    if(self_destroy) {
        myhtml_free(mf);
        return NULL;
    }
    
    return mf;
}

void * myfont_malloc(myfont_font_t* mf, size_t size)
{
    return (void*)mchar_async_malloc(mf->mchar, mf->mchar_node_id, size);
}

void * myfont_calloc(myfont_font_t* mf, size_t count, size_t size)
{
    void *data = (void*)mchar_async_malloc(mf->mchar, mf->mchar_node_id, (size * count));
    memset(data, 0, (size * count));
    
    return data;
}

void myfont_free(myfont_font_t *mf, void* data)
{
    mchar_async_free(mf->mchar, mf->mchar_node_id, data);
}

void myfont_load(myfont_font_t *mf, const char *filepath)
{
    FILE *fh = fopen(filepath, "rb");
    if(fh == NULL)
        return;
    
    if(fseek(fh, 0L, SEEK_END)) {
        fclose(fh);
        return;
    }
    
    long file_size = ftell(fh);
    if(file_size == -1) {
        fclose(fh);
        return;
    }
    
    if(fseek(fh, 0L, SEEK_SET)) {
        fclose(fh);
        return;
    }
    
    if(file_size > 0)
        mf->file_size = (size_t)file_size;
    else
        return;
    
    mf->file_data = (uint8_t*)myhtml_malloc(file_size);
    
    if(mf->file_data == NULL)
        return;
    
    if(fread(mf->file_data, 1, file_size, fh) != file_size) {
        fclose(fh);
        return;
    }
    
    fclose(fh);
    
    if(mf->file_size < 12)
        return;
    
    uint8_t *data = (uint8_t*)mf->file_data;
    
    mf->header.version_major = myfont_read_u16(&data);
    mf->header.version_minor = myfont_read_u16(&data);
    mf->header.numTables     = myfont_read_u16(&data);
    mf->header.searchRange   = myfont_read_u16(&data);
    mf->header.entrySelector = myfont_read_u16(&data);
    mf->header.rangeShift    = myfont_read_u16(&data);
    
    if(mf->file_size < (12 + (mf->header.numTables * 16)))
        return;
    
    for(uint16_t i = 0; i < mf->header.numTables; i++)
    {
        myfont_table_t table;
        table.tag      = myfont_read_u32_as_net(&data);
        table.checkSum = myfont_read_u32(&data);
        table.offset   = myfont_read_u32(&data);
        table.length   = myfont_read_u32(&data);
        
        switch(table.tag) {
            case MyFONT_TABLE_TYPE_cmap: mf->cache.tables_offset[ MyFONT_TKEY_cmap ] = table.offset; break;
            case MyFONT_TABLE_TYPE_head: mf->cache.tables_offset[ MyFONT_TKEY_head ] = table.offset; break;
            case MyFONT_TABLE_TYPE_hhea: mf->cache.tables_offset[ MyFONT_TKEY_hhea ] = table.offset; break;
            case MyFONT_TABLE_TYPE_hmtx: mf->cache.tables_offset[ MyFONT_TKEY_hmtx ] = table.offset; break;
            case MyFONT_TABLE_TYPE_maxp: mf->cache.tables_offset[ MyFONT_TKEY_maxp ] = table.offset; break;
            case MyFONT_TABLE_TYPE_name: mf->cache.tables_offset[ MyFONT_TKEY_name ] = table.offset; break;
            case MyFONT_TABLE_TYPE_OS_2: mf->cache.tables_offset[ MyFONT_TKEY_OS_2 ] = table.offset; break;
            case MyFONT_TABLE_TYPE_post: mf->cache.tables_offset[ MyFONT_TKEY_post ] = table.offset; break;
            case MyFONT_TABLE_TYPE_cvt:  mf->cache.tables_offset[ MyFONT_TKEY_cvt  ] = table.offset; break;
            case MyFONT_TABLE_TYPE_fpgm: mf->cache.tables_offset[ MyFONT_TKEY_fpgm ] = table.offset; break;
            case MyFONT_TABLE_TYPE_glyf: mf->cache.tables_offset[ MyFONT_TKEY_glyf ] = table.offset; break;
            case MyFONT_TABLE_TYPE_loca: mf->cache.tables_offset[ MyFONT_TKEY_loca ] = table.offset; break;
            case MyFONT_TABLE_TYPE_prep: mf->cache.tables_offset[ MyFONT_TKEY_prep ] = table.offset; break;
            case MyFONT_TABLE_TYPE_gasp: mf->cache.tables_offset[ MyFONT_TKEY_gasp ] = table.offset; break;
            case MyFONT_TABLE_TYPE_CFF:  mf->cache.tables_offset[ MyFONT_TKEY_CFF  ] = table.offset; break;
            case MyFONT_TABLE_TYPE_VORG: mf->cache.tables_offset[ MyFONT_TKEY_VORG ] = table.offset; break;
            case MyFONT_TABLE_TYPE_SVG:  mf->cache.tables_offset[ MyFONT_TKEY_SVG  ] = table.offset; break;
            case MyFONT_TABLE_TYPE_EBDT: mf->cache.tables_offset[ MyFONT_TKEY_EBDT ] = table.offset; break;
            case MyFONT_TABLE_TYPE_EBLC: mf->cache.tables_offset[ MyFONT_TKEY_EBLC ] = table.offset; break;
            case MyFONT_TABLE_TYPE_EBSC: mf->cache.tables_offset[ MyFONT_TKEY_EBSC ] = table.offset; break;
            case MyFONT_TABLE_TYPE_CBDT: mf->cache.tables_offset[ MyFONT_TKEY_CBDT ] = table.offset; break;
            case MyFONT_TABLE_TYPE_CBLC: mf->cache.tables_offset[ MyFONT_TKEY_CBLC ] = table.offset; break;
            case MyFONT_TABLE_TYPE_BASE: mf->cache.tables_offset[ MyFONT_TKEY_BASE ] = table.offset; break;
            case MyFONT_TABLE_TYPE_GDEF: mf->cache.tables_offset[ MyFONT_TKEY_GDEF ] = table.offset; break;
            case MyFONT_TABLE_TYPE_GPOS: mf->cache.tables_offset[ MyFONT_TKEY_GPOS ] = table.offset; break;
            case MyFONT_TABLE_TYPE_GSUB: mf->cache.tables_offset[ MyFONT_TKEY_GSUB ] = table.offset; break;
            case MyFONT_TABLE_TYPE_JSTF: mf->cache.tables_offset[ MyFONT_TKEY_JSTF ] = table.offset; break;
            case MyFONT_TABLE_TYPE_MATH: mf->cache.tables_offset[ MyFONT_TKEY_MATH ] = table.offset; break;
            case MyFONT_TABLE_TYPE_DSIG: mf->cache.tables_offset[ MyFONT_TKEY_DSIG ] = table.offset; break;
            case MyFONT_TABLE_TYPE_hdmx: mf->cache.tables_offset[ MyFONT_TKEY_hdmx ] = table.offset; break;
            case MyFONT_TABLE_TYPE_kern: mf->cache.tables_offset[ MyFONT_TKEY_kern ] = table.offset; break;
            case MyFONT_TABLE_TYPE_LTSH: mf->cache.tables_offset[ MyFONT_TKEY_LTSH ] = table.offset; break;
            case MyFONT_TABLE_TYPE_PCLT: mf->cache.tables_offset[ MyFONT_TKEY_PCLT ] = table.offset; break;
            case MyFONT_TABLE_TYPE_VDMX: mf->cache.tables_offset[ MyFONT_TKEY_VDMX ] = table.offset; break;
            case MyFONT_TABLE_TYPE_vhea: mf->cache.tables_offset[ MyFONT_TKEY_vhea ] = table.offset; break;
            case MyFONT_TABLE_TYPE_vmtx: mf->cache.tables_offset[ MyFONT_TKEY_vmtx ] = table.offset; break;
            case MyFONT_TABLE_TYPE_COLR: mf->cache.tables_offset[ MyFONT_TKEY_COLR ] = table.offset; break;
            case MyFONT_TABLE_TYPE_CPAL: mf->cache.tables_offset[ MyFONT_TKEY_CPAL ] = table.offset; break;
            default:
                break;
        };
    }
    
    mf->file_path = (char *)myhtml_calloc(strlen(filepath), sizeof(char));
    
    if(mf->file_path) {
        strncpy(mf->file_path, filepath, strlen(filepath));
    }
    
    myfont_load_table_cmap(mf);
    myfont_load_table_head(mf);
    myfont_load_table_name(mf);
    myfont_load_table_os_2(mf);
    myfont_load_table_maxp(mf);
    myfont_load_table_hhea(mf);
    myfont_load_table_hmtx(mf);
    myfont_load_table_loca(mf);
    myfont_load_table_glyf(mf);
    myfont_load_table_vhea(mf);
    myfont_load_table_vmtx(mf);
    myfont_load_table_pclt(mf);
}

void myfont_font_print_exists_table(myfont_font_t *mf, FILE *file)
{
    size_t i;
    for(i = 0; i < MyFONT_TKEY_LAST_KEY; i++)
    {
        if(mf->cache.tables_offset[i]) {
            fprintf(file, "%s = %u\n", myfont_table_name[i], mf->cache.tables_offset[i]);
        }
    }
}

// metrics
float myfont_metrics_baseline(myfont_font_t *mf, float font_size)
{
    return (float)(mf->table_hhea.Ascender) * font_size / ((float)mf->table_head.unitsPerEm);
}

float myfont_metrics_ascender(myfont_font_t *mf, float font_size)
{
    return 0.0f;
}

float myfont_metrics_descender(myfont_font_t *mf, float font_size)
{
    return (float)(mf->table_hhea.Ascender - mf->table_hhea.Descender) * font_size / ((float)mf->table_head.unitsPerEm);
}

float myfont_metrics_line_gap(myfont_font_t *mf, float font_size)
{
    return (float)(mf->table_hhea.LineGap) * font_size / ((float)mf->table_head.unitsPerEm);
}

float myfont_metrics_x_height(myfont_font_t *mf, float font_size)
{
    int16_t xheight = 0;
    
    if(mf->table_os_2.version > 1)
    {
        if(mf->table_os_2.sxHeight)
            xheight = mf->table_os_2.sxHeight;
    }
    
    if(xheight == 0 && mf->table_pclt.xHeight)
        xheight = (int16_t)mf->table_pclt.xHeight;
    
    if(xheight == 0)
    {
        uint16_t glyph_index = myfont_glyph_index_by_code(mf, (unsigned long)('x'));
        
        if(glyph_index) {
            myfont_table_glyph_t glyph;
            myfont_glyf_load(mf, &glyph, glyph_index);
            
            xheight = glyph.head.yMax;
        }
    }
    
    return (float)(mf->table_hhea.Ascender - xheight) * font_size / (float)mf->table_head.unitsPerEm;
}

float myfont_metrics_cap_height(myfont_font_t *mf, float font_size)
{
    int16_t cap_height = 0;
    
    if(mf->table_os_2.version > 1) {
        if(mf->table_os_2.sCapHeight)
            cap_height = mf->table_os_2.sCapHeight;
    }
    
    if(cap_height == 0 && mf->table_pclt.capHeight)
        cap_height = (int16_t)mf->table_pclt.capHeight;
    
    if(cap_height == 0)
    {
        uint16_t glyph_index = myfont_glyph_index_by_code(mf, (unsigned long)('H'));
        
        if(glyph_index) {
            myfont_table_glyph_t glyph;
            myfont_glyf_load(mf, &glyph, glyph_index);
            
            cap_height = glyph.head.yMax;
        }
    }
    
    return(float)(mf->table_hhea.Ascender - cap_height) * font_size / (float)mf->table_head.unitsPerEm;
}

float myfont_metrics_font_height(myfont_font_t *mf, float font_size)
{
    return (float)(mf->table_hhea.Ascender - mf->table_hhea.Descender) * font_size / (float)mf->table_head.unitsPerEm;
}

// width, height and ...
float myfont_metrics_width(myfont_font_t *mf, unsigned long codepoint, float font_size)
{
    if(mf->table_hhea.numberOfHMetrics == 0 || mf->table_hmtx.hMetrics == NULL)
        return 0.0f;
    
    uint16_t glyph_index = myfont_glyph_index_by_code(mf, codepoint);
    uint16_t width = mf->table_hmtx.hMetrics[glyph_index].advanceWidth;
    
    uint16_t reso = mf->table_head.unitsPerEm;
    float fsize = (float)width * font_size / (float)reso;
    
    return fsize;
}

float myfont_metrics_height(myfont_font_t *mf, unsigned long codepoint, float font_size)
{
    if(mf->table_vhea.numOfLongVerMetrics == 0 || mf->table_vmtx.vMetrics == NULL)
        return myfont_metrics_font_height(mf, font_size);
    
    uint16_t glyph_index = myfont_glyph_index_by_code(mf, codepoint);
    uint16_t height = mf->table_vmtx.vMetrics[glyph_index].advanceHeight;
    
    uint16_t reso = mf->table_head.unitsPerEm;
    float fsize = (float)height * font_size / (float)reso;
    
    return fsize;
}

float myfont_metrics_glyph_offset_y(myfont_font_t *mf, unsigned long codepoint, float font_size)
{
    uint16_t glyph_index = myfont_glyph_index_by_code(mf, codepoint);
    return (float)((mf->table_hhea.Ascender - mf->table_glyf.cache[glyph_index].head.yMax)) * font_size / ((float)mf->table_head.unitsPerEm);
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

