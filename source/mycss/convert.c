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

#include "convert.h"
#include "mycore/utils/resources.h"

const char * mycss_convert_split_dimension_string(mycore_string_t* str, double* value, bool* is_float)
{
    size_t length = mycss_convert_data_to_double(str->data, str->length, value, is_float);
    return &str->data[length];
}

// TODO: float or double???
size_t mycss_convert_data_to_double(const char *data, size_t size, double *return_num, bool* is_float)
{
    double p10;
    bool is_negative = false;
    size_t offset = 0;
    
    *return_num = 0.0f;
    
    switch (data[offset]) {
        case '-': is_negative = true; /* fall through */
        case '+': offset++;
    }
    
    double number    = 0.;
    int num_digits   = 0;
    int num_decimals = 0;
    int exponent     = 0;
    
    // digits
    while(offset < size && (data[offset] >= '0' && data[offset] <= '9'))
    {
        number = (data[offset] - '0') + number * 10;
        
        ++offset;
        ++num_digits;
    }
    
    if(offset == size) {
        if(is_negative) number = -number;
        
        *return_num = number;
        
        if(is_float)
            *is_float = false;
        
        return offset;
    }
    
    // decimals
    if(data[offset] == '.') {
        ++offset;
        
        while (offset < size && (data[offset] >= '0' && data[offset] <= '9'))
        {
            number = (data[offset] - '0') + number * 10;
            
            ++offset;
            ++num_digits;
            ++num_decimals;
        }
        
        exponent -= num_decimals;
    }
    else {
        if(is_negative) number = -number;
        
        *return_num = number;
        
        if(is_float)
            *is_float = false;
        
        return offset;
    }
    
    if(num_digits == 0)
        return 0;
    
    if(is_float)
        *is_float = true;
    
    // Correct for sign
    if(is_negative) number = -number;
    
    int n = 0;
    
    // Process an exponent string
    if(offset < size && (data[offset] == 'e' || data[offset] == 'E'))
    {
        ++offset;
        
        if(offset >= size || (data[offset] != '-' && data[offset] != '+' &&
                              (data[offset] < '0' || data[offset] > '9')))
        {
            offset--;
        }
        else {
            // Handle optional sign
            is_negative = false;
            
            switch(data[offset]) {
                case '-': is_negative = true; /* fall through */
                case '+': offset++;
            }
            
            // Process string of digits
            while(offset < size && (data[offset] >= '0' && data[offset] <= '9'))
            {
                n = (data[offset] - '0') + n * 10;
                ++offset;
            }
            
            if(is_negative) {
                exponent -= n;
            } else {
                exponent += n;
            }
        }
    }
    
    // Scale the result
    p10 = 10.;
    n = exponent;
    
    if (n < 0) n = -n;
    
    while (n) {
        if (n & 1) {
            if (exponent < 0) {
                number /= p10;
            } else {
                number *= p10;
            }
        }
        
        n >>= 1;
        p10 *= p10;
    }
    
    *return_num = number;
    
    if(is_float)
        *is_float = true;
    
    return offset;
}

size_t mycss_convert_data_to_integer(const char* data, size_t size, long* return_num)
{
    long res_num = 0;
    bool is_negative = false;
    size_t offset = 0;
    
    switch (data[offset]) {
        case '-': is_negative = true;
        case '+': offset++;
    }
    
    const unsigned char* u_data = (const unsigned char*)data;
    
    while(offset < size && mycore_string_chars_num_map[u_data[offset]] != 0xff)
    {
        res_num = mycore_string_chars_num_map[ u_data[offset] ] + res_num * 10;
        ++offset;
    }
    
    if(is_negative)
        res_num = -res_num;
    
    *return_num = res_num;
    
    return offset;
}

size_t mycss_convert_hex_to_codepoint(const char *data, size_t size, size_t *codepoint, unsigned int max_consumed)
{
    const unsigned char *u_data = (const unsigned char*)data;
    
    size_t length = 0;
    *codepoint = 0;
    
    while(length < size)
    {
        if(mycore_string_chars_hex_map[u_data[length]] != 0xff) {
            *codepoint <<= 4;
            *codepoint |= mycore_string_chars_hex_map[ u_data[length] ];
            
            --max_consumed;
            
            if(max_consumed == 0)
                break;
        }
        else
            break;
        
        ++length;
    }
    
    return length;
}

size_t mycss_convert_unicode_range_to_codepoint(const char *data, size_t size, size_t *start, size_t *end)
{
    size_t length = mycss_convert_hex_to_codepoint(data, size, start, 6);
    
    if(length == size) {
        *end = 0;
        return length;
    }
    
    if(data[length] == '?')
    {
        *end = *start;
        
        do {
            *start <<= 4;
            *start |= mycore_string_chars_hex_map[ 0x30 ]; // 0x30 == '0'
            
            *end <<= 4;
            *end |= mycore_string_chars_hex_map[ 0x46 ]; // 0x46 == 'F'
            
            ++length;
        }
        while(length < size && data[length] == '?');
        
        return length;
    }
    
    if(data[length] == '-') {
        ++length;
        
        length += mycss_convert_hex_to_codepoint(&data[length], (size - length), end, 6);
    }
    else
        *end = 0;
    
    return length;
}


