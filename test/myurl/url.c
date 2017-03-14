/*
 Copyright (C) 2015-2017 Alexander Borisov
 
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

#include <myurl/url.h>
#include <myurl/serialization.h>
#include <myhtml/mystring.h>
#include <mycore/utils/mchar_async.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

struct test_res {
    char*  data;
    size_t size;
}
typedef test_res_t;

struct test_pos {
    size_t begin;
    size_t length;
}
typedef test_pos_t;

enum test_type {
    TEST_TYPE_UNDEF   = 0x00,
    TEST_TYPE_FIRST   = '1',
    TEST_TYPE_SECOND  = '2',
    TEST_TYPE_THIRD   = '3',
    TEST_TYPE_FOURTH  = '4'
};

static mchar_async_t* MCharOBJ = NULL;
static size_t MCharOBJNode = 0;

test_pos_t test_get_value(const char *data, size_t* length, size_t data_size, const char* some);

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
        fprintf(stderr, "Could not read %ld bytes (%zu bytes done)\n", size, nread);
        exit(EXIT_FAILURE);
    }
    
    fclose(fh);
    
    return (test_res_t){file_data, (size_t)size};
}

mystatus_t test_serialization_callback(const char* data, size_t len, void* ctx)
{
    mycore_string_t *str = ctx;
    mycore_string_append(str, data, len);
    
    return MyCORE_STATUS_OK;
}

myurl_entry_t * test_parse_url(const char *data, size_t length, myurl_entry_t* base_url)
{
    myurl_t *url = myurl_create();
    if(url == NULL) {
        fprintf(stderr, "Could create url object\n");
        exit(EXIT_FAILURE);
    }
    
    if(myurl_init(url)) {
        fprintf(stderr, "Could init url object\n");
        exit(EXIT_FAILURE);
    }
    
    myurl_entry_t *url_entry = myurl_parse(url, data, length, base_url, NULL);
    
    if(url_entry == NULL) {
        myurl_destroy(url, true);
        return NULL;
    }
    
    return url_entry;
}

void test_destroy_url(myurl_entry_t* entry_url)
{
    if(entry_url) {
        myurl_t *url = entry_url->url_ref;
        myurl_entry_destroy(entry_url, true);
        myurl_destroy(url, true);
    }
}

myurl_host_type_t test_host_type_from_data(const char *data, size_t length)
{
    if(strncmp("IPv4", data, length) == 0) {
        return MyURL_HOST_TYPE_IPv4;
    }
    else if(strncmp("IPv6", data, length) == 0) {
        return MyURL_HOST_TYPE_IPv6;
    }
    else if(strncmp("DOMAIN", data, length) == 0) {
        return MyURL_HOST_TYPE_DOMAIN;
    }
    else if(strncmp("OPAQUE", data, length) == 0) {
        return MyURL_HOST_TYPE_OPAQUE;
    }
    
    return MyURL_HOST_TYPE_UNDEF;
}

myurl_host_type_t test_get_domain_type(const char *data, size_t* length, size_t data_size)
{
    test_pos_t domain_type = test_get_value(data, length, data_size, "%DOMAIN_TYPE:");
    myurl_host_type_t domain_type_int = test_host_type_from_data(&data[domain_type.begin], domain_type.length);
    
    return domain_type_int;
}

test_pos_t test_get_value(const char *data, size_t* length, size_t data_size, const char* some)
{
    test_pos_t pos = {0};
    size_t some_len = strlen(some);
    
    size_t len = *length + some_len;
    
    if(len >= data_size)
        return pos;
    
    if(strncmp(some, &data[ *length ], some_len))
        return pos;
    
    pos.begin = len;
    
    while(len < data_size) {
        if(data[len] == '%')
        {
            size_t bpos = len;
            bpos++;
            
            while(bpos < data_size) {
                if((bpos - 1) > len && (data[bpos] < 'A' || data[bpos] > 'Z') && data[bpos] != '_') {
                    if(data[bpos] == ':') {
                        if(strncmp("%URL", &data[len], 4) == 0)
                            pos.length = ((len - pos.begin) - 2);
                        else
                            pos.length = ((len - pos.begin) - 1);
                        
                        *length = len;
                        return pos;
                    }
                    
                    break;
                }
                
                bpos++;
            }
        }
        
        len++;
    }
    
    *length = len;
    pos.length = ((len - pos.begin) - 1);
    
    return pos;
}

/* FIRST */
bool test_for_type_first_entry(const char *data, size_t* length, size_t data_size)
{
    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
    if(url.length == 0)
        return true;
    
    //printf("%.*s\n", (int)url.length, &data[ url.begin ]);
    
    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, NULL);
    
    /* get expected */
    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
    if(expect.length == 0) {
        if(url_entry == NULL)
            return true;
    }
    
    if(url_entry == NULL) {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tResult:\n");
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_t cmp_str = {0};
    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
    
    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
    
    /* compare */
    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
    {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        mycore_string_destroy(&cmp_str, false);
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_destroy(&cmp_str, false);
    test_destroy_url(url_entry);
    
    return true;
}

bool test_for_type_first(const char *data, size_t length, size_t data_size)
{
    while(length < data_size) {
        if(test_for_type_first_entry(data, &length, data_size) == false)
            return false;
    }
    
    return true;
}

/* SECOND */
bool test_for_type_second_entry(const char *data, size_t* length, size_t data_size)
{
    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
    if(url.length == 0)
        return true;
    
    /* get domain_type */
    myurl_host_type_t domain_type = test_get_domain_type(data, length, data_size);
    
    //printf("%.*s\n", (int)url.length, &data[ url.begin ]);
    
    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, NULL);
    
    /* get expected */
    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
    if(expect.length == 0) {
        if(url_entry == NULL)
            return true;
    }
    
    if(url_entry == NULL) {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tResult:\n");
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        test_destroy_url(url_entry);
        return true;
    }
    
    if(url_entry->host.type != domain_type) {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tDomain Type: %d\n", url_entry->host.type);
        fprintf(stderr, "\tDomain Ip Version Type: %d\n", url_entry->host.value.ipv.type);
        fprintf(stderr, "\tExpect Domain Type: %d\n\n", domain_type);
        
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_t cmp_str = {0};
    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
    
    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
    
    /* compare */
    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
    {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        mycore_string_destroy(&cmp_str, false);
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_destroy(&cmp_str, false);
    test_destroy_url(url_entry);
    
    return true;
}

bool test_for_type_second(const char *data, size_t length, size_t data_size)
{
    while(length < data_size) {
        if(test_for_type_second_entry(data, &length, data_size) == false)
            return false;
    }
    
    return true;
}

/* THIRD */
bool test_for_type_third_entry(const char *data, size_t* length, size_t data_size)
{
    test_pos_t url = test_get_value(data, length, data_size, "%URL:");
    if(url.length == 0)
        return true;
    
    /* get base */
    test_pos_t base = test_get_value(data, length, data_size, "%BASE:");
    if(base.length == 0)
        return true;
    
    myurl_entry_t *base_entry = test_parse_url(&data[ base.begin ], base.length, NULL);
    myurl_entry_t *url_entry = test_parse_url(&data[ url.begin ], url.length, base_entry);
    
    /* get expected */
    test_pos_t expect = test_get_value(data, length, data_size, "%EXPECT:");
    if(expect.length == 0) {
        if(url_entry == NULL)
            return true;
    }
    
    if(url_entry == NULL) {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tBASE: %.*s\n", (int)base.length, &data[ base.begin ]);
        fprintf(stderr, "\tResult:\n");
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_t cmp_str = {0};
    mycore_string_init(MCharOBJ, MCharOBJNode, &cmp_str, 1024);
    
    myurl_serialization(url_entry, false, test_serialization_callback, &cmp_str);
    
    /* compare */
    if(cmp_str.length != expect.length || strncmp(cmp_str.data, &data[expect.begin], cmp_str.length))
    {
        fprintf(stderr, "Test FAILURE!\n");
        fprintf(stderr, "\tURL: %.*s\n", (int)url.length, &data[ url.begin ]);
        fprintf(stderr, "\tBASE: %.*s\n", (int)base.length, &data[ base.begin ]);
        fprintf(stderr, "\tResult: %.*s\n", (int)cmp_str.length, cmp_str.data);
        fprintf(stderr, "\tExpect: %.*s\n\n", (int)expect.length, &data[expect.begin]);
        
        mycore_string_destroy(&cmp_str, false);
        test_destroy_url(url_entry);
        return true;
    }
    
    mycore_string_destroy(&cmp_str, false);
    test_destroy_url(url_entry);
    
    return true;
}

bool test_for_type_third(const char *data, size_t length, size_t data_size)
{
    while(length < data_size) {
        if(test_for_type_third_entry(data, &length, data_size) == false)
            return false;
    }
    
    return true;
}

void test_by_type(const char *data, size_t data_size, const char* filename)
{
    printf("Test file: %s\n", filename);
    
    size_t length = 8;
    
    if(data_size <= length || strncmp("type ", data, 5)) {
        fprintf(stderr, "Could not read type form %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    switch ((unsigned char)data[5]) {
        case TEST_TYPE_FIRST:
            test_for_type_first(&data[8], 0, (data_size - 8));
            break;
            
        case TEST_TYPE_SECOND:
            test_for_type_second(&data[8], 0, (data_size - 8));
            break;
            
        case TEST_TYPE_THIRD:
            test_for_type_third(&data[8], 0, (data_size - 8));
            break;
            
        default:
            break;
    }
}

void test(const char* filename)
{
    test_res_t test_data = test_load_file(filename);
    test_by_type(test_data.data, test_data.size, filename);
    
    if(test_data.data)
        free(test_data.data);
}

void test_read_dir(const char* dir_path)
{
    char path[(4096 * 4)];
    sprintf(path, "%s", dir_path);
    
    printf("Tests in directory: %s\n", path);
    
    size_t path_len = strlen(dir_path);
    
    DIR *dir;
    struct dirent *ent;
    struct stat path_stat;
    
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
            
            test(path);
        }
        
        closedir (dir);
    }
}

int main(int argc, const char * argv[])
{
    setbuf(stdout, NULL);
    
    if (argc < 2) {
        printf("Bad ARGV!\nUse: url <test_file_path>\n");
        exit(EXIT_FAILURE);
    }
    
    MCharOBJ = mchar_async_create();
    if(MCharOBJ == NULL)
        return EXIT_FAILURE;
    
    if(mchar_async_init(MCharOBJ, 4, 4096))
        return EXIT_FAILURE;
    
    MCharOBJNode = mchar_async_node_add(MCharOBJ, NULL);
    
    test_read_dir(argv[1]);
    //test_read_dir("/new/C-git/Modest/test/myurl/data");
    
    mchar_async_destroy(MCharOBJ, true);
    
    return EXIT_SUCCESS;
}
