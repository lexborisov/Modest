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

#ifndef MyURL_SCHEME_CONST_H
#define MyURL_SCHEME_CONST_H
#pragma once

enum myurl_scheme_id {
	MyURL_SCHEME_ID_UNDEF      = 0x0000,
	MyURL_SCHEME_ID_ABOUT      = 0x0001,
	MyURL_SCHEME_ID_BLOB       = 0x0002,
	MyURL_SCHEME_ID_DATA       = 0x0003,
	MyURL_SCHEME_ID_FILE       = 0x0004,
	MyURL_SCHEME_ID_FILESYSTEM = 0x0005,
	MyURL_SCHEME_ID_FTP        = 0x0006,
	MyURL_SCHEME_ID_GOPHER     = 0x0007,
	MyURL_SCHEME_ID_HTTP       = 0x0008,
	MyURL_SCHEME_ID_HTTPS      = 0x0009,
	MyURL_SCHEME_ID_WS         = 0x000a,
	MyURL_SCHEME_ID_WSS        = 0x000b,
	MyURL_SCHEME_ID_LAST_ENTRY = 0x000c
}
typedef myurl_scheme_id_t;


#endif /* MyURL_SCHEME_CONST_H */
