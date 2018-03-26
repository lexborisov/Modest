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

#ifndef MyHTML_MyCSS_SELECTORS_MYOSI_H
#define MyHTML_MyCSS_SELECTORS_MYOSI_H
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mycss_selectors mycss_selectors_t;
typedef struct mycss_selectors_entry mycss_selectors_entry_t;
typedef struct mycss_selectors_entries_list mycss_selectors_entries_list_t;
typedef struct mycss_selectors_list mycss_selectors_list_t;
typedef struct mycss_selectors_specificity mycss_selectors_specificity_t;

#include "mycss/myosi.h"
#include "mycss/mystring.h"
#include "mycss/namespace/myosi.h"
#include "mycss/declaration/myosi.h"
#include "mycore/utils/mcobject.h"

typedef bool (*mycss_selectors_state_f)(mycss_entry_t* entry, mycss_selectors_t* selectors, mycss_selectors_entry_t* selector, mycss_token_t* token);
typedef void (*mycss_callback_selector_done_f)(mycss_selectors_t* selectors, mycss_selectors_entry_t* selector);

enum mycss_selectors_match {
    MyCSS_SELECTORS_MATCH_EQUAL      = 0x00, //  =
    MyCSS_SELECTORS_MATCH_INCLUDE    = 0x01, // ~=
    MyCSS_SELECTORS_MATCH_DASH       = 0x02, // |=
    MyCSS_SELECTORS_MATCH_PREFIX     = 0x03, // ^=
    MyCSS_SELECTORS_MATCH_SUFFIX     = 0x04, // $=
    MyCSS_SELECTORS_MATCH_SUBSTRING  = 0x05, // *=
    MyCSS_SELECTORS_MATCH_LAST_ENTRY = 0x06
}
typedef mycss_selectors_match_t;

enum mycss_selectors_combinator {
    MyCSS_SELECTORS_COMBINATOR_UNDEF             = 0x00, // two compound selectors [key=val].foo
    MyCSS_SELECTORS_COMBINATOR_DESCENDANT        = 0x01, // '>>' or WHITESPACE
    MyCSS_SELECTORS_COMBINATOR_CHILD             = 0x02, // '>'
    MyCSS_SELECTORS_COMBINATOR_NEXT_SIBLING      = 0x03, // '+'
    MyCSS_SELECTORS_COMBINATOR_FOLLOWING_SIBLING = 0x04, // '~'
    MyCSS_SELECTORS_COMBINATOR_COLUMN            = 0x05, // '||'
    MyCSS_SELECTORS_COMBINATOR_LAST_ENTRY        = 0x06
}
typedef mycss_selectors_combinator_t;

enum mycss_selectors_mod {
    MyCSS_SELECTORS_MOD_UNDEF       = 0x00,
    MyCSS_SELECTORS_MOD_I           = 0x01
}
typedef mycss_selectors_mod_t;

enum mycss_selectors_flags {
    MyCSS_SELECTORS_FLAGS_UNDEF         = 0x00,
    MyCSS_SELECTORS_FLAGS_SELECTOR_BAD  = 0x01
}
typedef mycss_selectors_flags_t;

enum mycss_selectors_type {
    MyCSS_SELECTORS_TYPE_UNDEF                   = 0x000, // tag name <div> = div in css
    MyCSS_SELECTORS_TYPE_ELEMENT                 = 0x001, // tag name <div> = div in css
    MyCSS_SELECTORS_TYPE_ID                      = 0x002, // #hash
    MyCSS_SELECTORS_TYPE_CLASS                   = 0x003, // .class
    MyCSS_SELECTORS_TYPE_ATTRIBUTE               = 0x004, // [key=val], in html <div key="val">
    MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION   = 0x005, // :function(...)
    MyCSS_SELECTORS_TYPE_PSEUDO_CLASS            = 0x006, // :pseudo
    MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT_FUNCTION = 0x007, // ::function(...)
    MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT          = 0x008, // ::pseudo
    MyCSS_SELECTORS_TYPE_LAST_ENTRY              = 0x009
}
typedef mycss_selectors_type_t;

enum mycss_selectors_sub_type {
    MyCSS_SELECTORS_SUB_TYPE_UNDEF   = 0x00,
    MyCSS_SELECTORS_SUB_TYPE_UNKNOWN = 0x01
}
typedef mycss_selectors_sub_type_t;

/* pseudo classes functions */
enum mycss_selectors_sub_type_pseudo_class_function {
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNDEF            = 0x00,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNKNOWN          = 0x01,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CONTAINS         = 0x02,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CURRENT          = 0x03,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DIR              = 0x04,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DROP             = 0x05,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_HAS              = 0x06,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LANG             = 0x07,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES          = 0x08,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT              = 0x09,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_CHILD        = 0x0a,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_COLUMN       = 0x0b,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_CHILD   = 0x0c,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_COLUMN  = 0x0d,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_OF_TYPE = 0x0e,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_OF_TYPE      = 0x0f,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY       = 0x10
}
typedef mycss_selectors_sub_type_pseudo_class_function_t;

/* pseudo classes */
enum mycss_selectors_sub_type_pseudo_class {
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_UNDEF             = 0x00,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_UNKNOWN           = 0x01,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ACTIVE            = 0x02,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ANY_LINK          = 0x03,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_BLANK             = 0x04,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_CHECKED           = 0x05,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_CURRENT           = 0x06,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DEFAULT           = 0x07,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DISABLED          = 0x08,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DROP              = 0x09,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_EMPTY             = 0x0a,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ENABLED           = 0x0b,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FIRST_CHILD       = 0x0c,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FIRST_OF_TYPE     = 0x0d,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FOCUS             = 0x0e,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUTURE            = 0x0f,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_HOVER             = 0x10,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_IN_RANGE          = 0x11,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_INDETERMINATE     = 0x12,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_INVALID           = 0x13,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_CHILD        = 0x14,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_OF_TYPE      = 0x15,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LINK              = 0x16,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ONLY_CHILD        = 0x17,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ONLY_OF_TYPE      = 0x18,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_OPTIONAL          = 0x19,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_OUT_OF_RANGE      = 0x1a,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_PAST              = 0x1b,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_PLACEHOLDER_SHOWN = 0x1c,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_READ_ONLY         = 0x1d,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_READ_WRITE        = 0x1e,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_REQUIRED          = 0x1f,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ROOT              = 0x20,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_SCOPE             = 0x21,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_TARGET            = 0x22,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_USER_ERROR        = 0x23,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_VALID             = 0x24,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_VISITED           = 0x25,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_ENTRY        = 0x26
}
typedef mycss_selectors_sub_type_pseudo_class_t;

/* pseudo element */
enum mycss_selectors_sub_type_pseudo_element {
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_UNDEF          = 0x00,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_UNKNOWN        = 0x01,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_AFTER          = 0x02,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_BACKDROP       = 0x03,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_BEFORE         = 0x04,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_FIRST_LETTER   = 0x05,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_FIRST_LINE     = 0x06,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_GRAMMAR_ERROR  = 0x07,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_MARKER         = 0x08,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_PLACEHOLDER    = 0x09,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_SELECTION      = 0x0a,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_SPELLING_ERROR = 0x0b,
    MyCSS_SELECTORS_SUB_TYPE_PSEUDO_ELEMENT_LAST_ENTRY     = 0x0c
}
typedef mycss_selectors_sub_type_pseudo_element_t;

enum mycss_selectors_function_drop_type {
    MyCSS_SELECTORS_FUNCTION_DROP_TYPE_UNDEF   = 0x000,
    MyCSS_SELECTORS_FUNCTION_DROP_TYPE_ACTIVE  = 0x001,
    MyCSS_SELECTORS_FUNCTION_DROP_TYPE_VALID   = 0x002,
    MyCSS_SELECTORS_FUNCTION_DROP_TYPE_INVALID = 0x004,
}
typedef mycss_selectors_function_drop_type_t;

struct mycss_selectors_specificity {
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct mycss_selectors {
    // refs
    mycss_entry_t* ref_entry;
    
    mycss_selectors_entry_t** entry;
    mycss_selectors_entry_t*  entry_last;
    
    mycss_selectors_list_t** list;
    mycss_selectors_list_t*  list_last;
    
    mycss_selectors_specificity_t* specificity;
    mycss_selectors_combinator_t* combinator;
    
    mycss_token_type_t ending_token;
    
    mcobject_t* mcobject_entries;
    mcobject_t* mcobject_list_entries;
};

struct mycss_selectors_entry {
    mycss_selectors_type_t type;
    unsigned int sub_type;
    mycss_selectors_flags_t flags;
    
    mycss_namespace_entry_t* ns_entry;
    
    mycore_string_t* key;
    void* value;
    
    mycss_selectors_combinator_t combinator;
    
    mycss_selectors_entry_t* next;
    mycss_selectors_entry_t* prev;
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyHTML_MyCSS_SELECTORS_MYOSI_H */
