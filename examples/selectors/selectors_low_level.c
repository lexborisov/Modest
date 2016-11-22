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

#include <myhtml/myhtml.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <modest/finder/finder.h>
#include "mycss/selectors/serialization.h"

myhtml_tree_t * parse_html(const char* data, size_t data_size)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_parse(tree, MyHTML_ENCODING_UTF_8, data, data_size);
    
    return tree;
}

void serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
}

mycss_entry_t * create_css_parser(void)
{
    // base init
    mycss_t *mycss = mycss_create();
    mycss_status_t status = mycss_init(mycss);
    
    if(status) {
        fprintf(stderr, "Can't init CSS Parser\n");
        exit(EXIT_FAILURE);
    }
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    
    if(status) {
        fprintf(stderr, "Can't init CSS Entry\n");
        exit(EXIT_FAILURE);
    }
    
    return entry;
}

int main(int argc, const char * argv[])
{
    const char *html = "<div><p id=p1><p id=p2><p id=p3><a>link</a><p id=p4><p id=p5><p id=p6></div>";
    const char *selector = "div > :nth-child(2n+1):not(:has(a))";
    
    myhtml_tree_t *html_tree = parse_html(html, strlen(html));
    mycss_entry_t *css_entry = create_css_parser();
    
    mycss_status_t out_status;
    modest_finder_t *finder = modest_finder_create_simple();
    
    mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry_selectors(css_entry), MyHTML_ENCODING_UTF_8, selector, strlen(selector), &out_status);
    
    if(list == NULL || (list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)) {
        fprintf(stderr, "Bad CSS Selectors\n");
        exit(EXIT_FAILURE);
    }
    
    myhtml_collection_t *collection = NULL;
    modest_finder_by_selectors_list(finder, html_tree, html_tree->node_html, list, &collection);
    
    /* print result */
    fprintf(stdout, "HTML Tree:\n");
    myhtml_tree_print_node_children(html_tree, html_tree->document, stdout, 0);
    fprintf(stdout, "\n");
    
    fprintf(stdout, "Selector:\n\t");
    mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), list, serialization_callback, NULL);
    fprintf(stdout, "\n");
    
    if(collection) {
        printf("\nFound result:\n");
        
        for(size_t i = 0; i < collection->length; i++) {
            fprintf(stdout, "\t");
            myhtml_tree_print_node(html_tree, collection->list[i], stdout);
        }
        
        fprintf(stdout, "\n");
    }
    else {
        printf("\nFound result: empty\n");
    }
    
    // destroy all
    mycss_selectors_list_destroy(mycss_entry_selectors(css_entry), list, true);
    myhtml_collection_destroy(collection);
    
    /* destroy Modest finder */
    modest_finder_destroy(finder, true);
    
    mycss_t *mycss = css_entry->mycss;
    mycss_entry_destroy(css_entry, true);
    mycss_destroy(mycss, true);
    
    myhtml_t* myhtml = html_tree->myhtml;
    myhtml_tree_destroy(html_tree);
    myhtml_destroy(myhtml);
    
    return 0;
}


