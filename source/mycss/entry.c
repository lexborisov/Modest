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

#include "mycss/entry.h"
#include "mycss/selectors/function_resource.h"

mycss_entry_t * mycss_entry_create(void)
{
    return (mycss_entry_t*)mycore_calloc(1, sizeof(mycss_entry_t));
}

mystatus_t mycss_entry_init(mycss_t* mycss, mycss_entry_t* entry)
{
    mystatus_t status;
    
    entry->mycss               = mycss;
    entry->parser              = NULL;
    entry->parser_switch       = NULL;
    entry->parser_original     = NULL;
    entry->parser_ending_token = MyCSS_TOKEN_TYPE_UNDEF;
    
    // Other init
    entry->mchar = mchar_async_create();
    if(entry->mchar == NULL)
        return MyCORE_STATUS_ERROR_MEMORY_ALLOCATION;
    
    if((status = mchar_async_init(entry->mchar, 128, (4096 * 5))))
        return status;
    
    /* init data nodes for save input char* */
    entry->mchar_node_id = mchar_async_node_add(entry->mchar, &status);
    if(status)
        return status;
    
    entry->mchar_value_node_id = mchar_async_node_add(entry->mchar, &status);
    if(status)
        return status;
    
    entry->parser_list = mycss_entry_parser_list_create_and_init(128);
    
    if(entry->parser_list == NULL)
        return MyCSS_STATUS_ERROR_PARSER_LIST_CREATE;
    
    /* String Entries */
    entry->mcobject_string_entries = mcobject_create();
    if(entry->mcobject_string_entries == NULL)
        return MyCSS_STATUS_ERROR_STRING_CREATE;
    
    mystatus_t myhtml_status = mcobject_init(entry->mcobject_string_entries, 256, sizeof(mycore_string_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_STRING_INIT;
    
    /* Selectors */
    entry->selectors = mycss_selectors_create();
    if(entry->selectors == NULL)
        return MyCSS_STATUS_ERROR_SELECTORS_CREATE;
    
    status = mycss_selectors_init(entry, entry->selectors);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    /* Namespace */
    entry->ns = mycss_namespace_create();
    if(entry->ns == NULL)
        return MyCSS_STATUS_ERROR_NAMESPACE_CREATE;
    
    status = mycss_namespace_init(entry, entry->ns);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    /* An+B */
    entry->anb = mycss_an_plus_b_create();
    if(entry->ns == NULL)
        return MyCSS_STATUS_ERROR_AN_PLUS_B_CREATE;
    
    status = mycss_an_plus_b_init(entry, entry->anb);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    /* Media */
    entry->media = mycss_media_create();
    if(entry->media == NULL)
        return MyCSS_STATUS_ERROR_MEDIA_CREATE;
    
    status = mycss_media_init(entry, entry->media);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    /* Declaration */
    entry->declaration = mycss_declaration_create();
    if(entry->declaration == NULL)
        return MyCSS_STATUS_ERROR_DECLARATION_CREATE;
    
    status = mycss_declaration_init(entry, entry->declaration);
    if(status != MyCSS_STATUS_OK)
        return status;
    
    /* Incoming Buffer */
    entry->mcobject_incoming_buffer = mcobject_create();
    if(entry->mcobject_incoming_buffer == NULL)
        return MyCSS_STATUS_ERROR_ENTRY_INCOMING_BUFFER_CREATE;
    
    myhtml_status = mcobject_init(entry->mcobject_incoming_buffer, 256, sizeof(mycore_incoming_buffer_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_ENTRY_INCOMING_BUFFER_INIT;
    
    /* callbacks */
    entry->token_ready_callback = mycss_parser_token_ready_callback_function;
    
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_entry_clean(mycss_entry_t* entry)
{
    mcobject_clean(entry->mcobject_incoming_buffer);
    mycss_entry_parser_list_clean(entry->parser_list);
    
    /* CSS Modules */
    mycss_selectors_clean(entry->selectors);
    mycss_namespace_clean(entry->ns);
    mycss_declaration_clean(entry->declaration);
    
    entry->parser               = NULL;
    entry->parser_switch        = NULL;
    entry->parser_original      = NULL;
    entry->parser_ending_token  = MyCSS_TOKEN_TYPE_UNDEF;
    entry->state                = MyCSS_TOKENIZER_STATE_DATA;
    entry->state_back           = MyCSS_TOKENIZER_STATE_DATA;
    entry->first_buffer         = NULL;
    entry->current_buffer       = NULL;
    entry->token_counter        = 0;
    entry->help_counter         = 0;
    entry->type                 = MyCSS_ENTRY_TYPE_CLEAN;
    
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_entry_clean_all(mycss_entry_t* entry)
{
    mcobject_clean(entry->mcobject_incoming_buffer);
    mchar_async_node_clean(entry->mchar, entry->mchar_node_id);
    mchar_async_node_clean(entry->mchar, entry->mchar_value_node_id);
    
    mycss_entry_parser_list_clean(entry->parser_list);
    
    mcobject_clean(entry->mcobject_string_entries);
    
    /* CSS Modules */
    mycss_selectors_clean_all(entry->selectors);
    mycss_namespace_clean_all(entry->ns);
    mycss_an_plus_b_clean_all(entry->anb);
    mycss_media_clean_all(entry->media);
    mycss_declaration_clean_all(entry->declaration);
    
    entry->parser               = NULL;
    entry->parser_switch        = NULL;
    entry->parser_original      = NULL;
    entry->parser_ending_token  = MyCSS_TOKEN_TYPE_UNDEF;
    entry->state                = MyCSS_TOKENIZER_STATE_DATA;
    entry->state_back           = MyCSS_TOKENIZER_STATE_DATA;
    entry->first_buffer         = NULL;
    entry->current_buffer       = NULL;
    entry->token_counter        = 0;
    entry->help_counter         = 0;
    entry->type                 = MyCSS_ENTRY_TYPE_CLEAN;
    
    return MyCSS_STATUS_OK;
}

mycss_entry_t * mycss_entry_destroy(mycss_entry_t* entry, bool self_destroy)
{
    if(entry == NULL)
        return NULL;
    
    entry->mchar = mchar_async_destroy(entry->mchar, 1);
    entry->mcobject_string_entries = mcobject_destroy(entry->mcobject_string_entries, true);
    entry->parser_list = mycss_entry_parser_list_destroy(entry->parser_list, true);
    
    /* CSS Modules */
    entry->selectors   = mycss_selectors_destroy(entry->selectors, true);
    entry->ns          = mycss_namespace_destroy(entry->ns, true);
    entry->anb         = mycss_an_plus_b_destroy(entry->anb, true);
    entry->media       = mycss_media_destroy(entry->media, true);
    entry->declaration = mycss_declaration_destroy(entry->declaration, true);
    
    entry->mcobject_incoming_buffer = mcobject_destroy(entry->mcobject_incoming_buffer, true);
    
    if(entry->token) {
        mycore_free(entry->token);
        entry->token = NULL;
    }
    
    if(self_destroy) {
        mycore_free(entry);
        return NULL;
    }
    
    return entry;
}

void mycss_entry_end(mycss_entry_t* entry)
{
    /* need some code */
}

/* api */
mycss_selectors_t * mycss_entry_selectors(mycss_entry_t* entry)
{
    return entry->selectors;
}

mycore_string_t * mycss_entry_string_create_and_init(mycss_entry_t* entry, size_t string_size)
{
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    
    if(str == NULL)
        return NULL;
    
    mycore_string_init(entry->mchar, entry->mchar_node_id, str, (string_size + 1));
    
    return str;
}

mycss_token_ready_callback_f mycss_entry_token_ready_callback(mycss_entry_t* entry, mycss_token_ready_callback_f callback_f)
{
    if(callback_f)
        entry->token_ready_callback = callback_f;
    
    return entry->token_ready_callback;
}

size_t mycss_entry_token_count(mycss_entry_t* entry)
{
    return entry->token_counter;
}

mycore_incoming_buffer_t * mycss_entry_incoming_buffer_current(mycss_entry_t* entry)
{
    return entry->current_buffer;
}

mycore_incoming_buffer_t * mycss_entry_incoming_buffer_first(mycss_entry_t* entry)
{
    return entry->first_buffer;
}

mycss_stylesheet_t * mycss_entry_stylesheet(mycss_entry_t* entry)
{
    return entry->stylesheet;
}

mycss_selectors_list_t * mycss_entry_current_selectors_list(mycss_entry_t* entry)
{
    return entry->selectors->list_last;
}

void mycss_entry_parser_set(mycss_entry_t* entry, mycss_parser_token_f parser)
{
    entry->parser = parser;
}

void mycss_entry_parser_switch_set(mycss_entry_t* entry, mycss_parser_token_f parser_switch)
{
    entry->parser_switch = parser_switch;
}

void mycss_entry_parser_original_set(mycss_entry_t* entry, mycss_parser_token_f parser_original)
{
    entry->parser_original = parser_original;
}

/* parser list */
mycss_entry_parser_list_t * mycss_entry_parser_list_create_and_init(size_t size)
{
    mycss_entry_parser_list_t* parser_list = mycore_malloc(sizeof(mycss_entry_parser_list_t));
    
    if(parser_list == NULL)
        return NULL;
    
    parser_list->length = 0;
    parser_list->size   = size;
    parser_list->list   = mycore_malloc(parser_list->size * sizeof(mycss_entry_parser_list_entry_t));
    
    if(parser_list->list == NULL) {
        mycore_free(parser_list);
        return NULL;
    }
    
    return parser_list;
}

void mycss_entry_parser_list_clean(mycss_entry_parser_list_t* parser_list)
{
    parser_list->length = 0;
}

mycss_entry_parser_list_t * mycss_entry_parser_list_destroy(mycss_entry_parser_list_t* parser_list, bool self_destroy)
{
    if(parser_list == NULL)
        return NULL;
    
    if(parser_list->list) {
        mycore_free(parser_list->list);
        parser_list->list = NULL;
    }
    
    if(self_destroy) {
        mycore_free(parser_list);
        return NULL;
    }
    
    return parser_list;
}

mystatus_t mycss_entry_parser_list_push(mycss_entry_t* entry, mycss_parser_token_f parser_func,
                                            mycss_parser_token_f parser_switch, mycss_token_type_t ending_token,
                                            bool is_local)
{
    mycss_entry_parser_list_t *parser_list = entry->parser_list;
    
    if(parser_list->length >= parser_list->size) {
        size_t new_size = parser_list->length + 1024;
        
        mycss_entry_parser_list_entry_t *new_list = mycore_realloc(parser_list->list, new_size * sizeof(mycss_entry_parser_list_entry_t));
        
        if(new_list) {
            parser_list->size = new_size;
            parser_list->list = new_list;
        }
        else
            return MyCSS_STATUS_ERROR_MEMORY_ALLOCATION;
    }
    
    mycss_entry_parser_list_entry_t *parser_list_entry = &parser_list->list[ parser_list->length ];
    
    parser_list_entry->parser        = parser_func;
    parser_list_entry->parser_switch = parser_switch;
    parser_list_entry->ending_token  = ending_token;
    parser_list_entry->is_local      = is_local;
    parser_list->length++;
    
    return MyCSS_STATUS_OK;
}

void mycss_entry_parser_list_pop(mycss_entry_t* entry)
{
    if(entry->parser_list->length == 0)
        return;
    
    mycss_entry_parser_list_t *parser_list = entry->parser_list;
    parser_list->length--;
    
    mycss_entry_parser_list_entry_t *list_entery = &parser_list->list[ parser_list->length ];
    
    if(entry->parser_ending_token != list_entery->ending_token)
        entry->parser_ending_token = list_entery->ending_token;
    
    entry->parser = list_entery->parser;
    entry->parser_switch = list_entery->parser_switch;
}

size_t mycss_entry_parser_list_length(mycss_entry_t* entry)
{
    return entry->parser_list->length;
}

mycss_token_type_t mycss_entry_parser_list_current_ending_token_type(mycss_entry_t* entry)
{
    return entry->parser_list->list[ (entry->parser_list->length - 1) ].ending_token;
}

mycss_parser_token_f mycss_entry_parser_list_current_parser(mycss_entry_t* entry)
{
    return entry->parser_list->list[ (entry->parser_list->length - 1) ].parser;
}

mycss_parser_token_f mycss_entry_parser_list_current_parser_switch(mycss_entry_t* entry)
{
    return entry->parser_list->list[ (entry->parser_list->length - 1) ].parser_switch;
}

bool mycss_entry_parser_list_current_is_local(mycss_entry_t* entry)
{
    return entry->parser_list->list[ (entry->parser_list->length - 1) ].is_local;
}

