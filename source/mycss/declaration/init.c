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

#include "mycss/declaration/init.h"


mycss_declaration_t * mycss_declaration_create(void)
{
    return (mycss_declaration_t*)mycore_calloc(1, sizeof(mycss_declaration_t));
}

mystatus_t mycss_declaration_init(mycss_entry_t* entry, mycss_declaration_t* declaration)
{
    declaration->ref_entry = entry;
    declaration->entry = NULL;
    declaration->ending_token = MyCSS_TOKEN_TYPE_UNDEF;
    
    /* Objects */
    declaration->mcobject_entries = mcobject_create();
    if(declaration->mcobject_entries == NULL)
        return MyCSS_STATUS_ERROR_DECLARATION_ENTRY_CREATE;
    
    mystatus_t myhtml_status = mcobject_init(declaration->mcobject_entries, 256, sizeof(mycss_declaration_entry_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_DECLARATION_ENTRY_INIT;
    
    /* Stack */
    declaration->stack = mycss_stack_create();
    if(declaration->stack == NULL)
        return MyCSS_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if(mycss_stack_init(declaration->stack, 512))
        return MyCSS_STATUS_ERROR_MEMORY_ALLOCATION;
    
    return MyCSS_STATUS_OK;
}

void mycss_declaration_clean(mycss_declaration_t* declaration)
{
    declaration->entry = NULL;
    declaration->ending_token = MyCSS_TOKEN_TYPE_UNDEF;
    
    mycss_stack_clean(declaration->stack);
}

void mycss_declaration_clean_all(mycss_declaration_t* declaration)
{
    declaration->entry = NULL;
    declaration->ending_token = MyCSS_TOKEN_TYPE_UNDEF;
    
    mcobject_clean(declaration->mcobject_entries);
    mycss_stack_clean(declaration->stack);
}

mycss_declaration_t * mycss_declaration_destroy(mycss_declaration_t* declaration, bool self_destroy)
{
    if(declaration == NULL)
        return NULL;
    
    declaration->mcobject_entries = mcobject_destroy(declaration->mcobject_entries, true);
    declaration->stack = mycss_stack_destroy(declaration->stack, true);
    
    if(self_destroy) {
        mycore_free(declaration);
        return NULL;
    }
    
    return declaration;
}

mycss_token_t * mycss_declaration_parse_token_callback(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_COMMENT)
        return token;
    
    bool last_response = true;
    while((last_response = entry->parser(entry, token, last_response)) == false) {};
    
    return entry->token;
}

void mycss_declaration_ending_token_type_set(mycss_declaration_t* declaration, mycss_token_type_t ending_token_type)
{
    declaration->ending_token = ending_token_type;
}

mycss_token_type_t mycss_declaration_ending_token_type(mycss_declaration_t* declaration)
{
    return declaration->ending_token;
}

mycss_declaration_entry_t * mycss_declaration_parse(mycss_declaration_t* declaration, myencoding_t encoding, const char* data, size_t data_size, mystatus_t* out_status)
{
    if(data == NULL || data_size == 0) {
        if(out_status)
            *out_status = MyCSS_STATUS_OK;
        
        return NULL;
    }
    
    mycss_declaration_clean(declaration);
    
    mycss_entry_t *entry = declaration->ref_entry;
    
    mycss_token_ready_callback_f tmp_token_ready_callback = entry->token_ready_callback;
    
    entry->token_ready_callback      = mycss_declaration_parse_token_callback;
    entry->parser                    = mycss_declaration_state_begin;
    entry->parser_original           = NULL;
    entry->parser_switch             = NULL;
    entry->state                     = MyCSS_TOKENIZER_STATE_DATA;
    entry->state_back                = MyCSS_TOKENIZER_STATE_DATA;
    entry->declaration->ending_token = MyCSS_TOKEN_TYPE_UNDEF;
    
    mycss_declaration_entry_t *dec_entry = NULL;
    
    declaration->entry = &dec_entry;
    declaration->entry_last = NULL;
    
    /* parsing */
    mycss_encoding_set(entry, encoding);
    
    mystatus_t status = mycss_tokenizer_chunk(entry, data, data_size);
    if(status != MyCSS_STATUS_OK) {
        if(out_status)
            *out_status = status;
        
        entry->token_ready_callback = tmp_token_ready_callback;
        return NULL;
    }
    
    status = mycss_tokenizer_end(entry);
    
    mycss_declaration_parser_end(entry, NULL);
    
    if(out_status)
        *out_status = status;
    
    entry->token_ready_callback = tmp_token_ready_callback;
    
    if(dec_entry)
        return dec_entry;
    
    return NULL;
}


