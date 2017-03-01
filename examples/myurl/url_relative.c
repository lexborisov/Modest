/*
 Copyright (C) 2017 Alexander Borisov
 
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

#include <string.h>
#include <myurl/url.h>

int main(int argc, const char * argv[])
{
    const char* data_base = "https://www.reddit.com/r/programming/";
    const char* data_relative = "../gaming/?count=25";
    
    myurl_t *url = myurl_create();
    if(url == NULL) {
        printf("Can't create URL object\n");
        return EXIT_FAILURE;
    }
    
    if(myurl_init(url)) {
        printf("Can't init URL object\n");
        return EXIT_FAILURE;
    }
    
    myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, NULL);
    myurl_entry_t *url_relative = myurl_parse(url, data_relative, strlen(data_relative), url_base, NULL);
    
    char *result = myurl_entry_as_string(url_relative, NULL);
    
    printf("Relative URL: %s\n", data_relative);
    printf("Base URL: %s\n", data_base);
    printf("Result URL: %s\n", result);
    
    myurl_entry_free_string(url_base, result);
    
    myurl_entry_destroy(url_base, true);
    myurl_entry_destroy(url_relative, true);
    myurl_destroy(url, true);
    
    return EXIT_SUCCESS;
}
