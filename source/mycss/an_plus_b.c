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

#include "mycss/an_plus_b.h"
#include "mycore/utils/resources.h"

mycss_an_plus_b_t * mycss_an_plus_b_create(void)
{
    return (mycss_an_plus_b_t*)mycore_calloc(1, sizeof(mycss_an_plus_b_t));
}

mystatus_t mycss_an_plus_b_init(mycss_entry_t* entry, mycss_an_plus_b_t* anb)
{
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_an_plus_b_clean_all(mycss_an_plus_b_t* anb)
{
    return MyCSS_STATUS_OK;
}

mycss_an_plus_b_t * mycss_an_plus_b_destroy(mycss_an_plus_b_t* anb, bool self_destroy)
{
    if(anb == NULL)
        return NULL;
    
    if(self_destroy) {
        mycore_free(anb);
        return NULL;
    }
    
    return anb;
}

/////////////////////////////////////////////////////////
//// An+B Entry
////
/////////////////////////////////////////////////////////
mycss_an_plus_b_entry_t * mycss_an_plus_b_entry_create(mycss_entry_t* entry)
{
    return (mycss_an_plus_b_entry_t*)mchar_async_malloc(entry->mchar,
                                                        entry->mchar_value_node_id,
                                                        sizeof(mycss_an_plus_b_entry_t));
}

void mycss_an_plus_b_entry_clean_all(mycss_an_plus_b_entry_t* anb_entry)
{
    memset(anb_entry, 0, sizeof(mycss_an_plus_b_entry_t));
}

mycss_an_plus_b_entry_t * mycss_an_plus_b_entry_destroy(mycss_entry_t* entry, mycss_an_plus_b_entry_t* anb_entry, bool self_destroy)
{
    if(anb_entry == NULL)
        return NULL;
    
    if(self_destroy) {
        mchar_async_free(entry->mchar, entry->mchar_value_node_id, (char*)anb_entry);
        return NULL;
    }
    
    return anb_entry;
}

/////////////////////////////////////////////////////////
//// An+B Parser
////
/////////////////////////////////////////////////////////
void mycss_an_plus_b_parser_expectations_error(mycss_entry_t* entry)
{
    mycss_an_plus_b_current_entry(entry)->is_broken = true;
}

/////////////////////////////////////////////////////////
//// An+B Serialization
////
/////////////////////////////////////////////////////////
void mycss_an_plus_b_serialization(mycss_an_plus_b_entry_t* anb_entry, mycore_callback_serialize_f callback, void* context)
{
    char data[512];
    
    if(anb_entry->a != 0) {
        int len = snprintf(data, 512, "%ld", anb_entry->a);
        
        if(len > 0)
            callback(data, (size_t)len, context);
    }
    
    callback("n", 1, context);
    
    if(anb_entry->b != 0) {
        if(anb_entry->b >= 0)
            callback("+", 1, context);
        
        int len = snprintf(data, 512, "%ld", anb_entry->b);
        
        if(len > 0)
            callback(data, (size_t)len, context);
    }
}

/////////////////////////////////////////////////////////
//// An+B State
////
/////////////////////////////////////////////////////////
bool mycss_an_plus_b_state_anb_begin(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_entry_create(entry);
    mycss_an_plus_b_entry_clean_all(anb_entry);
    
    *entry->anb->entry = anb_entry;
    
    return mycss_an_plus_b_state_anb(entry, token, true);
}

bool mycss_an_plus_b_state_anb(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_current_entry(entry);
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_WHITESPACE:
            break;
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            if(mycore_strncasecmp(str.data, "-n-", 3) == 0)
            {
                anb_entry->a = -1;
                
                if(str.length == 3) {
                    anb_entry->b = -1;
                    
                    entry->parser = mycss_an_plus_b_state_anb_plus_n_hyphen;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                /* -n-* */
                size_t len = str.length - 2;
                if(mycss_convert_data_to_integer(&str.data[2], len, &anb_entry->b) != len) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_hyphen_n_hyphen_asterisk_end");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strncasecmp(str.data, "-n", 2) == 0) {
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_hyphen_n_end");
                
                anb_entry->a = -1;
                
                if(str.length == 2) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                size_t len = str.length - 2;
                if(mycss_convert_data_to_integer(&str.data[2], len, &anb_entry->b) != len) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strncasecmp(str.data, "n-", 2) == 0)
            {
                anb_entry->a = 1;
                
                if(str.length == 2) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n_hyphen;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                size_t len = str.length - 1;
                if(mycss_convert_data_to_integer(&str.data[1], len, &anb_entry->b) != len) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_n");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strncasecmp(str.data, "n", 1) == 0)
            {
                anb_entry->a = 1;
                
                if(str.length == 1) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                size_t len = str.length - 1;
                if(mycss_convert_data_to_integer(&str.data[1], len, &anb_entry->b) != len) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_n");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strcasecmp(str.data, "even") == 0) {
                anb_entry->a = 2;
                anb_entry->b = 0;
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_e_v_e_n");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strcasecmp(str.data, "odd") == 0) {
                anb_entry->a = 2;
                anb_entry->b = 1;
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_o_d_d");
                entry->parser = entry->parser_switch;
            }
            else {
                mycore_string_destroy(&str, false);
                
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            
            mycore_string_destroy(&str, false);
            break;
        }
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '+') {
                anb_entry->a = 1;
                
                entry->parser = mycss_an_plus_b_state_anb_plus;
            }
            else {
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            break;
        }
        case MyCSS_TOKEN_TYPE_NUMBER: {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            mycss_convert_data_to_integer(str.data, str.length, &anb_entry->b);
            
            mycore_string_destroy(&str, false);
            
            MyCORE_DEBUG("mycss_an_plus_b_state_anb_number");
            entry->parser = entry->parser_switch;
            break;
        }
        case MyCSS_TOKEN_TYPE_DIMENSION: {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            size_t consumed_len = mycss_convert_data_to_integer(str.data, str.length, &anb_entry->a);
            
            if(mycore_strncasecmp(&str.data[consumed_len], "n-", 2) == 0)
            {
                size_t rem = str.length - consumed_len;
                
                if(rem == 2) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n_hyphen;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                rem -= 1;
                if(mycss_convert_data_to_integer(&str.data[(consumed_len + 1)], rem, &anb_entry->b) != rem) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_n_hyphen_asterisk_end");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strncasecmp(&str.data[consumed_len], "n", 1) == 0)
            {
                size_t rem = (str.length - consumed_len) - 1;
                
                if(rem == 0) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                if(mycss_convert_data_to_integer(&str.data[(consumed_len + 1)], rem, &anb_entry->b) != rem) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_n_end");
                entry->parser = entry->parser_switch;
            }
            else {
                mycore_string_destroy(&str, false);
                
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            
            mycore_string_destroy(&str, false);
            break;
        }
        default: {
            mycss_an_plus_b_parser_expectations_error(entry);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_an_plus_b_state_anb_plus(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_current_entry(entry);
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_IDENT: {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            if(mycore_strncasecmp(str.data, "n-", 2) == 0)
            {
                if(str.length == 2) {
                    entry->parser = mycss_an_plus_b_state_anb_plus_n_hyphen;
                    
                    mycore_string_destroy(&str, false);
                    return true;
                }
                
                size_t len = str.length - 1;
                if(mycss_convert_data_to_integer(&str.data[1], len, &anb_entry->b) != len) {
                    /* parse error */
                    anb_entry->is_broken = true;
                }
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_plus_n_hyphen_asterisk_end");
                entry->parser = entry->parser_switch;
            }
            else if(mycore_strncasecmp(str.data, "n", 1) == 0) {
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_plus_n");
                entry->parser = mycss_an_plus_b_state_anb_plus_n;
            }
            else {
                mycore_string_destroy(&str, false);
                
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            
            mycore_string_destroy(&str, false);
            break;
        }
        default: {
            mycss_an_plus_b_parser_expectations_error(entry);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_an_plus_b_state_anb_plus_n_hyphen(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
        
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_current_entry(entry);
    
    if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        /* begin from 0-9 */
        if(mycore_string_chars_num_map[ (const unsigned char)(*token->data) ] != 0xff)
        {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            long res;
            mycss_convert_data_to_integer(str.data, str.length, &res);
            
            anb_entry->b = -res;
            
            MyCORE_DEBUG("mycss_an_plus_b_state_anb_plus_n_hyphen_zero_hyphen_nine_end");
            entry->parser = entry->parser_switch;
            
            mycore_string_destroy(&str, false);
        }
        else {
            mycss_an_plus_b_parser_expectations_error(entry);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        mycss_an_plus_b_parser_expectations_error(entry);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}

bool mycss_an_plus_b_state_anb_plus_n(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_current_entry(entry);
    
    switch (token->type) {
        case MyCSS_TOKEN_TYPE_DELIM: {
            if(*token->data == '+') {
                entry->parser = mycss_an_plus_b_state_anb_plus_n_plus;
            }
            else if(*token->data == '-') {
                entry->parser = mycss_an_plus_b_state_anb_plus_n_hyphen;
            }
            else {
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            break;
        }
        case MyCSS_TOKEN_TYPE_NUMBER: {
            if(*token->data == '+' || *token->data == '-')
            {
                mycore_string_t str;
                mycss_token_data_to_string(entry, token, &str, true, false);
                
                mycss_convert_data_to_integer(str.data, str.length, &anb_entry->b);
                
                MyCORE_DEBUG("mycss_an_plus_b_state_anb_plus_n_begin_plus_vertical_bar_hyphen");
                entry->parser = entry->parser_switch;
                
                mycore_string_destroy(&str, false);
            }
            else {
                mycss_an_plus_b_parser_expectations_error(entry);
                entry->parser = entry->parser_switch;
                return false;
            }
            break;
        }
        default: {
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    
    return true;
}

bool mycss_an_plus_b_state_anb_plus_n_plus(mycss_entry_t* entry, mycss_token_t* token, bool last_response)
{
    if(token->type == MyCSS_TOKEN_TYPE_WHITESPACE)
        return true;
    
    mycss_an_plus_b_entry_t *anb_entry = mycss_an_plus_b_current_entry(entry);
    
    if(token->type == MyCSS_TOKEN_TYPE_NUMBER) {
        /* begin from 0-9 */
        if(mycore_string_chars_num_map[ (const unsigned char)(*token->data) ] != 0xff)
        {
            mycore_string_t str;
            mycss_token_data_to_string(entry, token, &str, true, false);
            
            mycss_convert_data_to_integer(str.data, str.length, &anb_entry->b);
            
            MyCORE_DEBUG("mycss_an_plus_b_state_anb_plus_n_plus_zero_hyphen_nine_end");
            entry->parser = entry->parser_switch;
            
            mycore_string_destroy(&str, false);
        }
        else {
            mycss_an_plus_b_parser_expectations_error(entry);
            entry->parser = entry->parser_switch;
            return false;
        }
    }
    else {
        mycss_an_plus_b_parser_expectations_error(entry);
        entry->parser = entry->parser_switch;
        return false;
    }
    
    return true;
}



