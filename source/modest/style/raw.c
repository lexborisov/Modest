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

#include "modest/style/raw.h"

modest_style_raw_declaration_t * modest_style_raw_declaration_create(modest_t* modest)
{
    modest_style_raw_declaration_t* raw_decl = (modest_style_raw_declaration_t*)mcobject_malloc(modest->mraw_style_declaration_obj, NULL);
    
    if(raw_decl == NULL)
        return NULL;
    
    memset(raw_decl, 0, sizeof(modest_style_raw_declaration_t));
    
    return raw_decl;
}


