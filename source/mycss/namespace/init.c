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

#include "mycss/namespace/init.h"

mycss_namespace_t * mycss_namespace_create(void)
{
    return (mycss_namespace_t*)mycore_calloc(1, sizeof(mycss_namespace_t));
}

mystatus_t mycss_namespace_init(mycss_entry_t* entry, mycss_namespace_t* ns)
{
    /* Objects Namespace */
    ns->mcobject_entries = mcobject_create();
    if(ns->mcobject_entries == NULL)
        return MyCSS_STATUS_ERROR_NAMESPACE_ENTRIES_CREATE;
    
    mystatus_t myhtml_status = mcobject_init(ns->mcobject_entries, 256, sizeof(mycss_namespace_entry_t));
    if(myhtml_status)
        return MyCSS_STATUS_ERROR_NAMESPACE_ENTRIES_INIT;
    
    return MyCSS_STATUS_OK;
}

void mycss_namespace_clean(mycss_namespace_t* ns)
{
    ns->entry = NULL;
}

mystatus_t mycss_namespace_clean_all(mycss_namespace_t* ns)
{
    mcobject_clean(ns->mcobject_entries);
    ns->entry = NULL;
    
    return MyCSS_STATUS_OK;
}

mycss_namespace_t * mycss_namespace_destroy(mycss_namespace_t* ns, bool self_destroy)
{
    if(ns == NULL)
        return NULL;
    
    ns->mcobject_entries = mcobject_destroy(ns->mcobject_entries, true);
    
    if(self_destroy) {
        mycore_free(ns);
        return NULL;
    }
    
    return ns;
}

mycss_namespace_entry_t * mycss_namespace_entry_create(mycss_namespace_t* ns)
{
    return mcobject_malloc(ns->mcobject_entries, NULL);
}

void mycss_namespace_entry_clean(mycss_namespace_entry_t* ns_entry)
{
    memset(ns_entry, 0, sizeof(mycss_namespace_entry_t));
}

mycss_namespace_entry_t * mycss_namespace_entry_destroy(mycss_namespace_entry_t* ns_entry, mycss_entry_t* entry, bool self_destroy)
{
    if(ns_entry->name) {
        mycore_string_destroy(ns_entry->name, false);
        mcobject_free(entry->mcobject_string_entries, ns_entry->name);
    }
    
    if(ns_entry->url) {
        mycore_string_destroy(ns_entry->url, false);
        mcobject_free(entry->mcobject_string_entries, ns_entry->url);
    }
    
    if(self_destroy) {
        mycore_free(ns_entry);
        return NULL;
    }
    
    return ns_entry;
}

void mycss_namespace_entry_append_to_current(mycss_namespace_t* ns, mycss_namespace_entry_t* ns_entry)
{
    if(ns->entry_last) {
        ns->entry_last->next = ns_entry;
        ns_entry->prev = ns->entry_last;
    }
    else {
        (*ns->entry) = ns_entry;
    }
    
    ns->entry_last = ns_entry;
}

mystatus_t mycss_namespace_stylesheet_init(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry)
{
    ns_stylesheet->name_tree = mctree_create(14);
    if(ns_stylesheet->name_tree == NULL)
        return MyCSS_STATUS_ERROR_NAMESPACE_CREATE;
    
    ns_stylesheet->ns_id_counter = 0;
    
    ns_stylesheet->entry_default = mycss_namespace_entry_create(entry->ns);
    if(ns_stylesheet->entry_default == NULL)
        return MyCSS_STATUS_ERROR_NAMESPACE_ENTRIES_CREATE;
    
    mycss_namespace_entry_clean(ns_stylesheet->entry_default);
    mycss_namespace_entry_clean(&ns_stylesheet->entry_undef);
    mycss_namespace_entry_clean(&ns_stylesheet->entry_any);
    
    /* init name for basic namespace entry; for default namespace entry name = NULL */
    ns_stylesheet->entry_undef.name = mycss_entry_string_create_and_init(entry, 2);
    if(ns_stylesheet->entry_undef.name == NULL)
        return MyCSS_STATUS_ERROR_STRING_CREATE;
    
    ns_stylesheet->entry_any.name = mycss_entry_string_create_and_init(entry, 2);
    if(ns_stylesheet->entry_any.name == NULL)
        return MyCSS_STATUS_ERROR_STRING_CREATE;
    
    mycore_string_append(ns_stylesheet->entry_any.name, "*", 1);
    ns_stylesheet->entry_any.ns_id = MyHTML_NAMESPACE_ANY;
    
    mycss_namespace_stylesheet_init_default(ns_stylesheet, entry, NULL, 0, MyHTML_NAMESPACE_ANY);
    
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_namespace_stylesheet_clean(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry)
{
    mctree_clean(ns_stylesheet->name_tree);
    ns_stylesheet->ns_id_counter = 0;
    
    mycss_namespace_stylesheet_init_default(ns_stylesheet, entry, NULL, 0, MyHTML_NAMESPACE_ANY);
    
    return MyCSS_STATUS_OK;
}

mycss_namespace_stylesheet_t * mycss_namespace_stylesheet_destroy(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry, bool self_destroy)
{
    mycss_namespace_entry_t* ns_entry = ns_stylesheet->entry_default;
    
    while(ns_entry) {
        mycss_namespace_entry_t* ns_entry_next = ns_entry->next;
        
        mycss_namespace_entry_destroy(ns_entry, entry, false);
        mcobject_free(entry->ns->mcobject_entries, ns_entry);
        
        ns_entry = ns_entry_next;
    }
    
    ns_stylesheet->name_tree = mctree_destroy(ns_stylesheet->name_tree);
    ns_stylesheet->entry_undef.name = mycore_string_destroy(ns_stylesheet->entry_undef.name, false);
    ns_stylesheet->entry_any.name = mycore_string_destroy(ns_stylesheet->entry_any.name, false);
    
    if(self_destroy) {
        mycore_free(ns_stylesheet);
        return NULL;
    }
    
    return ns_stylesheet;
}

mystatus_t mycss_namespace_stylesheet_init_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry, const char* url, size_t url_length, myhtml_namespace_t def_ns)
{
    mycore_string_t *str = ns_stylesheet->entry_default->url;
    
    if(str == NULL) {
        str = mcobject_malloc(entry->mcobject_string_entries, NULL);
        mycore_string_init(entry->mchar, entry->mchar_node_id, str, (url_length + 1));
        
        ns_stylesheet->entry_default->url = str;
    }
    else
        mycore_string_clean(str);
    
    if(url && url_length) {
        mycore_string_append(str, url, url_length);
        ns_stylesheet->entry_default->ns_id = myhtml_namespace_id_by_url(url, url_length);
    }
    else
        ns_stylesheet->entry_default->ns_id = def_ns;
    
    ns_stylesheet->entry_default->mctree_id = 0;
    ns_stylesheet->entry_default->name      = NULL;
    ns_stylesheet->entry_default->next      = NULL;
    ns_stylesheet->entry_default->prev      = NULL;
    
    return MyCSS_STATUS_OK;
}

void mycss_namespace_stylesheet_append_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_namespace_entry_t* ns_entry)
{
    if(ns_stylesheet->entry_default == NULL) {
        ns_stylesheet->entry_default = ns_entry;
        return;
    }
    
    mycss_namespace_entry_t* ns_entry_cur = ns_stylesheet->entry_default;
    
    while(ns_entry_cur->next)
        ns_entry_cur = ns_entry_cur->next;
    
    ns_entry_cur->next = ns_entry;
    ns_entry->prev = ns_entry_cur;
    
    ns_stylesheet->entry_default = ns_entry;
}

void mycss_namespace_stylesheet_destroy_default(mycss_namespace_stylesheet_t* ns_stylesheet, mycss_entry_t* entry)
{
    mycore_string_t *str = ns_stylesheet->entry_default->url;
    
    if(str) {
        mycore_string_destroy(str, false);
        mcobject_free(entry->mcobject_string_entries, str);
        
        ns_stylesheet->entry_default->url = NULL;
    }
}

const char * mycss_namespace_name_by_id(mycss_namespace_t* ns, mctree_t* name_tree, size_t ns_id, size_t* length)
{
    if(ns_id < MyHTML_NAMESPACE_LAST_ENTRY)
        return myhtml_namespace_name_by_id((myhtml_namespace_t)ns_id, length);
    
    ns_id -= MyHTML_NAMESPACE_LAST_ENTRY;
    
    mycss_namespace_entry_t *entry = (mycss_namespace_entry_t*)(name_tree->nodes[ ns_id ].value);
    
    if(length)
        *length = entry->name->length;
    
    return entry->name->data;
}

const char * mycss_namespace_name_by_entry(mycss_namespace_entry_t* ns_entry, mctree_t* name_tree, size_t* length, bool* is_default)
{
    if(ns_entry->name == NULL) {
        if(is_default)
            *is_default = true;
        
        if(length)
            *length = 0;
        
        if(ns_entry->ns_id <= MyHTML_NAMESPACE_LAST_ENTRY)
            return myhtml_namespace_name_by_id(ns_entry->ns_id, length);
        
        return NULL;
    }
    
    if(is_default)
        *is_default = false;
    
    if(length)
        *length = ns_entry->name->length;
    
    return ns_entry->name->data;
}

mycss_namespace_entry_t * mycss_namespace_entry_by_name(mycss_namespace_t *ns, mctree_t* name_tree, const char* ns_name, size_t length, bool case_insensitive)
{
    if(ns == NULL)
        return NULL;
    
    mctree_index_t idx;
    if(case_insensitive)
        idx = mctree_search_lowercase(name_tree, ns_name, length);
    else
        idx = mctree_search(name_tree, ns_name, length);
    
    if(idx == 0)
        return 0;
    
    return (mycss_namespace_entry_t*)(name_tree->nodes[ idx ].value);
}


