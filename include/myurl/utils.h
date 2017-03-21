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
 Foundation, Inc., 51 Franklin avl_treet, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MyURL_UTILS_H
#define MyURL_UTILS_H
#pragma once

typedef struct myurl_utils_data_list myurl_utils_data_list_t;

#include <myurl/myosi.h>
#include <myurl/parser.h>
#include <myhtml/mystring.h>

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

struct myurl_utils_serialization_ctx {
    char*  data;
    size_t size;
    size_t length;
    
    myurl_t* url;
    bool error;
}
typedef myurl_utils_serialization_ctx_t;

char * myurl_utils_data_copy(myurl_t* url, const char* data, size_t size);
mystatus_t myurl_utils_data_copy_set(myurl_t* url, const char* data, size_t size, char** to, size_t* to_length);
mystatus_t myurl_utils_data_copy_append(myurl_t* url, const char* data, size_t size, char** to, size_t* to_length);
void myurl_utils_data_set_null(myurl_t* url, char** to, size_t* length);
void myurl_utils_data_set_empty(myurl_t* url, char** to, size_t* length);
char * myurl_utils_percent_encode(myurl_t* url, const char* data, size_t size, const unsigned char* encode_set, size_t* return_length);
size_t myurl_utils_percent_decode_bytes_in_data(char* data, size_t size);

bool myurl_utils_is_windows_drive_letter(const char* data, size_t length, size_t size);
bool myurl_utils_is_double_dot_path_segment(const char* data, size_t length);
bool myurl_utils_is_single_dot_path_segment(const char* data, size_t length);

size_t myurl_convert_integer_to_data_without_check_buffer(long digit, char* return_str);
size_t myurl_convert_integer_to_hex_data_without_check_buffer(long digit, char* return_str);

//void myurl_utils_data_set(myurl_parser_t* parser, myurl_parser_data_t* parse_data, const unsigned char* data, size_t length);
//void myurl_utils_data_append(myurl_parser_t* parser, myurl_parser_data_t* parse_data, const unsigned char* data, size_t length);
//void myurl_utils_data_copy(myurl_parser_t* parser, myurl_parser_data_t* to, const myurl_parser_data_t* from);
//void myurl_utils_data_destroy(myurl_parser_t* parser, myurl_parser_data_t* parse_data, bool self_destroy);



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_UTILS_H */
