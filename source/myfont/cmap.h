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

#ifndef MyFONT_CMAP_H
#define MyFONT_CMAP_H
#pragma once

#include "myfont/myosi.h"

#ifdef __cplusplus
extern "C" {
#endif

// table cmap
// + formats
// for Format 8 and 12
struct myfont_tcmap_group {
    uint32_t startCharCode;
    uint32_t endCharCode;
    uint32_t startGlyphID;
}
typedef myfont_tcmap_group_t;

// ++ Format 0: Byte encoding table
struct myfont_tcmap_format_0 {
    uint16_t length;
    uint16_t language;
    uint8_t  glyphIdArray[256];
}
typedef myfont_tcmap_format_0_t;

// ++ Format 2: High-byte mapping through table
struct myfont_tcmap_format_2_subHeader {
    uint16_t firstCode;
    uint16_t entryCount;
    int16_t  idDelta;
    uint16_t idRangeOffset;
}
typedef myfont_tcmap_f2_sub_header_t;

struct myfont_tcmap_format_2 {
    uint16_t  length;
    uint16_t  language;
    uint16_t  subHeaderKeys[256];
    
    myfont_tcmap_f2_sub_header_t *subHeaders;
    uint16_t *glyphIndexArray;
}
typedef myfont_tcmap_format_2_t;

// ++ Format 4: Segment mapping to delta values
// from length to rangeShift
#define MyFONT_TCMAP_FORMAT_4_FIRST_LENGTH (2 * 6)

struct myfont_tcmap_format_4 {
    uint16_t length;
    uint16_t language;
    uint16_t segCountX2;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
    uint16_t *endCount;       // [segCountX2 / 2]
    uint16_t reservedPad;
    uint16_t *startCount;     // [segCountX2 / 2]
    int16_t  *idDelta;        // [segCountX2 / 2]
    uint16_t *idRangeOffset;  // [segCountX2 / 2]
    uint16_t *glyphIdArray;
    
    /* user def */
    uint16_t numGlyphId;
    uint16_t segCount;
}
typedef myfont_tcmap_format_4_t;

// ++ Format 6: Trimmed table mapping
struct myfont_tcmap_format_6 {
    uint16_t length;
    uint16_t language;
    uint16_t firstCode;
    uint16_t entryCount;
    uint16_t *glyphIdArray;   // [entryCount]
}
typedef myfont_tcmap_format_6_t;

// +++ Format 8: mixed 16-bit and 32-bit coverage
struct myfont_tcmap_format_8 {
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    uint8_t  is32[8192];
    uint32_t nGroups;         // follow myfont_tcmap_group_t
}
typedef myfont_tcmap_format_8_t;

// +++ Format 10: Trimmed array
struct myfont_tcmap_format_10 {
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    uint32_t startCharCode;
    uint32_t numChars;
    uint16_t *glyphs;
}
typedef myfont_tcmap_format_10_t;

// +++ Format 12: Segmented coverage
struct myfont_tcmap_format_12 {
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    uint32_t nGroups;         // follow myfont_tcmap_group_t
}
typedef myfont_tcmap_format_12_t;

// +++ Format 13: Many-to-one range mappings.
struct myfont_tcmap_format_13 {
    uint16_t reserved;
    uint32_t length;
    uint32_t language;
    // Glyph index to be used for all the characters in the group's range.
    uint32_t nGroups;         // follow myfont_tcmap_group_t
}
typedef myfont_tcmap_format_13_t;

// +++ Format 14: Unicode Variation Sequences
struct myfont_tcmap_format_14 {
    uint8_t  varSelector[3];    // uint24_t
    uint32_t length;
    uint32_t numVarSelectorRecords;
}
typedef myfont_tcmap_format_14_t;

struct myfont_tcmap_f14_records {
    uint32_t defaultUVSOffset;
    uint32_t nonDefaultUVSOffset;
}
typedef myfont_tcmap_f14_records_t;

// Default UVS Table
struct myfont_tcmap_f14_val_range {
    uint8_t startUnicodeValue[3];  // uint24_t
    uint8_t additionalCount;
}
typedef myfont_tcmap_f14_val_range_t;

struct myfont_tcmap_f14_def_uvs {
    uint32_t numUnicodeValueRanges;
    myfont_tcmap_f14_val_range_t *value_ranges;
}
typedef myfont_tcmap_f14_def_uvs_t;

// Non-Default UVS Table
struct myfont_tcmap_f14_mapp {
    uint8_t startUnicodeValue[3];  // uint24_t
    uint8_t additionalCount;
}
typedef myfont_tcmap_f14_mapp_t;

struct myfont_tcmap_f14_non_def_uvs {
    uint32_t numUVSMappings;
    myfont_tcmap_f14_mapp_t *mappings;
}
typedef myfont_tcmap_f14_non_def_uvs_t;

// cmap headers
struct myfont_tcmap_header {
    uint16_t version;
    uint16_t numTables;
}
typedef myfont_tcmap_header_t;

struct myfont_tcmap_record {
    uint16_t platformID;
    uint16_t encodingID;
    uint32_t offset;
}
typedef myfont_tcmap_record_t;

struct myfont_tcmap_entry {
    uint16_t format;
    void *header;
}
typedef myfont_tcmap_entry_t;

struct myfont_table_cmap {
    myfont_tcmap_header_t header;
    myfont_tcmap_record_t *records;
    myfont_tcmap_entry_t  *entries;
}
typedef myfont_table_cmap_t;

#include "myfont/myfont.h"

mystatus_t myfont_load_table_cmap(myfont_font_t* mf, uint8_t* data, size_t data_size);

uint16_t myfont_glyph_index_by_codepoint(myfont_font_t *mf, unsigned long char_code, mystatus_t* status);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyFONT_CMAP_H */
