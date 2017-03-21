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

#ifndef MODEST_MYOSI_H
#define MODEST_MYOSI_H
#pragma once

#include "mycore/myosi.h"
#include "myhtml/myhtml.h"
#include "mycss/mycss.h"

#define MODEST_VERSION_MAJOR 0
#define MODEST_VERSION_MINOR 0
#define MODEST_VERSION_PATCH 6

#define MODEST_VERSION_STRING MyCORE_STR(MODEST_VERSION_MAJOR) MyCORE_STR(.) MyCORE_STR(MODEST_VERSION_MINOR) MyCORE_STR(.) MyCORE_STR(MODEST_VERSION_PATCH)

#ifdef __cplusplus
extern "C" {
#endif

// base
/*
 Very important!!!
 
 for myhtml             0..00ffff;      MyHTML_STATUS_OK    == 0x000000
 for mycss and modules  010000..01ffff; MyCSS_STATUS_OK     == 0x000000
 for modest             020000..02ffff; MODEST_STATUS_OK    == 0x000000
 for myrender           030000..037777; MyRENDER_STATUS_OK  == 0x000000
 for myurl              038888..0388ff; MyURL_STATUS_OK     == 0x000000
 for myunicode          038900..038bff; MyUNICODE_STATUS_OK == 0x000000
 not occupied           038c00..03ffff;
 for mydom              040000..04ffff; MyDOM_STATUS_OK     == 0x000000
 for mynetwork          050000..05ffff; MyNETWORK_STATUS_OK == 0x000000
 for myecma             060000..06ffff; MyECMA_STATUS_OK    == 0x000000
 not occupied           070000..
*/
enum modest_status {
    MODEST_STATUS_OK                             = 0x000000,
    MODEST_STATUS_ERROR                          = 0x020000,
    MODEST_STATUS_ERROR_MEMORY_ALLOCATION        = 0x020001,
    MODEST_STATUS_ERROR_MNODE_CREATE             = 0x020102,
    MODEST_STATUS_ERROR_MNODE_INIT               = 0x020103,
    MODEST_STATUS_ERROR_MNODE_NODE_ADD           = 0x020104,
    MODEST_STATUS_ERROR_STYLESHEET_CREATE        = 0x020110,
    MODEST_STATUS_ERROR_STYLESHEET_INIT          = 0x020111,
    MODEST_STATUS_ERROR_STYLESHEET_NODE_ADD      = 0x020112,
    MODEST_STATUS_ERROR_STYLE_TYPE_CREATE        = 0x020120,
    MODEST_STATUS_ERROR_STYLE_TYPE_NODE_ADD      = 0x020121,
    MODEST_STATUS_ERROR_STYLE_DECLARATION_CREATE = 0x020122,
    MODEST_STATUS_ERROR_STYLE_DECLARATION_INIT   = 0x020123,
    MODEST_STATUS_ERROR_AVL_TREE_CREATE          = 0x020124,
    MODEST_STATUS_ERROR_AVL_TREE_INIT            = 0x020125,
}
typedef modest_status_t;

typedef struct modest modest_t;
typedef struct modest_node modest_node_t;
typedef struct modest_style_sheet modest_style_sheet_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_MYOSI_H */
