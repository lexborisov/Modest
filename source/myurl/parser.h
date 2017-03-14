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

#ifndef MyURL_PARSER_H
#define MyURL_PARSER_H
#pragma once

#include "myurl/myosi.h"
#include "myurl/utils.h"

#define myurl_parser_digit(onechar) (onechar >= 0x30 && onechar <= 0x39)
#define myurl_parser_alpha_upper(onechar) (onechar >= 0x41 && onechar <= 0x5A)
#define myurl_parser_alpha_lower(onechar) (onechar >= 0x61 && onechar <= 0x7A)
#define myurl_parser_alpha(onechar) (myurl_parser_alpha_upper(onechar) || myurl_parser_alpha_lower(onechar))

#define myurl_parser_alphanumeric(onechar) (myurl_parser_digit(onechar) || myurl_parser_alpha(onechar))

#define myurl_parser_swap_path(url, base) \
    if(url->path) \
        myurl_utils_data_list_destroy(url->path, true); \
    url->path = base->path

#define myurl_parser_copy_scheme(parser, to, from) \
    to->scheme.scheme = from->scheme.scheme; \
    myurl_utils_data_copy(parser, &to->scheme.origin, &from->scheme.origin)

#define myurl_parser_copy_path(parser, to, from) \
    myurl_utils_data_list_copy(parser, to->path, from->path)

#define myurl_parser_copy_attr(url, from, to, attr) \
    myurl_utils_data_copy_set(url, from->attr, from->attr ## _length, &to->attr, &to->attr ## _length)

#define myurl_parser_copy_buffer(url, data, data_length, to) \
    myurl_utils_data_copy_set(url, &data[ url->begin ], (data_length - url->begin), &to, &to ## _length)

#define myurl_parser_append_buffer(url, data, begin, data_length, to) \
    myurl_utils_data_copy_append(url, &data[ begin ], (data_length - begin), &to, &to ## _length)

#define myurl_parser_is_includes_credentials(url_entry) (url_entry->username_length || url_entry->password_length)

#ifdef __cplusplus
extern "C" {
#endif

size_t myurl_parser_begin(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_size);

size_t myurl_parser_state_undef(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_scheme_start(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_scheme(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_no_scheme(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_special_relative_or_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_path_or_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_relative(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_relative_slash(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_special_authority_slashes(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_special_authority_ignore_slashes(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_authority(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_host_hostname(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_port(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_file(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_file_slash(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_file_host(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_path_start(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_path(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_cannot_be_a_base_URL_path(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_query(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_fragment(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);

/* ends */
size_t myurl_parser_state_relative_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_authority_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_host_hostname_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_port_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_file_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_file_host_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_path_start_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_path_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_cannot_be_a_base_URL_path_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);
size_t myurl_parser_state_query_end(myurl_t* url, myurl_entry_t* url_entry, myurl_entry_t* url_base, const char* data, size_t data_length, size_t data_size);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_PARSER_H */
