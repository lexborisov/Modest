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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>

#include <myhtml/myhtml.h>
#include <myhtml/mystring.h>
#include <myhtml/serialization.h>

#include <mycss/mycss.h>
#include <mycss/declaration/init.h>

#define TEST_FAILED(status) ((status) != 0)

typedef bool (*test_read_dir_callback_f)(const char* filename, size_t filename_length, void* ctx);

struct test_stat {
    size_t good;
    size_t total;
}
typedef test_stat_t;

struct test_data {
    myhtml_tree_t* tree;
    mycss_entry_t* entry;
    
    test_stat_t stat;
}
typedef test_data_t;

struct test_res {
    char*  data;
    size_t size;
}
typedef test_res_t;

test_res_t test_load_file(const char* filename)
{
    FILE *fh = fopen(filename, "rb");
    if(fh == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(fseek(fh, 0L, SEEK_END) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    long size = ftell(fh);
    
    if(fseek(fh, 0L, SEEK_SET) != 0) {
        fprintf(stderr, "Can't set position (fseek) in file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if(size <= 0) {
        fprintf(stderr, "Can't get file size or file is empty: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    char *file_data = (char*)malloc(size + 1);
    if(file_data == NULL) {
        fprintf(stderr, "Can't allocate mem for file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t nread = fread(file_data, 1, size, fh);
    if (nread != size) {
        fprintf(stderr, "Could not read %ld bytes (" MyCORE_FORMAT_Z " bytes done)\n", size, nread);
        exit(EXIT_FAILURE);
    }

    fclose(fh);
    
    return (test_res_t){file_data, (size_t)size};
}

void test_init_str_raw(mycore_string_raw_t* str, size_t size)
{
    str->size   = size;
    str->length = 0;
    str->data   = (char*)mycore_malloc(str->size * sizeof(char));
    
    if(str->data == NULL) {
        fprintf(stderr, "Can't allocation resources for mycore_string_raw_t object\n");
        exit(EXIT_FAILURE);
    }
}

void test_reallocate_str(mycore_string_raw_t *str, size_t size)
{
    str->data = (char*)mycore_realloc(str->data, size * sizeof(char));
    
    if(str->data == NULL) {
        fprintf(stderr, "Can't reallocation resources for mycore_string_raw_t object\n");
        exit(EXIT_FAILURE);
    }
}

void test_str_set_term(mycore_string_raw_t *str)
{
    if((str->length + 1) >= str->size)
        test_reallocate_str(str, 64);
    
    str->data[ str->length ] = '\0';
}

mycore_string_raw_t test_combine_to_style(const char* one, size_t one_len, const char* two, size_t two_len)
{
    size_t new_size = one_len + two_len;
    
    mycore_string_raw_t str = {0};
    test_init_str_raw(&str, (new_size + 2));
    
    memcpy(str.data, one, sizeof(char) * one_len);
    str.length = one_len;
    
    str.data[str.length] = ':';
    str.length++;
    
    memcpy(&str.data[str.length], two, sizeof(char) * two_len);
    str.length += two_len;
    
    str.data[ str.length ] = '\0';
    
    return str;
}

/* basic init */
myhtml_tree_t * test_declaration_create_myhtml(void)
{
    myhtml_t* myhtml = myhtml_create();
    if(myhtml == NULL)
        exit(EXIT_FAILURE);
    
    myhtml_status_t status = myhtml_init(myhtml, MyHTML_OPTIONS_PARSE_MODE_SINGLE, 1, 0);
    if(TEST_FAILED(status)) exit(EXIT_FAILURE);
    
    myhtml_tree_t* tree = myhtml_tree_create();
    if(tree == NULL)
        exit(EXIT_FAILURE);
    
    status = myhtml_tree_init(tree, myhtml);
    if(TEST_FAILED(status)) exit(EXIT_FAILURE);
    
    myhtml_tree_parse_flags_set(tree, MyHTML_TREE_PARSE_FLAGS_SKIP_WHITESPACE_TOKEN|MyHTML_TREE_PARSE_FLAGS_WITHOUT_DOCTYPE_IN_TREE);
    
    return tree;
}

void test_declaration_destroy_myhtml(myhtml_tree_t *tree)
{
    myhtml_t* myhtml = tree->myhtml;
    
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}

mycss_entry_t * test_declaration_create_mycss(void)
{
    mycss_t *mycss = mycss_create();
    if(mycss == NULL)
        exit(EXIT_FAILURE);
        
    mycss_status_t status = mycss_init(mycss);
    if(TEST_FAILED(status)) exit(EXIT_FAILURE);
    
    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    if(entry == NULL)
        exit(EXIT_FAILURE);
    
    status = mycss_entry_init(mycss, entry);
    if(TEST_FAILED(status)) exit(EXIT_FAILURE);
    
    return entry;
}

void test_declaration_destroy_mycss(mycss_entry_t *entry)
{
    mycss_t *mycss = entry->mycss;
    
    mycss_entry_destroy(entry, true);
    mycss_destroy(mycss, true);
}

test_stat_t test_read_dir(const char* dir_path, test_read_dir_callback_f callback, void* context)
{
    /* ho-ho-ho */
    char path[(4096 * 4)];
    sprintf(path, "%s", dir_path);
    
    printf("Tests in directory: %s\n", path);
    
    size_t path_len = strlen(dir_path);

    DIR *dir;
    struct dirent *ent;
    struct stat path_stat;

    test_stat_t result_stat = {0};

    if((dir = opendir(dir_path)) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            sprintf(&path[path_len], "/%s", ent->d_name);

            if(stat(path, &path_stat) != 0) {
                fprintf(stderr, "Can't get status for file: %s\n", path);
                exit(EXIT_FAILURE);
            }

            if(ent->d_name[0] == '.' || S_ISDIR(path_stat.st_mode))
                continue;
            
            result_stat.total++;
            printf(MyCORE_FORMAT_Z ") %s: ", result_stat.total, ent->d_name);
            
            if(callback(path, (strlen(ent->d_name) + path_len + 1), context)) {
                result_stat.good++;
            }
        }

        closedir (dir);
    }
    
    return result_stat;
}

/* test */
bool test_process_elements(test_data_t *test_data, myhtml_collection_t *collection, test_stat_t* result_stat);
mycore_string_raw_t test_process_result_from_node(test_data_t *test_data, myhtml_tree_node_t *node);
mycore_string_raw_t test_process_serialize_stype(test_data_t *test_data, const char* style, size_t style_size);
mystatus_t test_process_serialize_callback(const char* buffer, size_t size, void* ctx);

bool test_process_callback(const char* filename, size_t filename_len, void* context)
{
    test_data_t *test_data = (test_data_t*)context;
    test_res_t html_data = test_load_file(filename);
    test_stat_t result_stat = {0};
    
    /* parse html */
    myhtml_status_t status = myhtml_parse(test_data->tree, MyENCODING_UTF_8, html_data.data, html_data.size);
    if(status) {
        fprintf(stderr, "Could parse HTML from file %s error code %d\n", filename, status);
        exit(EXIT_FAILURE);
    }
    
    /* find test elements */
    myhtml_collection_t *collection = myhtml_get_nodes_by_name_in_scope(test_data->tree, NULL, test_data->tree->node_body, "test", 4, NULL);
    
    if(collection->length)
        test_process_elements(test_data, collection, &result_stat);
    
    myhtml_collection_destroy(collection);
    
    if((result_stat.total - result_stat.good)) {
        printf("\tResult: ");
    }
    
    printf("count(" MyCORE_FORMAT_Z ") good(" MyCORE_FORMAT_Z ") bad(" MyCORE_FORMAT_Z ")\n", result_stat.total, result_stat.good, (result_stat.total - result_stat.good));
    
    test_data->stat.good += result_stat.good;
    test_data->stat.total += result_stat.total;
    
    mycore_free(html_data.data);
    return true;
}

bool test_process_elements(test_data_t *test_data, myhtml_collection_t *collection, test_stat_t* result_stat)
{
    for(size_t i = 0; i < collection->length; i++)
    {
        myhtml_tree_node_t *node = collection->list[i];
        myhtml_tree_attr_t* attr_name = myhtml_attribute_by_key(node, "name", 4);
        myhtml_tree_attr_t* attr_value = myhtml_attribute_by_key(node, "value", 5);
        
        size_t name_length;
        size_t value_length;
        
        const char* name = myhtml_attribute_value(attr_name, &name_length);
        const char* value = myhtml_attribute_value(attr_value, &value_length);
        
        mycore_string_raw_t style = test_combine_to_style(name, name_length, value, value_length);
        
        mycore_string_raw_t correct_result = test_process_result_from_node(test_data, node);
        mycore_string_raw_t parse_result = test_process_serialize_stype(test_data, style.data, style.length);
        
        result_stat->total++;
        
        if(correct_result.length == parse_result.length &&
           strcmp(correct_result.data, parse_result.data) == 0)
        {
            result_stat->good++;
        }
        else {
            if((result_stat->total - result_stat->good) == 1) {
                printf("\n");
            }
            
            printf("\tBad: name=\"%s\" value=\"%s\" need=\"%s\" result=\"%s\"\n", name, value, correct_result.data, parse_result.data);
        }

        mycore_string_raw_destroy(&style, false);
        mycore_string_raw_destroy(&correct_result, false);
        mycore_string_raw_destroy(&parse_result, false);
        
        mycss_entry_clean_all(test_data->entry);
    }
    
    return true;
}

mycore_string_raw_t test_process_result_from_node(test_data_t *test_data, myhtml_tree_node_t *node)
{
    mycore_string_raw_t str = {0};
    
    if(myhtml_serialization_node_buffer(node->child, &str)) {
        fprintf(stderr, "Could serialization HTML node\n");
        exit(EXIT_FAILURE);
    }
    
    return str;
}

mycore_string_raw_t test_process_serialize_stype(test_data_t *test_data, const char* style, size_t style_size)
{
    mycore_string_raw_t str;
    test_init_str_raw(&str, 4096);
    
    mycss_status_t status;
    mycss_declaration_entry_t *declaration = mycss_declaration_parse(test_data->entry->declaration, MyENCODING_UTF_8, style, style_size, &status);
    
    if(status) {
        fprintf(stderr, "Could parse CSS Style (%d): %s\n", status, style);
        exit(EXIT_FAILURE);
    }
    
    mycss_declaration_serialization_entry_only_value(test_data->entry, declaration, test_process_serialize_callback, &str);
    test_str_set_term(&str);
    
    return str;
}

mystatus_t test_process_serialize_callback(const char* buffer, size_t size, void* ctx)
{
    mycore_string_raw_t *str = (mycore_string_raw_t*)ctx;
    
    if((str->length + size) >= str->size)
        test_reallocate_str(str, 4096);
    
    memcpy(&str->data[ str->length ], buffer, sizeof(char) * size);
    str->length += size;
    
    return MyCORE_STATUS_OK;
}

int main(int argc, const char * argv[])
{
    setbuf(stdout, NULL);
    
    if (argc < 2) {
        printf("Bad ARGV!\nUse: declaration <path_to_dir_test>\n");
        exit(EXIT_FAILURE);
    }
    
    test_data_t test_data = {
        test_declaration_create_myhtml(),
        test_declaration_create_mycss(),
        {0}
    };
    
    //test_read_dir("/new/C-git/Modest/test/mycss/data/declaration", test_process_callback, &test_data);
    
    test_read_dir(argv[1], test_process_callback, &test_data);
    
    size_t bad_count = (test_data.stat.total - test_data.stat.good);
    printf("\nTotal: " MyCORE_FORMAT_Z "; Good: " MyCORE_FORMAT_Z "; Bad: " MyCORE_FORMAT_Z "\n", test_data.stat.total, test_data.stat.good, bad_count);
    
    test_declaration_destroy_myhtml(test_data.tree);
    test_declaration_destroy_mycss(test_data.entry);
    
    return (bad_count ? EXIT_FAILURE : EXIT_SUCCESS);
}




