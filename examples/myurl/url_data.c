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
    const char* data_base = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAOCAYAAAAmL5yKAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAGlSURBVDhPnZDfS1NhGMfff8oLEUE0FBfqmrigi/DKrvKqiNDEKYjCUJdH3I/Q5WoLdYmlU1FP0LQoEclYOCcoMbJuDAUVA/v0vK8/QssL98AH3u97zud7Ho4ajr8i2P8sJ2JDcVSwf5BcR7sqEHpqQpF/60ro0e5Zwb1FiPyAoW14tAIVE5fjGDPKaUHYhOQhTO1DYu+Y/4mn/C0Io3oDAyasCYtHsPALRmUL5+R56j9AdwbsA4jJpnq0q6y+JyboO11ibUBt8jxpuV8VPgn6I5M7cpDRrhSETKiXf3BXuPP+X8Zlo3V5JyUs/4aZXaNIQQj12AqY0CBPL9KW+kIwbWF/b2MqW8d09iZzW27mf0aNo13lOynwpPZpTHpotstpfVOK9105oeUKnqeqiK06iWduMLbhIvG1Gvub2zjaVV09fhPqRgq5nyimYaaEptlrtCfL6Fu6TvhzJREpeZF28nLdxevNamazNcbRrvJ2WiY4/Hm4w/ncihRwO1pwVqjLWuxS2t+W0SVbWR8dDK5UGke7qsPrMyGX0a7y9fSaQy48eNjIH2VPyHZqSIx2AAAAAElFTkSuQmCC";
    
    myurl_t *url = myurl_create();
    if(url == NULL) {
        printf("Can't create URL object\n");
        return EXIT_FAILURE;
    }
    
    if(myurl_init(url)) {
        printf("Can't init URL object\n");
        return EXIT_FAILURE;
    }
    
    printf("Parse URL: %s\n\n", data_base);
    
    myurl_entry_t *url_base = myurl_parse(url, data_base, strlen(data_base), NULL, NULL);
    char *path = myurl_entry_path_as_string(url_base, NULL);
    
    printf("Result data from URL: %s\n", path);
    
    myurl_entry_free_string(url_base, path);
    myurl_entry_destroy(url_base, true);
    myurl_destroy(url, true);
    
    return EXIT_SUCCESS;
}
