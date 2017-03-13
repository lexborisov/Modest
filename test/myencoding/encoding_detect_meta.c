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

#include <myhtml/myhtml.h>
#include <myencoding/encoding.h>

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

size_t test_skip_whitespace(const unsigned char *udata, size_t length, size_t data_size)
{
    while(length < data_size) {
        if(udata[length] != 0x09 && udata[length] != 0x0A && udata[length] != 0x0C && udata[length] != 0x0D && udata[length] != 0x20) {
            return length;
        }
        
        length++;
    }
    
    return length;
}

size_t test_skip_not_whitespace(const unsigned char *udata, size_t length, size_t data_size)
{
    while(length < data_size) {
        if(udata[length] == 0x09 || udata[length] == 0x0A || udata[length] == 0x0C || udata[length] == 0x0D || udata[length] == 0x20) {
            return length;
        }
        
        length++;
    }
    
    return length;
}

size_t test_find_body_end(const unsigned char *udata, size_t length, size_t data_size)
{
    while((length + 1) < data_size) {
        if(udata[length] == 0x0A && udata[(length + 1)] == 0x0A) {
            return (length + 1);
        }
        
        length++;
    }
    
    return data_size;
}

void test_entries(const char* filename)
{
    size_t length = 0;
    test_res_t test_data = test_load_file(filename);
    
    size_t code_begin = 0, code_length = 0;
    size_t body_begin = 0;
    
    myencoding_t encoding;
    const unsigned char *udata = (const unsigned char*)test_data.data;
    
    printf("Test, get encoding from <meta ...> element:\n");
    
    while(length < test_data.size)
    {
        /* Find Encoding in Test Header */
        /* skip ws */
        length = code_begin = test_skip_whitespace(udata, length, test_data.size);
        
        if(length >= test_data.size)
            return;
        
        /* find ws */
        length = test_skip_not_whitespace(udata, length, test_data.size);
        code_length = length - code_begin;
        
        if(strncmp("not-determined", &test_data.data[code_begin], strlen("not-determined")) == 0) {
            encoding = MyENCODING_NOT_DETERMINED;
        }
        else if(myencoding_by_name(&test_data.data[code_begin], code_length, &encoding) == false) {
            fprintf(stderr, "Can't get encoding from test header: %.*s\n", (int)code_length, &test_data.data[code_begin]);
            exit(EXIT_FAILURE);
        }
        
        /* Find Test Data */
        /* get begin of body */
        length = body_begin = test_skip_whitespace(udata, length, test_data.size);
        
        /* get end of body */
        length = test_find_body_end(udata, length, test_data.size);
        
        myencoding_t find_encoding = myencoding_prescan_stream_to_determine_encoding(&test_data.data[body_begin], (length - body_begin));
        
        if(find_encoding != encoding) {
            fprintf(stderr, "ERROR! WRONG! ACHTUNG! Header Encoding not equally Encoding after parsing body\n");
            fprintf(stderr, "Header: %.*s\n", (int)code_length, &test_data.data[code_begin]);
            fprintf(stderr, "Body: %.*s\n", (int)(length - body_begin), &test_data.data[body_begin]);
            
            exit(EXIT_FAILURE);
        }
        
        printf("\t%.*s: Ok\n", (int)code_length, &test_data.data[code_begin]);
    }
}

int main(int argc, const char * argv[])
{
    if (argc < 2) {
        printf("Bad ARGV!\nUse: encoding_detect_meta <test_file_path>\n");
        exit(EXIT_FAILURE);
    }
    
    test_entries(argv[1]);
    
    //test_entries("/new/C-git/Modest/test/myhtml/data/encoding/detect_meta.html");
    
    return EXIT_SUCCESS;
}
