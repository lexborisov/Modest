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

#include <modest/modest.h>
#include <modest/finder/finder.h>
#include <modest/finder/thread.h>
#include <modest/node/serialization.h>
#include <myhtml/serialization.h>

myhtml_tree_t * parse_html(const char* data, size_t data_size, myhtml_callback_tree_node_f cai, void* cai_ctx)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_callback_tree_node_insert_set(tree, cai, cai_ctx);
    
    myhtml_parse(tree, MyHTML_ENCODING_UTF_8, data, data_size);
    
    return tree;
}

void destroy_html(myhtml_tree_t* myhtml_tree)
{
    myhtml_t* myhtml = myhtml_tree->myhtml;
    myhtml_tree_destroy(myhtml_tree);
    myhtml_destroy(myhtml);
}

mycss_entry_t * parse_css(const char* data, size_t data_size)
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
    
    mycss_parse(entry, MyHTML_ENCODING_UTF_8, data, data_size);
    
    return entry;
}

void destroy_css(mycss_entry_t *mycss_entry)
{
    mycss_t* mycss = mycss_entry->mycss;
    mycss_entry_destroy(mycss_entry, true);
    mycss_destroy(mycss, true);
}

void serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
}

void callback_for_create_mnode(myhtml_tree_t* tree, myhtml_tree_node_t* node, void* ctx)
{
    if(node->data)
        return;
    
    modest_t *modest = (modest_t*)ctx;
    
    /* create modest node */
    modest_node_t *m_node = modest_node_create(modest);
    if(m_node == NULL)
        return;
    
    modest_node_init(modest, m_node);
    
    node->data = (void*)m_node;
}

void print_tree(modest_t* modest, myhtml_tree_t* myhtml_tree, myhtml_tree_node_t* scope_node, mycss_entry_t *mycss_entry)
{
    myhtml_tree_node_t* node = scope_node;
    
    while(node) {
        modest_node_t *m_node = (modest_node_t*)node->data;
        
        myhtml_serialization_node_callback(myhtml_tree, node, serialization_callback, NULL);
        
        if(m_node) {
            printf(" {");
            
            modest_node_raw_serialization(mycss_entry, m_node, serialization_callback, NULL);
            
            printf("}\n");
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


int main(int argc, const char * argv[])
{
    char *html = "<div id=div1>a</div><div id=div2>b</div><div id=div3>c</div><div id=div4>c</div>";
    char *css = "div {padding: 0;} div[id=div2], div[id=div4] {padding-left: 130px;}";
    
    /*
     Init Modest
     */
    modest_t *modest = modest_create();
    modest_status_t status = modest_init(modest);
    
    if(status) {
        fprintf(stderr, "Can't init Modest\n");
        exit(EXIT_FAILURE);
    }
    
    /*
     Parse HTML, CSS
     */
    modest->myhtml_tree = parse_html(html, strlen(html), callback_for_create_mnode, (void*)modest);
    modest->mycss_entry = parse_css(css, strlen(css));
    
    mycss_stylesheet_t *stylesheet = mycss_entry_stylesheet(modest->mycss_entry);
    
    /*
     Init Finder for comparison selectors and tree nodes
     */
    modest_finder_t* finder = modest_finder_create();
    status = modest_finder_init(finder, modest->myhtml_tree, stylesheet);
    
    modest_finder_thread_t *finder_thread = modest_finder_thread_create();
    modest_finder_thread_init(finder, finder_thread, 2);
    
    /*
     Comparison selectors and tree nodes with two threads
     */
    status = modest_finder_thread_process(modest, finder_thread, modest->myhtml_tree,
                                          modest->myhtml_tree->node_html, stylesheet->sel_list_first);
    
    /*
     Print
     */
    print_tree(modest, modest->myhtml_tree, modest->myhtml_tree->node_html, modest->mycss_entry);
    
    /*
     Destroy Finder and Threads
     */
    finder_thread = modest_finder_thread_destroy(finder_thread, true);
    finder = modest_finder_destroy(finder, true);
    
    /*
     Destroy Stylesheet
     */
    mycss_stylesheet_destroy(stylesheet, true);
    
    /*
     Destroy other
     */
    destroy_css(modest->mycss_entry);
    destroy_html(modest->myhtml_tree);
    
    /*
     Destroy Modest
     */
    modest = modest_destroy(modest, true);
    
    return 0;
}


