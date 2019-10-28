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

#include "modest/finder/pseudo_class.h"
#include "modest/finder/resource.h"

bool modest_finder_selector_sub_type_pseudo_class_function_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    mycss_selectors_list_t *list = selector->value;
    bool i_found;
    
    for(size_t i = 0; i < list->entries_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, NULL, list->entries_list[i].entry, spec, modest_finder_callback_found_with_bool, &i_found);
        
        if(i_found == true)
            return true;
    }
    
    return false;
}

/* after create render */
bool modest_finder_selector_sub_type_pseudo_class_function_dir(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_has(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    mycss_selectors_list_t *list = selector->value;
    bool i_found;
    
    for(size_t i = 0; i < list->entries_list_length; i++)
    {
        i_found = false;
        
        mycss_selectors_entry_t *sel_entry = list->entries_list[i].entry;
        
        if(sel_entry->combinator == MyCSS_SELECTORS_COMBINATOR_UNDEF)
            modest_finder_node_combinator_descendant(finder, base_node, NULL, sel_entry, spec, modest_finder_callback_found_with_bool, &i_found);
        else
            modest_finder_static_selector_combinator_map[sel_entry->combinator](finder, base_node, NULL, sel_entry, spec, modest_finder_callback_found_with_bool, &i_found);
        
        if(i_found == true)
            return true;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_contains(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node == NULL)
        return false;
    
    myhtml_tree_node_t *text_node = myhtml_node_child(base_node);
    if(text_node == NULL)
        return false;

    const char* text = myhtml_node_text(text_node, NULL);
    if(text == NULL)
        return false;

    mycss_selectors_list_t *list = (mycss_selectors_list_t*)selector->value;
    for(size_t i = 0; i < list->entries_list_length; i++) {
        char *data = NULL;
        data = mycore_malloc(0);
        if(data == NULL) {
            return false;
        }
        
        mycss_selectors_entry_t *sel_entry = list->entries_list[i].entry;
        if(sel_entry->key->data){
            const char *str = sel_entry->key->data;
            int length = strlen(str) + 1;

            char *new_data = mycore_realloc(data, length);
            if(new_data == NULL) {
                mycore_free(data);
                return false;
            }

            snprintf(new_data, length, "%s", str);
            data = new_data;
        }

        mycss_selectors_entry_t *next = sel_entry->next;
        while(next) {
            if(next->key->data) {
                int prev = strlen(data);
                const char *whitespace = (prev > 0) ? " " : "";
                const char *str = next->key->data;
                int length = strlen(whitespace) + strlen(str) + 1;

                char *new_data = mycore_realloc(data, prev + length);
                if(new_data == NULL) {
                    mycore_free(data);
                    return false;
                }
                
                snprintf(&new_data[prev], length, "%s%s", whitespace, str);
                data = new_data;
            }
            next = next->next;
        }

        if(strstr(text, data) != NULL) {
            mycore_free(data);
            return true;
        }
        mycore_free(data);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_lang(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_matches(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    mycss_selectors_list_t *list = selector->value;
    bool i_found, is_true = false;
    
    for(size_t i = 0; i < list->entries_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, NULL, list->entries_list[i].entry, spec, modest_finder_callback_found_with_bool, &i_found);
        
        if(i_found == true) {
            modest_finder_specificity_inc(list->entries_list[i].entry, spec);
            
            if(is_true == false)
                is_true = true;
        }
    }
    
    return is_true;
}

bool modest_finder_selector_sub_type_pseudo_class_function_not(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    mycss_selectors_list_t *list = selector->value;
    
    bool i_found;
    mycss_selectors_specificity_t work_spec = {0, 0, 0};
    
    for(size_t i = 0; i < list->entries_list_length; i++)
    {
        i_found = false;
        modest_finder_node_combinator_undef(finder, base_node, NULL, list->entries_list[i].entry, &work_spec, modest_finder_callback_found_with_bool, &i_found);
        
        if(i_found == true)
            return false;
        else {
            modest_finder_specificity_inc(list->entries_list[i].entry, &work_spec);
        }
    }
    
    if(work_spec.a)
        spec->a++;
    else if(work_spec.b)
        spec->b++;
    else if(work_spec.c)
        spec->c++;
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_child_check_selectors(modest_finder_t* finder, bool* i_found, myhtml_tree_node_t* node, mycss_selectors_list_t *list, mycss_selectors_specificity_t* spec)
{
    for(size_t i = 0; i < list->entries_list_length; i++)
    {
        *i_found = false;
        modest_finder_node_combinator_undef(finder, node, NULL, list->entries_list[i].entry, spec, modest_finder_callback_found_with_bool, i_found);
        
        if(*i_found) {
            /*
             :nth-child(even of li, .item) has a specificity of (0,1,1)--like 
             a tag selector plus a pseudo-class--when matched against <li>, 
             and a specificity of (0,2,0)--like a class selector plus 
             a pseudo-class--when matched against <li class=item id=foo>.
             */
            spec->b++;
            modest_finder_specificity_inc(list->entries_list[i].entry, spec);
        }
        else
            return false;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->value == NULL)
        return false;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    if(anb->of) {
        bool i_found;
        mycss_selectors_specificity_t temp_spec = {0, 0, 0};
        
        if(spec->b)
            spec->b--;
        
        if(modest_finder_selector_sub_type_pseudo_class_function_nth_child_check_selectors(finder, &i_found, node, anb->of, spec) == false)
            return false;
        
        node_pos++;
        node = node->prev;
        
        while(node)
        {
            for(size_t i = 0; i < anb->of->entries_list_length; i++)
            {
                i_found = false;
                modest_finder_node_combinator_undef(finder, node, NULL, anb->of->entries_list[i].entry, &temp_spec, modest_finder_callback_found_with_bool, &i_found);
                
                if(i_found) {
                    node_pos++;
                    break;
                }
            }
            
            node = node->prev;
        }
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

bool modest_finder_selector_sub_type_pseudo_class_function_nth_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->value == NULL)
        return false;
    
    mycss_an_plus_b_entry_t *anb = mycss_selector_value_an_plus_b(selector->value);
    
    long node_pos = 0;
    myhtml_tree_node_t* node = base_node;
    
    if(anb->of) {
        bool i_found;
        mycss_selectors_specificity_t temp_spec = {0, 0, 0};
        
        if(spec->b)
            spec->b--;
        
        if(modest_finder_selector_sub_type_pseudo_class_function_nth_child_check_selectors(finder, &i_found, node, anb->of, spec) == false)
            return false;
        
        while(node)
        {
            for(size_t i = 0; i < anb->of->entries_list_length; i++)
            {
                i_found = false;
                modest_finder_node_combinator_undef(finder, node, NULL, anb->of->entries_list[i].entry, &temp_spec, modest_finder_callback_found_with_bool, &i_found);
                
                if(i_found == true) {
                    node_pos++;
                    break;
                }
            }
            
            node = node->next;
        }
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

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_column(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_function_nth_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->value == NULL)
        return false;
    
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

bool modest_finder_selector_sub_type_pseudo_class_function_nth_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->value == NULL)
        return false;
    
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
bool modest_finder_selector_sub_type_pseudo_class_undef(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_active(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if (base_node->token)
	return modest_finder_match_attribute_only_key(base_node->token->attr_first, "active", 6);
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_any_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

bool modest_finder_selector_sub_type_pseudo_class_blank(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

bool modest_finder_selector_sub_type_pseudo_class_checked(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT || base_node->tag_id == MyHTML_TAG_MENUITEM)
    {
        myhtml_token_attr_t* attr = base_node->token->attr_first;
        
        while (attr)
        {
            if(attr->key.length == 4) {
                if(mycore_strncasecmp("type", attr->key.data, 4) == 0)
                {
                    if(attr->value.length == 8) {
                        if(mycore_strncasecmp("checkbox", attr->value.data, 8) == 0) {
                            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "checked", 7);
                        }
                    }
                    else if(attr->value.length == 5) {
                        if(mycore_strncasecmp("radio", attr->value.data, 5) == 0) {
                            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "checked", 7);
                        }
                    }
                    
                    break;
                }
            }
            
            attr = attr->next;
        }
    }
    else if(base_node->tag_id == MyHTML_TAG_OPTION)
    {
        return modest_finder_match_attribute_only_key(base_node->token->attr_first, "selected", 8);
    }
    else if(base_node->token && base_node->tag_id >= MyHTML_TAG_LAST_ENTRY)
    {
	return modest_finder_match_attribute_only_key(base_node->token->attr_first, "checked", 7);
    }
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_current(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_default(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_disabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

    /* custom HTML tag*/
    if(base_node->token && base_node->tag_id >= MyHTML_TAG_LAST_ENTRY)
    {
	if (modest_finder_match_attribute_only_key(base_node->token->attr_first, "disabled", 8))
	    return true;
	return false;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_drop(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_empty(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

bool modest_finder_selector_sub_type_pseudo_class_enabled(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return !modest_finder_selector_sub_type_pseudo_class_disabled(finder, base_node, selector, spec);
}

bool modest_finder_selector_sub_type_pseudo_class_first_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    myhtml_tree_node_t *node = base_node->prev;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
            return false;
        
        node = node->prev;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_first_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    myhtml_tree_node_t *node = base_node->prev;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns)
            return false;
        
        node = node->prev;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_focus(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if (base_node->token)
	return modest_finder_match_attribute_only_key(base_node->token->attr_first, "focus", 5);
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_future(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_hover(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if (base_node->token)
	return modest_finder_match_attribute_only_key(base_node->token->attr_first, "hover", 5);
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_in_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_indeterminate(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_invalid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_last_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id != MyHTML_TAG__TEXT && node->tag_id != MyHTML_TAG__COMMENT)
            return false;
        
        node = node->next;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_last_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    myhtml_tree_node_t *node = base_node->next;
    
    while(node) {
        if(node->tag_id == base_node->tag_id && node->ns == base_node->ns)
            return false;
        
        node = node->next;
    }
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_link(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

bool modest_finder_selector_sub_type_pseudo_class_only_child(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return
    modest_finder_selector_sub_type_pseudo_class_first_child(finder, base_node, selector, spec) &&
    modest_finder_selector_sub_type_pseudo_class_last_child(finder, base_node, selector, spec);
}

bool modest_finder_selector_sub_type_pseudo_class_only_of_type(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return
    modest_finder_selector_sub_type_pseudo_class_first_of_type(finder, base_node, selector, spec) &&
    modest_finder_selector_sub_type_pseudo_class_last_of_type(finder, base_node, selector, spec);
}

bool modest_finder_selector_sub_type_pseudo_class_optional(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_SELECT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(base_node->token)
            return !modest_finder_match_attribute_only_key(base_node->token->attr_first, "required", 8);
        else
            return true;
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_out_of_range(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_past(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_placeholder_shown(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(base_node->token)
            return modest_finder_match_attribute_only_key(base_node->token->attr_first, "placeholder", 11);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_read_only(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(modest_finder_selector_sub_type_pseudo_class_read_write(finder, base_node, selector, spec))
        return false;
    
    return true;
}

bool modest_finder_selector_sub_type_pseudo_class_read_write(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node->tag_id == MyHTML_TAG_INPUT ||
       base_node->tag_id == MyHTML_TAG_TEXTAREA)
    {
        if(modest_finder_match_attribute_only_key(base_node->token->attr_first, "readonly", 8))
            return false;
        
        return !modest_finder_selector_sub_type_pseudo_class_disabled(finder, base_node, selector, spec);
    }
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_required(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
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

bool modest_finder_selector_sub_type_pseudo_class_root(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(base_node->tree && base_node->tree->node_html == base_node)
        return true;
    
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_scope(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_target(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_user_error(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_valid(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_sub_type_pseudo_class_visited(modest_finder_t* finder, myhtml_tree_node_t* base_node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}


