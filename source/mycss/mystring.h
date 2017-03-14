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

#ifndef MyHTML_MyCSS_MYSTRING_H
#define MyHTML_MyCSS_MYSTRING_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycore/incoming.h"
#include "mycore/mystring.h"
#include "myencoding/encoding.h"
    
enum mycss_string_process_state {
    MyCSS_STRING_PROCESS_STATE_DATA       = 0x00,
    MyCSS_STRING_PROCESS_STATE_ESCAPED    = 0x01,
    MyCSS_STRING_PROCESS_STATE_LAST_ENTRY = 0x02
}
typedef mycss_string_process_state_t;

struct mycss_string_escaped_res {
    unsigned short consumed;
    size_t code_point;
};

struct mycss_string_res {
    mycss_string_escaped_res_t escaped;
    mycss_string_process_state_t state;
    
    myencoding_t encoding;
    myencoding_result_t encoding_res;
    bool case_insensitive;
};

size_t mycss_string_data_process(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res);
void mycss_string_data_process_end(mycore_string_t* str, mycss_string_res_t *out_res);

size_t mycss_string_process_state_data(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res);
size_t mycss_string_process_state_data_utf_8(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res);
size_t mycss_string_process_state_escaped(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res);
size_t mycss_string_process_state_escaped_utf_8(mycore_string_t* str, const char* data, size_t length, size_t size, mycss_string_res_t *out_res);

void mycss_string_res_clean(mycss_string_res_t* res);
void mycss_string_escaped_res_clean(mycss_string_escaped_res_t* res);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_MYSTRING_H */
