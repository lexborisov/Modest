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

#ifndef MyHTML_MyCSS_SELECTORS_VALUE_RESOURCE_H
#define MyHTML_MyCSS_SELECTORS_VALUE_RESOURCE_H
#pragma once

#include "mycss/selectors/myosi.h"

static const mycss_selectors_value_destroy_f mycss_selectors_value_destroy_map[MyCSS_SELECTORS_TYPE_LAST_ENTRY] = {
    mycss_selectors_value_undef_destroy,     /* MyCSS_SELECTORS_TYPE_UNDEF */
    mycss_selectors_value_element_destroy,   /* MyCSS_SELECTORS_TYPE_ELEMENT */
    mycss_selectors_value_id_destroy,        /* MyCSS_SELECTORS_TYPE_ID */
    mycss_selectors_value_class_destroy,     /* MyCSS_SELECTORS_TYPE_CLASS */
    mycss_selectors_value_attribute_destroy, /* MyCSS_SELECTORS_TYPE_ATTRIBUTE */
    mycss_selectors_value_pseudo_class_function_destroy,  /* MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION */
    mycss_selectors_value_undef_destroy,     /* MyCSS_SELECTORS_TYPE_PSEUDO_CLASS */
    mycss_selectors_value_undef_destroy,     /* MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT_FUNCTION */
    mycss_selectors_value_undef_destroy      /* MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT */
};

static const mycss_selectors_value_function_destroy_f mycss_selectors_value_function_destroy_map[MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY] = {
    mycss_selectors_value_pseudo_class_function_undef_destroy,
    mycss_selectors_value_pseudo_class_function_undef_destroy,
    mycss_selectors_value_pseudo_class_function_contains_destroy,
    mycss_selectors_value_pseudo_class_function_current_destroy,
    mycss_selectors_value_pseudo_class_function_dir_destroy,
    mycss_selectors_value_pseudo_class_function_drop_destroy,
    mycss_selectors_value_pseudo_class_function_has_destroy,
    mycss_selectors_value_pseudo_class_function_lang_destroy,
    mycss_selectors_value_pseudo_class_function_matches_destroy,
    mycss_selectors_value_pseudo_class_function_not_destroy,
    mycss_selectors_value_pseudo_class_function_nth_child_destroy,
    mycss_selectors_value_pseudo_class_function_nth_column_destroy,
    mycss_selectors_value_pseudo_class_function_nth_last_child_destroy,
    mycss_selectors_value_pseudo_class_function_nth_last_column_destroy,
    mycss_selectors_value_pseudo_class_function_nth_last_of_type_destroy,
    mycss_selectors_value_pseudo_class_function_nth_of_type_destroy,
};

#endif /* MyHTML_MyCSS_SELECTORS_VALUE_RESOURCE_H */
