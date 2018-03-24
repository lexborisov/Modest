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

#ifndef MODEST_FINDER_RESOURCE_H
#define MODEST_FINDER_RESOURCE_H
#pragma once

/* see enum mycss_selectors_type (mycss_selectors_type_t) on mycss/selectors/myosi.h */
static const modest_finder_selector_type_f modest_finder_static_selector_type_map[MyCSS_SELECTORS_TYPE_LAST_ENTRY] =
{
    modest_finder_selector_type_undef,                   /* MyCSS_SELECTORS_TYPE_UNDEF */
    modest_finder_selector_type_element,                 /* MyCSS_SELECTORS_TYPE_ELEMENT */
    modest_finder_selector_type_id,                      /* MyCSS_SELECTORS_TYPE_ID */
    modest_finder_selector_type_class,                   /* MyCSS_SELECTORS_TYPE_CLASS */
    modest_finder_selector_type_attribute,               /* MyCSS_SELECTORS_TYPE_ATTRIBUTE */
    modest_finder_selector_type_pseudo_class_function,   /* MyCSS_SELECTORS_TYPE_PSEUDO_CLASS_FUNCTION */
    modest_finder_selector_type_pseudo_class,            /* MyCSS_SELECTORS_TYPE_PSEUDO_CLASS */
    modest_finder_selector_type_pseudo_element_function, /* MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT_FUNCTION */
    modest_finder_selector_type_pseudo_element           /* MyCSS_SELECTORS_TYPE_PSEUDO_ELEMENT */
};

/* see enum mycss_selectors_sub_type (mycss_selectors_sub_type_t) on mycss/selectors/myosi.h */
static const modest_finder_selector_type_f modest_finder_static_selector_sub_type_pseudo_class_function_map[MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY] =
{
    modest_finder_selector_sub_type_pseudo_class_function_undef,              /* UNDEF */
    modest_finder_selector_sub_type_pseudo_class_function_undef,              /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNKNOWN */
    modest_finder_selector_sub_type_pseudo_class_function_contains,         /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CONTAINS */
    modest_finder_selector_sub_type_pseudo_class_function_current,            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CURRENT */
    modest_finder_selector_sub_type_pseudo_class_function_dir,                /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DIR */
    modest_finder_selector_sub_type_pseudo_class_function_drop,               /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DROP */
    modest_finder_selector_sub_type_pseudo_class_function_has,                /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_HAS */
    modest_finder_selector_sub_type_pseudo_class_function_lang,               /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LANG */
    modest_finder_selector_sub_type_pseudo_class_function_matches,            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES */
    modest_finder_selector_sub_type_pseudo_class_function_not,                /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT */
    modest_finder_selector_sub_type_pseudo_class_function_nth_child,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_CHILD */
    modest_finder_selector_sub_type_pseudo_class_function_nth_column,         /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_COLUMN */
    modest_finder_selector_sub_type_pseudo_class_function_nth_last_child,     /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_CHILD */
    modest_finder_selector_sub_type_pseudo_class_function_nth_last_column,    /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_COLUMN */
    modest_finder_selector_sub_type_pseudo_class_function_nth_last_of_type,   /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_OF_TYPE */
    modest_finder_selector_sub_type_pseudo_class_function_nth_of_type        /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_OF_TYPE */

};

/* see enum mycss_selectors_sub_type (mycss_selectors_sub_type_t) on mycss/selectors/myosi.h */
static const modest_finder_selector_type_f modest_finder_static_selector_sub_type_pseudo_class_map[MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_ENTRY] =
{
    modest_finder_selector_sub_type_pseudo_class_undef,              /* UNDEF */
    modest_finder_selector_sub_type_pseudo_class_undef,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_UNKNOWN */
    modest_finder_selector_sub_type_pseudo_class_active,            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ACTIVE */
    modest_finder_selector_sub_type_pseudo_class_any_link,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ANY_LINK */
    modest_finder_selector_sub_type_pseudo_class_blank,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_BLANK */
    modest_finder_selector_sub_type_pseudo_class_checked,           /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_CHECKED */
    modest_finder_selector_sub_type_pseudo_class_current,           /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_CURRENT */
    modest_finder_selector_sub_type_pseudo_class_default,           /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DEFAULT */
    modest_finder_selector_sub_type_pseudo_class_disabled,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DISABLED */
    modest_finder_selector_sub_type_pseudo_class_drop,              /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_DROP */
    modest_finder_selector_sub_type_pseudo_class_empty,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_EMPTY */
    modest_finder_selector_sub_type_pseudo_class_enabled,           /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ENABLED */
    modest_finder_selector_sub_type_pseudo_class_first_child,       /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FIRST_CHILD */
    modest_finder_selector_sub_type_pseudo_class_first_of_type,     /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FIRST_OF_TYPE */
    modest_finder_selector_sub_type_pseudo_class_focus,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FOCUS */
    modest_finder_selector_sub_type_pseudo_class_future,            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUTURE */
    modest_finder_selector_sub_type_pseudo_class_hover,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_HOVER */
    modest_finder_selector_sub_type_pseudo_class_in_range,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_IN_RANGE */
    modest_finder_selector_sub_type_pseudo_class_indeterminate,     /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_INDETERMINATE */
    modest_finder_selector_sub_type_pseudo_class_invalid,           /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_INVALID */
    modest_finder_selector_sub_type_pseudo_class_last_child,        /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_CHILD */
    modest_finder_selector_sub_type_pseudo_class_last_of_type,      /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_OF_TYPE */
    modest_finder_selector_sub_type_pseudo_class_link,              /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LINK */
    modest_finder_selector_sub_type_pseudo_class_only_child,        /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ONLY_CHILD */
    modest_finder_selector_sub_type_pseudo_class_only_of_type,      /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ONLY_OF_TYPE */
    modest_finder_selector_sub_type_pseudo_class_optional,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_OPTIONAL */
    modest_finder_selector_sub_type_pseudo_class_out_of_range,      /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_OUT_OF_RANGE */
    modest_finder_selector_sub_type_pseudo_class_past,              /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_PAST */
    modest_finder_selector_sub_type_pseudo_class_placeholder_shown, /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_PLACEHOLDER_SHOWN */
    modest_finder_selector_sub_type_pseudo_class_read_only,         /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_READ_ONLY */
    modest_finder_selector_sub_type_pseudo_class_read_write,        /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_READ_WRITE */
    modest_finder_selector_sub_type_pseudo_class_required,          /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_REQUIRED */
    modest_finder_selector_sub_type_pseudo_class_root,              /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_ROOT */
    modest_finder_selector_sub_type_pseudo_class_scope,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_SCOPE */
    modest_finder_selector_sub_type_pseudo_class_target,            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_TARGET */
    modest_finder_selector_sub_type_pseudo_class_user_error,        /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_USER_ERROR */
    modest_finder_selector_sub_type_pseudo_class_valid,             /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_VALID */
    modest_finder_selector_sub_type_pseudo_class_visited            /* MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_VISITED */
};

/* see enum mycss_selectors_combinator (mycss_selectors_combinator_t) on mycss/selectors/myosi.h */
static const modest_finder_selector_combinator_f modest_finder_static_selector_combinator_map[MyCSS_SELECTORS_COMBINATOR_LAST_ENTRY] =
{
    modest_finder_node_combinator_undef,             /* MyCSS_SELECTORS_COMBINATOR_UNDEF */
    modest_finder_node_combinator_descendant,        /* MyCSS_SELECTORS_COMBINATOR_DESCENDANT */
    modest_finder_node_combinator_child,             /* MyCSS_SELECTORS_COMBINATOR_CHILD */
    modest_finder_node_combinator_next_sibling,      /* MyCSS_SELECTORS_COMBINATOR_NEXT_SIBLING */
    modest_finder_node_combinator_following_sibling, /* MyCSS_SELECTORS_COMBINATOR_FOLLOWING_SIBLING */
    modest_finder_node_combinator_column             /* MyCSS_SELECTORS_COMBINATOR_COLUMN */
};

/* see enum mycss_selectors_match (mycss_selectors_match_t) on mycss/selectors/myosi.h */
static const modest_finder_match_f modest_finder_static_selector_match_map[MyCSS_SELECTORS_MATCH_LAST_ENTRY] =
{
    modest_finder_match_attribute_eq,         /* MyCSS_SELECTORS_MATCH_EQUAL */
    modest_finder_match_attribute_ws,         /* MyCSS_SELECTORS_MATCH_INCLUDE */
    modest_finder_match_attribute_hsp,        /* MyCSS_SELECTORS_MATCH_DASH */
    modest_finder_match_attribute_begin,      /* MyCSS_SELECTORS_MATCH_PREFIX */
    modest_finder_match_attribute_end,        /* MyCSS_SELECTORS_MATCH_SUFFIX */
    modest_finder_match_attribute_sub         /* MyCSS_SELECTORS_MATCH_SUBSTRING */
};

#endif /* MODEST_FINDER_RESOURCE_H */
