/*
 Copyright (C) 2016 Alexander Borisov
 
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
static void modest_finder_thread_stream(mythread_id_t thread_id, void* arg);
static modest_finder_thread_context_t * modest_finder_thread_create_context(modest_finder_thread_t* finder_thread, size_t count);
//static void modest_finder_thread_callback_found(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_list_t* selector_list,
//                                                mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec, void* ctx);

/* basic functions */
modest_finder_thread_t * modest_finder_thread_create(void)
{
    return (modest_finder_thread_t*)myhtml_calloc(1, sizeof(modest_finder_thread_t));
}

modest_status_t modest_finder_thread_init(modest_finder_t* finder, modest_finder_thread_t* finder_thread, size_t thread_count)
{
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
    finder_thread->thread = mythread_create();
    
    if(finder_thread->thread == NULL)
        return MODEST_STATUS_OK;
    
    myhtml_status_t status = mythread_init(finder_thread->thread, "lastmac", thread_count);
    if(status) {
        mythread_destroy(finder_thread->thread, NULL, true);
        return MODEST_STATUS_OK;
    }
    
    finder_thread->thread->context = finder_thread;
    
    /* create threads */
    for(size_t i = finder_thread->thread->pth_list_root; i < finder_thread->thread->pth_list_size; i++) {
        myhread_create_stream(finder_thread->thread, mythread_function, modest_finder_thread_stream, MyTHREAD_OPT_UNDEF, &status);
    }
    
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
    
    finder_thread->entry_obj = mcobject_async_destroy(finder_thread->entry_obj, true);
    finder_thread->declaration_obj = mcobject_async_destroy(finder_thread->declaration_obj, true);
    
    if(finder_thread->thread) {
        finder_thread->thread->stream_opt = MyTHREAD_OPT_QUIT;
        
        for(size_t i = finder_thread->thread->pth_list_root; i < finder_thread->thread->pth_list_size; i++) {
            finder_thread->thread->pth_list[i].data.opt = MyTHREAD_OPT_QUIT;
        }
        
        finder_thread->thread = mythread_destroy(finder_thread->thread, NULL, true);
    }
    
    if(finder_thread->context_list) {
        myhtml_free(finder_thread->context_list);
        
        finder_thread->context_list = NULL;
        finder_thread->context_list_size = 0;
    }
    
    if(self_destroy) {
        myhtml_free(finder_thread);
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

modest_status_t modest_finder_thread_process(modest_t* modest, modest_finder_thread_t* finder_thread, myhtml_tree_t* myhtml_tree,
                                             myhtml_tree_node_t* scope_node, mycss_selectors_list_t* selector_list)
{
    finder_thread->base_node = scope_node;
    finder_thread->selector_list = selector_list;
    
    if(finder_thread->finder == NULL)
        return MODEST_STATUS_ERROR;
    
    finder_thread->finder->html_tree = myhtml_tree;
    
    mythread_resume_all(finder_thread->thread);
    modest_finder_thread_wait_for_all_done(finder_thread);
    
    /* calc result */
    modest_finder_thread_context_t* context_list = finder_thread->context_list;
    myhtml_tree_node_t* node = scope_node;
    
    /* compare results */
    while(node) {
        for(size_t i = finder_thread->thread->pth_list_root; i < finder_thread->thread->pth_list_size; i++)
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
    const struct timespec tomeout = {0, 0};
    
    for (size_t idx = finder_thread->thread->pth_list_root; idx < finder_thread->thread->pth_list_size; idx++) {
        while((finder_thread->thread->pth_list[idx].data.opt & MyTHREAD_OPT_DONE) == 0) {
            myhtml_thread_nanosleep(&tomeout);
        }
    }
}

modest_finder_thread_context_t * modest_finder_thread_create_context(modest_finder_thread_t* finder_thread, size_t count)
{
    /* +1 because threads ids begin 1 */
    count++;
    finder_thread->context_list_size = count;
    
    modest_finder_thread_context_t *ctx = myhtml_calloc(count, sizeof(modest_finder_thread_context_t));
    
    if(ctx == NULL)
        return NULL;
    
    mcobject_async_status_t mcstatus;
    
    for(size_t i = 1; i < count; i++) {
        ctx[i].entry_node_id = mcobject_async_node_add(finder_thread->entry_obj, &mcstatus);
        
        if(mcstatus) {
            while(i) {
                i--;
                mcobject_async_node_delete(finder_thread->entry_obj, ctx[i].entry_node_id);
            }
            
            return NULL;
        }
    }
    
    for(size_t i = 1; i < count; i++) {
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
    
    return false;
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

void modest_finder_thread_stream(mythread_id_t thread_id, void* arg)
{
    mythread_context_t* ctx = (mythread_context_t*)arg;
    modest_finder_thread_t* finder_thread = (modest_finder_thread_t*)ctx->mythread->context;
    mycss_selectors_list_t* selector_list = finder_thread->selector_list;
    
    modest_finder_thread_found_context_t found_ctx = {finder_thread, &finder_thread->context_list[ctx->id]};
    
    size_t count = 0, counnt_done = ctx->id - 1;
    size_t offset = (ctx->mythread->pth_list_size - 1);
    
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
    
    ctx->opt = MyTHREAD_OPT_STOP|MyTHREAD_OPT_DONE;
}


