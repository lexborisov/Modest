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
#include <mycss/declaration/init.h>
#include <mycss/declaration/entry.h>

myhtml_tree_t * parse_html(const char* data, size_t data_size)
{
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    myhtml_parse(tree, MyHTML_ENCODING_UTF_8, data, data_size);
    
    return tree;
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
    const char *html = "<div id=div1><div id=div2 style=\"width: 13px; height: 30.4em\"></div><ul style=\"height: 12px\"></ul></div>";
    
    myhtml_tree_t *html_tree = parse_html(html, strlen(html));
    mycss_entry_t *css_entry = create_css_parser();
    
    /* print tree */
    fprintf(stdout, "HTML Tree:\n");
    myhtml_tree_print_node_children(html_tree, html_tree->document, stdout, 1);
    fprintf(stdout, "\n");
    
    /* find and parse style attributes */
    myhtml_tree_node_t *node = html_tree->node_html;
    
    fprintf(stdout, "Parse result:\n");
    
    while(node) {
        myhtml_tree_attr_t *attr = myhtml_attribute_by_key(node, "style", 5);
        
        if(attr) {
            mycss_declaration_entry_t *dec_entry = mycss_declaration_parse(css_entry->declaration, MyHTML_ENCODING_UTF_8,
                                                                           attr->value.data, attr->value.length, NULL);
            
            /* print result */
            if(dec_entry) {
                fprintf(stdout, "\tNode: ");
                myhtml_tree_print_node(html_tree, node, stdout);
                fprintf(stdout, "\tDeclaration: ");
                mycss_declaration_entries_print(css_entry->declaration, dec_entry, stdout);
                fprintf(stdout, "\n\n");
            }
        }
        
        /* run on a tree without recursion */
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
    
    // destroy all
    mycss_t *mycss = css_entry->mycss;
    mycss_entry_destroy(css_entry, true);
    mycss_destroy(mycss, true);
    
    myhtml_t* myhtml = html_tree->myhtml;
    myhtml_tree_destroy(html_tree);
    myhtml_destroy(myhtml);
    
    return 0;
}


