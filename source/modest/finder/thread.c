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

#include "modest/finder/thread.h"

/* private functions */
#ifndef MyCORE_BUILD_WITHOUT_THREADS
static void modest_finder_thread_stream(mythread_id_t thread_id, void* arg);
#else
static void modest_finder_thread_stream_single(modest_finder_thread_t* finder_thread, mycss_selectors_list_t* selector_list);
#endif

static modest_finder_thread_context_t * modest_finder_thread_create_context(modest_finder_thread_t* finder_thread, size_t count);
//static void modest_finder_thread_callback_found(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list,
//                                                mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx);

/* basic functions */
modest_finder_thread_t * modest_finder_thread_create(void)
{
    return (modest_finder_thread_t*)mycore_calloc(1, sizeof(modest_finder_thread_t));
}

mystatus_t modest_finder_thread_init(modest_finder_t* finder, modest_finder_thread_t* finder_thread, size_t thread_count)
{
#ifdef MyCORE_BUILD_WITHOUT_THREADS
    thread_count = 1;
#endif
    
    finder_thread->finder = finder;
    
    /* objects for nodes */
    finder_thread->entry_obj = mcobject_async_create();
    if(finder_thread->entry_obj == NULL)
        return MODEST_STATUS_OK;
    
    mcobject_async_status_t mcstatus = mcobject_async_init(finder_thread->entry_obj, 128, 1024, sizeof(modest_finder_thread_entry_t));
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    /* objects for declarations */
    finder_thread->declaration_obj = mcobject_async_create();
    if(finder_thread->declaration_obj == NULL)
        return MODEST_STATUS_OK;
    
    mcstatus = mcobject_async_init(finder_thread->declaration_obj, 128, 1024, sizeof(modest_finder_thread_declaration_t));
    if(mcstatus)
        return MODEST_STATUS_OK;
    
    finder_thread->context_list = modest_finder_thread_create_context(finder_thread, thread_count);
    if(finder_thread->context_list == NULL)
        return MODEST_STATUS_OK;
    
    /* create and init threads */
#ifdef MyCORE_BUILD_WITHOUT_THREADS
    finder_thread->thread = NULL;
#else
    finder_thread->thread = mythread_create();
    
    if(finder_thread->thread == NULL)
        return MODEST_STATUS_OK;
    
    mystatus_t status = mythread_init(finder_thread->thread, MyTHREAD_TYPE_STREAM, thread_count, 0);
    if(status) {
        mythread_destroy(finder_thread->thread, NULL, NULL, true);
        return MODEST_STATUS_OK;
    }
    
    finder_thread->thread->context = finder_thread;
    
    /* create threads */
    for(size_t i = 0; i < finder_thread->thread->entries_size; i++) {
        myhread_entry_create(finder_thread->thread, mythread_function, modest_finder_thread_stream, MyTHREAD_OPT_STOP);
    }
#endif
    
    return MODEST_STATUS_OK;
}

void modest_finder_thread_clean(modest_finder_thread_t* finder_thread, bool self_destroy)
{
    for(size_t i = 1; i < finder_thread->context_list_size; i++) {
        mcobject_async_node_clean(finder_thread->entry_obj, finder_thread->context_list[i].entry_node_id);
        mcobject_async_node_clean(finder_thread->declaration_obj, finder_thread->context_list[i].declaration_node_id);
    }
}

modest_finder_thread_t * modest_finder_thread_destroy(modest_finder_thread_t* finder_thread, bool self_destroy)
{
    if(finder_thread == NULL)
        return NULL;
    
#ifndef MyCORE_BUILD_WITHOUT_THREADS
    if(finder_thread->thread) {
        finder_thread->thread = mythread_destroy(finder_thread->thread, mythread_callback_quit, NULL, true);
    }
#endif
    
    finder_thread->entry_obj = mcobject_async_destroy(finder_thread->entry_obj, true);
    finder_thread->declaration_obj = mcobject_async_destroy(finder_thread->declaration_obj, true);
    
    if(finder_thread->context_list) {
        mycore_free(finder_thread->context_list);
        
        finder_thread->context_list = NULL;
        finder_thread->context_list_size = 0;
    }
    
    if(self_destroy) {
        mycore_free(finder_thread);
        return NULL;
    }
    
    return finder_thread;
}

void modest_finder_thread_collate_node(modest_t* modest, myhtml_tree_node_t* node, modest_finder_thread_entry_t* entry)
{
    modest_finder_thread_declaration_t* dec = entry->declaration;
    
    while(dec) {
        if(dec->entry)
            modest_style_map_collate_declaration(modest, node, dec->entry, dec->entry->type, &dec->raw_spec);
        
        dec = dec->next;
    }
}

#ifdef MyCORE_BUILD_WITHOUT_THREADS
mystatus_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread,
                                        myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list)
{
    finder_thread->base_node = scope_node;
    finder_thread->selector_list = selector_list;
    
    if(finder_thread->finder == NULL)
        return MODEST_STATUS_ERROR;
    
    modest_finder_thread_stream_single(finder_thread, selector_list);
    
    /* calc result */
    modest_finder_thread_context_t* context = finder_thread->context_list;
    myhtml_tree_node_t* node = scope_node;
    
    /* compare results */
    while(node) {
        modest_finder_thread_entry_t* entry = context->entry;
        
        while(entry) {
            if(entry->node == node)
            {
                if(entry->next)
                    entry->next->prev = entry->prev;
                else
                    context->entry_last = entry->prev;
                
                if(entry->prev)
                    entry->prev->next = entry->next;
                else
                    context->entry = entry->next;
                
                modest_finder_thread_collate_node(modest, node, entry);
            }
            
            entry = entry->next;
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != scope_node && node->next == NULL)
                node = node->parent;
            
            if(node == scope_node)
                break;
            
            node = node->next;
        }
    }
    
    return MyCORE_STATUS_OK;
}

#else /* end def MyCORE_BUILD_WITHOUT_THREADS */
mystatus_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread,
                                        myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list)
{
    finder_thread->base_node = scope_node;
    finder_thread->selector_list = selector_list;
    
    if(finder_thread->finder == NULL)
        return MODEST_STATUS_ERROR;
    
    mythread_resume(finder_thread->thread, MyTHREAD_OPT_UNDEF);
    modest_finder_thread_wait_for_all_done(finder_thread);
    
    /* calc result */
    modest_finder_thread_context_t* context_list = finder_thread->context_list;
    myhtml_tree_node_t* node = scope_node;
    
    /* compare results */
    while(node) {
        for(size_t i = 0; i < finder_thread->thread->entries_length; i++)
        {
            modest_finder_thread_context_t* context = &context_list[i];
            modest_finder_thread_entry_t* entry = context->entry;
            
            while(entry) {
                if(entry->node == node)
                {
                    if(entry->next)
                        entry->next->prev = entry->prev;
                    else
                        context->entry_last = entry->prev;
                    
                    if(entry->prev)
                        entry->prev->next = entry->next;
                    else
                        context->entry = entry->next;
                    
                    modest_finder_thread_collate_node(modest, node, entry);
                }
                
                entry = entry->next;
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != scope_node && node->next == NULL)
                node = node->parent;
            
            if(node == scope_node)
                break;
            
            node = node->next;
        }
    }
    
    return MODEST_STATUS_OK;
}

void modest_finder_thread_wait_for_all_done(modest_finder_thread_t* finder_thread)
{
    for (size_t idx = 0; idx < finder_thread->thread->entries_length; idx++) {
        while((finder_thread->thread->entries[idx].context.opt & MyTHREAD_OPT_DONE) == 0) {
            mythread_nanosleep_sleep(finder_thread->thread->timespec);
        }
    }
}
#endif /* if undef MyCORE_BUILD_WITHOUT_THREADS */

modest_finder_thread_context_t * modest_finder_thread_create_context(modest_finder_thread_t* finder_thread, size_t count)
{
    finder_thread->context_list_size = count;
    
    modest_finder_thread_context_t *ctx = mycore_calloc(count, sizeof(modest_finder_thread_context_t));
    
    if(ctx == NULL)
        return NULL;
    
    mcobject_async_status_t mcstatus;
    
    for(size_t i = 0; i < count; i++) {
        ctx[i].entry_node_id = mcobject_async_node_add(finder_thread->entry_obj, &mcstatus);
        
        if(mcstatus) {
            while(i) {
                i--;
                mcobject_async_node_delete(finder_thread->entry_obj, ctx[i].entry_node_id);
            }
            
            mycore_free(ctx);
            return NULL;
        }
    }
    
    for(size_t i = 0; i < count; i++) {
        ctx[i].declaration_node_id = mcobject_async_node_add(finder_thread->declaration_obj, &mcstatus);
        
        if(mcstatus) {
            size_t t = count;
            while(t > 1) {
                t--;
                mcobject_async_node_delete(finder_thread->entry_obj, ctx[t].entry_node_id);
            }
            
            while(i > 1) {
                i--;
                mcobject_async_node_delete(finder_thread->declaration_obj, ctx[i].declaration_node_id);
            }
            
            mycore_free(ctx);
            return NULL;
        }
    }
    
    return ctx;
}

bool modest_finder_thread_spec_is_up(modest_style_raw_specificity_t* spec_f, modest_style_raw_specificity_t* spec_t)
{
    if(spec_f->x > spec_t->x)
        return true;
    else if(spec_f->x < spec_t->x)
        return false;
    
    if(spec_f->a > spec_t->a)
        return true;
    else if(spec_f->a < spec_t->a)
        return false;
    
    if(spec_f->b > spec_t->b)
        return true;
    else if(spec_f->b < spec_t->b)
        return false;
    
    if(spec_f->c > spec_t->c)
        return true;
    else if(spec_f->c < spec_t->c)
        return false;
    
    /* when a property is repeated with multiple values take the last one*/
    return true;
}

void modest_finder_thread_declaratin_append(modest_finder_thread_found_context_t* found_context, bool is_low_priority,
                                            modest_finder_thread_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                            modest_style_raw_specificity_t* raw_spec)
{
    if(entry->declaration == NULL) {
        entry->declaration = entry->declaration_last = mcobject_async_malloc(found_context->finder_thread->declaration_obj,
                                                                             found_context->context->declaration_node_id, NULL);
        
        entry->declaration->entry     = dec_entry;
        entry->declaration->raw_spec  = *raw_spec;
        entry->declaration->next      = NULL;
        entry->declaration->prev      = NULL;
        
        return;
    }
    
    modest_finder_thread_declaration_t* thr_dec = entry->declaration;
    
    while(thr_dec) {
        if(thr_dec->entry->type == dec_entry->type)
        {
            if(modest_finder_thread_spec_is_up(raw_spec, &thr_dec->raw_spec)) {
                thr_dec->entry    = dec_entry;
                thr_dec->raw_spec = *raw_spec;
            }
            
            return;
        }
        
        thr_dec = thr_dec->next;
    }
    
    thr_dec = mcobject_async_malloc(found_context->finder_thread->declaration_obj,
                                    found_context->context->declaration_node_id, NULL);
    
    thr_dec->next     = NULL;
    thr_dec->entry    = dec_entry;
    thr_dec->raw_spec = *raw_spec;
    
    entry->declaration_last->next = thr_dec;
    thr_dec->prev = entry->declaration_last;
    
    entry->declaration_last = thr_dec;
}

void modest_finder_thread_declaratin_list_replace(modest_finder_thread_found_context_t* found_context,
                                                  modest_finder_thread_entry_t* entry, mycss_declaration_entry_t* dec_entry,
                                                  mycss_selectors_specificity_t* spec)
{
    while(dec_entry) {
        modest_style_raw_specificity_t raw_spec = {((unsigned int)dec_entry->is_important), spec->a, spec->b, spec->c};
        
        modest_finder_thread_declaratin_append(found_context, false, entry, dec_entry, &raw_spec);
        
        dec_entry = dec_entry->next;
    }
}

void modest_finder_thread_callback_found(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx)
{
    modest_finder_thread_found_context_t* found_context = (modest_finder_thread_found_context_t*)ctx;
    modest_finder_thread_context_t* thread_context = found_context->context;
    
    if(thread_context->entry_last) {
        modest_finder_thread_entry_t* entry = thread_context->entry;
        
        while(entry)
        {
            if(entry->node == node) {
                modest_finder_thread_declaratin_list_replace(found_context, entry, selector_list->declaration_entry, spec);
                return;
            }
            
            entry = entry->next;
        }
    }
    
    modest_finder_thread_entry_t* entry = mcobject_async_malloc(found_context->finder_thread->entry_obj, thread_context->entry_node_id, NULL);
    memset(entry, 0, sizeof(modest_finder_thread_entry_t));
    
    entry->node = node;
    
    modest_finder_thread_declaratin_list_replace(found_context, entry, selector_list->declaration_entry, spec);
    
    if(thread_context->entry_last) {
        entry->prev = thread_context->entry_last;
        
        thread_context->entry_last->next = entry;
        thread_context->entry_last = entry;
    }
    else {
        thread_context->entry_last = thread_context->entry = entry;
    }
}

void modest_finder_thread_stream_single(modest_finder_thread_t* finder_thread, mycss_selectors_list_t* selector_list)
{
    modest_finder_thread_found_context_t found_ctx = {finder_thread, finder_thread->context_list};
    
    while(selector_list)
    {
        for(size_t i = 0; i < selector_list->entries_list_length; i++) {
            mycss_selectors_entries_list_t *entries = &selector_list->entries_list[i];
            mycss_selectors_specificity_t spec = entries->specificity;
            
            modest_finder_node_combinator_begin(finder_thread->finder, finder_thread->base_node, selector_list,
                                                entries->entry, &spec, modest_finder_thread_callback_found, &found_ctx);
        }
        
        selector_list = selector_list->next;
    }
}

#ifndef MyCORE_BUILD_WITHOUT_THREADS
void modest_finder_thread_stream(mythread_id_t thread_id, void* arg)
{
    mythread_context_t* ctx = (mythread_context_t*)arg;
    modest_finder_thread_t* finder_thread = (modest_finder_thread_t*)ctx->mythread->context;
    mycss_selectors_list_t* selector_list = finder_thread->selector_list;
    
    modest_finder_thread_found_context_t found_ctx = {finder_thread, &finder_thread->context_list[ctx->id]};
    
    size_t count = 0, counnt_done = ctx->id - 1;
    size_t offset = (ctx->mythread->entries_size - 1);
    
    while(selector_list) {
        for(size_t i = 0; i < selector_list->entries_list_length; i++) {
            /* split selectors by thread id */
            if(count == counnt_done) {
                mycss_selectors_entries_list_t *entries = &selector_list->entries_list[i];
                mycss_selectors_specificity_t spec = entries->specificity;
                
                modest_finder_node_combinator_begin(finder_thread->finder, finder_thread->base_node, selector_list,
                                                    entries->entry, &spec, modest_finder_thread_callback_found, &found_ctx);
                
                counnt_done += offset;
            }
            
            count++;
        }
        
        selector_list = selector_list->next;
    }
}
#endif

