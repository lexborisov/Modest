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

#include <mycss/api.h>

int main(int argc, const char * argv[])
{
    char *css = "@charset \"cp1251\"; #best-id {}";
    
    myencoding_t encoding = mycss_encoding_check_charset_rule(css, strlen(css));
    
    if(encoding == MyENCODING_WINDOWS_1251)
        printf("Detected Encoding: windows-1251\n");
    else
        printf("Detected Encoding: something wrong\n");
    
    return 0;
}



