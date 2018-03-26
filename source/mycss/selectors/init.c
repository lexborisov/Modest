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

#include "mycss/selectors/init.h"
#include "mycss/selectors/value_resource.h"

mycss_selectors_t * mycss_selectors_create(void)
{
    return (mycss_selectors_t*)mycore_calloc(1, sizeof(mycss_selectors_t));
}

mystatus_t mycss_selectors_init(mycss_entry_t* entry, mycss_selectors_t* selectors)
{
    selectors->ref_entry  = entry;
    selectors->entry      = NULL;
    selectors->entry_last = NULL;
    selectors->list       = NULL;
    selectors->list_last  = NULL;
    selectors->combinator = NULL;
    
    /* Objects Selector */
    selectors->mcobject_entries = mcobject_create();
    if(selectors->mcobject_entries == NULL)
        return MyCSS_STATUS_ERROR_SELECTORS_ENTRIES_CREATE;
    
    mystatus_t myhtml_status = mcobject_init(selectors->mcobject_entries, 256, sizeof(mycss_selectors_entry_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_SELECTORS_ENTRIES_INIT;
    
    /* Selectors List Entries */
    selectors->mcobject_list_entries = mcobject_create();
    if(selectors->mcobject_list_entries == NULL)
        return MyCSS_STATUS_ERROR_SELECTORS_LIST_CREATE;
    
    myhtml_status = mcobject_init(selectors->mcobject_list_entries, 256, sizeof(mycss_selectors_list_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_SELECTORS_LIST_INIT;
    
    return MyCSS_STATUS_OK;
}

void mycss_selectors_clean(mycss_selectors_t* selectors)
{
    selectors->entry      = NULL;
    selectors->entry_last = NULL;
    selectors->list       = NULL;
    selectors->list_last  = NULL;
    selectors->combinator = NULL;
}

mystatus_t mycss_selectors_clean_all(mycss_selectors_t* selectors)
{
    selectors->entry      = NULL;
    selectors->entry_last = NULL;
    selectors->list       = NULL;
    selectors->list_last  = NULL;
    selectors->combinator = NULL;
    
    mcobject_clean(selectors->mcobject_entries);
    mcobject_clean(selectors->mcobject_list_entries);
    
    return MyCSS_STATUS_OK;
}

mycss_selectors_t * mycss_selectors_destroy(mycss_selectors_t* selectors, bool self_destroy)
{
    if(selectors == NULL)
        return NULL;
    
    selectors->mcobject_entries = mcobject_destroy(selectors->mcobject_entries, true);
    selectors->mcobject_list_entries = mcobject_destroy(selectors->mcobject_list_entries, true);
    
    if(self_destroy) {
        mycore_free(selectors);
        return NULL;
    }
    
    return selectors;
}

void mycss_selectors_entry_clean(mycss_selectors_entry_t* sel_entry)
{
    memset(sel_entry, 0, sizeof(mycss_selectors_entry_t));
}

mycss_token_t * mycss_selectors_parse_token_callback(mycss_entry_t* entry, mycss_token_t* token)
{
    if(token->type == MyCSS_TOKEN_TYPE_COMMENT)
        return token;
    
    bool last_response = true;
    while((last_response = entry->parser(entry, token, last_response)) == false) {};
    
    return entry->token;
}

mycss_selectors_list_t * mycss_selectors_parse_by_function(mycss_selectors_t* selectors, mycss_parser_token_f func, myencoding_t encoding, const char* data, size_t data_size, mystatus_t* out_status)
{
    mycss_entry_t *entry = selectors->ref_entry;
    
    mycss_entry_clean(entry);
    
    entry->token_ready_callback      = mycss_selectors_parse_token_callback;
    entry->parser                    = func;
    entry->parser_original           = NULL;
    entry->parser_switch             = NULL;
    entry->state                     = MyCSS_TOKENIZER_STATE_DATA;
    entry->state_back                = MyCSS_TOKENIZER_STATE_DATA;
    entry->selectors->ending_token   = MyCSS_TOKEN_TYPE_UNDEF;
    
    mycss_selectors_list_t *list = NULL;
    selectors->list = &list;

    /* parsing */
    mycss_encoding_set(entry, encoding);
    
    mystatus_t status = mycss_tokenizer_chunk(entry, data, data_size);
    if(status != MyCSS_STATUS_OK) {
        if(out_status)
            *out_status = status;
        
        return NULL;
    }
    
    status = mycss_tokenizer_end(entry);
    
    if(out_status)
        *out_status = status;
    
    if(list)
        return list;

    return NULL;
}

mycss_selectors_list_t * mycss_selectors_parse(mycss_selectors_t* selectors, myencoding_t encoding, const char* data, size_t data_size, mystatus_t* out_status)
{
    return mycss_selectors_parse_by_function(selectors, mycss_selectors_state_complex_selector_list, encoding, data, data_size, out_status);
}

mycss_selectors_entry_t * mycss_selectors_entry_find_first(mycss_selectors_entry_t* selector)
{
    while(selector->prev)
        selector = selector->prev;
    
    return selector;
}

mycss_selectors_entry_t * mycss_selectors_entry_create(mycss_selectors_t* selectors)
{
    mycss_selectors_entry_t* selector = mcobject_malloc(selectors->mcobject_entries, NULL);
    mycss_selectors_entry_clean(selector);
    
    return selector;
}

mycss_selectors_entry_t * mycss_selectors_entry_destroy(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, bool self_destroy)
{
    if(selector == NULL)
        return NULL;
    
    if(selector->key) {
        mycore_string_destroy(selector->key, false);
        mcobject_free(selectors->ref_entry->mcobject_string_entries, selector->key);
    }
    
    if(selector->value) {
        selector->value = mycss_selector_value_destroy(selectors->ref_entry, selector->type, selector->sub_type, selector->value, true);
    }
    
    if(self_destroy) {
        mcobject_free(selectors->mcobject_entries, selector);
        return NULL;
    }
    
    return selector;
}

void * mycss_selectors_entry_value_destroy(mycss_entry_t* entry, mycss_selectors_entry_t* selector_entry, bool destroy_self)
{
    return mycss_selector_value_destroy(entry, selector_entry->type, selector_entry->sub_type, selector_entry->value, destroy_self);
}

mycss_selectors_entries_list_t * mycss_selectors_entries_list_create(mycss_selectors_t* selectors)
{
    mycss_entry_t* entry = selectors->ref_entry;
    
    return (mycss_selectors_entries_list_t*) mchar_async_malloc(entry->mchar,
                                                          entry->mchar_value_node_id,
                                                          sizeof(mycss_selectors_entries_list_t));
}

mycss_selectors_entries_list_t * mycss_selectors_entries_list_add_one(mycss_selectors_t* selectors, mycss_selectors_entries_list_t* entries, size_t current_size)
{
    mycss_entry_t* entry = selectors->ref_entry;
    size_t current_size_char = current_size * sizeof(mycss_selectors_entries_list_t);
    
    return (mycss_selectors_entries_list_t*)
    mchar_async_realloc(entry->mchar, entry->mchar_value_node_id,
                        (char*)entries, current_size_char, (current_size_char + sizeof(mycss_selectors_entries_list_t)));
}

mycss_selectors_entries_list_t * mycss_selectors_entries_list_destroy(mycss_selectors_t* selectors, mycss_selectors_entries_list_t* entries)
{
    mycss_entry_t* entry = selectors->ref_entry;
    mchar_async_free(entry->mchar, entry->mchar_value_node_id, (char*)entries);
    
    return NULL;
}

mycss_selectors_entry_t * mycss_selectors_entry(mycss_selectors_t* selectors)
{
    if(selectors->entry == NULL)
        return NULL;
    
    return *selectors->entry;
}

void mycss_selectors_entry_append_to_current(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector)
{
    if(selectors->entry_last) {
        selectors->entry_last->next = selector;
        selector->prev = selectors->entry_last;
    }
    else {
        (*selectors->entry) = selector;
    }
    
    selectors->entry_last = selector;
}


