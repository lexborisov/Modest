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
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/declaration/init.h>
#include <mycss/declaration/entry.h>
#include <mycss/declaration/serialization.h>

#define DIE(msg, ...) do { fprintf(stderr, msg, ##__VA_ARGS__); exit(EXIT_FAILURE); } while(0)
#define CHECK_STATUS(msg, ...) do {if(status) DIE(msg, ##__VA_ARGS__);} while(0)

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
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

void print_entries(mycss_entry_t* entry, mycss_declaration_entry_t* declr_entry)
{
    if(declr_entry == NULL)
        return;
    
    while(declr_entry) {
        printf("\t");
        mycss_declaration_serialization_entry(entry, declr_entry, serialization_callback, NULL);
        
        if(declr_entry->next)
            printf(";\n");
        else
            printf(";");
        
        declr_entry = declr_entry->next;
    }
}

void parse_style_of_node_and_print(myhtml_tree_t *html_tree, mycss_entry_t *css_entry)
{
    myhtml_tree_node_t *node = html_tree->node_html;
    printf("Result:\n");
    
    /* run on a tree without recursion */
    while(node) {
        myhtml_tree_attr_t *attr_style = myhtml_attribute_by_key(node, "style", 5);
        
        if(attr_style) {
            mycss_declaration_entry_t *dec_entry = mycss_declaration_parse(css_entry->declaration, MyENCODING_UTF_8,
                                                                           attr_style->value.data, attr_style->value.length, NULL);
            
            if(dec_entry) {
                printf("Node:\n\t");
                myhtml_serialization_tree_callback(node, serialization_callback, NULL);
                printf("\nDeclaration:\n");
                print_entries(css_entry, dec_entry);
                printf("\n\n");
            }
        }
        
        if(node->child)
            node = node->child;
        else {
            while(node != html_tree->node_html && node->next == NULL)
                node = node->parent;
            
            if(node == html_tree->node_html)
                break;
            
            node = node->next;
        }
    }
}

int main(int argc, const char * argv[])
{
    const char *html = "<div><div style=\"width: 13px; height: 30.4em; background-image: none, cross-fade(32% image(rgba(12, 21, 32, 0.32)), red), string(this-is-string);\"></div></div>";
    
    myhtml_tree_t *html_tree = parse_html(html, strlen(html));
    mycss_entry_t *css_entry = create_css_parser();
    
    /* print tree */
    printf("HTML:\n\t");
    myhtml_serialization_tree_callback(html_tree->node_html, serialization_callback, NULL);
    printf("\n\n");
    
    /* find, parse and print style attributes */
    parse_style_of_node_and_print(html_tree, css_entry);
    
    // destroy all
    mycss_t *mycss = css_entry->mycss;
    mycss_entry_destroy(css_entry, true);
    mycss_destroy(mycss, true);
    
    myhtml_t* myhtml = html_tree->myhtml;
    myhtml_tree_destroy(html_tree);
    myhtml_destroy(myhtml);
    
    return 0;
}


