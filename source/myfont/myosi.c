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

#include "myfont/myosi.h"

uint32_t myfont_read_u32_as_net(uint8_t** data)
{
    int cp = 0;
    
    cp  = **data;       (*data)++;
    cp |= **data << 8;  (*data)++;
    cp |= **data << 16; (*data)++;
    cp |= **data << 24; (*data)++;
    
    return (uint32_t)cp;
}

uint32_t myfont_read_u32(uint8_t** data)
{
    int cp = 0;
    
    cp  = **data << 24; (*data)++;
    cp |= **data << 16; (*data)++;
    cp |= **data << 8;  (*data)++;
    cp |= **data;       (*data)++;
    
    return (uint32_t)cp;
}

int32_t myfont_read_32(uint8_t** data)
{
    int cp = 0;
    
    cp  = **data << 24; (*data)++;
    cp |= **data << 16; (*data)++;
    cp |= **data << 8;  (*data)++;
    cp |= **data;       (*data)++;
    
    return (int32_t)cp;
}

uint32_t myfont_htonl(uint32_t data)
{
    int cp = 0;
    
    cp  = data << 24;
    cp |= data << 16;
    cp |= data << 8;
    cp |= data;
    
    return (uint32_t)cp;
}

uint16_t myfont_read_u16(uint8_t** data)
{
    int cp = 0;
    
    cp  = **data << 8;  (*data)++;
    cp |= **data;       (*data)++;
    
    return (uint16_t)cp;
}

int16_t myfont_read_16(uint8_t** data)
{
    int cp = 0;
    
    cp  = **data << 8; (*data)++;
    cp |= **data;      (*data)++;
    
    return (int16_t)cp;
}

uint8_t myfont_read_u8(uint8_t** data)
{
    int cp = **data;
    (*data)++;
    
    return (uint8_t)cp;
}

int8_t myfont_read_8(uint8_t** data)
{
    int cp = **data;
    (*data)++;
    
    return (int8_t)cp;
}


