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

#include "modest/style/map.h"
#include "modest/style/map_resource.h"

void modest_style_map_collate_declaration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(decl->type >= MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        return;
    
    modest_style_map_static_collate_declaration[ decl->type ](modest, node, decl, spec);
}

void modest_style_map_collate_declaration_undef(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    
}

void modest_style_map_collate_declaration_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->height == NULL) {
        m_node->raw_style->height = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *height = m_node->raw_style->height;
    
    if(modest_finder_thread_spec_is_up(spec, &height->spec)) {
        height->declaration = decl;
        height->spec = *spec;
    }
}

void modest_style_map_collate_declaration_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->width == NULL) {
        m_node->raw_style->width = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *width = m_node->raw_style->width;
    
    if(modest_finder_thread_spec_is_up(spec, &width->spec)) {
        width->declaration = decl;
        width->spec = *spec;
    }
}

void modest_style_map_collate_declaration_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t val_four = *((mycss_values_shorthand_four_t*)(decl->value));
    mycss_declaration_t* declaration = modest->mycss_entry->declaration;
    
    if(val_four.two == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        
        val_four.two   = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.one, true);
        
        mycss_declaration_entry_type_set(val_four.two, MyCSS_PROPERTY_TYPE_PADDING_RIGHT);
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_PADDING_LEFT);
    }
    else if(val_four.three == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_PADDING_LEFT);
    }
    else if(val_four.four == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        
        val_four.four = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_PADDING_LEFT);
    }
    else {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        mycss_declaration_entry_important_set(val_four.four, decl->is_important);
    }
    
    modest_style_map_collate_declaration_padding_top(modest, node, val_four.one, spec);
    modest_style_map_collate_declaration_padding_right(modest, node, val_four.two, spec);
    modest_style_map_collate_declaration_padding_bottom(modest, node, val_four.three, spec);
    modest_style_map_collate_declaration_padding_left(modest, node, val_four.four, spec);
}

void modest_style_map_collate_declaration_padding_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->padding_top == NULL) {
        m_node->raw_style->padding_top = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *padding_top = m_node->raw_style->padding_top;
    
    if(modest_finder_thread_spec_is_up(spec, &padding_top->spec)) {
        padding_top->declaration = decl;
        padding_top->spec = *spec;
    }
}

void modest_style_map_collate_declaration_padding_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->padding_right == NULL) {
        m_node->raw_style->padding_right = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *padding_right = m_node->raw_style->padding_right;
    
    if(modest_finder_thread_spec_is_up(spec, &padding_right->spec)) {
        padding_right->declaration = decl;
        padding_right->spec = *spec;
    }
}

void modest_style_map_collate_declaration_padding_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->padding_bottom == NULL) {
        m_node->raw_style->padding_bottom = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *padding_bottom = m_node->raw_style->padding_bottom;
    
    if(modest_finder_thread_spec_is_up(spec, &padding_bottom->spec)) {
        padding_bottom->declaration = decl;
        padding_bottom->spec = *spec;
    }
}

void modest_style_map_collate_declaration_padding_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->padding_left == NULL) {
        m_node->raw_style->padding_left = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *padding_left = m_node->raw_style->padding_left;
    
    if(modest_finder_thread_spec_is_up(spec, &padding_left->spec)) {
        padding_left->declaration = decl;
        padding_left->spec = *spec;
    }
}

/* margin */
void modest_style_map_collate_declaration_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t val_four = *((mycss_values_shorthand_four_t*)(decl->value));
    mycss_declaration_t* declaration = modest->mycss_entry->declaration;
    
    if(val_four.two == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        
        val_four.two   = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.one, true);
        
        mycss_declaration_entry_type_set(val_four.two, MyCSS_PROPERTY_TYPE_MARGIN_RIGHT);
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_MARGIN_LEFT);
    }
    else if(val_four.three == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_MARGIN_LEFT);
    }
    else if(val_four.four == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        
        val_four.four = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_MARGIN_LEFT);
    }
    else {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        mycss_declaration_entry_important_set(val_four.four, decl->is_important);
    }
    
    modest_style_map_collate_declaration_margin_top(modest, node, val_four.one, spec);
    modest_style_map_collate_declaration_margin_right(modest, node, val_four.two, spec);
    modest_style_map_collate_declaration_margin_bottom(modest, node, val_four.three, spec);
    modest_style_map_collate_declaration_margin_left(modest, node, val_four.four, spec);
}

void modest_style_map_collate_declaration_margin_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->margin_bottom == NULL) {
        m_node->raw_style->margin_bottom = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *margin_bottom = m_node->raw_style->margin_bottom;
    
    if(modest_finder_thread_spec_is_up(spec, &margin_bottom->spec)) {
        margin_bottom->declaration = decl;
        margin_bottom->spec = *spec;
    }
}

void modest_style_map_collate_declaration_margin_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->margin_left == NULL) {
        m_node->raw_style->margin_left = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *margin_left = m_node->raw_style->margin_left;
    
    if(modest_finder_thread_spec_is_up(spec, &margin_left->spec)) {
        margin_left->declaration = decl;
        margin_left->spec = *spec;
    }
}

void modest_style_map_collate_declaration_margin_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->margin_right == NULL) {
        m_node->raw_style->margin_right = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *margin_right = m_node->raw_style->margin_right;
    
    if(modest_finder_thread_spec_is_up(spec, &margin_right->spec)) {
        margin_right->declaration = decl;
        margin_right->spec = *spec;
    }
}

void modest_style_map_collate_declaration_margin_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->margin_top == NULL) {
        m_node->raw_style->margin_top = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *margin_top = m_node->raw_style->margin_top;
    
    if(modest_finder_thread_spec_is_up(spec, &margin_top->spec)) {
        margin_top->declaration = decl;
        margin_top->spec = *spec;
    }
}

/* display */
void modest_style_map_collate_declaration_display(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->display == NULL) {
        m_node->raw_style->display = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *display = m_node->raw_style->display;
    
    if(modest_finder_thread_spec_is_up(spec, &display->spec)) {
        display->declaration = decl;
        display->spec = *spec;
    }
}

/* border width */
void modest_style_map_collate_declaration_border_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t val_four = *((mycss_values_shorthand_four_t*)(decl->value));
    mycss_declaration_t* declaration = modest->mycss_entry->declaration;
    
    if(val_four.two == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        
        val_four.two   = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.one, true);
        
        mycss_declaration_entry_type_set(val_four.two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH);
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH);
    }
    else if(val_four.three == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH);
    }
    else if(val_four.four == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        
        val_four.four = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH);
    }
    else {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        mycss_declaration_entry_important_set(val_four.four, decl->is_important);
    }
    
    modest_style_map_collate_declaration_border_top_width(modest, node, val_four.one, spec);
    modest_style_map_collate_declaration_border_right_width(modest, node, val_four.two, spec);
    modest_style_map_collate_declaration_border_bottom_width(modest, node, val_four.three, spec);
    modest_style_map_collate_declaration_border_left_width(modest, node, val_four.four, spec);
}

void modest_style_map_collate_declaration_border_top_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_top_width == NULL) {
        m_node->raw_style->border_top_width = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_top_width = m_node->raw_style->border_top_width;
    
    if(modest_finder_thread_spec_is_up(spec, &border_top_width->spec)) {
        border_top_width->declaration = decl;
        border_top_width->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_right_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_right_width == NULL) {
        m_node->raw_style->border_right_width = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_right_width = m_node->raw_style->border_right_width;
    
    if(modest_finder_thread_spec_is_up(spec, &border_right_width->spec)) {
        border_right_width->declaration = decl;
        border_right_width->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_bottom_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_bottom_width == NULL) {
        m_node->raw_style->border_bottom_width = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_bottom_width = m_node->raw_style->border_bottom_width;
    
    if(modest_finder_thread_spec_is_up(spec, &border_bottom_width->spec)) {
        border_bottom_width->declaration = decl;
        border_bottom_width->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_left_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_left_width == NULL) {
        m_node->raw_style->border_left_width = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_left_width = m_node->raw_style->border_left_width;
    
    if(modest_finder_thread_spec_is_up(spec, &border_left_width->spec)) {
        border_left_width->declaration = decl;
        border_left_width->spec = *spec;
    }
}

/* border style */
void modest_style_map_collate_declaration_border_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t val_four = *((mycss_values_shorthand_four_t*)(decl->value));
    mycss_declaration_t* declaration = modest->mycss_entry->declaration;
    
    if(val_four.two == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        
        val_four.two   = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.one, true);
        
        mycss_declaration_entry_type_set(val_four.two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE);
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE);
    }
    else if(val_four.three == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        
        val_four.three = mycss_declaration_entry_clone(declaration, val_four.one, true);
        val_four.four  = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE);
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE);
    }
    else if(val_four.four == NULL) {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        
        val_four.four = mycss_declaration_entry_clone(declaration, val_four.two, true);
        
        mycss_declaration_entry_type_set(val_four.four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE);
    }
    else {
        mycss_declaration_entry_important_set(val_four.one, decl->is_important);
        mycss_declaration_entry_important_set(val_four.two, decl->is_important);
        mycss_declaration_entry_important_set(val_four.three, decl->is_important);
        mycss_declaration_entry_important_set(val_four.four, decl->is_important);
    }
    
    modest_style_map_collate_declaration_border_top_style(modest, node, val_four.one, spec);
    modest_style_map_collate_declaration_border_right_style(modest, node, val_four.two, spec);
    modest_style_map_collate_declaration_border_bottom_style(modest, node, val_four.three, spec);
    modest_style_map_collate_declaration_border_left_style(modest, node, val_four.four, spec);
}

void modest_style_map_collate_declaration_border_top_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_top_style == NULL) {
        m_node->raw_style->border_top_style = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_top_style = m_node->raw_style->border_top_style;
    
    if(modest_finder_thread_spec_is_up(spec, &border_top_style->spec)) {
        border_top_style->declaration = decl;
        border_top_style->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_right_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_right_style == NULL) {
        m_node->raw_style->border_right_style = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_right_style = m_node->raw_style->border_right_style;
    
    if(modest_finder_thread_spec_is_up(spec, &border_right_style->spec)) {
        border_right_style->declaration = decl;
        border_right_style->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_bottom_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_bottom_style == NULL) {
        m_node->raw_style->border_bottom_style = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_bottom_style = m_node->raw_style->border_bottom_style;
    
    if(modest_finder_thread_spec_is_up(spec, &border_bottom_style->spec)) {
        border_bottom_style->declaration = decl;
        border_bottom_style->spec = *spec;
    }
}

void modest_style_map_collate_declaration_border_left_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->border_left_style == NULL) {
        m_node->raw_style->border_left_style = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *border_left_style = m_node->raw_style->border_left_style;
    
    if(modest_finder_thread_spec_is_up(spec, &border_left_style->spec)) {
        border_left_style->declaration = decl;
        border_left_style->spec = *spec;
    }
}

/* box sizing */
void modest_style_map_collate_declaration_box_sizing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->box_sizing == NULL) {
        m_node->raw_style->box_sizing = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *box_sizing = m_node->raw_style->box_sizing;
    
    if(modest_finder_thread_spec_is_up(spec, &box_sizing->spec)) {
        box_sizing->declaration = decl;
        box_sizing->spec = *spec;
    }
}

/* vertical align */
void modest_style_map_collate_declaration_vertical_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->vertical_align == NULL) {
        m_node->raw_style->vertical_align = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *vertical_align = m_node->raw_style->vertical_align;
    
    if(modest_finder_thread_spec_is_up(spec, &vertical_align->spec)) {
        vertical_align->declaration = decl;
        vertical_align->spec = *spec;
    }
}

/* vertical align */
void modest_style_map_collate_declaration_line_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->line_height == NULL) {
        m_node->raw_style->line_height = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *line_height = m_node->raw_style->line_height;
    
    if(modest_finder_thread_spec_is_up(spec, &line_height->spec)) {
        line_height->declaration = decl;
        line_height->spec = *spec;
    }
}

/* text decoration */
void modest_style_map_collate_declaration_text_decoration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_decoration_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->text_decoration_color == NULL) {
        m_node->raw_style->text_decoration_color = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *text_decoration_color = m_node->raw_style->text_decoration_color;
    
    if(modest_finder_thread_spec_is_up(spec, &text_decoration_color->spec)) {
        text_decoration_color->declaration = decl;
        text_decoration_color->spec = *spec;
    }
}

void modest_style_map_collate_declaration_text_decoration_line(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->text_decoration_line == NULL) {
        m_node->raw_style->text_decoration_line = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *text_decoration_line = m_node->raw_style->text_decoration_line;
    
    if(modest_finder_thread_spec_is_up(spec, &text_decoration_line->spec)) {
        text_decoration_line->declaration = decl;
        text_decoration_line->spec = *spec;
    }
}

void modest_style_map_collate_declaration_text_decoration_skip(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->text_decoration_skip == NULL) {
        m_node->raw_style->text_decoration_skip = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *text_decoration_skip = m_node->raw_style->text_decoration_skip;
    
    if(modest_finder_thread_spec_is_up(spec, &text_decoration_skip->spec)) {
        text_decoration_skip->declaration = decl;
        text_decoration_skip->spec = *spec;
    }
}

void modest_style_map_collate_declaration_text_decoration_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    
    if(m_node->raw_style->text_decoration_style == NULL) {
        m_node->raw_style->text_decoration_style = modest_style_raw_declaration_create(modest);
    }
    
    modest_style_raw_declaration_t *text_decoration_style = m_node->raw_style->text_decoration_style;
    
    if(modest_finder_thread_spec_is_up(spec, &text_decoration_style->spec)) {
        text_decoration_style->declaration = decl;
        text_decoration_style->spec = *spec;
    }
}

/* not yet */
void modest_style_map_collate_declaration_align_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_align_items(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_align_self(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_delay(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_fill_mode(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_iteration_count(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_name(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_play_state(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_animation_timing_function(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_appearance(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_backface_visibility(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_attachment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_clip(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_repeat(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_background_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_bookmark_label(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_bookmark_level(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_bookmark_state(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_bottom_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_bottom_left_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_bottom_right_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_collapse(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_image_outset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_image_repeat(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_image_slice(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_image_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_left_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_right_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_top_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_top_left_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_border_top_right_radius(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_box_decoration_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_box_shadow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_box_suppress(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_break_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_break_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_break_inside(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_caption_side(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_caret(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_caret_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_caret_shape(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_clear(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_clear_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_color_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_color_interpolation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_color_interpolation_filters(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_color_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_count(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_fill(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_gap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_rule(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_rule_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_rule_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_rule_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_span(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_column_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_columns(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_contain(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_continue(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_counter_increment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_cue(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_cue_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_cue_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_cursor(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_empty_cells(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_fill(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_fill_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_fill_rule(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_basis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_direction(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_flow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_grow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_shrink(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_flex_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_float(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_float_displace(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_family(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_feature_settings(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_kerning(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_language_override(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_size_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_stretch(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_synthesis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_alternates(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_caps(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_east_asian(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_ligatures(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_numeric(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_variant_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_font_weight(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_glyph_orientation_vertical(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_hanging_punctuation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_hyphens(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_image_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_indent_edge_reset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_inline_size_step(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_justify_content(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_letter_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_line_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_line_height_step(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_list_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_list_style_image(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_list_style_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_list_style_type(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_marker(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_marker_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_marker_mid(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_marker_side(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_marker_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_max_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_max_lines(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_max_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_min_height(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_min_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_nav_down(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_nav_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_nav_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_nav_up(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_offset_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_offset_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_offset_end(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_offset_start(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_order(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_orphans(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_outline(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_outline_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_outline_offset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_outline_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_outline_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_overflow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_overflow_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_overflow_x(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_overflow_y(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_pause(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_pause_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_pause_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_perspective(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_perspective_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_presentation_level(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_quotes(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_region_fragment(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_resize(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_rest(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_rest_after(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_rest_before(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_ruby_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_ruby_merge(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_ruby_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_scroll_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_scroll_snap_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_scroll_snap_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_scroll_snap_stop(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_scroll_snap_type(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_shape_image_threshold(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_shape_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_shape_outside(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_shape_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_speak(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_speak_as(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_string_set(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_dasharray(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_dashoffset(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_linecap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_linejoin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_miterlimit(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_opacity(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_stroke_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_tab_size(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_table_layout(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_align(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_align_all(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_align_last(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_combine_upright(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_emphasis(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_emphasis_color(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_emphasis_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_emphasis_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_indent(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_justify(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_orientation(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_overflow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_rendering(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_shadow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_size_adjust(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_transform(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_text_underline_position(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_touch_action(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transform(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transform_box(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transform_origin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transform_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transition(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transition_delay(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transition_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transition_property(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_transition_timing_function(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_unicode_bidi(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_user_select(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_visibility(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_balance(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_duration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_family(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_pitch(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_range(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_rate(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_stress(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_voice_volume(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_white_space(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_widows(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_will_change(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_word_break(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_word_spacing(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_word_wrap(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_wrap_flow(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_wrap_through(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_writing_mode(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}

void modest_style_map_collate_declaration_z_index(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, modest_style_raw_specificity_t* spec)
{
}


