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

#include "modest/style/sheet.h"

modest_style_sheet_t * modest_style_sheet_create(modest_t* modest)
{
    modest_style_sheet_t* m_stylesheet = (modest_style_sheet_t*)mcobject_async_malloc(modest->mstylesheet_obj, modest->mstylesheet_node_id, NULL);
    
    if(m_stylesheet == NULL)
        return NULL;
    
    memset(m_stylesheet, 0, sizeof(modest_style_sheet_t));
    
    return m_stylesheet;
}

mystatus_t modest_style_sheet_init(modest_t* modest, modest_style_sheet_t* m_stylesheet)
{
    return MODEST_STATUS_OK;
}


