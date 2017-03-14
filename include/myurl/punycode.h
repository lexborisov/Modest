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
 Foundation, Inc., 51 Franklin avl_treet, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MyURL_PUNYCODE_H
#define MyURL_PUNYCODE_H
#pragma once

#include <myurl/myosi.h>
#include <myhtml/mystring.h>
#include <myencoding/encoding.h>

#ifdef __cplusplus
extern "C" {
#endif

enum myurl_punycode_const {
    MyURL_PUNYCODE_CONST_BASE         = 36,
    MyURL_PUNYCODE_CONST_TMIN         = 1,
    MyURL_PUNYCODE_CONST_TMAX         = 26,
    MyURL_PUNYCODE_CONST_SKEW         = 38,
    MyURL_PUNYCODE_CONST_DAMP         = 700,
    MyURL_PUNYCODE_CONST_INITIAL_BIAS = 72,
    MyURL_PUNYCODE_CONST_INITIAL_N    = 0x80,
    MyURL_PUNYCODE_CONST_DELIMITER    = 0x2D
};

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyURL_PUNYCODE_H */
