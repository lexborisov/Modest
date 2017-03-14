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

#ifndef MyHTML_MyCSS_AN_PLUS_B_H
#define MyHTML_MyCSS_AN_PLUS_B_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/selectors/list.h"

#define mycss_an_plus_b_current_entry(entry) (*entry->anb->entry)

struct mycss_an_plus_b {
    mycss_an_plus_b_entry_t** entry;
};

struct mycss_an_plus_b_entry {
    long a;
    long b;
    long n;
    
    bool is_broken;
    mycss_selectors_list_t* of;
};

mycss_an_plus_b_t * mycss_an_plus_b_create(void);
mystatus_t mycss_an_plus_b_init(mycss_entry_t* entry, mycss_an_plus_b_t* anb);
mystatus_t mycss_an_plus_b_clean_all(mycss_an_plus_b_t* anb);
mycss_an_plus_b_t * mycss_an_plus_b_destroy(mycss_an_plus_b_t* anb, bool self_destroy);

mycss_an_plus_b_entry_t * mycss_an_plus_b_entry_create(mycss_entry_t* entry);
void mycss_an_plus_b_entry_clean_all(mycss_an_plus_b_entry_t* anb_entry);
mycss_an_plus_b_entry_t * mycss_an_plus_b_entry_destroy(mycss_entry_t* entry, mycss_an_plus_b_entry_t* anb_entry, bool self_destroy);

void mycss_an_plus_b_serialization(mycss_an_plus_b_entry_t* anb_entry, mycore_callback_serialize_f callback, void* context);

void mycss_an_plus_b_parser_expectations_error(mycss_entry_t* entry);

bool mycss_an_plus_b_state_anb_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_an_plus_b_state_anb(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_an_plus_b_state_anb_plus(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_an_plus_b_state_anb_plus_n_hyphen(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_an_plus_b_state_anb_plus_n(mycss_entry_t* entry, mycss_token_t* token, bool last_response);
bool mycss_an_plus_b_state_anb_plus_n_plus(mycss_entry_t* entry, mycss_token_t* token, bool last_response);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_AN_PLUS_B_H */
