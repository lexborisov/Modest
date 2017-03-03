///*
// Copyright (C) 2016 Alexander Borisov
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// 
// Author: lex.borisov@gmail.com (Alexander Borisov)
//*/
//
//#include "myhtml/myhtml.h"
//#include "mycss/mycss.h"
//#include "modest/modest.h"
//
//#include "mycss/selectors/serialization.h"
//#include "mycss/declaration/init.h"
//#include "modest/finder/finder.h"
//#include "modest/finder/thread.h"
//#include "myhtml/encoding.h"
//#include "myfont/myfont.h"
//#include "modest/node/serialization.h"
//
//#include "myurl/url.h"
//#include "myurl/serialization.h"
//
//struct res_data {
//    char *data;
//    size_t size;
//};
//
//struct res_data load_data(const char* filename)
//{
//    FILE *f = fopen(filename, "rb");
//    fseek(f, 0L, SEEK_END);
//    
//    long l = ftell(f);
//    fseek(f, 0L, SEEK_SET);
//    
//    char *html = (char*)mycore_malloc(l);
//    if(fread(html, 1, l, f) != l) {
//        exit(1);
//    }
//    
//    fclose(f);
//    
//    struct res_data res = {html, (size_t)l};
//    return res;
//}
//
//void serialization_callback(const char* data, size_t len, void* ctx)
//{
//    printf("%.*s", (int)len, data);
//}
//
//myhtml_tree_t * myhtml(const char* data, size_t data_size, bool is_file, bool print_result, myhtml_callback_tree_node_f cai, void* cai_ctx)
//{
//    setbuf(stdout, NULL);
//    
//    myhtml_t* myhtml = myhtml_create();
//    myhtml_init(myhtml, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 1, 0);
//    
//    uint64_t all_start = myhtml_hperf_clock(NULL);
//    uint64_t tree_init_start = myhtml_hperf_clock(NULL);
//    
//    myhtml_tree_t* tree = myhtml_tree_create();
//    myhtml_tree_init(tree, myhtml);
//    
//    myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
//    
//    uint64_t tree_init_stop = myhtml_hperf_clock(NULL);
//    uint64_t parse_start = myhtml_hperf_clock(NULL);
//    
//    if(is_file) {
//        struct res_data res = load_data(data);
//        
//        myencoding_t encoding = myencoding_prescan_stream_to_determine_encoding(res.data, res.size);
//        
//        if(encoding == MyENCODING_NOT_DETERMINED)
//            encoding = MyENCODING_UTF_8;
//        
//        myhtml_parse(tree, encoding, res.data, res.size);
//        free(res.data);
//    }
//    else {
//        myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);
//    }
//    
//    uint64_t parse_stop = myhtml_hperf_clock(NULL);
//    uint64_t all_stop = myhtml_hperf_clock(NULL);
//    
//    if(print_result) {
//        myhtml_tree_print_node_children(tree, tree->document, stdout, 0);
//    }
//    
//    printf("\n\nMyHTML Information:\n");
//    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
//    myhtml_hperf_print("\tFirst Tree init", tree_init_start, tree_init_stop, stdout);
//    myhtml_hperf_print("\tParse html", parse_start, parse_stop, stdout);
//    myhtml_hperf_print("\tTotal", all_start, all_stop, stdout);
//    printf("\n");
//    
//    //myhtml_tree_destroy(tree);
//    //myhtml_destroy(myhtml);
//    
//    return tree;
//}
//
//mycss_entry_t * mycss(const char* data, size_t data_size, bool is_file, bool print_result)
//{
//    // base init
//    mycss_t *mycss = mycss_create();
//    mycss_init(mycss);
//    
//    // currenr entry work init
//    mycss_entry_t *entry = mycss_entry_create();
//    mycss_entry_init(mycss, entry);
//    
//    uint64_t parse_start = myhtml_hperf_clock(NULL);
//    
//    if(is_file) {
//        struct res_data res = load_data(data);
//        mycss_parse(entry, MyENCODING_UTF_8, res.data, res.size);
//        free(res.data);
//    }
//    else {
//        mycss_parse(entry, MyENCODING_UTF_8, data, data_size);
//    }
//    
//    uint64_t parse_stop = myhtml_hperf_clock(NULL);
//    
//    if(print_result) {
//        printf("\n");
//        mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(entry);
//        mycss_selectors_serialization_list(entry->selectors, stylesheet->sel_list_first, serialization_callback, NULL);
//    }
//    
//    printf("\n------------\nMyCSS Information:\n");
//    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
//    myhtml_hperf_print("\tParse css", parse_start, parse_stop, stdout);
//    
//    //mycss_entry_destroy(entry, true);
//    //mycss_destroy(mycss, true);
//    
//    return entry;
//}
//
//void print_tree_after_all(modest_t* modest, myhtml_tree_t* myhtml_tree, myhtml_tree_node_t* scope_node, mycss_entry_t *mycss_entry)
//{
//    myhtml_tree_node_t* node = scope_node;
//    
//    while(node) {
//        modest_node_t *m_node = (modest_node_t*)node->data;
//        
//        myhtml_tree_print_node(myhtml_tree, node, stdout);
//        
//        if(m_node) {
//            printf("\tstyles: ");
//            
//            modest_node_raw_serialization(modest, m_node, serialization_callback, NULL);
//            
//            printf("\n");
//        }
//        
//        if(node->child)
//            node = node->child;
//        else {
//            while(node != scope_node && node->next == NULL)
//                node = node->parent;
//            
//            if(node == scope_node)
//                break;
//            
//            node = node->next;
//        }
//    }
//}
//
//size_t count = 0;
//
//void modest_callback_for_create_mnode(myhtml_tree_t* tree, myhtml_tree_node_t* node, void* ctx)
//{
//    if(node->tag_id == MyHTML_TAG__TEXT) {
//        return;
//    }
//    
//    modest_t *modest = (modest_t*)ctx;
//    
//    /* create modest node */
//    modest_node_t *m_node = modest_node_create(modest);
//    if(m_node == NULL)
//        return;
//    
//    modest_node_init(modest, m_node);
//    
//    node->data = (void*)m_node;
//}
//
//int main2222(int argc, const char * argv[])
//{
//    const char* data_base = "https://lenta.ru/news/2017/........./02/23/minsk_docs/";
//    const char* data_rel  = "/comments//news/2017/02/23/minsk_docs/";
//    
//    printf("base: %s\n", data_base);
//    printf("rela: %s\n", data_rel);
//    
//    myurl_t *url = myurl_create();
//    myurl_init(url);
//    
//    mystatus_t status;
//    myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, &status);
//    myurl_entry_t *url_entry = myurl_parse(url, data_rel, strlen(data_rel), url_base, &status);
//    
//    printf("result:   ");
//    myurl_serialization(url_entry, false, serialization_callback, NULL);
//    printf("\n");
//    
//    if(status) {
//        exit(1);
//    }
//    
//    myurl_destroy(url, true);
//}
//
//int main_23(int argc, const char * argv[])
//{
//    setbuf(stdout, NULL);
//    
//    //char *html_f = "/new/C-git/lexbor/test/test.html";
//    char *html_f = "/new/C-git/habr/1.html";
//    //char *html_f = "/new/C-git/HTML_BENTCHMARK/booking.com.html";
//    
//    //char *css_f = "/new/C-git/habr/1_glob.css";
//    char *css_f = "/new/C-git/CSS_BENCHMARK/baseguide.css";
//    
//    //char *css_f = "/new/C-git/bootstrap.css";
//    
//    char *html = "Привет UTF8! <br><br>";
//    char *css = ".radio input[type=\"radio\"]:checked + label::before {} .checkbox input[type=\"checkbox\"]:checked + label::before {}";
//    
//    char *selector = "menu";
//    
//    modest_t *modest = modest_create();
//    modest_init(modest);
//    
//    myhtml_tree_t *myhtml_tree = myhtml(html_f, strlen(html_f), true, false, modest_callback_for_create_mnode, (void*)modest);
//    mycss_entry_t *mycss_entry = mycss(css_f, strlen(css_f), true, false);
//    
////    myhtml_tree_t *myhtml_tree = myhtml(html, strlen(html), false, true, modest_callback_for_create_mnode, (void*)modest);
////    mycss_entry_t *mycss_entry = mycss(css, strlen(css), false, false);
//    
//    modest->myhtml_tree = myhtml_tree;
//    modest->mycss_entry = mycss_entry;
//    
//    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(mycss_entry);
//    
//    /* simple api */
//    uint64_t parse_simple_start = myhtml_hperf_clock(NULL);
//    uint64_t parse_simple_stop = myhtml_hperf_clock(NULL);
//    
//    
//    
//    /* full api */
//    uint64_t parse_start = myhtml_hperf_clock(NULL);
//    
//    
//    modest_finder_t* finder = modest_finder_create();
//    modest_finder_init(finder);
//    
////     threads 
//    modest_finder_thread_t *finder_thread = modest_finder_thread_create();
//    modest_finder_thread_init(finder, finder_thread, 4);
//    
//    modest_finder_thread_process(modest, finder_thread, myhtml_tree->node_html, stylesheet->sel_list_first);
//    
//    finder_thread = modest_finder_thread_destroy(finder_thread, true);
//    finder = modest_finder_destroy(finder, true);
//    
//    
//    uint64_t parse_stop = myhtml_hperf_clock(NULL);
//    
////    print_tree_after_all(modest, myhtml_tree, myhtml_tree->node_html, mycss_entry);
//    
//    printf("\n\n------------\nInformation:\n");
//    printf("\tTicks/sec: %llu\n", (unsigned long long) myhtml_hperf_res(NULL));
//    myhtml_hperf_print("\tFound selectors", parse_start, parse_stop, stdout);
//    myhtml_hperf_print("\tParse and Found Simple selectors", parse_simple_start, parse_simple_stop, stdout);
//    printf("\n");
//    
////    printf("\nPrint result:\n");
////    for(size_t i = 0; i < full_collection->length; i++) {
////        myhtml_tree_print_node(myhtml_tree, full_collection->list[i], stdout);
////    }
////    printf("\nFound: %zu\n", full_collection->length);
////    printf("\n");
////
////    modest_finder_destroy(finder_full, true);
//    
//    modest = modest_destroy(modest, true);
//    
//    mycss_t* mycss = mycss_entry->mycss;
//    mycss_stylesheet_destroy(stylesheet, true);
//    mycss_entry_destroy(mycss_entry, true);
//    mycss_destroy(mycss, true);
//    
//    myhtml_t* myhtml = myhtml_tree->myhtml;
//    myhtml_tree_destroy(myhtml_tree);
//    myhtml_destroy(myhtml);
//    
//    return 0;
//}
//
//
//
//
//
//




















///*
// Copyright (C) 2015-2017 Alexander Borisov
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
// 
// Author: lex.borisov@gmail.com (Alexander Borisov)
//*/
//
//#include <myurl/url.h>
//#include <myurl/serialization.h>
//#include <myhtml/mystring.h>
//#include <myhtml/utils/mchar_async.h>
//
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <dirent.h>
//
//struct test_res {
//    char*  data;
//    size_t size;
//}
//typedef test_res_t;
//
//struct test_pos {
//    size_t begin;
//    size_t length;
//}
//typedef test_pos_t;
//
//enum test_type {
//    TEST_TYPE_UNDEF   = 0x00,
//    TEST_TYPE_FIRST   = '1',
//    TEST_TYPE_SECOND  = '2',
//    TEST_TYPE_THIRD   = '3',
//    TEST_TYPE_FOURTH  = '4'
//};
//
//static mchar_async_t* MCharOBJ = NULL;
//static size_t MCharOBJNode = 0;
//
//test_pos_t test_get_value(const char *data, size_t* length, size_t data_size, const char* some);
//
//test_res_t test_load_file(const char* filename)
//{
//    FILE *fh = fopen(filename, "rb");
//    if(fh == NULL) {
//        fprintf(stderr, "Can't open file: %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    if(fseek(fh, 0L, SEEK_END) != 0) {
//        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    long size = ftell(fh);
//    
//    if(fseek(fh, 0L, SEEK_SET) != 0) {
//        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    if(size <= 0) {
//        fprintf(stderr, "Can't get file size or file is empty: %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    char *file_data = (char*)malloc(size + 1);
//    if(file_data == NULL) {
//        fprintf(stderr, "Can't allocate mem for file: %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    size_t nread = fread(file_data, 1, size, fh);
//    if (nread != size) {
//        fprintf(stderr, "Could not read %ld bytes (%zu bytes done)\n", size, nread);
//        exit(EXIT_FAILURE);
//    }
//    
//    fclose(fh);
//    
//    return (test_res_t){file_data, (size_t)size};
//}
//
//void test_serialization_callback(const char* data, size_t len, void* ctx)
//{
//    mycore_string_t *str = ctx;
//    mycore_string_append(str, data, len);
//}
//
//myurl_entry_t * test_parse_url(const char *data, size_t length, myurl_entry_t* base_url)
//{
//    myurl_t *url = myurl_create();
//    if(url == NULL) {
//        fprintf(stderr, "Could create url object\n");
//        exit(EXIT_FAILURE);
//    }
//    
//    if(myurl_init(url)) {
//        fprintf(stderr, "Could init url object\n");
//        exit(EXIT_FAILURE);
//    }
//    
//    myurl_entry_t *url_entry = myurl_parse(url, data, length, base_url, NULL);
//    
//    if(url_entry == NULL) {
//        myurl_destroy(url, true);
//        return NULL;
//    }
//    
//    return url_entry;
//}
//
//void test_destroy_url(myurl_entry_t* entry_url)
//{
//    if(entry_url) {
//        myurl_t *url = entry_url->url_ref;
//        myurl_entry_destroy(entry_url, true);
//        myurl_destroy(url, true);
//    }
//}
//
//myurl_host_type_t test_host_type_from_data(const char *data, size_t length)
//{
//    if(strncmp("IPv4", data, length) == 0) {
//        return MyURL_HOST_TYPE_IPv4;
//    }
//    else if(strncmp("IPv6", data, length) == 0) {
//        return MyURL_HOST_TYPE_IPv6;
//    }
//    else if(strncmp("DOMAIN", data, length) == 0) {
//        return MyURL_HOST_TYPE_DOMAIN;
//    }
//    else if(strncmp("OPAQUE", data, length) == 0) {
//        return MyURL_HOST_TYPE_OPAQUE;
//    }
//    
//    return MyURL_HOST_TYPE_UNDEF;
//}
//
//myurl_host_type_t test_get_domain_type(const char *data, size_t* length, size_t data_size)
//{
//    test_pos_t domain_type = test_get_value(data, length, data_size, "%DOMAIN_TYPE:");
//    myurl_host_type_t domain_type_int = test_host_type_from_data(&data[domain_type.begin], domain_type.length);
//    
//    return domain_type_int;
//}
//
//test_pos_t test_get_value(const char *data, size_t* length, size_t data_size, const char* some)
//{
//    test_pos_t pos = {0};
//    size_t some_len = strlen(some);
//    
//    size_t len = *length + some_len;
//    
//    if(len >= data_size)
//        return pos;
//    
//    if(strncmp(some, &data[ *length ], some_len))
//        return pos;
//    
//    pos.begin = len;
//    
//    while(len < data_size) {
//        if(data[len] == '%')
//        {
//            size_t bpos = len;
//            bpos++;
//            
//            while(bpos < data_size) {
//                if((bpos - 1) > len && (data[bpos] < 'A' || data[bpos] > 'Z') && data[bpos] != '_') {
//                    if(data[bpos] == ':') {
//                        if(strncmp("%URL", &data[len], 4) == 0)
//                            pos.length = ((len - pos.begin) - 2);
//                        else
//                            pos.length = ((len - pos.begin) - 1);
//                        
//                        *length = len;
//                        return pos;
//                    }
//                    
//                    break;
//                }
//                
//                bpos++;
//            }
//        }
//        
//        len++;
//    }
//    
//    *length = len;
//    pos.length = ((len - pos.begin) - 1);
//    
//    return pos;
//}
//
///* FIRST */
//bool test_for_type_first_entry(const char *data, size_t* length, size_t data_size)
//{
//    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
//    if(url.length == 0)
//        return true;
//    
//    //printf("%.*s\n", (int)url.length, &data[ url.begin ]);
//    
//    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, NULL);
//    
//    /* get expected */
//    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
//    if(expect.length == 0) {
//        if(url_entry == NULL)
//            return true;
//    }
//    
//    if(url_entry == NULL) {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tResult:\n");
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_t cmp_str = {0};
//    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
//    
//    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
//    
//    /* compare */
//    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
//    {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        mycore_string_destroy(&cmp_str, false);
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_destroy(&cmp_str, false);
//    test_destroy_url(url_entry);
//    
//    return true;
//}
//
//bool test_for_type_first(const char *data, size_t length, size_t data_size)
//{
//    while(length < data_size) {
//        if(test_for_type_first_entry(data, &length, data_size) == false)
//            return false;
//    }
//    
//    return true;
//}
//
///* SECOND */
//bool test_for_type_second_entry(const char *data, size_t* length, size_t data_size)
//{
//    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
//    if(url.length == 0)
//        return true;
//    
//    /* get domain_type */
//    myurl_host_type_t domain_type = test_get_domain_type(data, length, data_size);
//    
//    //printf("%.*s\n", (int)url.length, &data[ url.begin ]);
//    
//    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, NULL);
//    
//    /* get expected */
//    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
//    if(expect.length == 0) {
//        if(url_entry == NULL)
//            return true;
//    }
//    
//    if(url_entry == NULL) {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tResult:\n");
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    if(url_entry->host.type != domain_type) {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tDomain Type: %d\n", url_entry->host.type);
//        fprintf(stderr, "\tDomain Ip Version Type: %d\n", url_entry->host.ipv.type);
//        fprintf(stderr, "\tExpect Domain Type: %d\n\n", domain_type);
//        
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_t cmp_str = {0};
//    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
//    
//    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
//    
//    /* compare */
//    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
//    {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        mycore_string_destroy(&cmp_str, false);
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_destroy(&cmp_str, false);
//    test_destroy_url(url_entry);
//    
//    return true;
//}
//
//bool test_for_type_second(const char *data, size_t length, size_t data_size)
//{
//    while(length < data_size) {
//        if(test_for_type_second_entry(data, &length, data_size) == false)
//            return false;
//    }
//    
//    return true;
//}
//
///* THIRD */
//bool test_for_type_third_entry(const char *data, size_t* length, size_t data_size)
//{
//    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
//    if(url.length == 0)
//        return true;
//    
//    /* get base */
//    test_pos_t base = test_get_value(data, length, data_size, "%BASE:");
//    if(base.length == 0)
//        return true;
//    
//    myurl_entry_t *base_entry = test_parse_url(&data[ base.begin ], base.length, NULL);
//    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, base_entry);
//    
//    /* get expected */
//    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
//    if(expect.length == 0) {
//        if(url_entry == NULL)
//            return true;
//    }
//    
//    if(url_entry == NULL) {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tBASE: %.*s\n", (int)base.length, &data[ base.begin ]);
//        fprintf(stderr, "\tResult:\n");
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_t cmp_str = {0};
//    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
//    
//    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
//    
//    /* compare */
//    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
//    {
//        fprintf(stderr, "Test FAILURE!\n");
//        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
//        fprintf(stderr, "\tBASE: %.*s\n", (int)base.length, &data[ base.begin ]);
//        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
//        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
//        
//        mycore_string_destroy(&cmp_str, false);
//        test_destroy_url(url_entry);
//        return true;
//    }
//    
//    mycore_string_destroy(&cmp_str, false);
//    test_destroy_url(url_entry);
//    
//    return true;
//}
//
//bool test_for_type_third(const char *data, size_t length, size_t data_size)
//{
//    while(length < data_size) {
//        if(test_for_type_third_entry(data, &length, data_size) == false)
//            return false;
//    }
//    
//    return true;
//}
//
//void test_by_type(const char *data, size_t data_size, const char* filename)
//{
//    printf("Test file: %s\n", filename);
//    
//    size_t length = 8;
//    
//    if(data_size <= length || strncmp("type ", data, 5)) {
//        fprintf(stderr, "Could not read type form %s\n", filename);
//        exit(EXIT_FAILURE);
//    }
//    
//    switch ((unsigned char)data[5]) {
//        case TEST_TYPE_FIRST:
//            test_for_type_first(&data[8], 0, (data_size - 8));
//            break;
//            
//        case TEST_TYPE_SECOND:
//            test_for_type_second(&data[8], 0, (data_size - 8));
//            break;
//            
//        case TEST_TYPE_THIRD:
//            test_for_type_third(&data[8], 0, (data_size - 8));
//            break;
//            
//        default:
//            break;
//    }
//}
//
//void test(const char* filename)
//{
//    test_res_t test_data = test_load_file(filename);
//    test_by_type(test_data.data, test_data.size, filename);
//    
//    if(test_data.data)
//        free(test_data.data);
//}
//
//void test_read_dir(const char* dir_path)
//{
//    char path[(4096 * 4)];
//    sprintf(path, "%s", dir_path);
//    
//    printf("Tests in directory: %s\n", path);
//    
//    size_t path_len = strlen(dir_path);
//    
//    DIR *dir;
//    struct dirent *ent;
//    struct stat path_stat;
//    
//    if((dir = opendir(dir_path)) != NULL)
//    {
//        while((ent = readdir(dir)) != NULL)
//        {
//            sprintf(&path[path_len], "/%s", ent->d_name);
//            
//            if(stat(path, &path_stat) != 0) {
//                fprintf(stderr, "Can't get status for file: %s\n", path);
//                exit(EXIT_FAILURE);
//            }
//            
//            if(ent->d_name[0] == '.' || S_ISDIR(path_stat.st_mode))
//                continue;
//            
//            test(path);
//        }
//        
//        closedir (dir);
//    }
//}
//
//int main(int argc, const char * argv[])
//{
//    setbuf(stdout, NULL);
//    
////    if (argc < 2) {
////        printf("Bad ARGV!\nUse: url <test_file_path>\n");
////        exit(EXIT_FAILURE);
////    }
//    
//    MCharOBJ = mchar_async_create(4, 4096);
//    if(MCharOBJ == NULL)
//        return EXIT_FAILURE;
//    
//    MCharOBJNode = mchar_async_node_add(MCharOBJ);
//    
//    //test_read_dir(argv[1]);
//    test_read_dir("/new/C-git/Modest/test/myurl/data");
//    
//    mchar_async_destroy(MCharOBJ, true);
//    
//    return EXIT_SUCCESS;
//}
//
//
//
//void test_serialization_callback_for_aim(const char* data, size_t len, void* ctx)
//{
//    printf("%.*s", (int)len, data);
//}
//
//int mainkj(int argc, const char * argv[])
//{
//    setbuf(stdout, NULL);
//    
//    //const char* data_base = "http://[::1.]/";
//    //const char* data_base = "file://localhost/C:/foo";
//    const char* data_rel  = "https://lenta.ru/news/2017/02/28/visa/";
//    
//    //printf("base: %s\n", data_base);
//    //    printf("rela: %s\n", data_rel);
//    
//    myurl_t *url = myurl_create();
//    myurl_init(url);
//    
//    for(size_t i = 0; i < 10000; i++)
//    {
//
//    
//    //myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, NULL);
//    myurl_entry_t *url_entry = myurl_parse(url, data_rel, strlen(data_rel), NULL, NULL);
//    
////    printf("result: ");
////    myurl_serialization(url_entry, false, test_serialization_callback_for_aim, NULL);
////    printf("\n");
////    
////    
////    if(myurl_entry_host_set(url_entry, "192.168.", strlen("192.168."))) {
////        printf("after changes host: ERROR\n");
////        exit(0);
////    }
////    
////    if(myurl_entry_path_set(url_entry, "new/path", strlen("new/path"))) {
////        printf("after change path: ERROR\n");
////        exit(0);
////    }
////    
////    if(myurl_entry_path_append_entry(url_entry, "lalaлвappendpath", strlen("lalaлвappendpath"))) {
////        printf("after append path: ERROR\n");
////        exit(0);
////    }
////    
////    if(myurl_entry_path_replace_entry(url_entry, 1, "beb#ebe", strlen("beb#ebe"))) {
////        printf("after append path: ERROR\n");
////        exit(0);
////    }
////    
////    printf("befor delete path entry by index 2: ");
////    myurl_serialization(url_entry, false, test_serialization_callback_for_aim, NULL);
////    printf("\n");
////    
////    myurl_entry_path_remove_entry(url_entry, 2);
////    
////    myurl_entry_query_set(url_entry, "lalala", 4);
////    myurl_entry_fragment_set(url_entry, "anch4", 5);
////    
////    printf("after changes: ");
////    myurl_serialization(url_entry, false, test_serialization_callback_for_aim, NULL);
////    printf("\n");
//    
////    char *host_data = myurl_entry_host_as_string(url_entry, NULL);
////    
//////    printf("HOST: %s\n", host_data);
////    
////    myurl_entry_host_free_string(url_entry, host_data);
//    
//    
//        myurl_entry_destroy(url_entry, true);
//        
////    printf("result: ");
////    
////    if(url_entry) {
////        myurl_serialization(url_entry, false, test_serialization_callback_for_aim, NULL);
////        printf("\n");
////    }
////    else {
////        printf("ERROR\n");
////    }
//    
//    
//    }
//    
//    myurl_destroy(url, true);
//    
//    return 1;
//}




















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
    const char* data_base = "http://lalal.ru/";
    
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
    myurl_entry_t *url_relative = myurl_parse(url, "bla.ru/", strlen("bla.ru/"), url_base, NULL);
    
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





