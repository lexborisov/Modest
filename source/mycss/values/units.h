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

#ifndef MyHTML_MyCSS_VALUES_UNITS_H
#define MyHTML_MyCSS_VALUES_UNITS_H
#pragma once

#include "mycss/myosi.h"
#include "mycore/utils.h"

#define mycss_units_is_angel_type(type)           (type >= 1  && type <= 4)
#define mycss_units_is_frequency_type(type)       (type >= 5  && type <= 6)
#define mycss_units_is_length_type(type)          (type >= 7  && type <= 24)
#define mycss_units_is_length_absolute_type(type) (type >= 7  && type <= 13)
#define mycss_units_is_length_relative_type(type) (type >= 14 && type <= 24)
#define mycss_units_is_resolution_type(type)      (type >= 25 && type <= 27)
#define mycss_units_is_time_type(type)            (type >= 28 && type <= 29)

#ifdef __cplusplus
extern "C" {
#endif

enum mycss_units_type {
    MyCSS_UNIT_TYPE_UNDEF      = 0x00,
    MyCSS_UNIT_TYPE_DEG        = 0x01,
    MyCSS_UNIT_TYPE_GRAD       = 0x02,
    MyCSS_UNIT_TYPE_RAD        = 0x03,
    MyCSS_UNIT_TYPE_TURN       = 0x04,
    MyCSS_UNIT_TYPE_HZ         = 0x05,
    MyCSS_UNIT_TYPE_KHZ        = 0x06,
    MyCSS_UNIT_TYPE_CM         = 0x07,
    MyCSS_UNIT_TYPE_IN         = 0x08,
    MyCSS_UNIT_TYPE_MM         = 0x09,
    MyCSS_UNIT_TYPE_PC         = 0x0a,
    MyCSS_UNIT_TYPE_PT         = 0x0b,
    MyCSS_UNIT_TYPE_PX         = 0x0c,
    MyCSS_UNIT_TYPE_Q          = 0x0d,
    MyCSS_UNIT_TYPE_CH         = 0x0e,
    MyCSS_UNIT_TYPE_EM         = 0x0f,
    MyCSS_UNIT_TYPE_EX         = 0x10,
    MyCSS_UNIT_TYPE_IC         = 0x11,
    MyCSS_UNIT_TYPE_REM        = 0x12,
    MyCSS_UNIT_TYPE_VB         = 0x13,
    MyCSS_UNIT_TYPE_VH         = 0x14,
    MyCSS_UNIT_TYPE_VI         = 0x15,
    MyCSS_UNIT_TYPE_VMAX       = 0x16,
    MyCSS_UNIT_TYPE_VMIN       = 0x17,
    MyCSS_UNIT_TYPE_VW         = 0x18,
    MyCSS_UNIT_TYPE_DPCM       = 0x19,
    MyCSS_UNIT_TYPE_DPI        = 0x1a,
    MyCSS_UNIT_TYPE_DPPX       = 0x1b,
    MyCSS_UNIT_TYPE_MS         = 0x1c,
    MyCSS_UNIT_TYPE_S          = 0x1d,
    MyCSS_UNIT_TYPE_LAST_ENTRY = 0x1e,
}
typedef mycss_units_type_t;

struct mycss_units_index_static_entry {
    const char* name;
    size_t name_length;
    
    mycss_units_type_t unit_type;
    
    size_t next;
    size_t curr;
}
typedef mycss_units_index_static_entry_t;


mycss_units_type_t mycss_units_type_by_name(const char *name, size_t length);
const mycss_units_index_static_entry_t * mycss_units_index_entry_by_name(const char* name, size_t length);
const char * mycss_units_name_by_type(mycss_units_type_t unit_type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_VALUES_UNITS_H */
