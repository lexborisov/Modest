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
    const char* data_base = "https://lastmac:12345@www.emaple.com:4433/programming/?id=777888999#somehash";
    
    myurl_t *url = myurl_create();
    if(url == NULL) {
        printf("Can't create URL object\n");
        return EXIT_FAILURE;
    }
    
    if(myurl_init(url)) {
        printf("Can't init URL object\n");
        return EXIT_FAILURE;
    }
    
    printf("Parse url \"%s\":\n", data_base);
    
    myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, NULL);
    
    const char *scheme   = myurl_entry_scheme_name(url_base, NULL);
    char *authority      = myurl_entry_authority_as_string(url_base, NULL);
    const char *username = myurl_entry_username(url_base, NULL);
    const char *password = myurl_entry_password(url_base, NULL);
    char *host           = myurl_entry_host_as_string(url_base, NULL);
    char *path           = myurl_entry_path_as_string(url_base, NULL);
    const char *query    = myurl_entry_query(url_base, NULL);
    const char *fragment = myurl_entry_fragment(url_base, NULL);
    
    printf("\tScheme: %s\n"         , (scheme ? scheme : ""));
    printf("\tScheme port: %u\n"    , myurl_entry_scheme_port(url_base));
    printf("\tAuthority (%s):\n"    , authority);
    printf("\t\tUsername: %s\n"     , username);
    printf("\t\tPassword: %s\n"     , password);
    printf("\tHost: %s\n"           , host);
    printf("\tPort is defined: %s\n", (myurl_entry_port_is_defined(url_base) ? "true" : "false"));
    printf("\tPort: %u\n"           , myurl_entry_port(url_base));
    printf("\tPath: %s\n"           , path);
    printf("\tQuery: %s\n"          , (query ? query : ""));
    printf("\tFragment: %s\n"       , (fragment ? fragment : ""));
    
    myurl_entry_free_string(url_base, authority);
    myurl_entry_free_string(url_base, host);
    myurl_entry_free_string(url_base, path);
    
    myurl_entry_destroy(url_base, true);
    myurl_destroy(url, true);
    
    return 0;
}
