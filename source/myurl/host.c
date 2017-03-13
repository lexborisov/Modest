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

#include "myurl/host.h"
#include "myurl/url.h"
#include "myurl/resources.h"
#include "mycore/utils/resources.h"

myurl_host_t * myurl_host_create(myurl_t* url)
{
    myurl_host_t *host = url->callback_malloc(sizeof(myurl_host_t), url->callback_ctx);
    
    if(host)
        memset(host, 0, sizeof(myurl_host_t));
    
    return host;
}

mystatus_t myurl_host_init(myurl_t* url)
{
    return MyURL_STATUS_OK;
}

void myurl_host_clean(myurl_t* url, myurl_host_t* host)
{
    if(host->type == MyURL_HOST_TYPE_DOMAIN)
        url->callback_free(host->value.domain.value, url->callback_ctx);
    
    if(host->type == MyURL_HOST_TYPE_OPAQUE)
        url->callback_free(host->value.opaque.value, url->callback_ctx);
    
    memset(host, 0, sizeof(myurl_host_t));
}

myurl_host_t * myurl_host_destroy(myurl_t* url, myurl_host_t* host, bool destroy_self)
{
    if(host == NULL)
        return NULL;
    
    myurl_host_clean(url, host);
    
    if(destroy_self) {
        return url->callback_free(host, url->callback_ctx);
    }
    
    return host;
}

mystatus_t myurl_host_copy(myurl_t* url, myurl_host_t* host_from, myurl_host_t* host_to)
{
    host_to->type = host_from->type;
    
    switch (host_from->type) {
        case MyURL_HOST_TYPE_DOMAIN:
            return myurl_utils_data_copy_set(url, host_from->value.domain.value, host_from->value.domain.length,
                                                  &host_to->value.domain.value, &host_to->value.domain.length);
            
        default:
            break;
    }
    
    return MyURL_STATUS_OK;
}

/* Create Values */
myurl_host_ipv_t * myurl_host_ipv6_entry_create(myurl_t* url)
{
    myurl_host_ipv_t *ipv = url->callback_malloc(sizeof(myurl_host_ipv_t), url->callback_ctx);
    
    if(ipv)
        memset(ipv, 0, sizeof(myurl_host_ipv_t));
    
    return ipv;
}

/* Parsing */
mystatus_t myurl_host_parser(myurl_t* url, myurl_host_t* host, const char* data, size_t data_size, bool is_special)
{
    size_t data_length = 0;
    
    /* 1 */
    if(data[data_length] == '[') {
        if(data[ (data_size - 1) ] != ']') {
            // parse error
            return MyURL_STATUS_ERROR;
        }
        
        data_length++;
        
        host->type = MyURL_HOST_TYPE_IPv6;
        return myurl_host_ipv6_parser(&host->value.ipv, &data[data_length], (data_size - 2));
    }
    
    /* 2 */
    if(is_special == false) {
        host->type = MyURL_HOST_TYPE_OPAQUE;
        return myurl_host_opaque_host_parser(url, &host->value.opaque, data, data_size);
    }
    
    /* 3 */
    char *domain = myurl_utils_data_copy(url, data, data_size);
    size_t domain_size = myurl_utils_percent_decode_bytes_in_data(domain, data_size);
    
    /* 4 */
    char* ascii_domain;
    size_t ascii_domain_size;
    mystatus_t status = myurl_host_domain_to_ascii(url, &ascii_domain, &ascii_domain_size, domain, domain_size,
                                                       false, false, MyURL_HOST_IDNA_PROCESSING_OPTION_NONTRANSITIONAL);
    /* 5 */
    if(status != MyURL_STATUS_OK) {
        // parse error
        return status;
    }
    
    /* 6 */
    const unsigned char *u_ascii_domain = (const unsigned char*)ascii_domain;
    data_length = 0;
    
    while(data_length < ascii_domain_size) {
        if(myurl_resources_static_map_forbidden_host_code_point[ u_ascii_domain[data_length] ] != 0xff) {
            // parse error
            return MyURL_STATUS_ERROR;
        }
        
        data_length++;
    }
    
    /* 7 */
    bool failure;
    if(myurl_host_ipv4_parser(&host->value.ipv, ascii_domain, ascii_domain_size, &failure) == MyURL_STATUS_OK) {
        url->callback_free(ascii_domain, url->callback_ctx);
        
        host->type = MyURL_HOST_TYPE_IPv4;
        return MyURL_STATUS_OK;
    }
    
    if(failure) {
        // parse error
        url->callback_free(ascii_domain, url->callback_ctx);
        return MyURL_STATUS_ERROR;
    }
    
    host->type = MyURL_HOST_TYPE_DOMAIN;
    host->value.domain.value = ascii_domain;
    host->value.domain.length = ascii_domain_size;
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_domain_to_ascii(myurl_t* url, char** return_domain, size_t* return_domain_size,
                                          char* domain, size_t domain_size,
                                          bool UseSTD3ASCIIRules, bool VerifyDnsLength,
                                          myurl_host_idna_processing_option_t opt)
{
    
    
    
    *return_domain = domain;
    *return_domain_size = domain_size;
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_opaque_host_parser(myurl_t* url, myurl_host_opaque_t* opaque, const char* data, size_t data_size)
{
    // TODO: see this
    /* 1 */
    /* If input contains a forbidden host code point excluding "%", validation error, return failure. */
    size_t length = 0, offset = 0;
    const unsigned char *u_data = (const unsigned char*)data;
    
    while(length < data_size) {
        if(myurl_resources_static_map_forbidden_host_code_point[ u_data[length] ] != 0xff) {
            offset = length;
            
            while(offset) {
                offset--;
                
                if(data[offset] == '%') {
                    break;
                }
            }
            
            if(offset == 0 && data[offset] != '%') {
                // parse error
                return MyURL_STATUS_ERROR;
            }
        }
        
        length++;
    }
    
    /* 2 */
    length = 0;
    char *in_hex_val = myurl_utils_percent_encode(url, data, data_size, myurl_resources_static_map_C0, &length);
    
    if(in_hex_val == NULL) {
        // parse error
        return MyURL_STATUS_ERROR;
    }
    
    /* 3 */
    opaque->value = in_hex_val;
    opaque->length = length;
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_ipv4_number_parser(const char* data, size_t data_size, unsigned int* number, bool* validationErrorFlag)
{
    size_t length = 0;
    
    /* 1 */
    unsigned int r = 10;
    
    /* 2 */
    if(data_size > 1) {
        if(*data == '0' && (data[1] == 'x' || data[1] == 'X')) {
            /* 2.1 */
            *validationErrorFlag = true;
            
            /* 2.2 */
            length += 2;
            
            /* 2.3 */
            r = 16;
        }
        else if(*data == '0') {
            /* 3.1 */
            *validationErrorFlag = true;
            
            /* 3.2 */
            length++;
            
            /* 3.3 */
            r = 8;
        }
    }
    
    *number = 0;
    
    if(r == 10) {
        while(length < data_size) {
            if(mycore_string_chars_num_map[ (unsigned char)data[length] ] == 0xff) {
                return MyURL_STATUS_ERROR;
            }
            
            *number = mycore_string_chars_num_map[ (unsigned char)data[length] ] + *number * r;
            
            length++;
        }
    }
    else if(r == 16) {
        while(length < data_size) {
            if(mycore_string_chars_hex_map[ (unsigned char)data[length] ] == 0xff) {
                return MyURL_STATUS_ERROR;
            }
            
            *number = mycore_string_chars_hex_map[ (unsigned char)data[length] ] + *number * r;
            
            length++;
        }
    }
    else {
        while(length < data_size) {
            if((unsigned char)data[length] < 0x30 || (unsigned char)data[length] > 0x37) {
                return MyURL_STATUS_ERROR;
            }
            
            *number = mycore_string_chars_num_map[ (unsigned char)data[length] ] + *number * r;
            
            length++;
        }
    }
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_ipv4_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size, bool* failure)
{
    if(failure)
        *failure = false;
    
    size_t data_length = 0;
    memset(ipv, 0, sizeof(myurl_host_ipv_t));
    
    /* 1 */
    bool validationErrorFlag = false;
    
    /* 2 */
    size_t part_begin = data_length;
    size_t part_count = 0;
    
    while(data_length < data_size)
    {
        if(data[data_length] == '.')
        {
            /* 4 */
            if(part_count == 3) {
                return MyURL_STATUS_ERROR;
            }
            
            /* 6.1 */
            if((data_length - part_begin) == 0) {
                return MyURL_STATUS_ERROR;
            }
            
            if(myurl_host_ipv4_number_parser(&data[part_begin], (data_length - part_begin), &ipv->pieces[part_count], &validationErrorFlag)) {
                return MyURL_STATUS_ERROR;
            }
            
            part_begin = data_length + 1;
            part_count++;
        }
        
        data_length++;
    }
    
    if(data_length - part_begin) {
        if(myurl_host_ipv4_number_parser(&data[part_begin], (data_length - part_begin), &ipv->pieces[part_count], &validationErrorFlag)) {
            return MyURL_STATUS_ERROR;
        }
        
        part_count++;
    }
    
    if(part_count == 0) {
        return MyURL_STATUS_ERROR;
    }
    
    /* 7 */
//    if(validationErrorFlag) {
//        // parse error
//    }
    
    /* 8 */
    for(size_t i = 0; i < part_count; i++) {
        if(ipv->pieces[i] > 255) {
            // parse error
            
            /* if not last */
            if(i != (part_count - 1)) {
                if(failure)
                    *failure = true;
                
                return MyURL_STATUS_ERROR;
            }
        }
    }
    
    /* 9 */
    if(ipv->pieces[(part_count - 1)] >= mycore_power(256, (5 - part_count))) {
        if(failure)
            *failure = true;
        
        return MyURL_STATUS_ERROR;
    }
    
    /* 10 */
    part_count--;
    unsigned int ipv4 = ipv->pieces[part_count];
    
    /* calc end char count */
    for(size_t i = 0; i < part_count; i++) {
        size_t n = mycore_power(256, (3 - i));
        ipv4 += ipv->pieces[i] * n;
    }
    
    ipv->pieces[0] = ipv4;
    ipv->type = MyURL_HOST_TYPE_IP_v4;
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_ipv6_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size)
{
    size_t data_length = 0;
    const unsigned char *u_data = (const unsigned char*)data;
    
    /* 1 */
    memset(ipv, 0, sizeof(myurl_host_ipv_t));
    /* 2 */
    unsigned int *piece = ipv->pieces;
    unsigned int *piece_pointer = ipv->pieces;
    /* 3 */
    unsigned int *compress_pointer = NULL;
    
    ipv->type = MyURL_HOST_TYPE_IP_v6;
    
    /* 5 */
    if(data[data_length] == ':') {
        data_length++;
        
        /* 5.1 */
        if(data_length >= data_size || data[data_length] != ':') {
            return MyURL_STATUS_ERROR;
        }
        
        /* 5.2 */
        data_length++;
        
        /* 5.3 */
        piece_pointer++;
        piece = piece_pointer;
        
        compress_pointer = piece_pointer;
    }
    
    /* 6 */
    while(data_length < data_size)
    {
        /* 6.1 */
        if(piece_pointer == &ipv->pieces[8]) {
            // parse error
            return MyURL_STATUS_ERROR;
        }
        
        /* 6.2 */
        if(data[data_length] == ':') {
            /* 6.2.1 */
            if(compress_pointer != NULL) {
                // parse error
                return MyURL_STATUS_ERROR;
            }
            
            /* 6.2.2 */
            data_length++;
            
            piece_pointer++;
            piece = piece_pointer;
            
            compress_pointer = piece_pointer;
            continue;
        }
        
        /* 6.3 and 6.4 */
        unsigned int num = 0;
        size_t i = 0;
        
        while((i < 4) && (data_length < data_size)) {
            if(mycore_string_chars_hex_map[ u_data[data_length] ] != 0xff) {
                num <<= 4;
                num |= mycore_string_chars_hex_map[ u_data[data_length] ];
            }
            else
                break;
            
            data_length++;
            i++;
        }
        
        /* 6.5 */
        if(data_length < data_size)
        {
            if(data[data_length] == '.') {
                /* 6.5.1 */
                if(i == 0) {
                    // parse error
                    return MyURL_STATUS_ERROR;
                }
                
                /* 6.5.2 */
                data_length -= i;
                
                /* 6.5.3 */
                if(myurl_host_ipv6_ipv4_parser(ipv, &data[data_length], (data_size - data_length), &piece_pointer)) {
                    return MyURL_STATUS_ERROR;
                }
                
                break;
            }
            else if(data[data_length] == ':') {
                /* 6.5.1 */
                data_length++;
                
                /* 6.5.2 */
                if(data_length >= data_size) {
                    // parse error
                    return MyURL_STATUS_ERROR;
                }
            }
            else {
                // parse error
                return MyURL_STATUS_ERROR;
            }
        }
        
        /* 6.6 */
        *piece = num;
        /* 6.7 */
        piece_pointer++;
        piece = piece_pointer;
    }
    
    /* 11 */
    /* 11.1 */
    if(compress_pointer) {
        unsigned int swaps = (unsigned int)(piece_pointer - compress_pointer);
        size_t i = 7;
        
        /* 11.2 and 11.3 */
        while(i && swaps > 0) {
            unsigned int *tmp = compress_pointer + (swaps - 1);
            unsigned int num = *tmp;
            
            *tmp = ipv->pieces[i];
            ipv->pieces[i] = num;
            
            swaps--;
            i--;
        }
        
        return MyURL_STATUS_OK;
    }
    
    /* 12 */
    if(compress_pointer == NULL && piece_pointer != &ipv->pieces[8]) {
        // parse error
        return MyURL_STATUS_ERROR;
    }
    
    return MyURL_STATUS_OK;
}

mystatus_t myurl_host_ipv6_ipv4_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size, unsigned int** piece_pointer)
{
    size_t data_length = 0;
    const unsigned char *u_data = (const unsigned char*)data;
    
    /* 8 */
    if((*piece_pointer - ipv->pieces) > 6) {
        // parse error
        return MyURL_STATUS_ERROR;
    }
    
    /* 9 */
    unsigned int numbersSeen = 0;
    
    /* 10 */
    while(data_length < data_size)
    {
        /* 10.1 */
        int value = -1;
        
        /* 10.2 */
        if(numbersSeen > 0)
        {
            if(data[data_length] != '.' || numbersSeen >= 4) {
                // parse error
                return MyURL_STATUS_ERROR;
            }
            
            data_length++;
            
            if(data_length >= data_size)
                return MyURL_STATUS_ERROR;
        }
        
        /* 10.3 */
        if(mycore_string_chars_num_map[ u_data[data_length] ] == 0xff) {
            // parse error
            return MyURL_STATUS_ERROR;
        }
        
        /* 10.4 */
        while(data_length < data_size && mycore_string_chars_num_map[ u_data[data_length] ] != 0xff)
        {
            /* 10.4.1 */
            unsigned int number = mycore_string_chars_num_map[ u_data[data_length] ];
            
            /* 10.4.2 */
            if(value == -1) {
                value = (int)number;
            }
            else if(value == 0) {
                // parse error
                return MyURL_STATUS_ERROR;
            }
            else {
                value = value * 10 + number;
            }
            
            /* 10.4.3 */
            if(value > 255) {
                // parse error
                return MyURL_STATUS_ERROR;
            }
            
            /* 10.4.2 */
            data_length++;
        }
        
        /* 10.5 */
        **piece_pointer = **piece_pointer * 0x100 + value;
        
        /* 10.6 */
        numbersSeen++;
        
        /* 10.7 */ // maybe: (numbersSeen % 2 == 0) ?
        if(numbersSeen == 2 || numbersSeen == 4) {
            (*piece_pointer)++;
        }
        
        /* 10.8 */
        if(data_length >= data_size && numbersSeen != 4) {
            // parse error
            return MyURL_STATUS_ERROR;
        }
    }
    
    return MyURL_STATUS_OK;
}


