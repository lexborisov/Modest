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

#ifndef MyHTML_MyCSS_ENTRY_H
#define MyHTML_MyCSS_ENTRY_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <mycss/myosi.h>
#include <mycss/mycss.h>
#include <mycss/parser.h>
#include <mycss/stylesheet.h>
#include <mycss/namespace/myosi.h>
#include <mycss/namespace/init.h>
#include <mycss/selectors/myosi.h>
#include <mycss/selectors/init.h>
#include <mycss/an_plus_b.h>
#include <mycss/declaration/myosi.h>
#include <mycss/declaration/init.h>
#include <mycss/declaration/entry.h>
#include <mycss/media/myosi.h>
#include <mycss/media/init.h>
#include <mycore/utils/mcobject.h>
#include <mycore/utils/mchar_async.h>

struct mycss_entry_parser_list_entry {
    mycss_parser_token_f parser;
    mycss_parser_token_f parser_switch;
    mycss_token_type_t   ending_token;
    
    bool is_local;
}
typedef mycss_entry_parser_list_entry_t;

struct mycss_entry_parser_list {
    mycss_entry_parser_list_entry_t* list;
    size_t size;
    size_t length;
}
typedef mycss_entry_parser_list_t;

struct mycss_entry {
    /* refs */
    mycss_t* mycss;
    mycss_token_t* token;
    mycss_stylesheet_t* stylesheet;
    
    /* objects and memory for css modules */
    mchar_async_t* mchar;
    size_t mchar_node_id;
    size_t mchar_value_node_id;
    
    mcobject_t* mcobject_string_entries;
    
    /* css modules */
    mycss_namespace_t*   ns;
    mycss_selectors_t*   selectors;
    mycss_an_plus_b_t*   anb;
    mycss_media_t*       media;
//    mycss_rules_t*       rules;
    mycss_declaration_t* declaration;
    void**               values;
    
    /* incoming buffer */
    mcobject_t* mcobject_incoming_buffer;
    mycore_incoming_buffer_t* first_buffer;
    mycore_incoming_buffer_t* current_buffer;
    
    /* options */
    mycss_entry_type_t type;
    myencoding_t encoding;
    
    /* tokenizer */
    mycss_tokenizer_state_t state;
    mycss_tokenizer_state_t state_back;
    
    /* parser */
    mycss_entry_parser_list_t* parser_list;
    mycss_parser_token_f parser;
    mycss_parser_token_f parser_switch;
    mycss_parser_token_f parser_error;
    mycss_parser_token_f parser_original;
    mycss_token_type_t   parser_ending_token;
    
    /* callbacks */
    mycss_token_ready_callback_f token_ready_callback;
    mycss_callback_selector_done_f callback_selector_done;
    
    /* helpers */
    size_t token_counter;
    size_t help_counter;
};

mycss_entry_t * mycss_entry_create(void);
mystatus_t mycss_entry_init(mycss_t* mycss, mycss_entry_t* entry);
mystatus_t mycss_entry_clean(mycss_entry_t* entry);
mystatus_t mycss_entry_clean_all(mycss_entry_t* entry);
mycss_entry_t * mycss_entry_destroy(mycss_entry_t* entry, bool self_destroy);

void mycss_entry_end(mycss_entry_t* entry);

/* api */
mycss_selectors_t * mycss_entry_selectors(mycss_entry_t* entry);

mycss_token_ready_callback_f mycss_entry_token_ready_callback(mycss_entry_t* entry, mycss_token_ready_callback_f callback_f);

size_t mycss_entry_token_count(mycss_entry_t* entry);
mycore_incoming_buffer_t * mycss_entry_incoming_buffer_current(mycss_entry_t* entry);
mycore_incoming_buffer_t * mycss_entry_incoming_buffer_first(mycss_entry_t* entry);

mycore_string_t * mycss_entry_string_create_and_init(mycss_entry_t* entry, size_t string_size);

mycss_stylesheet_t * mycss_entry_stylesheet(mycss_entry_t* entry);
mycss_selectors_list_t * mycss_entry_current_selectors_list(mycss_entry_t* entry);

void mycss_entry_parser_set(mycss_entry_t* entry, mycss_parser_token_f parser);
void mycss_entry_parser_switch_set(mycss_entry_t* entry, mycss_parser_token_f parser_switch);
void mycss_entry_parser_original_set(mycss_entry_t* entry, mycss_parser_token_f parser_original);

/* parser list */
mycss_entry_parser_list_t * mycss_entry_parser_list_create_and_init(size_t size);
void mycss_entry_parser_list_clean(mycss_entry_parser_list_t* parser_list);
mycss_entry_parser_list_t * mycss_entry_parser_list_destroy(mycss_entry_parser_list_t* parser_list, bool self_destroy);

mystatus_t mycss_entry_parser_list_push(mycss_entry_t* entry, mycss_parser_token_f parser_func,
                                            mycss_parser_token_f parser_switch, mycss_token_type_t ending_token,
                                            bool is_local);

void mycss_entry_parser_list_pop(mycss_entry_t* entry);
size_t mycss_entry_parser_list_length(mycss_entry_t* entry);
mycss_token_type_t mycss_entry_parser_list_current_ending_token_type(mycss_entry_t* entry);
mycss_parser_token_f mycss_entry_parser_list_current_parser(mycss_entry_t* entry);
mycss_parser_token_f mycss_entry_parser_list_current_parser_switch(mycss_entry_t* entry);
bool mycss_entry_parser_list_current_is_local(mycss_entry_t* entry);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_ENTRY_H */
