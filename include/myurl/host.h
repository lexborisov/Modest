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

#ifndef MyURL_HOST_H
#define MyURL_HOST_H
#pragma once

#include <myurl/myosi.h>
#include <myhtml/mystring.h>

#include <myurl/parser.h>
#include <myurl/utils.h>

#ifdef __cplusplus
extern "C" {
#endif

enum myurl_host_type {
    MyURL_HOST_TYPE_UNDEF   = 0x00,
    MyURL_HOST_TYPE_DOMAIN  = 0x01,
    MyURL_HOST_TYPE_IPv4    = 0x02,
    MyURL_HOST_TYPE_IPv6    = 0x03,
    MyURL_HOST_TYPE_OPAQUE  = 0x04,
}
typedef myurl_host_type_t;

enum myurl_host_ipv_type {
    MyURL_HOST_TYPE_IP_UNDEF = 0x00,
    MyURL_HOST_TYPE_IP_v4    = 0x01,
    MyURL_HOST_TYPE_IP_v6    = 0x02,
}
typedef myurl_host_ipv_type_t;

enum myurl_host_idna_processing_option {
    MyURL_HOST_IDNA_PROCESSING_OPTION_UNDEF            = 0x00,
    MyURL_HOST_IDNA_PROCESSING_OPTION_TRANSITIONAL     = 0x01,
    MyURL_HOST_IDNA_PROCESSING_OPTION_NONTRANSITIONAL  = 0x02,
}
typedef myurl_host_idna_processing_option_t;

struct myurl_host_ipv {
    unsigned int pieces[9];
    myurl_host_ipv_type_t type;
}
typedef myurl_host_ipv_t;

struct myurl_host_opaque {
    char* value;
    size_t length;
}
typedef myurl_host_opaque_t;

struct myurl_host_domain {
    char* value;
    size_t length;
}
typedef myurl_host_domain_t;

struct myurl_host {
    union {
        myurl_host_ipv_t ipv;
        myurl_host_opaque_t opaque;
        myurl_host_domain_t domain;
    } value;
    
    myurl_host_type_t type;
}
typedef myurl_host_t;

myurl_host_t * myurl_host_create(myurl_t* url);
mystatus_t myurl_host_init(myurl_t* url);
void myurl_host_clean(myurl_t* url, myurl_host_t* host);

myurl_host_t * myurl_host_destroy(myurl_t* url, myurl_host_t* host, bool destroy_self);
mystatus_t myurl_host_copy(myurl_t* url, myurl_host_t* host_from, myurl_host_t* host_to);

mystatus_t myurl_host_parser(myurl_t* url, myurl_host_t* host, const char* data, size_t data_size, bool is_special);
mystatus_t myurl_host_ipv4_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size, bool* failure);
mystatus_t myurl_host_ipv6_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size);
mystatus_t myurl_host_ipv6_ipv4_parser(myurl_host_ipv_t* ipv, const char* data, size_t data_size, unsigned int** piece_pointer);
mystatus_t myurl_host_opaque_host_parser(myurl_t* url, myurl_host_opaque_t* opaque, const char* data, size_t data_size);
mystatus_t myurl_host_domain_to_ascii(myurl_t* url, char** return_domain, size_t* return_domain_size, char* domain, size_t domain_size, bool UseSTD3ASCIIRules, bool VerifyDnsLength, myurl_host_idna_processing_option_t opt);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_HOST_H */
