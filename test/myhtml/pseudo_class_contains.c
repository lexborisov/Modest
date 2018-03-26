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

#include <modest/finder/finder.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#define CHECK_STATUS(msg, ...) do {if(status) DIE(msg, ##__VA_ARGS__);} while(0)

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

mystatus_t serialization_bad_selectors(const char* buffer, size_t size, void* ctx)
{
    printf("%.*s", (int)size, buffer);
    return MyCORE_STATUS_OK;
}

myhtml_tree_t * parse_html(const char* data, size_t data_size)
{
    myhtml_t* myhtml = myhtml_create();
    mystatus_t status = myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    CHECK_STATUS("Can't init MyHTML object\n");
    
    myhtml_tree_t* tree = myhtml_tree_create();
    status = myhtml_tree_init(tree, myhtml);
    
    CHECK_STATUS("Can't init MyHTML Tree object\n");
    
    status = myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    CHECK_STATUS("Can't parse HTML:\n%s\n", data);
    
    return tree;
}

mycss_entry_t * create_css_parser(void)
{
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    
    CHECK_STATUS("Can't init MyCSS object\n");
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    
    CHECK_STATUS("Can't init MyCSS Entry object\n");
    
    return entry;
}

mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size)
{
    mystatus_t out_status;
    mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry_selectors(css_entry),
                                                         MyENCODING_UTF_8,
                                                         selector, selector_size,
                                                         &out_status);

    // printf("\nprepare_selector()\n");
    // printf("\t%s\n", (list != NULL)?"has list":"no list");

    /* check parsing errors */
    if(list == NULL || (list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)) {
        fprintf(stderr, "Bad CSS Selectors\n");
        
        if(list) {
            mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), list,
                                               serialization_bad_selectors, NULL);
            printf("\n");
        }
        
        exit(EXIT_FAILURE);
    }
    
    // printf("\treturn list\n");
    return list;
}

void print_found_result(myhtml_tree_t* html_tree, myhtml_collection_t *collection)
{
    if(collection) {
        for(size_t i = 0; i < collection->length; i++) {
            printf("\n\t");
            myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
        }
        
        printf("\n");
    }
    else {
        printf("empty\n");
    }
}

int main(int argc, const char * argv[])
{
    const char *html = "<div>a<p id=\"c d\">c d</p><p id=\"c\">c</p></div>";
    // const char *selector = ":has(p)";
    // const char *selector = ":contains(c d)";
    // const char *selector = ":contains(c)";
    const char *selector = ":contains(c,d)";
    // const char *selector = "p:contains('c d')"; // Bad Selector
    // const char *selector = "p:contains(\"c d\")"; // Bad Selector
    
    /* init MyHTML and parse HTML */
    myhtml_tree_t *html_tree = parse_html(html, strlen(html));
    
    /* create css parser and finder for selectors */
    mycss_entry_t *css_entry = create_css_parser();
    modest_finder_t *finder = modest_finder_create_simple();
    
    /* parse selectors */
    mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));
    
    /* find nodes by selector */
    myhtml_collection_t *collection = NULL;
    modest_finder_by_selectors_list(finder, html_tree->node_html, selectors_list, &collection);
    
    /* print result */
    /* print selector */
    printf("Incoming selector:\n\t");
    mycss_selectors_serialization_list(mycss_entry_selectors(css_entry),
                                       selectors_list, serialization_callback, NULL);
    printf("\n\n");
    
    /* print tree */
    printf("Incoming tree:\n\t");
    myhtml_serialization_tree_callback(html_tree->node_html, serialization_callback, NULL);
    
    /* print found result */
    printf("\n\nFound nodes:");
    print_found_result(html_tree, collection);
    
    /* destroy all */
    myhtml_collection_destroy(collection);
    
    /* destroy selector list */
    mycss_selectors_list_destroy(mycss_entry_selectors(css_entry), selectors_list, true);
    
    /* destroy Modest Finder */
    modest_finder_destroy(finder, true);
    
    /* destroy MyCSS */
    mycss_t *mycss = css_entry->mycss;
    mycss_entry_destroy(css_entry, true);
    mycss_destroy(mycss, true);
    
    /* destroy MyHTML */
    myhtml_t* myhtml = html_tree->myhtml;
    myhtml_tree_destroy(html_tree);
    myhtml_destroy(myhtml);
    
    return 0;
}


