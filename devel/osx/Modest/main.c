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
#include "myencoding/encoding.h"
#include "myfont/myfont.h"
#include "modest/node/serialization.h"

#include "myurl/url.h"
#include "myurl/serialization.h"

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
    
    char *html = (char*)mycore_malloc(l);
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

//myhtml_tree_t * myhtml(const char* data, size_t data_size, bool is_file, bool print_result, myhtml_callback_tree_node_f cai, void* cai_ctx)
//{
//    setbuf(stdout, NULL);
//    
//    myhtml_t* myhtml = myhtml_create();
//    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
//    
////    uint64_t all_start = mycore_hperf_clock(NULL);
////    uint64_t tree_init_start = mycore_hperf_clock(NULL);
//    
//    myhtml_tree_t* tree = myhtml_tree_create();
//    myhtml_tree_init(tree, myhtml);
//    
//    myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
//    
////    uint64_t tree_init_stop = mycore_hperf_clock(NULL);
////    uint64_t parse_start = mycore_hperf_clock(NULL);
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
////    uint64_t parse_stop = mycore_hperf_clock(NULL);
////    uint64_t all_stop = mycore_hperf_clock(NULL);
//    
//    if(print_result) {
//        myhtml_tree_print_node_children(tree, tree->document, stdout, 0);
//    }
//    
//    printf("\n\nMyHTML Information:\n");
////    printf("\tTicks/sec: %llu\n", (unsigned long long) mycore_hperf_res(NULL));
////    mycore_hperf_print("\tFirst Tree init", tree_init_start, tree_init_stop, stdout);
////    mycore_hperf_print("\tParse html", parse_start, parse_stop, stdout);
////    mycore_hperf_print("\tTotal", all_start, all_stop, stdout);
////    printf("\n");
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
//    uint64_t parse_start = mycore_hperf_clock(NULL);
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
//    uint64_t parse_stop = mycore_hperf_clock(NULL);
//    
//    if(print_result) {
//        printf("\n");
//        mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(entry);
//        mycss_selectors_serialization_list(entry->selectors, stylesheet->sel_list_first, serialization_callback, NULL);
//    }
//    
//    printf("\n------------\nMyCSS Information:\n");
//    printf("\tTicks/sec: %llu\n", (unsigned long long) mycore_hperf_res(NULL));
//    mycore_hperf_print("\tParse css", parse_start, parse_stop, stdout);
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
//    
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#include <time.h>
//#include <sys/stat.h>
//
//#include <stdbool.h>
//
//
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <dirent.h>
//#include <string.h>
//#include <unistd.h>
//
//
//struct res_html_test {
//    char *html;
//    size_t len;
//    size_t size;
//};
//
//struct chunk_res_test {
//    struct res_html_test data;
//    struct res_html_test result;
//};
//
//struct chunk_res_result {
//    myhtml_tree_t *tree;
//    size_t good;
//    size_t bad;
//    
//    bool is_fragment;
//    bool enabled_script;
//    myhtml_tag_id_t tag_id;
//    enum myhtml_namespace ns;
//};
//
//typedef void (*chunk_test_f)(struct chunk_res_test *res_test, struct chunk_res_result *result);
//
//size_t read_line(char *html, size_t size)
//{
//    size_t len;
//    for (len = 0; len < size; len++) {
//        if(html[len] == '\n')
//            break;
//    }
//    
//    return len;
//}
//
//void init_res_test_data(struct res_html_test* data)
//{
//    data->len  = 0;
//    data->size = 4096;
//    data->html = malloc(sizeof(char) * data->size);
//    
//    if(data->html == NULL) {
//        fprintf(stderr, "Can't init resurces for test object\n");
//        exit(EXIT_FAILURE);
//    }
//}
//
//void init_res_test(struct chunk_res_test* res_test)
//{
//    init_res_test_data(&res_test->data);
//    init_res_test_data(&res_test->result);
//}
//
//void clean_res_test(struct chunk_res_test* res_test)
//{
//    res_test->data.len   = 0;
//    res_test->result.len = 0;
//}
//
//void append_to_test(struct res_html_test* data, const char *text, size_t len, bool add_newline, bool to_lowercase)
//{
//    if(text == NULL)
//        return;
//    
//    if((data->len + len + 2) >= data->size) {
//        data->size = data->size + len + 2048;
//        data->html = realloc(data->html, data->size);
//        
//        if(data->html == NULL) {
//            fprintf(stderr, "Can't realloc resurces for test object\n");
//            exit(EXIT_FAILURE);
//        }
//    }
//    
//    if(add_newline && data->len) {
//        data->html[data->len] = '\n';
//        data->len++;
//    }
//    
//    memcpy(&data->html[data->len], text, len);
//    
//    if(to_lowercase) {
//        for(size_t i = data->len; i < (data->len + len); i++) {
//            if(data->html[i] > 0x40 && data->html[i] < 0x5b)
//                data->html[i] |= 0x60;
//        }
//    }
//    
//    data->len += len;
//    data->html[data->len] = '\0';
//}
//
//bool sort_text(myhtml_tree_attr_t *attr1, size_t size, myhtml_tree_attr_t **list, size_t i, size_t *len)
//{
//    unsigned char *fisrt = (unsigned char*)attr1->key.data;
//    unsigned char *sec = (unsigned char*)list[i]->key.data;
//    
//    for (size_t j = 0; j < size; j++)
//    {
//        if(fisrt[j] > sec[j]) {
//            break;
//        }
//        else if(fisrt[j] < sec[j]) {
//            memmove(&list[(i + 1)], &list[i], sizeof(myhtml_tree_attr_t*));
//            list[i] = attr1;
//            (*len)++;
//            return true;
//        }
//    }
//    
//    return false;
//}
//
//myhtml_tree_attr_t ** sort_attr(myhtml_tree_node_t *node)
//{
//    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);
//    myhtml_tree_attr_t **list = calloc(1024, sizeof(myhtml_tree_attr_t*));
//    size_t len = 1;
//    size_t i;
//    
//    list[0] = attr;
//    attr = attr->next;
//    
//    while (attr) {
//        for (i = 0; i < len; i++) {
//            if(attr->key.length > list[i]->key.length)
//            {
//                if(sort_text(attr, list[i]->key.length, list, i, &len))
//                    break;
//            }
//            else {
//                if(sort_text(attr, attr->key.length, list, i, &len))
//                    break;
//            }
//        }
//        
//        if(i == len) {
//            list[i] = attr;
//            len++;
//        }
//        
//        attr = attr->next;
//    }
//    
//    return list;
//}
//
//void print_node_attr(myhtml_tree_node_t *node, struct res_html_test* data, size_t inc)
//{
//    if(myhtml_node_attribute_first(node) == NULL)
//        return;
//    
//    myhtml_tree_attr_t **list_attr = sort_attr(node);
//    
//    size_t len = 0;
//    while (*list_attr != NULL)
//    {
//        myhtml_tree_attr_t *attr = *list_attr;
//        
//        const char *name = myhtml_attribute_key(attr, &len);
//        
//        if(name) {
//            append_to_test(data, "\n", 1, false, false);
//            
//            for(size_t i = 0; i < inc; i++)
//                append_to_test(data, "  ", 2, false, false);
//            
//            if(attr->ns == MyHTML_NAMESPACE_XML) {
//                append_to_test(data, "xml ", 4, false, false);
//            }
//            else if(attr->ns == MyHTML_NAMESPACE_XMLNS) {
//                append_to_test(data, "xmlns ", 6, false, false);
//            }
//            else if(attr->ns == MyHTML_NAMESPACE_XLINK) {
//                append_to_test(data, "xlink ", 6, false, false);
//            }
//            
//            append_to_test(data, name, len, false, false);
//            
//            const char *value = myhtml_attribute_value(attr, &len);
//            
//            if(value) {
//                append_to_test(data, "=\"", 2, false, false);
//                append_to_test(data, value, len, false, false);
//                append_to_test(data, "\"", 1, false, false);
//            }
//            else {
//                append_to_test(data, "=\"\"", 3, false, false);
//            }
//        }
//        
//        //attr = myhtml_attribute_next(attr);
//        list_attr++;
//    }
//}
//
//void print_tree(myhtml_tree_t* tree, myhtml_tree_node_t *node, struct res_html_test* data, size_t inc)
//{
//    while (node)
//    {
//        if(data->len)
//            append_to_test(data, "\n", 1, false, false);
//        
//        for(size_t i = 0; i < inc; i++)
//            append_to_test(data, "  ", 2, false, false);
//        
//        size_t len = 0;
//        
//        if(myhtml_node_tag_id(node) == MyHTML_TAG__TEXT)
//        {
//            const char *text = myhtml_node_text(node, &len);
//            
//            append_to_test(data, "\"", 1, false, false);
//            append_to_test(data, text, len, false, false);
//            append_to_test(data, "\"", 1, false, false);
//        }
//        else if(myhtml_node_tag_id(node) == MyHTML_TAG__COMMENT)
//        {
//            const char *text = myhtml_node_text(node, &len);
//            
//            append_to_test(data, "<!-- ", 5, false, false);
//            append_to_test(data, text, len, false, false);
//            append_to_test(data, " -->", 4, false, false);
//        }
//        else if(myhtml_node_tag_id(node) == MyHTML_TAG__DOCTYPE)
//        {
//            append_to_test(data, "<!DOCTYPE", strlen("<!DOCTYPE"), false, false);
//            
//            if(tree->doctype.attr_name) {
//                append_to_test(data, " ", 1, false, false);
//                append_to_test(data, tree->doctype.attr_name, strlen(tree->doctype.attr_name), false, false);
//            }
//            
//            if(tree->doctype.attr_public) {
//                append_to_test(data, " \"", 2, false, false);
//                append_to_test(data, tree->doctype.attr_public, strlen(tree->doctype.attr_public), false, false);
//                append_to_test(data, "\"", 1, false, false);
//            }
//            
//            if(tree->doctype.attr_system) {
//                append_to_test(data, " \"", 2, false, false);
//                append_to_test(data, tree->doctype.attr_system, strlen(tree->doctype.attr_system), false, false);
//                append_to_test(data, "\"", 1, false, false);
//            }
//            
//            append_to_test(data, ">", 1, false, false);
//        }
//        else {
//            const char *tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), &len);
//            
//            if(tag_name) {
//                append_to_test(data, "<", 1, false, false);
//                
//                switch (myhtml_node_namespace(node)) {
//                    case MyHTML_NAMESPACE_SVG:
//                        append_to_test(data, "svg ", 4, false, false);
//                        append_to_test(data, tag_name, len, false, false);
//                        break;
//                        
//                    case MyHTML_NAMESPACE_MATHML:
//                        append_to_test(data, "math ", 5, false, false);
//                        append_to_test(data, tag_name, len, false, true);
//                        break;
//                        
//                    default:
//                        append_to_test(data, tag_name, len, false, false);
//                        break;
//                }
//            }
//            else
//                // it can not be
//                printf("<!something is wrong!");
//            
//            //            if(myhtml_node_is_close_self(node))
//            //                append_to_test(data, " /", 2, false);
//            
//            append_to_test(data, ">", 1, false, false);
//            
//            if(myhtml_node_tag_id(node) == MyHTML_TAG_TEMPLATE &&
//               myhtml_node_namespace(node) == MyHTML_NAMESPACE_HTML)
//            {
//                append_to_test(data, "\n", 1, false, false);
//                
//                for(size_t i = 0; i <= inc; i++)
//                    append_to_test(data, "  ", 2, false, false);
//                
//                append_to_test(data, "content", 7, false, false);
//                
//                print_tree(tree, myhtml_node_child(node), data, (inc + 2));
//                node = myhtml_node_next(node);
//                
//                continue;
//            }
//            
//            // print node attributes
//            print_node_attr(node, data, (inc + 1));
//        }
//        
//        // print childs
//        print_tree(tree, myhtml_node_child(node), data, (inc + 1));
//        node = myhtml_node_next(node);
//    }
//}
//
//void chunk_process(struct chunk_res_test *res_test, struct chunk_res_result *result)
//{
//    struct res_html_test data;
//    init_res_test_data(&data);
//    
//    if(result->enabled_script)
//        result->tree->flags |= MyHTML_TREE_FLAGS_SCRIPT;
//    
//    //printf("%.*s\n", res_test->data.len, res_test->data.html);
//    
//    if(result->is_fragment == false) {
//        myhtml_parse_single(result->tree, MyENCODING_UTF_8, res_test->data.html, res_test->data.len);
//        print_tree(result->tree, result->tree->document->child, &data, 0);
//    }
//    else {
//        myhtml_parse_fragment_single(result->tree, MyENCODING_UTF_8, res_test->data.html, res_test->data.len, result->tag_id, result->ns);
//        print_tree(result->tree, result->tree->document->child->child, &data, 0);
//    }
//    
//    if(res_test->result.len != data.len) {
//        result->bad++;
//        
//        printf("Error:\n");
//        printf("Original raw:\n%.*s\n", (int)res_test->data.len, res_test->data.html);
//        printf("Original:\n%s\n", res_test->result.html);
//        printf("Result:\n%s\n", data.html);
//    }
//    else if(strcmp(res_test->result.html, data.html) == 0) {
//        result->good++;
//        printf("Done\n");
//    }
//    else {
//        result->bad++;
//        printf("Error with len ==:\n");
//        printf("Original raw:\n%.*s\n", (int)res_test->data.len, res_test->data.html);
//        printf("Original:\n%s\n", res_test->result.html);
//        printf("Result:\n%s\n", data.html);
//    }
//    
//    myhtml_tree_clean(result->tree);
//    //mythread_clean(result->tree->myhtml->thread);
//    
//    free(data.html);
//}
//
//void read_chunk(struct res_data* res, chunk_test_f func, struct chunk_res_result *result)
//{
//    struct chunk_res_test res_test;
//    init_res_test(&res_test);
//    
//    result->is_fragment = false;
//    
//    size_t i = 0; size_t state = 0;
//    while (i < res->size)
//    {
//        size_t line_len = read_line(&res->data[i], (res->size - i));
//        
//        if(line_len == 0 && state != 1) {
//            if((i + 1) < res->size && res->data[(i + 1)] != '#') {
//                append_to_test(&res_test.result, "\n", 1, true, false);
//                i++;
//                continue;
//            }
//            
//            if(res_test.data.len)
//                func(&res_test, result);
//            
//            state = 0;
//            result->is_fragment = false;
//            result->enabled_script = false;
//            clean_res_test(&res_test);
//        }
//        else if(res->data[i] == '#') {
//            
//            if(line_len == strlen("#script-on") && strncmp(&res->data[i], "#script-on", strlen("#script-on")) == 0) {
//                result->enabled_script = true;
//            }
//            else if(state == 0) {
//                if(strncmp(&res->data[i], "#data", line_len) == 0) {
//                    state = 1;
//                }
//            }
//            else if(state == 1) {
//                if(strncmp(&res->data[i], "#errors", line_len) == 0) {
//                    state = 2;
//                }
//            }
//            else if(state == 2 && line_len > 9) {
//                if(strncmp(&res->data[i], "#document-fragment", line_len) == 0) {
//                    state = 3;
//                    result->is_fragment = true;
//                }
//            }
//            else if(state == 2 || state == 3) {
//                if(strncmp(&res->data[i], "#document", line_len) == 0) {
//                    state = 4;
//                }
//            }
//            else {
//                fprintf(stderr, "Bad position in text\n");
//                exit(EXIT_FAILURE);
//            }
//            
//            i += line_len;
//        }
//        else if(state == 1) {
//            append_to_test(&res_test.data, &res->data[i], line_len, true, false);
//            i += line_len;
//        }
//        else if(state == 3) {
//            const char *data = &res->data[i];
//            size_t j;
//            
//            for(j = 0; j < line_len; j++)
//            {
//                if(data[j] == ' ')
//                {
//                    while(j < line_len) {
//                        if(data[j] != ' ' && data[j] != '\n' && data[j] != '\t' && data[j] != '\r')
//                            break;
//                        
//                        j++;
//                    }
//                    
//                    break;
//                }
//            }
//            
//            if(j == line_len) {
//                result->tag_id = myhtml_tag_id_by_name(result->tree, data, line_len);
//                result->ns = MyHTML_NAMESPACE_HTML;
//            }
//            else {
//                result->tag_id = myhtml_tag_id_by_name(result->tree, &data[j], (line_len - j));
//                
//                if(strncasecmp("math", data, 4) == 0) {
//                    result->ns = MyHTML_NAMESPACE_MATHML;
//                }
//                else if(strncasecmp("svg", data, 3) == 0) {
//                    result->ns = MyHTML_NAMESPACE_SVG;
//                }
//                else {
//                    result->ns = MyHTML_NAMESPACE_HTML;
//                }
//            }
//            
//            i += line_len;
//        }
//        else if(state == 4) {
//            if(res->data[i] == '|') {
//                append_to_test(&res_test.result, &res->data[(i + 2)], (line_len - 2), true, false);
//            }
//            else if(res->data[i] != '\n') {
//                append_to_test(&res_test.result, &res->data[i], line_len, true, false);
//            }
//            
//            i += line_len;
//        }
//        else {
//            i += line_len;
//        }
//        
//        i++;
//    }
//}
//
//void read_dir(const char* from_dir)
//{
//    myhtml_t* myhtml = myhtml_create();
//    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
//    
//    myhtml_tree_t* tree = myhtml_tree_create();
//    myhtml_tree_init(tree, myhtml);
//    
//    DIR *dir;
//    struct dirent *ent;
//    struct stat path_stat;
//    
//    size_t count = 0;
//    size_t from_dir_len = strlen(from_dir);
//    
//    char path[4096];
//    strncpy(path, from_dir, from_dir_len);
//    
//    if((dir = opendir(from_dir)) == NULL) {
//        fprintf(stderr, "Can't open directory: %s\n", from_dir);
//    }
//    
//    struct chunk_res_result result = {tree, 0, 0};
//    
//    while((ent = readdir(dir)) != NULL)
//    {
//        sprintf(&path[from_dir_len], "%s", ent->d_name);
//        stat(path, &path_stat);
//        
//        if(ent->d_name[0] != '.' && !S_ISDIR(path_stat.st_mode) &&
//           ent->d_namlen > 4 &&
//           strcmp(".dat", &ent->d_name[ (ent->d_namlen - 4) ]) == 0)
//        {
//            count++;
//            
//            struct res_data res = load_data(path);
//            read_chunk(&res, chunk_process, &result);
//            free(res.data);
//        }
//    }
//    
//    closedir (dir);
//    
//    myhtml_tree_destroy(tree);
//    myhtml_destroy(myhtml);
//    
//    printf("\nGood: %zu; Bad: %zu\n\n", result.good, result.bad);
//}

//#include "myhtml/serialization.h"
//
//int main(int argc, const char * argv[])
//{
//    setbuf(stdout, 0);
//    
////    read_dir("/new/C-git/tree-construction/");
////    return 0;
//    
//    const char* path = "/new/test.html";
//    struct res_data res = load_data(path);
//    
//    size_t i = 0;
//    
//    myhtml_t* myhtml = myhtml_create();
//    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
//    
//    myhtml_tree_t* tree = myhtml_tree_create();
//    mystatus_t status = myhtml_tree_init(tree, myhtml);
//    if(status) {
//        fprintf(stderr, "Init Tree return BAD status!!!\n");
//        exit(EXIT_FAILURE);
//    }
//    
//    while(i < 1000) {
//        if(myhtml_parse(tree, MyENCODING_UTF_8, res.data, res.size)) {
//            fprintf(stderr, "Parser return BAD status!!!\n");
//            exit(EXIT_FAILURE);
//        }
//        
//        //myhtml_serialization_tree_callback(tree->document, serialization_callback, NULL);
//        //printf("%zu\n", i);
//        i++;
//    }
//    
//    myhtml_tree_destroy(tree);
//    myhtml_destroy(myhtml);
//}











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

#include <myfont/myfont.h>
#include <myencoding/encoding.h>

void usage(const char *path, float font_size, size_t codepoint)
{
    printf("Usage:\n");
    printf("\tprogram [char in UTF-8] [font fize in px] [font path]\n");
    printf("\tdefault: program \"x\" %.f %s\n\n", font_size, path);
}

int main(int argc, const char * argv[])
{
    /* set and get params */
    const char *path = "/new/C-git/Modest/third_party/font/Arkhip.ttf";
    float font_size = 200.0f;
    
    size_t codepoint;
    myencoding_ascii_utf_8_to_codepoint((unsigned char*)"x", &codepoint);
    
    if (argc == 2) {
        if(myencoding_ascii_utf_8_to_codepoint((const unsigned char*)argv[1], &codepoint) == 0) {
            fprintf(stderr, "Bad char code point\n");
            return EXIT_FAILURE;
        }
    }
    else if (argc == 3) {
        long num = strtol(argv[2], NULL, 0);
        
        if(num < 1) {
            fprintf(stderr, "To small font size param\n");
            return EXIT_FAILURE;
        }
        
        font_size = (float)num;
    }
    else if (argc == 4) {
        path = argv[3];
    }
    else {
        usage(path, font_size, codepoint);
    }
    
    myfont_font_t *mf = myfont_create();
    myfont_init(mf);
    
    uint8_t *font_data;
    mystatus_t mf_status = myfont_load_from_file(mf, path, &font_data, NULL);
    
    if(mf_status) {
        myfont_destroy(mf, true);
        
        if(mf_status == MyFONT_STATUS_ERROR_FILE_OPEN) {
            fprintf(stderr, "Can't open font file %s\n", path);
        }
        else {
            fprintf(stderr, "Can't load font file %s\n", path);
        }
        
        return EXIT_FAILURE;
    }
    
    char data[5];
    size_t len = myencoding_codepoint_to_ascii_utf_8(codepoint, data);
    data[len] = '\0';
    
    /* work code */
    uint16_t glyph_index = myfont_glyph_index_by_codepoint(mf, codepoint, NULL);
    
    float baseline   = myfont_metrics_baseline(mf, font_size);
    float ascender   = myfont_metrics_ascender(mf, font_size);
    float descender  = myfont_metrics_descender(mf, font_size);
    float x_height   = myfont_metrics_x_height(mf, font_size);
    float cap_height = myfont_metrics_cap_height(mf, font_size);
    float offset     = myfont_metrics_glyph_offset_y(mf, codepoint, font_size, NULL);
    float width      = myfont_metrics_width(mf, codepoint, font_size, NULL);
    float height     = myfont_metrics_height(mf, codepoint, font_size, NULL);
    
    /* print result */
    printf("Font file: %s\n", path);
    printf("Font size: %.fpx\n\n", font_size);
    
    printf("Metrics for code point " MyCORE_FORMAT_Z " (%s):\n", codepoint, data);
    printf("\tBaseline: %.05f\n", baseline);
    printf("\tAscender: %.05f\n", ascender);
    printf("\tDescender: %.05f\n", descender);
    printf("\tX-Height: %.05f\n", x_height);
    printf("\tCap-Height: %.05f\n", cap_height);
    printf("\tWidth: %.05f\n", width);
    printf("\tHeight: %.05f\n", height);
    
    /* print html svg */
    printf("\n<svg width=\"%f\" height=\"%f\">\n", width + 4.0f, descender + 4.0f);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(0,124,110);stroke-width:1\" />\n", 0.0f, ascender, width, ascender);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(140,0,110);stroke-width:1\" />\n", 0.0f, cap_height, width, cap_height);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(140,124,110);stroke-width:1\" />\n", 0.0f, x_height, width, x_height);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(0,255,0);stroke-width:1\" />\n", 0.0f, baseline, width, baseline);
    printf("\t<line x1=%f y1=%f x2=%f y2=%f style=\"stroke:rgb(255,0,0);stroke-width:1\" />\n", 0.0f, descender, width, descender);
    
    if(glyph_index < mf->table_maxp.numGlyphs) {
        myfont_table_glyph_t *glyph = &mf->table_glyf.cache[glyph_index];
        
        printf("\t<polyline points=\"");
        for(size_t i = 0; i < glyph->pointCount; i++) {
            
            float x = (float)((glyph->head.xMax + glyph->simple.xCoordinates[i]) - glyph->head.xMax) * font_size / ((float)mf->table_head.unitsPerEm);
            float y = (float)((glyph->head.yMax - glyph->simple.yCoordinates[i])) * font_size / ((float)mf->table_head.unitsPerEm);
            
            printf("%f,%f ", x, (y + offset));
        }
        printf("\" />\n");
    }
    
    printf("</svg>\n");
    
    myfont_destroy_font_data(mf, font_data);
    myfont_destroy(mf, true);
    
    return 0;
}






















//int mainsdfsfd(int argc, const char * argv[])
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
//    uint64_t parse_simple_start = mycore_hperf_clock(NULL);
//    uint64_t parse_simple_stop = mycore_hperf_clock(NULL);
//    
//    
//    
//    /* full api */
//    uint64_t parse_start = mycore_hperf_clock(NULL);
//    
//    
//    modest_finder_t* finder = modest_finder_create();
//    modest_finder_init(finder);
//    
////     threads 
//    modest_finder_thread_t *finder_thread = modest_finder_thread_create();
//    modest_finder_thread_init(finder, finder_thread, 4);
//    
//#ifndef MyCORE_BUILD_WITHOUT_THREADS
//    modest_finder_thread_process(modest, finder_thread, myhtml_tree->node_html, stylesheet->sel_list_first);
//#endif
//    
//    finder_thread = modest_finder_thread_destroy(finder_thread, true);
//    finder = modest_finder_destroy(finder, true);
//    
//    
//    uint64_t parse_stop = mycore_hperf_clock(NULL);
//    
////    print_tree_after_all(modest, myhtml_tree, myhtml_tree->node_html, mycss_entry);
//    
//    printf("\n\n------------\nInformation:\n");
//    printf("\tTicks/sec: %llu\n", (unsigned long long) mycore_hperf_res(NULL));
//    mycore_hperf_print("\tFound selectors", parse_start, parse_stop, stdout);
//    mycore_hperf_print("\tParse and Found Simple selectors", parse_simple_start, parse_simple_stop, stdout);
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




















///*
// Copyright (C) 2017 Alexander Borisov
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
// */
//
//#include <string.h>
//#include <myurl/url.h>
//
//int main(int argc, const char * argv[])
//{
//    const char* data_base = "http://lalal.ru/";
//    
//    myurl_t *url = myurl_create();
//    if(url == NULL) {
//        printf("Can't create URL object\n");
//        return EXIT_FAILURE;
//    }
//    
//    if(myurl_init(url)) {
//        printf("Can't init URL object\n");
//        return EXIT_FAILURE;
//    }
//    
//    printf("Parse url \"%s\":\n", data_base);
//    
//    myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, NULL);
//    myurl_entry_t *url_relative = myurl_parse(url, "bla.ru/", strlen("bla.ru/"), url_base, NULL);
//    
//    const char *scheme   = myurl_entry_scheme_name(url_base, NULL);
//    char *authority      = myurl_entry_authority_as_string(url_base, NULL);
//    const char *username = myurl_entry_username(url_base, NULL);
//    const char *password = myurl_entry_password(url_base, NULL);
//    char *host           = myurl_entry_host_as_string(url_base, NULL);
//    char *path           = myurl_entry_path_as_string(url_base, NULL);
//    const char *query    = myurl_entry_query(url_base, NULL);
//    const char *fragment = myurl_entry_fragment(url_base, NULL);
//    
//    printf("\tScheme: %s\n"         , (scheme ? scheme : ""));
//    printf("\tScheme port: %u\n"    , myurl_entry_scheme_port(url_base));
//    printf("\tAuthority (%s):\n"    , authority);
//    printf("\t\tUsername: %s\n"     , username);
//    printf("\t\tPassword: %s\n"     , password);
//    printf("\tHost: %s\n"           , host);
//    printf("\tPort is defined: %s\n", (myurl_entry_port_is_defined(url_base) ? "true" : "false"));
//    printf("\tPort: %u\n"           , myurl_entry_port(url_base));
//    printf("\tPath: %s\n"           , path);
//    printf("\tQuery: %s\n"          , (query ? query : ""));
//    printf("\tFragment: %s\n"       , (fragment ? fragment : ""));
//    
//    myurl_entry_free_string(url_base, authority);
//    myurl_entry_free_string(url_base, host);
//    myurl_entry_free_string(url_base, path);
//    
//    myurl_entry_destroy(url_base, true);
//    myurl_destroy(url, true);
//    
//    return 0;
//}
//




