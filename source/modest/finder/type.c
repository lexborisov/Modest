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

#include "modest/finder/type.h"
#include "modest/finder/resource.h"

bool modest_finder_selector_type_undef(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_type_element(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    /* namespace */
    if(selector->ns_entry) {
        if(selector->ns_entry->ns_id != MyHTML_NAMESPACE_ANY && selector->ns_entry->ns_id != node->ns)
            return false;
    }
    
    /* tag match */
    mycore_string_t *str = selector->key;
    if(str->length == 1 && *str->data == '*')
        return true;
    
    if(node->tree) {
        myhtml_tag_id_t tag_id = myhtml_tag_id_by_name(node->tree, str->data, str->length);
        
        if(tag_id == node->tag_id)
            return true;
    }
    
    return false;
}

bool modest_finder_selector_type_id(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(node->token == NULL)
        return false;
    
    if(node->tree) {
        return modest_finder_match_attribute_eq(node->token->attr_first,
                                                "id", 2,
                                                selector->key->data, selector->key->length,
                                                (node->tree->compat_mode != MyHTML_TREE_COMPAT_MODE_QUIRKS));
    }
    
    return false;
}

bool modest_finder_selector_type_class(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(node->token == NULL)
        return false;
    
    if(node->tree) {
        return modest_finder_match_attribute_ws(node->token->attr_first,
                                                "class", 5,
                                                selector->key->data, selector->key->length,
                                                (node->tree->compat_mode != MyHTML_TREE_COMPAT_MODE_QUIRKS));
    }
    
    return false;
}

bool modest_finder_selector_type_attribute(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    /* namespace */
    if(selector->ns_entry) {
        if(selector->ns_entry->ns_id != MyHTML_NAMESPACE_ANY && selector->ns_entry->ns_id != node->ns)
            return false;
    }
    
    if(node->token == NULL)
        return false;
    
    mycss_selectors_object_attribute_t *sel_attr = mycss_selector_value_attribute(selector->value);
    
    if(sel_attr) {
        if(sel_attr->value == NULL)
            return false;
        
        if(sel_attr->match < MyCSS_SELECTORS_MATCH_LAST_ENTRY)
            return modest_finder_static_selector_match_map[sel_attr->match](node->token->attr_first,
                                                                            selector->key->data, selector->key->length,
                                                                            sel_attr->value->data, sel_attr->value->length,
                                                                            (sel_attr->mod & MyCSS_SELECTORS_MOD_I));
    }
    else {
        return modest_finder_match_attribute_only_key(node->token->attr_first,
                                                      selector->key->data, selector->key->length);
    }
    
    return false;
}

bool modest_finder_selector_type_pseudo_class_function(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->sub_type < MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_FUNCTION_LAST_ENTRY)
        return modest_finder_static_selector_sub_type_pseudo_class_function_map[selector->sub_type](finder, node, selector, spec);
    
    return false;
}

bool modest_finder_selector_type_pseudo_class(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    if(selector->sub_type < MyCSS_SELECTORS_SUB_TYPE_PSEUDO_CLASS_LAST_ENTRY)
        return modest_finder_static_selector_sub_type_pseudo_class_map[selector->sub_type](finder, node, selector, spec);
    
    return false;
}

bool modest_finder_selector_type_pseudo_element_function(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}

bool modest_finder_selector_type_pseudo_element(modest_finder_t* finder, myhtml_tree_node_t* node, mycss_selectors_entry_t* selector, mycss_selectors_specificity_t* spec)
{
    return false;
}


