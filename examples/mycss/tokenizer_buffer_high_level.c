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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mycss/api.h>

#include "example.h"

mycss_token_t * token_ready_callback(mycss_entry_t* entry, mycss_token_t* token)
{
    // print token name
    size_t tokens_count = mycss_entry_token_count(entry);
    mycss_token_type_t token_type = mycss_token_type(token);

    mycore_string_t str;
    mycss_token_data_to_string(entry, token, &str, true);

    printf("Token " MyCORE_FMT_Z "; %s; \"%s\"\n", tokens_count,
           mycss_token_name_by_type(token_type),
           mycore_string_data(&str));

    mycore_string_destroy(&str, false);

    return token;
}

int main(int argc, const char * argv[])
{
    char *css_chunk_1 = "#ident [name=\"best";
    char *css_chunk_2 = "-name\"] {rgba(0, 0";
    char *css_chunk_3 = ", 0, 0.1);}";

    // basic init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);

    // check initialization
    if (MyCSS_FAILED(status)) return EXIT_FAILURE;

    // current entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);

    // set custom callback for token is ready
    mycss_entry_token_ready_callback(entry, token_ready_callback);

    // this is example, you can not specify, dy default MyENCODING_UTF_8
    mycss_encoding_set(entry, MyENCODING_UTF_8);

    // parse css chunks
    mycss_parse_chunk(entry, css_chunk_1, strlen(css_chunk_1));
    mycss_parse_chunk(entry, css_chunk_2, strlen(css_chunk_2));
    mycss_parse_chunk(entry, css_chunk_3, strlen(css_chunk_3));
    mycss_parse_chunk_end(entry);

    // release resurces
    mycss_entry_destroy(entry, true);
    mycss_destroy(mycss, true);

    return 0;
}



