/*
 Copyright (C) 2016-2017 Alexander Borisov
 
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

#include "mycss/media/init.h"

mycss_media_t * mycss_media_create(void)
{
    return (mycss_media_t*)mycore_calloc(1, sizeof(mycss_media_t));
}

mystatus_t mycss_media_init(mycss_entry_t* entry, mycss_media_t* media)
{
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_media_clean_all(mycss_media_t* media)
{
    return MyCSS_STATUS_OK;
}

mycss_media_t * mycss_media_destroy(mycss_media_t* media, bool self_destroy)
{
    if(media == NULL)
        return NULL;
    
    if(self_destroy) {
        mycore_free(media);
        return NULL;
    }
    
    return media;
}


