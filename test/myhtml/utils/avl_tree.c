/*
 Copyright (C) 2015-2016 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#include <myhtml/utils/avl_tree.h>

#define test_exit fprintf(stderr, "ERROR! Wrong tree construction!\n"); exit(EXIT_FAILURE);

myhtml_utils_avl_tree_t * avl_tree_create(void)
{
    myhtml_utils_avl_tree_t *avl_tree = myhtml_utils_avl_tree_create();
    if(avl_tree == NULL) {
        fprintf(stderr, "Can't allocate memory for AVL-Tree object\n");
        exit(EXIT_FAILURE);
    }
    
    if(myhtml_utils_avl_tree_init(avl_tree)) {
        fprintf(stderr, "Can't init AVL-Tree object\n");
        exit(EXIT_FAILURE);
    }
    
    return avl_tree;
}

void test_for_three(myhtml_utils_avl_tree_node_t *find_node)
{
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2 */
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 3) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 3 */
    find_node = find_node->right;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
}

void avl_tree_test_3_0(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_3_1(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_3_2(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_3_3(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_3_4(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_3_5(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    
    if(root_node == NULL || root_node->type != 2) {test_exit}
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    test_for_three(find_node);
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_4(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2 */
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 3) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 3 */
    find_node = find_node->right;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 4) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 4 */
    find_node = find_node->right;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_5(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2 */
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 4 */
    find_node = find_node->right;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 3) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 5) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 3 */
    find_node = find_node->left;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 4) {test_exit}
    
    /* 5 */
    find_node = find_node->parent->right;
    
    if(find_node->type  != 5) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 4) {test_exit}
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 4);
    
    printf("");
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_1L(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 1);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 2);
    
    /* 2 */
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 3 */
    find_node = find_node->parent;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 2) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 4 */
    find_node = find_node->right;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_1R(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 4);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2 */
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 3) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 3 */
    find_node = find_node->right;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_2L(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 1);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 2);
    
    /* 2 */
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 3 */
    find_node = find_node->parent;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 2) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 4 */
    find_node = find_node->right;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_2R(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 4);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2 */
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 3) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 3 */
    find_node = find_node->right;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_sub_1L(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 1);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 2);
    
    /* 2 */
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 3 */
    find_node = find_node->parent;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 2) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 4) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 5) {test_exit}
    
    /* 4 */
    find_node = find_node->right;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 5 */
    find_node = find_node->parent->parent;
    
    if(find_node->type  != 5) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 3) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 6) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 6 */
    find_node = find_node->right;
    
    if(find_node->type  != 6) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 7) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 5) {test_exit}
    
    /* 7 */
    find_node = find_node->right;
    
    if(find_node->type  != 7) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 6) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_sub_1R(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 7);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 1);
    
    /* 1 */
    if(find_node->type  != 1) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 2) {test_exit}
    
    /* 2*/
    find_node = find_node->parent;
    
    if(find_node->type  != 2) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 1) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 3 */
    find_node = find_node->parent;
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 2) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 5) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    /* 5 */
    find_node = find_node->right;
    
    if(find_node->type  != 5) {test_exit}
    if(find_node->left  == NULL || find_node->left->type != 4) {test_exit}
    if(find_node->right == NULL || find_node->right->type != 6) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 3) {test_exit}
    
    /* 4 */
    find_node = find_node->left;
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 5) {test_exit}
    
    /* 6 */
    find_node = find_node->parent->right;
    
    if(find_node->type  != 6) {test_exit}
    if(find_node->left  != NULL) {test_exit}
    if(find_node->right != NULL) {test_exit}
    if(find_node->parent == NULL || find_node->parent->type != 5) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_0(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 8);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 4);
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    if(find_node->left->right->type != 3) {test_exit}
    
    if(find_node->right->type != 7) {test_exit}
    if(find_node->right->left->type != 6) {test_exit}
    if(find_node->right->right->type != 9) {test_exit}
    if(find_node->right->left->left->type != 5) {test_exit}
    if(find_node->right->right->right->type != 10) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_1(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 8);
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 5);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 4);
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    if(find_node->left->right->type != 3) {test_exit}
    
    if(find_node->right->type != 7) {test_exit}
    if(find_node->right->left->type != 6) {test_exit}
    if(find_node->right->right->type != 9) {test_exit}
    if(find_node->right->right->right->type != 10) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_2(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 8);
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 6);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 4);
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    if(find_node->left->right->type != 3) {test_exit}
    
    if(find_node->right->type != 7) {test_exit}
    if(find_node->right->left->type != 5) {test_exit}
    if(find_node->right->right->type != 9) {test_exit}
    if(find_node->right->right->right->type != 10) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_3(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 9);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 4);
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    if(find_node->left->right->type != 3) {test_exit}
    
    if(find_node->right->type != 8) {test_exit}
    if(find_node->right->left->type != 6) {test_exit}
    if(find_node->right->right->type != 10) {test_exit}
    if(find_node->right->left->left->type != 5) {test_exit}
    if(find_node->right->left->right->type != 7) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_4(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 4);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 3);
    
    if(find_node->type  != 3) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    
    if(find_node->right->type != 8) {test_exit}
    if(find_node->right->left->type != 6) {test_exit}
    if(find_node->right->right->type != 9) {test_exit}
    if(find_node->right->left->left->type != 5) {test_exit}
    if(find_node->right->left->right->type != 7) {test_exit}
    if(find_node->right->right->right->type != 10) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

void avl_tree_test_delete_10_5(void)
{
    myhtml_utils_avl_tree_t *avl_tree = avl_tree_create();
    myhtml_utils_avl_tree_node_t *root_node = NULL;
    
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 1, (void*)(1));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 2, (void*)(2));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 3, (void*)(3));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 4, (void*)(4));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 5, (void*)(5));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 6, (void*)(6));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 7, (void*)(7));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 8, (void*)(8));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 9, (void*)(9));
    myhtml_utils_avl_tree_add(avl_tree, &root_node, 10, (void*)(10));
    
    myhtml_utils_avl_tree_delete(avl_tree, &root_node, 6);
    
    myhtml_utils_avl_tree_node_t *find_node = myhtml_utils_avl_tree_search_by_type(avl_tree, root_node, 4);
    
    if(find_node->type  != 4) {test_exit}
    if(find_node->parent != NULL) {test_exit}
    
    if(find_node->left->type != 2) {test_exit}
    if(find_node->left->left->type != 1) {test_exit}
    if(find_node->left->right->type != 3) {test_exit}
    
    if(find_node->right->type != 8) {test_exit}
    if(find_node->right->left->type != 5) {test_exit}
    if(find_node->right->right->type != 9) {test_exit}
    if(find_node->right->left->right->type != 7) {test_exit}
    if(find_node->right->right->right->type != 10) {test_exit}
    
    avl_tree = myhtml_utils_avl_tree_destroy(avl_tree, true);
}

int main(int argc, const char * argv[])
{
    myhtml_utils_avl_tree_t *avl_tree = myhtml_utils_avl_tree_create();
    
    avl_tree_test_3_0();
    avl_tree_test_3_1();
    avl_tree_test_3_2();
    avl_tree_test_3_3();
    avl_tree_test_3_4();
    avl_tree_test_3_5();
    avl_tree_test_4();
    avl_tree_test_5();
    
    avl_tree_test_delete_1L();
    avl_tree_test_delete_1R();
    avl_tree_test_delete_2L();
    avl_tree_test_delete_2R();
    
    avl_tree_test_delete_sub_1L();
    avl_tree_test_delete_sub_1R();
    
    avl_tree_test_delete_10_0();
    avl_tree_test_delete_10_1();
    avl_tree_test_delete_10_2();
    avl_tree_test_delete_10_3();
    avl_tree_test_delete_10_4();
    avl_tree_test_delete_10_5();
    
    return EXIT_SUCCESS;
}


