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

#include "modest/style/map.h"
#include "modest/style/map_resource.h"

void modest_style_map_collate_declaration(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(type < MyCSS_PROPERTY_TYPE_LAST_ENTRY)
        modest_style_map_static_collate_declaration[ type ](modest, node, decl, type, spec);
}

void modest_style_map_collate_declaration_undef(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    
}

void modest_style_map_collate_declaration_for_all(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL)
        return;
    
    modest_node_t *m_node = (modest_node_t*)node->data;
    modest_style_raw_declaration_t *raw_declr = modest_node_raw_declaration_by_type(modest, m_node, type);
    
    if(raw_declr == NULL) {
        raw_declr = modest_style_raw_declaration_create(modest);
        modest_node_raw_declaration_set_by_type(modest, m_node, type, raw_declr);
    }
    
    if(modest_finder_thread_spec_is_up(spec, &raw_declr->spec)) {
        raw_declr->declaration = decl;
        raw_declr->spec = *spec;
    }
}

void modest_style_map_collate_declaration_padding(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t *val_four = (mycss_values_shorthand_four_t*)decl->value;
    
    if(val_four->two == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_LEFT, spec);
    }
    else if(val_four->three == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_PADDING_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_PADDING_LEFT, spec);
    }
    else if(val_four->four == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_PADDING_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_PADDING_LEFT, spec);
    }
    else {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_PADDING_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_PADDING_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_PADDING_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->four, MyCSS_PROPERTY_TYPE_PADDING_LEFT, spec);
    }
}

/* margin */
void modest_style_map_collate_declaration_margin(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t *val_four = (mycss_values_shorthand_four_t*)decl->value;
    
    if(val_four->two == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_LEFT, spec);
    }
    else if(val_four->three == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_MARGIN_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_MARGIN_LEFT, spec);
    }
    else if(val_four->four == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_MARGIN_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_MARGIN_LEFT, spec);
    }
    else {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_MARGIN_TOP, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_MARGIN_RIGHT, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_MARGIN_BOTTOM, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->four, MyCSS_PROPERTY_TYPE_MARGIN_LEFT, spec);
    }
}

/* border width */
void modest_style_map_collate_declaration_border_width(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t *val_four = (mycss_values_shorthand_four_t*)decl->value;
    
    if(val_four->two == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
    }
    else if(val_four->three == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
    }
    else if(val_four->four == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
    }
    else {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
    }
}

/* border style */
void modest_style_map_collate_declaration_border_style(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;
    
    mycss_values_shorthand_four_t *val_four = (mycss_values_shorthand_four_t*)decl->value;
    
    if(val_four->two == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
    }
    else if(val_four->three == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
    }
    else if(val_four->four == NULL) {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
    }
    else {
        modest_style_map_collate_declaration_for_all(modest, node, val_four->one, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->two, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->three, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, val_four->four, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
    }
}

/* background */
void modest_style_map_collate_declaration_background(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_background_t* background = decl->value;
    if(background == NULL)
        return;

    if(background->image) {
        modest_style_map_collate_declaration_for_all(modest, node, background->image, MyCSS_PROPERTY_TYPE_BACKGROUND_IMAGE, spec);
    }
    if(background->color) {
        modest_style_map_collate_declaration_for_all(modest, node, background->color, MyCSS_PROPERTY_TYPE_BACKGROUND_COLOR, spec);
    }
    if(background->attachment) {
        modest_style_map_collate_declaration_for_all(modest, node, background->attachment, MyCSS_PROPERTY_TYPE_BACKGROUND_ATTACHMENT, spec);
    }
    if(background->position) {
        modest_style_map_collate_declaration_for_all(modest, node, background->position, MyCSS_PROPERTY_TYPE_BACKGROUND_POSITION, spec);
    }
    if(background->size) {
        modest_style_map_collate_declaration_for_all(modest, node, background->size, MyCSS_PROPERTY_TYPE_BACKGROUND_SIZE, spec);
    }
    if(background->repeat) {
        modest_style_map_collate_declaration_for_all(modest, node, background->repeat, MyCSS_PROPERTY_TYPE_BACKGROUND_REPEAT, spec);
    }
    if(background->size) {
        modest_style_map_collate_declaration_for_all(modest, node, background->size, MyCSS_PROPERTY_TYPE_BACKGROUND_SIZE, spec);
    }
    if(background->origin) {
        modest_style_map_collate_declaration_for_all(modest, node, background->origin, MyCSS_PROPERTY_TYPE_BACKGROUND_ORIGIN, spec);
    }
    if(background->clip) {
        modest_style_map_collate_declaration_for_all(modest, node, background->clip, MyCSS_PROPERTY_TYPE_BACKGROUND_CLIP, spec);
    }
}

/* border */
void modest_style_map_collate_declaration_border(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_border_t *border = decl->value;

    if(border == NULL)
        return;

    if(border->width) {
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
    }
    if(border->style) {
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
    }
    if(border->color) {
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_TOP_COLOR, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_COLOR, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_LEFT_COLOR, spec);
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_COLOR, spec);
    }
}

/* border-top */
void modest_style_map_collate_declaration_border_top(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_border_t *border = decl->value;

    if(border == NULL)
        return;

    if(border->width) {
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_TOP_WIDTH, spec);
    }
    if(border->style) {
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_TOP_STYLE, spec);
    }
    if(border->color) {
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_TOP_COLOR, spec);
    }
}

/* border-bottom */
void modest_style_map_collate_declaration_border_bottom(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_border_t *border = decl->value;

    if(border == NULL)
        return;

    if(border->width) {
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_WIDTH, spec);
    }
    if(border->style) {
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_STYLE, spec);
    }
    if(border->color) {
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_BOTTOM_COLOR, spec);
    }
}

/* border-left */
void modest_style_map_collate_declaration_border_left(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_border_t *border = decl->value;

    if(border == NULL)
        return;

    if(border->width) {
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_LEFT_WIDTH, spec);
    }
    if(border->style) {
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_LEFT_STYLE, spec);
    }
    if(border->color) {
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_LEFT_COLOR, spec);
    }
}

/* border-right */
void modest_style_map_collate_declaration_border_right(modest_t* modest, myhtml_tree_node_t* node, mycss_declaration_entry_t* decl, mycss_property_type_t type, modest_style_raw_specificity_t* spec)
{
    if(node->data == NULL || decl->value == NULL)
        return;

    mycss_values_border_t *border = decl->value;

    if(border == NULL)
        return;

    if(border->width) {
        modest_style_map_collate_declaration_for_all(modest, node, border->width, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_WIDTH, spec);
    }
    if(border->style) {
        modest_style_map_collate_declaration_for_all(modest, node, border->style, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_STYLE, spec);
    }
    if(border->color) {
        modest_style_map_collate_declaration_for_all(modest, node, border->color, MyCSS_PROPERTY_TYPE_BORDER_RIGHT_COLOR, spec);
    }
}

