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

#ifndef MODEST_STYLE_RAW_H
#define MODEST_STYLE_RAW_H
#pragma once

#include <modest/myosi.h>
#include <modest/modest.h>
#include <mycore/utils/mcobject.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct modest_style_raw_declaration modest_style_raw_declaration_t;
typedef struct modest_style_raw_specificity modest_style_raw_specificity_t;

struct modest_style_raw_specificity {
    unsigned int x;
    unsigned int a;
    unsigned int b;
    unsigned int c;
};

struct modest_style_raw_declaration {
    mycss_declaration_entry_t* declaration;
    modest_style_raw_specificity_t spec;
};

modest_style_raw_declaration_t * modest_style_raw_declaration_create(modest_t* modest);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_RAW_H */
