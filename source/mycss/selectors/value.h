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

#ifndef MyHTML_MyCSS_SELECTORS_VALUE_H
#define MyHTML_MyCSS_SELECTORS_VALUE_H
#pragma once

#define mycss_selector_value_attribute(obj) ((mycss_selectors_object_attribute_t*)(obj))
#define mycss_selector_value_string(obj) ((mycore_string_t*)(obj))
#define mycss_selector_value_an_plus_b(obj) ((mycss_an_plus_b_entry_t*)(obj))
#define mycss_selector_value_drop(obj) ((mycss_selectors_function_drop_type_t)(obj))
#define mycss_selector_value_lang(obj) ((mycss_selectors_value_lang_t*)(obj))
#define mycss_selector_value_function(obj) ((mycss_result_entry_t*)(obj))
#define mycss_selector_value_destroy(entry, type, sub_type, value, self_destroy) (mycss_selectors_value_destroy_map[type](entry, type, sub_type, value, self_destroy))

#ifdef __cplusplus
extern "C" {
#endif

#include "mycss/entry.h"
#include "mycss/selectors/myosi.h"
#include "mycore/utils/mchar_async.h"

typedef void * (*mycss_selectors_value_destroy_f)(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
typedef void * (*mycss_selectors_value_function_destroy_f)(mycss_entry_t* entry, void* value, bool self_destroy);

struct mycss_selectors_value_attribute {
    mycore_string_t* value;
    
    mycss_selectors_match_t match;
    mycss_selectors_mod_t mod;
}
typedef mycss_selectors_object_attribute_t;

struct mycss_selectors_value_lang {
    mycore_string_t str;
    struct mycss_selectors_value_lang* next;
}
typedef mycss_selectors_value_lang_t;


/* create */
void * mycss_selectors_value_undef_create(mycss_entry_t* entry, bool set_clean);
mycss_selectors_object_attribute_t * mycss_selectors_value_attribute_create(mycss_entry_t* entry, bool set_clean);

/* destroy */
void * mycss_selectors_value_undef_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
void * mycss_selectors_value_id_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
void * mycss_selectors_value_class_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
void * mycss_selectors_value_element_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
void * mycss_selectors_value_attribute_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_destroy(mycss_entry_t* entry, mycss_selectors_type_t type, int sub_type, void* value, bool self_destroy);

/* pseudo class function create */
void * mycss_selectors_value_pseudo_class_function_undef_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_current_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_dir_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_drop_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_has_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_lang_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_matches_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_not_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_child_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_column_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_last_child_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_last_column_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_last_of_type_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_nth_of_type_create(mycss_entry_t* entry, bool set_clean);
void * mycss_selectors_value_pseudo_class_function_contains_create(mycss_entry_t* entry, bool set_clean);

/* pseudo class function destroy */
void * mycss_selectors_value_pseudo_class_function_undef_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_current_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_dir_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_drop_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_has_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_lang_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_matches_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_not_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_child_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_column_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_last_child_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_last_column_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_last_of_type_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_nth_of_type_destroy(mycss_entry_t* entry, void* value, bool self_destroy);
void * mycss_selectors_value_pseudo_class_function_contains_destroy(mycss_entry_t* entry, void* value, bool self_destroy);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_VALUE_H */
