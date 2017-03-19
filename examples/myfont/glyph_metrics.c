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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <myfont/myfont.h>
#include <myencoding/encoding.h>

void usage(const char *path, float font_size, size_t codepoint)
{
    printf("Usage:\n");
    printf("\tprogram [char in UTF-8] [font fize in px] [font path]\n");
    printf("\tdefault: program \"x\" %.f %s\n\n", font_size, path);
}

int main(int argc, const char * argv[])
{
    /* set and get params */
    const char *path = "third_party/font/Arkhip.ttf";
    float font_size = 200.0f;
    
    size_t codepoint;
    myencoding_ascii_utf_8_to_codepoint((unsigned char*)"x", &codepoint);
    
    if (argc == 2) {
        if(myencoding_ascii_utf_8_to_codepoint((const unsigned char*)argv[1], &codepoint) == 0) {
            fprintf(stderr, "Bad char code point\n");
            return EXIT_FAILURE;
        }
    }
    else if (argc == 3) {
        long num = strtol(argv[2], NULL, 0);
        
        if(num < 1) {
            fprintf(stderr, "To small font size param\n");
            return EXIT_FAILURE;
        }
        
        font_size = (float)num;
    }
    else if (argc == 4) {
        path = argv[3];
    }
    else {
        usage(path, font_size, codepoint);
    }
    
    myfont_font_t *mf = myfont_create();
    myfont_init(mf);
    
    uint8_t *font_data;
    mystatus_t mf_status = myfont_load_from_file(mf, path, &font_data, NULL);
    
    if(mf_status) {
        myfont_destroy(mf, true);
        
        if(mf_status == MyFONT_STATUS_ERROR_FILE_OPEN) {
            fprintf(stderr, "Can't open font file %s\n", path);
        }
        else {
            fprintf(stderr, "Can't load font file %s\n", path);
        }
        
        return EXIT_FAILURE;
    }
    
    char data[5];
    size_t len = myencoding_codepoint_to_ascii_utf_8(codepoint, data);
    data[len] = '\0';
    
    /* work code */
    uint16_t glyph_index = myfont_glyph_index_by_codepoint(mf, codepoint, NULL);
    
    float baseline   = myfont_metrics_baseline(mf, font_size);
    float ascender   = myfont_metrics_ascender(mf, font_size);
    float descender  = myfont_metrics_descender(mf, font_size);
    float x_height   = myfont_metrics_x_height(mf, font_size);
    float cap_height = myfont_metrics_cap_height(mf, font_size);
    float offset     = myfont_metrics_glyph_offset_y(mf, codepoint, font_size, NULL);
    float width      = myfont_metrics_width(mf, codepoint, font_size, NULL);
    float height     = myfont_metrics_height(mf, codepoint, font_size, NULL);
    
    /* print result */
    printf("Font file: %s\n", path);
    printf("Font size: %.fpx\n\n", font_size);
    
    printf("Metrics for code point " MyCORE_FORMAT_Z " (%s):\n", codepoint, data);
    printf("\tBaseline: %.05f\n", baseline);
    printf("\tAscender: %.05f\n", ascender);
    printf("\tDescender: %.05f\n", descender);
    printf("\tX-Height: %.05f\n", x_height);
    printf("\tCap-Height: %.05f\n", cap_height);
    printf("\tWidth: %.05f\n", width);
    printf("\tHeight: %.05f\n", height);
    
    /* print html svg */
    printf("\n<svg width=\"%f\" height=\"%f\">\n", width + 4.0f, descender + 4.0f);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(0,124,110);stroke-width:1\" />\n", 0.0f, ascender, width, ascender);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(140,0,110);stroke-width:1\" />\n", 0.0f, cap_height, width, cap_height);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(140,124,110);stroke-width:1\" />\n", 0.0f, x_height, width, x_height);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(0,255,0);stroke-width:1\" />\n", 0.0f, baseline, width, baseline);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(255,0,0);stroke-width:1\" />\n", 0.0f, descender, width, descender);
    
    if(glyph_index < mf->table_maxp.numGlyphs) {
        myfont_table_glyph_t *glyph = &mf->table_glyf.cache[glyph_index];
        
        printf("\t<polyline points=\"");
        for(size_t i = 0; i < glyph->pointCount; i++) {
            
            float x = (float)((glyph->head.xMax + glyph->simple.xCoordinates[i]) - glyph->head.xMax) * font_size / ((float)mf->table_head.unitsPerEm);
            float y = (float)((glyph->head.yMax - glyph->simple.yCoordinates[i])) * font_size / ((float)mf->table_head.unitsPerEm);
            
            printf("%f,%f ", x, (y + offset));
        }
        printf("\" />\n");
    }
    
    printf("</svg>\n");
    
    myfont_destroy_font_data(mf, font_data);
    myfont_destroy(mf, true);
    
    return 0;
}


