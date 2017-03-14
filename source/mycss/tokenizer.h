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

#ifndef MyHTML_MyCSS_TOKENIZER_H
#define MyHTML_MyCSS_TOKENIZER_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/myosi.h"
#include "mycss/mycss.h"
#include "mycss/entry.h"
#include "mycss/check.h"
#include "mycss/tokenizer_global.h"
#include "mycss/tokenizer_end.h"

#include "mycore/incoming.h"

#define MyCSS_TOKEN_READY_CALLBACK_FUNCTION(ENTRY, TOKEN) \
    ++ENTRY->token_counter; \
    if(ENTRY->token_ready_callback) \
        (void)ENTRY->token_ready_callback(ENTRY, TOKEN)

#define MyCSS_TOKEN_READY_CALLBACK_FUNCTION_WITH_REPLACE(ENTRY, TOKEN) \
    ++ENTRY->token_counter; \
    if(ENTRY->token_ready_callback) \
        TOKEN = ENTRY->token_ready_callback(ENTRY, TOKEN)

struct mycss_token {
    mycss_token_type_t type;
    size_t begin;
    size_t length;
    
    const char* data;
};

mystatus_t mycss_tokenizer_state_init(mycss_t* mycss);
void mycss_tokenizer_state_destroy(mycss_t* mycss);

mystatus_t mycss_tokenizer_chunk(mycss_entry_t* entry, const char* css, size_t css_length);
mystatus_t mycss_tokenizer_process(mycss_entry_t* entry, const char* css, size_t css_length);
mystatus_t mycss_tokenizer_end(mycss_entry_t* entry);

size_t mycss_tokenizer_run_state_single(mycss_entry_t* entry, mycss_tokenizer_state_t state, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_set_current_buffer_for_continue(mycss_entry_t* entry, size_t css_offset, size_t css_minus_offset);
size_t mycss_tokenizer_token_strcasecmp(mycss_entry_t* entry, mycss_token_t* token, const char* to, size_t to_length);


size_t mycss_tokenizer_state_quotation_mark(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_quotation_mark_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_number_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_number_sign_name_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_number_sign_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_dollar_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_apostrophe(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_apostrophe_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_left_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_right_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_asterisk(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_plus_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_plus_sign_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_comma(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_hyphen_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_hyphen_minus_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_hyphen_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_hyphen_minus_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_hyphen_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_solidus_comment_end(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_colon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_semicolon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_less_than_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_less_than_sign_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_less_than_sign_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_commercial_at(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_commercial_at_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_commercial_at_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_commercial_at_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_commercial_at_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_left_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_reverse_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_right_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_circumflex_accent(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_left_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_right_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_letter_u(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_letter_u_next(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_name_start_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_vertical_line(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);
size_t mycss_tokenizer_state_tilde(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

size_t mycss_tokenizer_state_delim_single_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
