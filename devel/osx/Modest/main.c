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
#include "modest/modest.h"

#include "mycss/selectors/serialization.h"
#include "mycss/declaration/init.h"
#include "modest/finder/finder.h"
#include "modest/finder/thread.h"
#include "myhtml/encoding.h"
#include "myfont/myfont.h"
#include "modest/node/serialization.h"

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
    if(fread(html, 1, l, f) != l) {
        exit(1);
    }
    
    fclose(f);
    
    struct res_data res = {html, (size_t)l};
    return res;
}

void serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
}

myhtml_tree_t * myhtml(const char* data, size_t data_size, bool is_file, bool print_result, myhtml_callback_tree_node_f cai, void* cai_ctx)
{
    setbuf(stdout, NULL);
    
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    uint64_t all_start = myhtml_hperf_clock(NULL);
    uint64_t tree_init_start = myhtml_hperf_clock(NULL);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
    
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
    }
    
    printf("\n\nMyHTML Information:\n");
    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
    myhtml_hperf_print("\tFirst Tree init", tree_init_start, tree_init_stop, stdout);
    myhtml_hperf_print("\tParse html", parse_start, parse_stop, stdout);
    myhtml_hperf_print("\tTotal", all_start, all_stop, stdout);
    printf("\n");
    
    //myhtml_tree_destroy(tree);
    //myhtml_destroy(myhtml);
    
    return tree;
}

mycss_entry_t * mycss(const char* data, size_t data_size, bool is_file, bool print_result)
{
    // base init
    mycss_t *mycss = mycss_create();
    mycss_init(mycss);
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    mycss_entry_init(mycss, entry);
    
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
        mycss_selectors_serialization_list(entry->selectors, stylesheet->sel_list_first, serialization_callback, NULL);
    }
    
    printf("\n------------\nMyCSS Information:\n");
    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
    myhtml_hperf_print("\tParse css", parse_start, parse_stop, stdout);
    
    //mycss_entry_destroy(entry, true);
    //mycss_destroy(mycss, true);
    
    return entry;
}

void print_tree_after_all(modest_t* modest, myhtml_tree_t* myhtml_tree, myhtml_tree_node_t* scope_node, mycss_entry_t *mycss_entry)
{
    myhtml_tree_node_t* node = scope_node;
    
    while(node) {
        modest_node_t *m_node = (modest_node_t*)node->data;
        
        myhtml_tree_print_node(myhtml_tree, node, stdout);
        
        if(m_node) {
            printf("\tstyles: ");
            
            modest_node_raw_serialization(mycss_entry, m_node, serialization_callback, NULL);
            
            printf("\n");
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != scope_node && node->next == NULL)
                node = node->parent;
            
            if(node == scope_node)
                break;
            
            node = node->next;
        }
    }
}

size_t count = 0;

void modest_callback_for_create_mnode(myhtml_tree_t* tree, myhtml_tree_node_t* node, void* ctx)
{
    if(node->tag_id == MyHTML_TAG__TEXT) {
        return;
    }
    
    modest_t *modest = (modest_t*)ctx;
    
    /* create modest node */
    modest_node_t *m_node = modest_node_create(modest);
    if(m_node == NULL)
        return;
    
    modest_node_init(modest, m_node);
    
    node->data = (void*)m_node;
}

int main(int argc, const char * argv[]) {
    setbuf(stdout, NULL);
    
    char *html_f = "/new/C-git/habr/1.html";
    char *css_f = "/new/C-git/habr/1_glob.css";
    //char *css_f = "/new/C-git/bootstrap.css";
    
    char *html = "<fff>sdsd<aaaa id=hash class=best><div a1><menu class=\"lalala\" id=\"menu-id\" b1><span span1><div a2></div></div><menu class=\"be\" id=\"menu\" b1><span span2></aaaa><a href=\"\" sec></a><div div1><div div2></div><div div3></div><div div4></div></div><p p1><p p2><p p3><p p4>";
    char *css = "div {font: italic 20px/1.667 Helvetica, Verdana, \"sans\"-serif, ultra-condensed bolder  ;}";
    
    char *selector = "menu";
    
    modest_t *modest = modest_create();
    modest_init(modest);
    
    myhtml_tree_t *myhtml_tree = myhtml(html_f, strlen(html_f), true, false, modest_callback_for_create_mnode, (void*)modest);
    mycss_entry_t *mycss_entry = mycss(css_f, strlen(css_f), true, true);
    
//    myhtml_tree_t *myhtml_tree = myhtml(html, strlen(html), false, true, modest_callback_for_create_mnode, (void*)modest);
//    mycss_entry_t *mycss_entry = mycss(css, strlen(css), false, true);
    
    modest->myhtml_tree = myhtml_tree;
    modest->mycss_entry = mycss_entry;
    
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(mycss_entry);
    
    /* simple api */
    uint64_t parse_simple_start = myhtml_hperf_clock(NULL);
    uint64_t parse_simple_stop = myhtml_hperf_clock(NULL);
    
    
    
    
    
    
    
    /* full api */
    uint64_t parse_start = myhtml_hperf_clock(NULL);
    
    
    modest_finder_t* finder = modest_finder_create();
    modest_finder_init(finder, myhtml_tree, stylesheet);
    
    /* threads */
    modest_finder_thread_t *finder_thread = modest_finder_thread_create();
    modest_finder_thread_init(finder, finder_thread, 8);
    
    modest_finder_thread_process(modest, finder_thread, myhtml_tree, myhtml_tree->node_html, stylesheet->sel_list_first);
    
    //finder_thread = modest_finder_thread_destroy(finder_thread, true);
    //finder = modest_finder_destroy(finder, true);
    
    
    uint64_t parse_stop = myhtml_hperf_clock(NULL);
    
    //print_tree_after_all(modest, myhtml_tree, myhtml_tree->node_html, mycss_entry);
    
    
    
    
    
    
    
    
    printf("\n\n------------\nInformation:\n");
    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
    myhtml_hperf_print("\tFound selectors", parse_start, parse_stop, stdout);
    myhtml_hperf_print("\tParse and Found Simple selectors", parse_simple_start, parse_simple_stop, stdout);
    printf("\n");
    
//    printf("\nPrint result:\n");
//    for(size_t i = 0; i < full_collection->length; i++) {
//        myhtml_tree_print_node(myhtml_tree, full_collection->list[i], stdout);
//    }
//    printf("\nFound: %zu\n", full_collection->length);
//    printf("\n");
//
//    modest_finder_destroy(finder_full, true);
    
    modest = modest_destroy(modest, true);
    
    mycss_t* mycss = mycss_entry->mycss;
    mycss_stylesheet_destroy(stylesheet, true);
    mycss_entry_destroy(mycss_entry, true);
    mycss_destroy(mycss, true);
    
    myhtml_t* myhtml = myhtml_tree->myhtml;
    myhtml_tree_destroy(myhtml_tree);
    myhtml_destroy(myhtml);
    
    return 0;
}




