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

#include "modest/finder/pseudo_class.h"
#include "modest/finder/resource.h"

bool modest_finder_selector_sub_type_pseudo_class_function_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    mycss_selectors_list_t *list = selector->value;
    
    modest_finder_callback_f current_callback_found = finder->callback_found;
    void *current_ctx = finder->callback_found_ctx;
    
    bool i_found;
    
    finder->callback_found = modest_finder_callback_found_with_bool;
    finder->callback_found_ctx = &i_found;
    
    for(size_t i = 0; i < list->selector_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, list->selector_list[i]);
        
        if(i_found == true) {
            finder->callback_found = current_callback_found;
            finder->callback_found_ctx = current_ctx;
            
            return true;
        }
    }
    
    finder->callback_found = current_callback_found;
    finder->callback_found_ctx = current_ctx;
    
    return false;
}

/* after create render */
bool modest_finder_selector_sub_type_pseudo_class_function_dir(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_has(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    mycss_selectors_list_t *list = selector->value;
    
    modest_finder_callback_f current_callback_found = finder->callback_found;
    void *current_ctx = finder->callback_found_ctx;
    
    bool i_found;
    
    finder->callback_found = modest_finder_callback_found_with_bool;
    finder->callback_found_ctx = &i_found;
    
    for(size_t i = 0; i < list->selector_list_length; i++)
    {
        i_found = false;
        
        mycss_selectors_entry_t *sel_entry = list->selector_list[i];
        
        if(sel_entry->combinator == MyCSS_SELECTORS_COMBINATOR_UNDEF)
            modest_finder_node_combinator_descendant(finder, base_node, sel_entry);
        else
            modest_finder_static_selector_combinator_map[sel_entry->combinator](finder, base_node, sel_entry);
        
        if(i_found == true) {
            finder->callback_found = current_callback_found;
            finder->callback_found_ctx = current_ctx;
            
            return true;
        }
    }
    
    finder->callback_found = current_callback_found;
    finder->callback_found_ctx = current_ctx;
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_lang(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_matches(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    mycss_selectors_list_t *list = selector->value;
    
    modest_finder_callback_f current_callback_found = finder->callback_found;
    void *current_ctx = finder->callback_found_ctx;
    
    bool i_found;
    
    finder->callback_found = modest_finder_callback_found_with_bool;
    finder->callback_found_ctx = &i_found;
    
    for(size_t i = 0; i < list->selector_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, list->selector_list[i]);
        
        if(i_found == true) {
            finder->callback_found = current_callback_found;
            finder->callback_found_ctx = current_ctx;
            
            return true;
        }
    }
    
    finder->callback_found = current_callback_found;
    finder->callback_found_ctx = current_ctx;
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_not(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    mycss_selectors_list_t *list = selector->value;
    
    modest_finder_callback_f current_callback_found = finder->callback_found;
    void *current_ctx = finder->callback_found_ctx;
    
    bool i_found;
    
    finder->callback_found = modest_finder_callback_found_with_bool;
    finder->callback_found_ctx = &i_found;
    
    for(size_t i = 0; i < list->selector_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, list->selector_list[i]);
        
        if(i_found == true) {
            finder->callback_found = current_callback_found;
            finder->callback_found_ctx = current_ctx;
            
            return false;
        }
    }
    
    finder->callback_found = current_callback_found;
    finder->callback_found_ctx = current_ctx;
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(selector->value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    if(anb->of) {
        modest_finder_callback_f current_callback_found = finder->callback_found;
        void *current_ctx = finder->callback_found_ctx;
        
        bool i_found;
        
        finder->callback_found = modest_finder_callback_found_with_bool;
        finder->callback_found_ctx = &i_found;
        
        mycss_selectors_list_t *list = anb->of;
        
        while(node)
        {
            for(size_t i = 0; i < list->selector_list_length; i++)
            {
                i_found = false;
                modest_finder_node_combinator_undef(finder, node, list->selector_list[i]);
                
                if(i_found == true) {
                    node_pos++;
                    break;
                }
                else if(node_pos == 0) {
                    finder->callback_found = current_callback_found;
                    finder->callback_found_ctx = current_ctx;
                    
                    return false;
                }
            }
            
            node = node->prev;
        }
        
        finder->callback_found = current_callback_found;
        finder->callback_found_ctx = current_ctx;
        
        if(node_pos == 0)
            return false;
    }
    else {
        while(node) {
            if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
                node_pos++;
            
            node = node->prev;
        }
    }
    
    if(anb->a == 0) {
        if(anb->b == node_pos)
            return true;
    }
    else {
        double n = (double)(node_pos - anb->b) / (double)anb->a;
        
        if(n >= 0.0f && (n - (double)((long)(n))) == 0.0f)
            return true;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(selector->value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    if(anb->of) {
        modest_finder_callback_f current_callback_found = finder->callback_found;
        void *current_ctx = finder->callback_found_ctx;
        
        bool i_found;
        
        finder->callback_found = modest_finder_callback_found_with_bool;
        finder->callback_found_ctx = &i_found;
        
        mycss_selectors_list_t *list = anb->of;
        
        while(node)
        {
            for(size_t i = 0; i < list->selector_list_length; i++)
            {
                i_found = false;
                modest_finder_node_combinator_undef(finder, node, list->selector_list[i]);
                
                if(i_found == true) {
                    node_pos++;
                    break;
                }
                else if(node_pos == 0) {
                    finder->callback_found = current_callback_found;
                    finder->callback_found_ctx = current_ctx;
                    
                    return false;
                }
            }
            
            node = node->next;
        }
        
        finder->callback_found = current_callback_found;
        finder->callback_found_ctx = current_ctx;
        
        if(node_pos == 0)
            return false;
    }
    else {
        while(node) {
            if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
                node_pos++;
            
            node = node->next;
        }
    }
    
    if(anb->a == 0) {
        if(anb->b == node_pos)
            return true;
    }
    else {
        double n = (double)(node_pos - anb->b) / (double)anb->a;
        
        if(n >= 0.0f && (n - (double)((long)(n))) == 0.0f)
            return true;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(selector->value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns) {
            node_pos++;
        }
        
        node = node->next;
    }
    
    if(anb->a == 0) {
        if(anb->b != node_pos)
            return false;
    }
    else {
        double n = (double)(node_pos - anb->b) / (double)anb->a;
        
        if(n < 0.0f || (n - (double)((long)(n))) != 0.0f)
            return false;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(selector->value == NULL)
        return NULL;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns) {
            node_pos++;
        }
        
        node = node->prev;
    }
    
    if(anb->a == 0) {
        if(anb->b != node_pos)
            return false;
    }
    else {
        double n = (double)(node_pos - anb->b) / (double)anb->a;
        
        if(n < 0.0f || (n - (double)((long)(n))) != 0.0f)
            return false;
    }
    
    return true;
}

/* classes */
bool modest_finder_selector_sub_type_pseudo_class_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_active(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_any_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_A ||
       base_node->tag_id == MyHTML_TAG_AREA ||
       base_node->tag_id == MyHTML_TAG_MAP)
    {
        if(base_node->token)
            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "href", 4);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_blank(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__COMMENT) {
            if(node->tag_id != MyHTML_TAG__TEXT)
                return false;
            
            if(node->token) {
                const char *data = node->token->str.data;
                size_t len = node->token->str.length;
                
                for(size_t i = 0; i < len; i++) {
                    if(data[i] != ' ' && data[i] != '\t' && data[i] != '\n' && data[i] != '\r')
                        return false;
                }
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != base_node && node->next == NULL)
                node = node->parent;
            
            if(node == base_node)
                break;
            
            node = node->next;
        }
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_checked(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT || base_node->tag_id == MyHTML_TAG_MENUITEM)
    {
        myhtml_token_attr_t* attr = base_node->token->attr_first;
        
        while (attr)
        {
            if(attr->key.length == 4) {
                if(myhtml_strncasecmp("type", attr->key.data, 4) == 0)
                {
                    if(attr->value.length == 8) {
                        if(myhtml_strncasecmp("checkbox", attr->value.data, 8) == 0) {
                            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "checked", 7);
                        }
                    }
                    else if(attr->value.length == 5) {
                        if(myhtml_strncasecmp("radio", attr->value.data, 5) == 0) {
                            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "checked", 7);
                        }
                    }
                    
                    break;
                }
            }
            
            attr = attr->next;
        }
    }
    else if(base_node->tag_id == MyHTML_TAG_OPTION) {
        return modest_finder_match_attribute_only_key(base_node->token->attr_first, "selected", 8);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_default(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_disabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->token == NULL)
        return false;
    
    if(base_node->tag_id == MyHTML_TAG_BUTTON ||
       base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_SELECT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(modest_finder_match_attribute_only_key(base_node->token->attr_first, "disabled", 8))
            return true;
        
        myhtml_tree_node_t* node = base_node->parent;
        
        while(node) {
            /* oh, see https://html.spec.whatwg.org/multipage/forms.html#concept-fe-disabled */
            if(node->tag_id == MyHTML_TAG_FIELDSET) {
                if(node->child && node->child->tag_id != MyHTML_TAG_LEGEND) {
                    if(node->token && modest_finder_match_attribute_only_key(node->token->attr_first, "disabled", 8))
                        return true;
                }
            }
            
            node = node->parent;
        }
        
        return false;
    }
    
    /* see https://html.spec.whatwg.org/multipage/forms.html#concept-option-disabled */
    if(base_node->tag_id == MyHTML_TAG_OPTION) {
        if(modest_finder_match_attribute_only_key(base_node->token->attr_first, "disabled", 8))
            return true;
        
        myhtml_tree_node_t* node = base_node->parent;
        
        while(node) {
            if(node->tag_id == MyHTML_TAG_OPTGROUP) {
                if(node->token)
                    return modest_finder_match_attribute_only_key(node->token->attr_first, "disabled", 8);
                
                return false;
            }
            
            node = node->parent;
        }
        
        return false;
    }
    
    if(base_node->tag_id == MyHTML_TAG_OPTGROUP ||
       base_node->tag_id == MyHTML_TAG_MENUITEM) {
        return modest_finder_match_attribute_only_key(base_node->token->attr_first, "disabled", 8);
    }
    
    if(base_node->tag_id == MyHTML_TAG_FIELDSET)
    {
        if(modest_finder_match_attribute_only_key(base_node->token->attr_first, "disabled", 8))
            return true;
        
        myhtml_tree_node_t* node = base_node->parent;
        
        while(node) {
            /* oh, see https://html.spec.whatwg.org/multipage/forms.html#concept-fieldset-disabled */
            if(node->tag_id == MyHTML_TAG_FIELDSET) {
                if(node->child && node->child->tag_id != MyHTML_TAG_LEGEND) {
                    if(node->token && modest_finder_match_attribute_only_key(node->token->attr_first, "disabled", 8))
                        return true;
                }
            }
            
            node = node->parent;
        }
        
        return false;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_empty(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->child;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__COMMENT)
            return false;
        
        if(node->child)
            node = node->child;
        else {
            while(node != base_node && node->next == NULL)
                node = node->parent;
            
            if(node == base_node)
                break;
            
            node = node->next;
        }
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_enabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return ~modest_finder_selector_sub_type_pseudo_class_disabled(finder, base_node, selector);
}

bool modest_finder_selector_sub_type_pseudo_class_first_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->prev;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
            return false;
        
        node = node->prev;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_first_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->prev;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns)
            return false;
        
        node = node->prev;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_focus(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_future(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_hover(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_in_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_indeterminate(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_invalid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
            return false;
        
        node = node->next;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns)
            return false;
        
        node = node->next;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_A ||
       base_node->tag_id == MyHTML_TAG_AREA ||
       base_node->tag_id == MyHTML_TAG_LINK)
    {
        if(base_node->token)
            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "href", 4);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_only_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return
    modest_finder_selector_sub_type_pseudo_class_first_child(finder, base_node, selector) &&
    modest_finder_selector_sub_type_pseudo_class_last_child(finder, base_node, selector);
}

bool modest_finder_selector_sub_type_pseudo_class_only_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return
    modest_finder_selector_sub_type_pseudo_class_first_of_type(finder, base_node, selector) &&
    modest_finder_selector_sub_type_pseudo_class_last_of_type(finder, base_node, selector);
}

bool modest_finder_selector_sub_type_pseudo_class_optional(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_SELECT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(base_node->token)
            return ~modest_finder_match_attribute_only_key(base_node->token->attr_first, "required", 8);
        else
            return true;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_out_of_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_past(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_placeholder_shown(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(base_node->token)
            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "placeholder", 11);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_read_only(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(modest_finder_selector_sub_type_pseudo_class_read_write(finder, base_node, selector))
        return false;
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_read_write(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(modest_finder_match_attribute_only_key(base_node->token->attr_first, "readonly", 8))
            return false;
        
        return ~modest_finder_selector_sub_type_pseudo_class_disabled(finder, base_node, selector);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_required(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_SELECT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(base_node->token)
            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "required", 8);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_root(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    if(finder->tree->node_html == base_node)
        return true;
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_scope(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_target(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_user_error(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_valid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_visited(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector)
{
    return false;
}


