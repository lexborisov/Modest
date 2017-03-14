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

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

mystatus_t serialization_bad_selectors(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

myhtml_tree_t * parse_html(myhtml_t* myhtml, const char* data, size_t data_size)
{
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
    
    return tree;
}

mycss_entry_t * create_css_parser(void)
{
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);
    
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

mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size)
{
    mystatus_t out_status;
    mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry_selectors(css_entry),
                                                         MyENCODING_UTF_8, selector, selector_size,
                                                         &out_status);
    /* check parsing errors */
    if(list == NULL || (list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)) {
        fprintf(stderr, "Bad CSS Selectors\n");
        
        if(list) {
            mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), list, serialization_bad_selectors, NULL);
            printf("\n");
        }
        
        exit(EXIT_FAILURE);
    }
    
    return list;
}

myhtml_collection_t * find_by_selectors_list(modest_finder_t *finder, myhtml_tree_node_t *scope, mycss_selectors_list_t *list)
{
    myhtml_collection_t *collection = NULL;
    modest_finder_by_selectors_list(finder, scope, list, &collection);
    
    return collection;
}

void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection)
{
    if(collection) {
        printf("%s:\n", caption);
        
        for(size_t i = 0; i < collection->length; i++) {
            printf("\t");
            myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
        }
        
        printf("\n");
    }
    else {
        printf("%s: empty\n", caption);
    }
}

int main(int argc, const char * argv[])
{
    const char *html_first  = "<div><a>link</a></div><div id=by_html_1>mu</div>";
    const char *html_second = "<div><a>link</a></div><div id=by_html_2>be</div>";
    const char *html_third  = "<div><a>link</a></div><div id=by_html_3>ca</div>";
    const char *selector    = "div:not(:has(a))";
    
    /* init MyHTML */
    myhtml_t *myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    /* create css parser and finder for selectors */
    mycss_entry_t *css_entry = create_css_parser();
    modest_finder_t *finder = modest_finder_create_simple();
    
    /* create tree and parse html */
    myhtml_tree_t *tree_first  = parse_html(myhtml, html_first, strlen(html_first));
    myhtml_tree_t *tree_second = parse_html(myhtml, html_second, strlen(html_second));
    myhtml_tree_t *tree_third  = parse_html(myhtml, html_third, strlen(html_third));
    
    /* prepare/parse selector */
    mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));
    
    /* find nodes by selector */
    myhtml_collection_t *collection_first  = find_by_selectors_list(finder, tree_first->node_html, selectors_list);
    myhtml_collection_t *collection_second = find_by_selectors_list(finder, tree_second->node_html, selectors_list);
    myhtml_collection_t *collection_third  = find_by_selectors_list(finder, tree_third->node_html, selectors_list);
    
    /* print all */
    /* print selector */
    printf("Incoming selector:\n\t");
    mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), selectors_list, serialization_callback, NULL);
    printf("\n\n");
    
    /* print trees */
    printf("Incoming trees:\n");
    printf("First:\n\t");    myhtml_serialization_tree_callback(tree_first->node_html , serialization_callback, NULL);
    printf("\nSecond:\n\t"); myhtml_serialization_tree_callback(tree_second->node_html, serialization_callback, NULL);
    printf("\nThird:\n\t");  myhtml_serialization_tree_callback(tree_third->node_html , serialization_callback, NULL);
    
    /* print found result */
    printf("\n\nFound:\n");
    print_found_result("In First tree" , tree_first , collection_first);
    print_found_result("In Second tree", tree_second, collection_second);
    print_found_result("In Third tree" , tree_third , collection_third);
    
    /* destroy */
    /* destroy all collections */
    myhtml_collection_destroy(collection_first);
    myhtml_collection_destroy(collection_second);
    myhtml_collection_destroy(collection_third);
    
    /* destroy selector list */
    mycss_selectors_list_destroy(mycss_entry_selectors(css_entry), selectors_list, true);
    
    /* destroy Modest Finder */
    modest_finder_destroy(finder, true);
    
    /* destroy MyCSS */
    mycss_t *mycss = css_entry->mycss;
    mycss_entry_destroy(css_entry, true);
    mycss_destroy(mycss, true);
    
    /* destroy MyHTML */
    myhtml_tree_destroy(tree_first);
    myhtml_tree_destroy(tree_second);
    myhtml_tree_destroy(tree_third);
    myhtml_destroy(myhtml);
    
    return 0;
}


