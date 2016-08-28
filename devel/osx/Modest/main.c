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

#include "myhtml/myhtml.h"
#include "mycss/mycss.h"
#include "mycss/declaration/init.h"
#include "modest/finder/finder.h"

struct res_data {
    char *data;
    size_t size;
};

struct res_data load_data(const char* filename)
{
    FILE *f = fopen(filename, "rb");
    fseek(f, 0L, SEEK_END);
    
    long l = ftell(f);
    fseek(f, 0L, SEEK_SET);
    
    char *html = (char*)myhtml_malloc(l);
    fread(html, 1, l, f);
    
    fclose(f);
    
    struct res_data res = {html, (size_t)l};
    return res;
}

myhtml_tree_t * myhtml(const char* data, size_t data_size, bool is_file, bool print_result)
{
    setbuf(stdout, NULL);
    
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    uint64_t all_start = myhtml_hperf_clock(NULL);
    uint64_t tree_init_start = myhtml_hperf_clock(NULL);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    uint64_t tree_init_stop = myhtml_hperf_clock(NULL);
    uint64_t parse_start = myhtml_hperf_clock(NULL);
    
    if(is_file) {
        struct res_data res = load_data(data);
        myhtml_parse(tree, MyHTML_ENCODING_UTF_8, res.data, res.size);
        free(res.data);
    }
    else {
        myhtml_parse(tree, MyHTML_ENCODING_UTF_8, data, data_size);
    }
    
    uint64_t parse_stop = myhtml_hperf_clock(NULL);
    uint64_t all_stop = myhtml_hperf_clock(NULL);
    
    if(print_result) {
        myhtml_tree_print_node_children(tree, tree->document, stdout, 0);
        
        printf("\n\nMyHTML Information:\n");
        printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
        myhtml_hperf_print("\tFirst Tree init", tree_init_start, tree_init_stop, stdout);
        myhtml_hperf_print("\tParse html", parse_start, parse_stop, stdout);
        myhtml_hperf_print("\tTotal", all_start, all_stop, stdout);
        printf("\n");
    }
    
    //myhtml_tree_destroy(tree);
    //myhtml_destroy(myhtml);
    
    return tree;
}

mycss_entry_t * mycss(const char* data, size_t data_size, bool is_file, bool print_result)
{
    // base init
    mycss_t *mycss = mycss_create();
    mycss_status_t status = mycss_init(mycss);
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);
    
    uint64_t parse_start = myhtml_hperf_clock(NULL);
    
    if(is_file) {
        struct res_data res = load_data(data);
        mycss_parse(entry, MyHTML_ENCODING_UTF_8, res.data, res.size);
        free(res.data);
    }
    else {
        mycss_parse(entry, MyHTML_ENCODING_UTF_8, data, data_size);
    }
    
    uint64_t parse_stop = myhtml_hperf_clock(NULL);
    
    if(print_result) {
        printf("\n");
        mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(entry);
        mycss_selectors_print_list(entry->selectors, stylesheet->sel_list_first, stdout);
        
        printf("\n------------\nMyCSS Information:\n");
        printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
        myhtml_hperf_print("\tParse css", parse_start, parse_stop, stdout);
    }
    
    //mycss_entry_destroy(entry, true);
    //mycss_destroy(mycss, true);
    
    return entry;
}

int main(int argc, const char * argv[]) {
    setbuf(stdout, NULL);
    
    char *html = "<fff>sdsd<aaaa id=hash class=best><div a1><menu class=\"lalala\" id=\"menu-id\" b1><span span1><div a2></div></div><span span2></aaaa><a href=\"\" sec></a><div div1><div div2></div><div div3></div><div div4></div></div><p p1><p p2><p p3><p p4>";
    //char *html = "/new/C-git/test_full.html";
    char *css = "img {width: auto\\9; height: auto; max-width: 100%; -ms-interpolation-mode: bicubic;}";
    char *selector = "html|fff >> div";
    
    myhtml_tree_t *myhtml_tree = myhtml(html, strlen(html), false, true);
    mycss_entry_t *mycss_entry = mycss(css, strlen(css), false, true);
    
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(mycss_entry);
    
    /* simple api */
    uint64_t parse_simple_start = myhtml_hperf_clock(NULL);
    
//    mycss_status_t out_status;
//    modest_finder_t *finder = modest_finder_create_simple(myhtml_tree, NULL);
//    
//    mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry->selectors, MyHTML_ENCODING_UTF_8, selector, strlen(selector), &out_status);
//    myhtml_collection_t *collection = modest_finder_by_selectors_list(finder, list, myhtml_tree->node_html, NULL);
//    
    uint64_t parse_simple_stop = myhtml_hperf_clock(NULL);
//
//    printf("\nPrint simple result:\n");
//    for(size_t i = 0; i < collection->length; i++) {
//        myhtml_tree_print_node(myhtml_tree, collection->list[i], stdout);
//    }
//    
//    finder = modest_finder_destroy(finder, true);
    
    /* full api */
    uint64_t parse_start = myhtml_hperf_clock(NULL);
    
    myhtml_collection_t* full_collection = NULL;
    modest_finder_t *finder_full = modest_finder_by_stylesheet(myhtml_tree, stylesheet, &full_collection, NULL, NULL);
    
    uint64_t parse_stop = myhtml_hperf_clock(NULL);
    
    printf("\n\n------------\nInformation:\n");
    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
    myhtml_hperf_print("\tFound selectors", parse_start, parse_stop, stdout);
    myhtml_hperf_print("\tParse and Found Simple selectors", parse_simple_start, parse_simple_stop, stdout);
    printf("\n");
    
    printf("\nPrint result:\n");
    for(size_t i = 0; i < full_collection->length; i++) {
        myhtml_tree_print_node(myhtml_tree, full_collection->list[i], stdout);
    }
    
    printf("\n");
    
    modest_finder_destroy(finder_full, true);
    
    return 0;
}

