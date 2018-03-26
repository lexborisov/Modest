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

#include "mycss/selectors/value.h"
#include "mycss/selectors/value_resource.h"

/////////////////////////////////////////////////////////
//// Create
////
/////////////////////////////////////////////////////////
void * mycss_selectors_value_undef_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

mycss_selectors_object_attribute_t * mycss_selectors_value_attribute_create(mycss_entry_t* entry, bool set_clean)
{
    mycss_selectors_object_attribute_t* attr = (mycss_selectors_object_attribute_t*)
        mchar_async_malloc(entry->mchar, entry->mchar_value_node_id, sizeof(mycss_selectors_object_attribute_t));
    
    if(set_clean)
        memset(attr, 0, sizeof(mycss_selectors_object_attribute_t));
    
    return attr;
}

/////////////////////////////////////////////////////////
//// Destroy
////
/////////////////////////////////////////////////////////
void * mycss_selectors_value_undef_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    mycore_string_destroy(mycss_selector_value_string(value), false);
    mcobject_free(entry->mcobject_string_entries, value);
    
    return NULL;
}

void * mycss_selectors_value_id_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    mycore_string_destroy(mycss_selector_value_string(value), false);
    
    if(self_destroy) {
        mcobject_free(entry->mcobject_string_entries, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_class_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    mycore_string_destroy(mycss_selector_value_string(value), false);
    
    if(self_destroy) {
        mcobject_free(entry->mcobject_string_entries, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_element_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    mycore_string_destroy(mycss_selector_value_string(value), false);
    
    if(self_destroy) {
        mcobject_free(entry->mcobject_string_entries, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_attribute_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    if(mycss_selector_value_attribute(value)->value) {
        mycore_string_destroy(mycss_selector_value_attribute(value)->value, false);
        mcobject_free(entry->mcobject_string_entries, mycss_selector_value_attribute(value)->value);
    }
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy)
{
    if(sub_type < MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY)
        return (mycss_selectors_value_function_destroy_map[sub_type](entry, value, self_destroy));
    
    return value;
}

/////////////////////////////////////////////////////////
//// Pseudo Class Function Create
////
/////////////////////////////////////////////////////////
void * mycss_selectors_value_pseudo_class_function_undef_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_current_create(mycss_entry_t* entry, bool set_clean)
{
    return mycss_selectors_list_create(entry->selectors);
}

void * mycss_selectors_value_pseudo_class_function_dir_create(mycss_entry_t* entry, bool set_clean)
{
    mycore_string_t *str = mcobject_malloc(entry->mcobject_string_entries, NULL);
    
    if(set_clean)
        mycore_string_clean_all(str);
    
    return str;
}

void * mycss_selectors_value_pseudo_class_function_drop_create(mycss_entry_t* entry, bool set_clean)
{
    /* not need create */
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_has_create(mycss_entry_t* entry, bool set_clean)
{
    return mycss_selectors_list_create(entry->selectors);
}

void * mycss_selectors_value_pseudo_class_function_contains_create(mycss_entry_t* entry, bool set_clean)
{
    return mycss_selectors_list_create(entry->selectors);
}

void * mycss_selectors_value_pseudo_class_function_lang_create(mycss_entry_t* entry, bool set_clean)
{
    mycss_selectors_value_lang_t* lang = (mycss_selectors_value_lang_t*)
    mchar_async_malloc(entry->mchar, entry->mchar_value_node_id, sizeof(mycss_selectors_value_lang_t));
    
    if(set_clean) {
        lang->next = NULL;
        mycore_string_clean_all(&lang->str);
    }
    
    return lang;
}

void * mycss_selectors_value_pseudo_class_function_matches_create(mycss_entry_t* entry, bool set_clean)
{
    return mycss_selectors_list_create(entry->selectors);
}

void * mycss_selectors_value_pseudo_class_function_not_create(mycss_entry_t* entry, bool set_clean)
{
    return mycss_selectors_list_create(entry->selectors);
}

void * mycss_selectors_value_pseudo_class_function_nth_child_create(mycss_entry_t* entry, bool set_clean)
{
    mycss_an_plus_b_entry_t* anb_entry = (mycss_an_plus_b_entry_t*)
        mchar_async_malloc(entry->mchar, entry->mchar_value_node_id, sizeof(mycss_an_plus_b_entry_t));
    
    if(set_clean)
        memset(anb_entry, 0, sizeof(mycss_an_plus_b_entry_t));
    
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_nth_column_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_child_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_column_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_of_type_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

void * mycss_selectors_value_pseudo_class_function_nth_of_type_create(mycss_entry_t* entry, bool set_clean)
{
    return NULL;
}

/////////////////////////////////////////////////////////
//// Pseudo Class Function Destroy
////
/////////////////////////////////////////////////////////
void * mycss_selectors_value_pseudo_class_function_undef_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    /* not need destroy */
    if(self_destroy) {
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_current_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycss_selectors_list_destroy(entry->selectors, value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_dir_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycore_string_destroy(value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_drop_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    /* not need destroy */
    if(self_destroy) {
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_has_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycss_selectors_list_destroy(entry->selectors, value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_contains_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycss_selectors_list_destroy(entry->selectors, value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_lang_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_selectors_value_lang_t *lang_entry = mycss_selector_value_lang(value);
    
    while(lang_entry) {
        mycore_string_destroy(&lang_entry->str, false);
        lang_entry = lang_entry->next;
    }
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    mycss_selector_value_lang(value)->next = NULL;
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_matches_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycss_selectors_list_destroy(entry->selectors, value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_not_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    return mycss_selectors_list_destroy(entry->selectors, value, self_destroy);
}

void * mycss_selectors_value_pseudo_class_function_nth_child_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = value;
    
    if(anb->of)
        anb->of = mycss_selectors_list_destroy(entry->selectors, anb->of, true);
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_nth_column_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_child_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = value;
    
    if(anb->of)
        anb->of = mycss_selectors_list_destroy(entry->selectors, anb->of, true);
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_column_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_nth_last_of_type_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}

void * mycss_selectors_value_pseudo_class_function_nth_of_type_destroy(mycss_entry_t* entry, void* value, bool self_destroy)
{
    if(value == NULL)
        return NULL;
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, value);
        return NULL;
    }
    
    return value;
}



