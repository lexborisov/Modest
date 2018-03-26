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

#include "mycss/selectors/function.h"
#include "mycss/selectors/function_resource.h"
#include "mycore/utils/resources.h"

/////////////////////////////////////////////////////////
//// Functions for a find Begin Function
////
/////////////////////////////////////////////////////////
const mycss_selectots_function_begin_entry_t * mycss_function_begin_entry_by_name(const char* name, size_t length)
{
    size_t idx = ((mycore_string_chars_lowercase_map[ (const unsigned char)name[0] ] *
                   mycore_string_chars_lowercase_map[ (const unsigned char)name[(length - 1)] ] *
                   length)
                  % MyCSS_SELECTORS_FUNCTION_NAME_STATIC_SIZE) + 1;
    
    while (mycss_selectors_function_begin_map_index[idx].name)
    {
        if(mycss_selectors_function_begin_map_index[idx].length == length) {
            if(mycore_strncasecmp(mycss_selectors_function_begin_map_index[idx].name, name, length) == 0)
                return &mycss_selectors_function_begin_map_index[idx];
            
            if(mycss_selectors_function_begin_map_index[idx].next)
                idx = mycss_selectors_function_begin_map_index[idx].next;
            else
                return NULL;
        }
        else if(mycss_selectors_function_begin_map_index[idx].length > length) {
            return NULL;
        }
        else {
            idx = mycss_selectors_function_begin_map_index[idx].next;
        }
    }
    
    return NULL;
}

mycss_selectors_function_begin_f mycss_function_begin_by_name(const char *name, size_t length)
{
    const mycss_selectots_function_begin_entry_t *entry = mycss_function_begin_entry_by_name(name, length);
    
    if(entry) {
        return entry->func;
    }
    
    return NULL;
}

/////////////////////////////////////////////////////////
//// Unknown, for not exists function
////
/////////////////////////////////////////////////////////
void mycss_selectors_begin_unknown(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_UNKNOWN;
    
    entry->parser = mycss_selectors_unknown_parser;
}

///////////////////////////////////////////////////////////
////// Begin functions
//////
///////////////////////////////////////////////////////////
void mycss_selectors_function_begin_nth_child(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_CHILD;
    
    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_with_selectors;
}

void mycss_selectors_function_begin_has(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_HAS;
    
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t **new_list = (mycss_selectors_list_t**)(&selectors->entry_last->value);
    mycss_selectors_list_t *current_list = selectors->list_last;
    
    selectors->list = new_list;
    selectors->list_last = NULL;
    selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_state_relative_selector_list(entry, NULL, true);
    
    (*new_list)->parent = current_list;
    
    mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_has, entry->parser_switch, entry->parser_ending_token, false);
}

void mycss_selectors_function_begin_contains(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CONTAINS;

    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t **new_list = (mycss_selectors_list_t**)(&selectors->entry_last->value);
    mycss_selectors_list_t *current_list = selectors->list_last;
    
    selectors->list = new_list;
    selectors->list_last = NULL;
    selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_state_relative_selector_list(entry, NULL, true);
    
    (*new_list)->parent = current_list;
    
    mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_contains, entry->parser_switch, entry->parser_ending_token, false);
}

void mycss_selectors_function_begin_nth_last_child(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_CHILD;

    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_with_selectors;
}

void mycss_selectors_function_begin_drop(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DROP;
    
    selector->value = NULL;
    entry->parser = mycss_selectors_function_parser_drop;
}

void mycss_selectors_function_begin_nth_last_of_type(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_OF_TYPE;
    
    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_without_selectors;
}

void mycss_selectors_function_begin_not(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NOT;
    
    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t **new_list = (mycss_selectors_list_t**)(&selectors->entry_last->value);
    mycss_selectors_list_t *current_list = selectors->list_last;
    
    selectors->list = new_list;
    selectors->list_last = NULL;
    selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_state_compound_selector_list(entry, NULL, true);
    
    (*new_list)->parent = current_list;
    
    mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_not_or_matches_or_current_parser,
                                 entry->parser_switch, entry->parser_ending_token, false);
}

void mycss_selectors_function_begin_current(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_CURRENT;

    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t **new_list = (mycss_selectors_list_t**)(&selectors->entry_last->value);
    mycss_selectors_list_t *current_list = selectors->list_last;
    
    selectors->list = new_list;
    selectors->list_last = NULL;
    selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_state_compound_selector_list(entry, NULL, true);
    
    (*new_list)->parent = current_list;
    
    mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_not_or_matches_or_current_parser,
                                 entry->parser_switch, entry->parser_ending_token, false);
}

void mycss_selectors_function_begin_nth_of_type(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_OF_TYPE;

    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_without_selectors;
}

void mycss_selectors_function_begin_nth_last_column(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_LAST_COLUMN;

    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_without_selectors;
}

void mycss_selectors_function_begin_dir(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_DIR;
    selector->value    = NULL;
    
    entry->parser = mycss_selectors_function_parser_dir;
}

void mycss_selectors_function_begin_matches(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_MATCHES;

    mycss_selectors_t *selectors = entry->selectors;
    mycss_selectors_list_t **new_list = (mycss_selectors_list_t**)(&selectors->entry_last->value);
    mycss_selectors_list_t *current_list = selectors->list_last;
    
    selectors->list = new_list;
    selectors->list_last = NULL;
    selectors->ending_token = entry->parser_ending_token;
    
    mycss_selectors_state_compound_selector_list(entry, NULL, true);
    
    (*new_list)->parent = current_list;
    
    mycss_entry_parser_list_push(entry, mycss_selectors_function_parser_not_or_matches_or_current_parser, entry->parser_switch, entry->parser_ending_token, false);
}

void mycss_selectors_function_begin_nth_column(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_NTH_COLUMN;

    entry->anb->entry = (mycss_an_plus_b_entry_t**)(&selector->value);
    
    entry->parser = mycss_an_plus_b_state_anb_begin;
    entry->parser_switch = mycss_selectors_function_parser_nth_without_selectors;
}

void mycss_selectors_function_begin_lang(mycss_entry_t* entry, mycss_selectors_entry_t* selector)
{
    selector->sub_type = MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LANG;
    selector->value    = NULL;
    
    entry->parser = mycss_selectors_function_parser_lang;
}


