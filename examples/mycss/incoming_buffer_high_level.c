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

// see tokenizer_buffer_high_level

mycss_token_t * token_ready_callback(mycss_entry_t* entry, mycss_token_t* token)
{
    // print token name
    size_t tokens_count = mycss_entry_token_count(entry);
    mycss_token_type_t token_type = mycss_token_type(token);

    printf("Token " MyCORE_FMT_Z "; %s; \"", tokens_count, mycss_token_name_by_type(token_type));

    // print data
    mycore_incoming_buffer_t *buffer = mycss_entry_incoming_buffer_current(entry);
    buffer = mycore_incoming_buffer_find_by_position(buffer, mycss_token_begin(token));

    //
    size_t absolute_begin = mycss_token_begin(token);
    size_t relative_begin = absolute_begin - mycore_incoming_buffer_offset(buffer);
    size_t length         = mycss_token_length(token);

    // if token data length in one buffer then print them all at once
    if((relative_begin + length) <= mycore_incoming_buffer_size(buffer))
    {
        const char *data = mycore_incoming_buffer_data(buffer);
        printf("%.*s\"\n", (int)length, &data[relative_begin]);

        return token;
    }

    // if the data are spread across multiple buffers that join them
    while(buffer) {
        const char *data = mycore_incoming_buffer_data(buffer);

        if((relative_begin + length) > mycore_incoming_buffer_size(buffer))
        {
            size_t relative_end = (mycore_incoming_buffer_size(buffer) - relative_begin);
            length -= relative_end;

            printf("%.*s", (int)relative_end, &data[relative_begin]);

            relative_begin = 0;
            buffer         = mycore_incoming_buffer_next(buffer);
        }
        else {
            printf("%.*s", (int)length, &data[relative_begin]);
            break;
        }
    }

    printf("\"\n");

    return token;
}

int main(int argc, const char * argv[])
{
    char *css_chunk_1 = "#ident [name=\"best";
    char *css_chunk_2 = "-nam";
    char *css_chunk_3 = "e\"] {rgba(0, 0";
    char *css_chunk_4 = ", 0, 0.1);}";

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
    mycss_parse_chunk(entry, css_chunk_4, strlen(css_chunk_4));
    mycss_parse_chunk_end(entry);

    // release resurces
    mycss_entry_destroy(entry, true);
    mycss_destroy(mycss, true);

    return 0;
}



