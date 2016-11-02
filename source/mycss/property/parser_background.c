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

#include "mycss/property/parser.h"

bool mycss_property_parser_background_position_check(mycss_values_background_position_t *position)
{
    if(position == NULL)
        return false;
    
    if(position->one.type == MyCSS_PROPERTY_VALUE__LENGTH ||
       position->one.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
                return true;
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT ||
       position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        else
                            return false;
                        
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                           position->four.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                           position->four.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                        {
                            return true;
                        }
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                   position->three.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                   position->three.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                {
                    if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                        return true;
                }
                
                return false;
            }
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_VALUE__LENGTH:
                    case MyCSS_PROPERTY_VALUE__PERCENTAGE:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_TOP:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_VALUE__LENGTH:
                    case MyCSS_PROPERTY_VALUE__PERCENTAGE:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            default:
                return false;
        }
    }
    
    if(position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_TOP ||
       position->one.type == MyCSS_PROPERTY_BACKGROUND_POSITION_BOTTOM)
    {
        switch (position->two.type) {
            case MyCSS_PROPERTY_VALUE_UNDEF:
                return true;
                
            case MyCSS_PROPERTY_VALUE__LENGTH:
            case MyCSS_PROPERTY_VALUE__PERCENTAGE:
            {
                switch (position->three.type) {
                    case MyCSS_PROPERTY_VALUE_UNDEF:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                            return true;
                        else
                            return false;
                        
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
                    case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
                    {
                        if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                           position->four.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                           position->four.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                        {
                            return true;
                        }
                        
                        return false;
                    }
                        
                    default:
                        return false;
                }
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_CENTER:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF)
                    return true;
                
                return false;
            }
                
            case MyCSS_PROPERTY_BACKGROUND_POSITION_LEFT:
            case MyCSS_PROPERTY_BACKGROUND_POSITION_RIGHT:
            {
                if(position->three.type == MyCSS_PROPERTY_VALUE_UNDEF ||
                   position->three.type == MyCSS_PROPERTY_VALUE__LENGTH ||
                   position->three.type == MyCSS_PROPERTY_VALUE__PERCENTAGE)
                {
                    if(position->four.type == MyCSS_PROPERTY_VALUE_UNDEF)
                        return true;
                }
                
                return false;
            }
                
            default:
                return false;
        }
    }
    
    return true;
}


