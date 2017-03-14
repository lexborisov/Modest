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

#ifndef MyHTML_MyCSS_MYCSS_H
#define MyHTML_MyCSS_MYCSS_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycss/entry.h"
#include "mycss/tokenizer.h"
#include "myhtml/myhtml.h"
#include "mycore/utils/mcobject_async.h"

struct mycss {
    mycss_tokenizer_state_f* parse_state_func;
};

mycss_t * mycss_create(void);
mystatus_t mycss_init(mycss_t* mycss);
mycss_t * mycss_destroy(mycss_t* mycss, bool self_destroy);

mystatus_t mycss_parse(mycss_entry_t* entry, myencoding_t encoding, const char* css, size_t css_size);
mystatus_t mycss_parse_chunk(mycss_entry_t* entry, const char* css, size_t css_size);
mystatus_t mycss_parse_chunk_end(mycss_entry_t* entry);

size_t mycss_token_begin(mycss_token_t* token);
size_t mycss_token_length(mycss_token_t* token);
size_t mycss_token_position(mycss_token_t* token, size_t *return_length);
mycss_token_type_t mycss_token_type(mycss_token_t* token);
const char * mycss_token_name_by_type(mycss_token_type_t type);
size_t mycss_token_data_to_string(mycss_entry_t* entry, mycss_token_t* token, mycore_string_t* str, bool init_string, bool case_insensitive);

mycore_incoming_buffer_t * mycss_token_buffer_first(mycss_entry_t* entry, mycss_token_t* token);

// encoding
void mycss_encoding_set(mycss_entry_t* entry, myencoding_t encoding);
myencoding_t mycss_encoding_get(mycss_entry_t* entry);
myencoding_t mycss_encoding_check_charset_rule(const char* css, size_t size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
