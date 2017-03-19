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

#ifndef MyHTML_MyCSS_TOKENIZER_GLOBAL_H
#define MyHTML_MyCSS_TOKENIZER_GLOBAL_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycss/mycss.h"
#include "mycss/entry.h"
#include "mycss/check.h"

size_t mycss_tokenizer_global_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_numeric(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_numeric_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_numeric_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_numeric_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_number_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_number_dot(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_number_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_number_e(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_number_e_plus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_number_e_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_ident(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_url_string_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_url_after(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_url_after_whitespace(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_url_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_bad_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_name(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_string_double_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_string_double_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_string_double_quoted_rsolidus_r(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_string_single_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_string_single_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_string_single_quoted_rsolidus_r(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_global_state_unicode_range_before(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_unicode_range(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_unicode_range_question(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_global_state_unicode_range_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_TOKENIZER_GLOBAL_H */
