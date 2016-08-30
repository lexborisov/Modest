/*
 Copyright (C) 2016 Alexander Borisov
 
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

#ifdef __cplusplus
extern "C" {
#endif

// base
/*
 Very important!!!
 
 for myhtml             0..00ffff;      MyHTML_STATUS_OK    == 0x000000
 for mycss and modules  010000..01ffff; MyCSS_STATUS_OK     == 0x000000
 for modest             020000..02ffff; MODEST_STATUS_OK    == 0x000000
 for myrender           030000..03ffff; MyRENDER_STATUS_OK  == 0x000000
 for mydom              040000..04ffff; MyDOM_STATUS_OK     == 0x000000
 for mynetwork          050000..05ffff; MyNETWORK_STATUS_OK == 0x000000
 for myecma             060000..06ffff; MyECMA_STATUS_OK    == 0x000000
 for myfont             070000..07ffff; MyFONT_STATUS_OK    == 0x000000
 not occupied           080000..
*/
enum modest_status {
    MODEST_STATUS_OK                      = 0x000000,
    MODEST_STATUS_ERROR_MEMORY_ALLOCATION = 0x020000
}
typedef modest_status_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_MYOSI_H */
