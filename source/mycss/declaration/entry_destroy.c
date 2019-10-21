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

#include "mycss/declaration/entry_destroy.h"

mycss_declaration_entry_t * mycss_declaration_entry_destroy_undef(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    if(decl_entry->value)
        decl_entry->value = mycss_values_destroy(declaration->ref_entry, decl_entry->value);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_type_list(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_type_list(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_padding(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_four(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_margin(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    return mycss_declaration_entry_destroy_padding(declaration, decl_entry, self_destroy);
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_width(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    return mycss_declaration_entry_destroy_padding(declaration, decl_entry, self_destroy);
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_radius(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    return mycss_declaration_entry_destroy_padding(declaration, decl_entry, self_destroy);
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_style(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    return mycss_declaration_entry_destroy_padding(declaration, decl_entry, self_destroy);
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_color(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    return mycss_declaration_entry_destroy_padding(declaration, decl_entry, self_destroy);
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_font(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_font(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_x(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_border(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_top_right_radius(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_two_type(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_top_left_radius(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_two_type(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_bottom_right_radius(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_two_type(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_bottom_left_radius(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_two_type(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}


mycss_declaration_entry_t * mycss_declaration_entry_destroy_background(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_background(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_background_image(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_image_list(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_background_repeat(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_background_repeat(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_background_position(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_background_position(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_background_size(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_background_size(declaration->ref_entry, decl_entry->value, true);
    
    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }
    
    return decl_entry;
}

mycss_declaration_entry_t * mycss_declaration_entry_destroy_border_spacing(mycss_declaration_t* declaration, mycss_declaration_entry_t* decl_entry, bool self_destroy)
{
    decl_entry->value = mycss_values_destroy_shorthand_two_type(declaration->ref_entry, decl_entry->value, true);

    if(self_destroy) {
        mcobject_free(declaration->mcobject_entries, decl_entry);
        return NULL;
    }

    return decl_entry;
}



