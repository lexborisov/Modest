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

#include "modest/style/type.h"

void * modest_style_type_create(modest_t* modest, size_t size)
{
    void* data = (void*)mchar_async_malloc(modest->mstyle_type_obj, modest->mstyle_type_node_id, size);
    
    if(data == NULL)
        return NULL;
    
    memset(data, 0, size);
    
    return data;
}

mystatus_t modest_style_type_init(modest_t* modest, void *data)
{
    return MODEST_STATUS_OK;
}
