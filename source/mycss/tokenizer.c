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

#include "mycss/tokenizer.h"
#include "mycss/tokenizer_resource.h"
#include "mycore/utils/resources.h"

mystatus_t mycss_tokenizer_chunk(mycss_entry_t* entry, const char* css, size_t css_length)
{
    entry->current_buffer = mycore_incoming_buffer_add(entry->current_buffer, entry->mcobject_incoming_buffer,
                                                       css, css_length);
    
    if(entry->current_buffer == NULL)
        return MyCSS_STATUS_ERROR_TOKENIZER_INCOMING_BUFFER_ADD;
    
    // first init
    if(entry->first_buffer == NULL)
        entry->first_buffer = entry->current_buffer;
    
    if(entry->token == NULL) {
        entry->token = (mycss_token_t*)mycore_calloc(1, sizeof(mycss_token_t));
        
        if(entry->token == NULL)
            return MyCSS_STATUS_ERROR_TOKENIZER_TOKEN_ALLOCATION;
    }
    
    return mycss_tokenizer_process(entry, css, css_length);
}

mystatus_t mycss_tokenizer_process(mycss_entry_t* entry, const char* css, size_t css_length)
{
    /*
     Why use utf-8 when the declaration says utf-16?
     The bytes of the encoding declaration spell out “@charset "…";” in ASCII, 
     but UTF-16 is not ASCII-compatible. Either you’ve typed in complete gibberish (like 䁣桡牳整•utf-16be∻) 
     to get the right bytes in the document, which we don’t want to encourage, 
     or your document is actually in an ASCII-compatible encoding and your encoding declaration is lying.
     
     Either way, defaulting to UTF-8 is a decent answer.
     
     As well, this mimics the behavior of HTML’s <meta charset> attribute.
     */
    if(entry->encoding == MyENCODING_UTF_16LE || entry->encoding == MyENCODING_UTF_16BE)
        entry->encoding = MyENCODING_UTF_8;
    
    mycss_t* mycss = entry->mycss;
    mycss_tokenizer_state_f* state_f = mycss->parse_state_func;
    
    mycore_incoming_buffer_t *current = entry->current_buffer;
    
    do {
        mycore_incoming_buffer_t *mt = entry->current_buffer;
        mt->length = 0;
        
        while (mt->length < mt->size) {
            mt->length = state_f[entry->state](entry, entry->token, mt->data, mt->length, mt->size);
        }
        
        entry->current_buffer = mt->next;
    }
    while(entry->current_buffer);
    
    entry->current_buffer = current;
    
    return MyCSS_STATUS_OK;
}

mystatus_t mycss_tokenizer_end(mycss_entry_t* entry)
{
    mycss_t* mycss = entry->mycss;
    mycss_tokenizer_state_f* state_f = mycss->parse_state_func;
    
    if(entry->state != MyCSS_TOKENIZER_STATE_DATA)
    {
        mycore_incoming_buffer_t *mt = entry->current_buffer;
        size_t end_state = (MyCSS_TOKENIZER_STATE_LAST_ENTRY + entry->state);
        
        mt->length = state_f[end_state](entry, entry->token, mt->data, mt->length, mt->size);
    }
    
    entry->type |= MyCSS_ENTRY_TYPE_END;
    
    return MyCSS_STATUS_OK;
}

size_t mycss_tokenizer_run_state_single(mycss_entry_t* entry, mycss_tokenizer_state_t state, const char* css, size_t css_offset, size_t css_size)
{
    mycss_t* mycss = entry->mycss;
    mycss_tokenizer_state_f* state_f = mycss->parse_state_func;
    
    return state_f[state](entry, entry->token, css, css_offset, css_size);
}

size_t mycss_tokenizer_state_set_current_buffer_for_continue(mycss_entry_t* entry, size_t css_offset, size_t css_minus_offset)
{
    if(css_minus_offset == 0)
        return css_offset;
    
    if(css_offset >= css_minus_offset)
        return css_offset;
    
    mycore_incoming_buffer_t *buffer = entry->current_buffer;
    
    size_t need = (css_minus_offset - css_offset);
    size_t position = buffer->offset - need;
    
    while(buffer && buffer->offset > position)
        buffer = buffer->prev;
    
    if(buffer == NULL)
        return 0;
    
    entry->current_buffer = buffer;
    
    return (position - buffer->offset);
}

size_t mycss_tokenizer_token_strcasecmp(mycss_entry_t* entry, mycss_token_t* token, const char* to, size_t to_length)
{
    mycore_incoming_buffer_t *buffer = mycore_incoming_buffer_find_by_position(entry->current_buffer, token->begin);
    
    size_t token_offset = token->begin - buffer->offset;
    
    return mycore_incoming_buffer_escaped_case_cmp(&buffer, to, to_length, &token_offset);
}

//////////////////////
// Begin All State
//
size_t mycss_tokenizer_state_data(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->begin = entry->current_buffer->offset + css_offset;
    token->data  = &css[css_offset];
    
    entry->state = mycss_begin_chars_state_map[ (const unsigned char)css[css_offset] ];
    
    css_offset++;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// whitespace
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_whitespace(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while(css_offset < css_size)
    {
        if(mycss_begin_chars_state_map[ u_css[css_offset] ] != MyCSS_TOKENIZER_STATE_WHITESPACE)
        {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_WHITESPACE;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0022 QUOTATION MARK (")
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_quotation_mark(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    // skip QUOTATION MARK (")
    token->begin += 1;
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED;
    entry->state_back = MyCSS_TOKENIZER_STATE_QUOTATION_MARK_BACK;
    
    return css_offset;
}

size_t mycss_tokenizer_state_quotation_mark_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0023 NUMBER SIGN (#)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_number_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    if(mycss_chars_name_code_point_map[ u_css[css_offset] ] != 0xff)
    {
        token->begin++;
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_BACK;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        if(css_offset >= css_size) {
            entry->state = MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_RSOLIDUS;
            return css_offset;
        }
        
        if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
            css_offset--;
            
            token->length = 1;
            token->type   = MyCSS_TOKEN_TYPE_DELIM;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
        }
        else {
            token->begin++;
            css_offset++;
            
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
            entry->state_back = MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_BACK;
        }
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_number_sign_name_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type = MyCSS_TOKEN_TYPE_HASH;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

size_t mycss_tokenizer_state_number_sign_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        return mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
    entry->state_back = MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_BACK;
    
    token->begin++;
    css_offset++;
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0024 DOLLAR SIGN ($)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_dollar_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '=') {
        css_offset++;
        
        token->length = 2;
        token->type = MyCSS_TOKEN_TYPE_SUFFIX_MATCH;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
    }
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0027 APOSTROPHE (')
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_apostrophe(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    // skip APOSTROPHE (')
    token->begin += 1;
    
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED;
    entry->state_back = MyCSS_TOKENIZER_STATE_QUOTATION_MARK_BACK;
    
    return css_offset;
}

size_t mycss_tokenizer_state_apostrophe_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0028 LEFT PARENTHESIS (()
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_left_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0029 RIGHT PARENTHESIS ())
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_right_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002A ASTERISK (*)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_asterisk(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '=') {
        css_offset++;
        
        token->length = 2;
        token->type = MyCSS_TOKEN_TYPE_SUBSTRING_MATCH;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
    }
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002B PLUS SIGN (+)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_plus_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DIGIT;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    }
    else if(css[css_offset] == '.') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_PLUS_SIGN_FULL_STOP;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_plus_sign_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        return mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002C COMMA (,)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_comma(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_COMMA;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002D HYPHEN-MINUS (-)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_hyphen_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    // If the input stream starts with a number, reconsume the current input code point,
    // consume a numeric token, and return it.
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DIGIT;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    }
    else if(css[css_offset] == '.') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_FULL_STOP;
    }
    
    // Otherwise, if the input stream starts with an identifier,
    // reconsume the current input code point, consume an ident-like token, and return it.
    // and check
    // Otherwise, if the next 2 input code points are U+002D HYPHEN-MINUS
    // U+003E GREATER-THAN SIGN (->), consume them and return a <CDC-token>.
    else if(css[css_offset] == '-') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS;
    }
    
    // Otherwise, if the input stream starts with an identifier,
    // reconsume the current input code point, consume an ident-like token, and return it.
    else if(mycss_begin_chars_state_map[ u_css[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_RSOLIDUS;
    }
    
    // Otherwise, return a <delim-token> with its value set to the current input code point.
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_hyphen_minus_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        return mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_hyphen_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '>') {
        css_offset++;
        
        token->length = 3;
        token->type   = MyCSS_TOKEN_TYPE_CDC;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    else if(mycss_begin_chars_state_map[ ((const unsigned char *)css)[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS_RSOLIDUS;
    }
    else {
        token->length = 1; // only '-'
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_hyphen_minus_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 2);
    }
    else {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_hyphen_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = 1; // only '-'
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    else {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002E FULL STOP (.)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] >= '0' && css[css_offset] <= '9') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+002F SOLIDUS (/)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '*') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_SOLIDUS_COMMENT_END;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    
    return css_offset;
}

size_t mycss_tokenizer_state_solidus_comment_end(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    while(css_offset < css_size)
    {
        if(css[css_offset] == '/') {
            if(css_offset == 0)
            {
                mycore_incoming_buffer_t *buffer = entry->current_buffer->prev;
                
                while(buffer && buffer->size == 0)
                    buffer = buffer->prev;
                
                if(buffer == NULL) {
                    // panic!, this in not normal, something is very wrong
                    entry->state = MyCSS_TOKENIZER_STATE_SOLIDUS;
                    break;
                }
                
                if(buffer->data[ (buffer->size - 1) ] == '*') {
                    css_offset++;
                    
                    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                    token->type = MyCSS_TOKEN_TYPE_COMMENT;
                    
                    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
                    
                    entry->state = MyCSS_TOKENIZER_STATE_DATA;
                    break;
                }
            }
            else if(css[ (css_offset - 1) ] == '*') {
                css_offset++;
                
                token->length = (entry->current_buffer->offset + css_offset) - token->begin;
                token->type = MyCSS_TOKEN_TYPE_COMMENT;
                
                MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
                
                entry->state = MyCSS_TOKENIZER_STATE_DATA;
                break;
            }
        }
        
        ++css_offset;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+003A COLON (:)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_colon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_COLON;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+003B SEMICOLON (;)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_semicolon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_SEMICOLON;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+003C LESS-THAN SIGN (<)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_less_than_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '!') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_less_than_sign_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '-') {
        css_offset++;
        entry->state = MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS_MINUS;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_less_than_sign_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '-') {
        css_offset++;
        
        token->length = 3;
        token->type   = MyCSS_TOKEN_TYPE_CDO;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 2);
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0040 COMMERCIAL AT (@)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_commercial_at(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '-') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_RSOLIDUS;
    }
    else if(mycss_begin_chars_state_map[ ((const unsigned char *)css)[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_commercial_at_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(mycss_begin_chars_state_map[ ((const unsigned char *)css)[css_offset] ] == MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT) {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK;
    }
    else if(css[css_offset] == '\\') {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS_RSOLIDUS;
    }
    else {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_commercial_at_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 2;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 2);
    }
    else {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_commercial_at_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
        css_offset = mycss_tokenizer_state_set_current_buffer_for_continue(entry, css_offset, 1);
    }
    else {
        css_offset++;
        
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_commercial_at_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type    = MyCSS_TOKEN_TYPE_AT_KEYWORD;
    token->begin  += 1;
    token->length -= 1;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+005B LEFT SQUARE BRACKET ([)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_left_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+005C REVERSE SOLIDUS (\)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_reverse_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '\n' || css[css_offset] == '\r' || css[css_offset] == 0x0C) {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
        
        entry->state = MyCSS_TOKENIZER_STATE_DATA;
    }
    else {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+005D RIGHT SQUARE BRACKET (])
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_right_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+005E CIRCUMFLEX ACCENT (^)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_circumflex_accent(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '=') {
        css_offset++;
        
        token->length = 2;
        token->type = MyCSS_TOKEN_TYPE_PREFIX_MATCH;
    }
    else {
        token->length = 1;
        token->type = MyCSS_TOKEN_TYPE_DELIM;
    }
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+007B LEFT CURLY BRACKET ({)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_left_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+007D RIGHT CURLY BRACKET (})
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_right_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// Digit
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DIGIT;
    entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC;
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+0055 LATIN CAPITAL LETTER U (U) || U+0075 LATIN SMALL LETTER U (u)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_letter_u(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '+') {
        ++css_offset;
        
        if(css_offset >= css_size) {
            entry->state = MyCSS_TOKENIZER_STATE_LETTER_U_NEXT;
            return css_offset;
        }
        
        if(mycore_string_chars_hex_map[ (const unsigned char)(css[css_offset]) ] != 0xff ||
           css[css_offset] == '?')
        {
            token->begin += 2;
            
            ++css_offset;
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_BEFORE;
        }
        else {
            entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
            entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
        }
    }
    else {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    
    return css_offset;
}

size_t mycss_tokenizer_state_letter_u_next(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(mycore_string_chars_hex_map[ (const unsigned char)(css[css_offset]) ] != 0xff ||
       css[css_offset] == '?')
    {
        token->begin += 2;
        
        ++css_offset;
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_BEFORE;
    }
    else {
        entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
        entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// name-start code point
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_name_start_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    entry->state = MyCSS_TOKENIZER_GLOBAL_STATE_NAME;
    entry->state_back = MyCSS_TOKENIZER_GLOBAL_STATE_IDENT;
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+007C VERTICAL LINE (|)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_vertical_line(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '=') {
        css_offset++;
        
        token->length = 2;
        token->type   = MyCSS_TOKEN_TYPE_DASH_MATCH;
    }
    else if(css[css_offset] == '|') {
        css_offset++;
        
        token->length = 2;
        token->type   = MyCSS_TOKEN_TYPE_COLUMN;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
    }
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// U+007E TILDE (~)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_tilde(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(css[css_offset] == '=') {
        css_offset++;
        
        token->length = 2;
        token->type   = MyCSS_TOKEN_TYPE_INCLUDE_MATCH;
    }
    else {
        token->length = 1;
        token->type   = MyCSS_TOKEN_TYPE_DELIM;
    }
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    entry->state = MyCSS_TOKENIZER_STATE_DATA;
    return css_offset;
}

/////////////////////////////////////////////////////////
//// anything else
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_state_delim_single_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    const unsigned char *u_css = (const unsigned char*)css;
    
    while (css_offset < css_size)
    {
        if(u_css[css_offset] < 128)
        {
            token->length = (entry->current_buffer->offset + css_offset) - token->begin;
            token->type   = MyCSS_TOKEN_TYPE_DELIM;
            
            MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
            
            entry->state = MyCSS_TOKENIZER_STATE_DATA;
            break;
        }
        
        css_offset++;
    }
    
    return css_offset;
}

/////////////////////////////////////////////////////////
//// init tokenizer
////
/////////////////////////////////////////////////////////
mystatus_t mycss_tokenizer_state_init(mycss_t* mycss)
{
    mycss->parse_state_func = (mycss_tokenizer_state_f*)mycore_calloc((MyCSS_TOKENIZER_STATE_LAST_ENTRY * 2), sizeof(mycss_tokenizer_state_f));
    
    if(mycss->parse_state_func == NULL)
        return MyCSS_STATUS_ERROR_TOKENIZER_STATE_ALLOCATION;
    
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_DATA] = mycss_tokenizer_state_data;
    
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_WHITESPACE] = mycss_tokenizer_state_whitespace;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_QUOTATION_MARK] = mycss_tokenizer_state_quotation_mark;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_QUOTATION_MARK_BACK] = mycss_tokenizer_state_quotation_mark_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_NUMBER_SIGN] = mycss_tokenizer_state_number_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_BACK] = mycss_tokenizer_state_number_sign_name_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_RSOLIDUS] = mycss_tokenizer_state_number_sign_name_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_DOLLAR_SIGN] = mycss_tokenizer_state_dollar_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_APOSTROPHE] = mycss_tokenizer_state_apostrophe;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_APOSTROPHE_BACK] = mycss_tokenizer_state_apostrophe_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LEFT_PARENTHESIS] = mycss_tokenizer_state_left_parenthesis;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_RIGHT_PARENTHESIS] = mycss_tokenizer_state_right_parenthesis;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_ASTERISK] = mycss_tokenizer_state_asterisk;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_PLUS_SIGN] = mycss_tokenizer_state_plus_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_PLUS_SIGN_FULL_STOP] = mycss_tokenizer_state_plus_sign_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMA] = mycss_tokenizer_state_comma;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_HYPHEN_MINUS] = mycss_tokenizer_state_hyphen_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_FULL_STOP] = mycss_tokenizer_state_hyphen_minus_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS] = mycss_tokenizer_state_hyphen_minus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS_RSOLIDUS] = mycss_tokenizer_state_hyphen_minus_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_RSOLIDUS] = mycss_tokenizer_state_hyphen_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_FULL_STOP] = mycss_tokenizer_state_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_SOLIDUS] = mycss_tokenizer_state_solidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_SOLIDUS_COMMENT_END] = mycss_tokenizer_state_solidus_comment_end;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COLON] = mycss_tokenizer_state_colon;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_SEMICOLON] = mycss_tokenizer_state_semicolon;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN] = mycss_tokenizer_state_less_than_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS] = mycss_tokenizer_state_less_than_sign_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS_MINUS] = mycss_tokenizer_state_less_than_sign_minus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMERCIAL_AT] = mycss_tokenizer_state_commercial_at;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS] = mycss_tokenizer_state_commercial_at_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS_RSOLIDUS] = mycss_tokenizer_state_commercial_at_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_RSOLIDUS] = mycss_tokenizer_state_commercial_at_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK] = mycss_tokenizer_state_commercial_at_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LEFT_SQUARE_BRACKET] = mycss_tokenizer_state_left_square_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_REVERSE_SOLIDUS] = mycss_tokenizer_state_reverse_solidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_RIGHT_SQUARE_BRACKET] = mycss_tokenizer_state_right_square_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_CIRCUMFLEX_ACCENT] = mycss_tokenizer_state_circumflex_accent;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LEFT_CURLY_BRACKET] = mycss_tokenizer_state_left_curly_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_RIGHT_CURLY_BRACKET] = mycss_tokenizer_state_right_curly_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_DIGIT] = mycss_tokenizer_state_digit;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LETTER_U] = mycss_tokenizer_state_letter_u;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LETTER_U_NEXT] = mycss_tokenizer_state_letter_u_next;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT] = mycss_tokenizer_state_name_start_code_point;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_VERTICAL_LINE] = mycss_tokenizer_state_vertical_line;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_TILDE] = mycss_tokenizer_state_tilde;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_DELIM_SINGLE_CODE_POINT] = mycss_tokenizer_state_delim_single_code_point;
    
    // global
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_BACK] = mycss_tokenizer_global_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC] = mycss_tokenizer_global_state_numeric;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS] = mycss_tokenizer_global_state_numeric_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS_RSOLIDUS] = mycss_tokenizer_global_state_numeric_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_RSOLIDUS] = mycss_tokenizer_global_state_numeric_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DIGIT] = mycss_tokenizer_global_state_number_digit;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DOT] = mycss_tokenizer_global_state_number_dot;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL] = mycss_tokenizer_global_state_number_decimal;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E] = mycss_tokenizer_global_state_number_e;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_PLUS_MINUS] = mycss_tokenizer_global_state_number_e_plus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_DECIMAL] = mycss_tokenizer_global_state_number_e_decimal;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_IDENT] = mycss_tokenizer_global_state_ident;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_URL] = mycss_tokenizer_global_state_url;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_URL_STRING_BACK] = mycss_tokenizer_global_state_url_string_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER] = mycss_tokenizer_global_state_url_after;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER_WHITESPACE] = mycss_tokenizer_global_state_url_after_whitespace;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_URL_RSOLIDUS] = mycss_tokenizer_global_state_url_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL] = mycss_tokenizer_global_state_bad_url;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NAME] = mycss_tokenizer_global_state_name;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_NAME_RSOLIDUS] = mycss_tokenizer_global_state_name_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED] = mycss_tokenizer_global_state_string_double_quoted;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS] = mycss_tokenizer_global_state_string_double_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS_R] = mycss_tokenizer_global_state_string_double_quoted_rsolidus_r;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED] = mycss_tokenizer_global_state_string_single_quoted;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS] = mycss_tokenizer_global_state_string_single_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS_R] = mycss_tokenizer_global_state_string_single_quoted_rsolidus_r;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_BEFORE] = mycss_tokenizer_global_state_unicode_range_before;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE] = mycss_tokenizer_global_state_unicode_range;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_QUESTION] = mycss_tokenizer_global_state_unicode_range_question;
    mycss->parse_state_func[MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_MINUS] = mycss_tokenizer_global_state_unicode_range_minus;
    
    // end
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_WHITESPACE] = mycss_tokenizer_end_state_whitespace;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_QUOTATION_MARK] = mycss_tokenizer_end_state_quotation_mark;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_QUOTATION_MARK_BACK] = mycss_tokenizer_end_state_quotation_mark_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_NUMBER_SIGN] = mycss_tokenizer_end_state_number_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_BACK] = mycss_tokenizer_end_state_number_sign_name_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_NUMBER_SIGN_NAME_RSOLIDUS] = mycss_tokenizer_end_state_number_sign_name_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_DOLLAR_SIGN] = mycss_tokenizer_end_state_dollar_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_APOSTROPHE] = mycss_tokenizer_end_state_apostrophe;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_APOSTROPHE_BACK] = mycss_tokenizer_end_state_apostrophe_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LEFT_PARENTHESIS] = mycss_tokenizer_end_state_left_parenthesis;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_RIGHT_PARENTHESIS] = mycss_tokenizer_end_state_right_parenthesis;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_ASTERISK] = mycss_tokenizer_end_state_asterisk;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_PLUS_SIGN] = mycss_tokenizer_end_state_plus_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_PLUS_SIGN_FULL_STOP] = mycss_tokenizer_end_state_plus_sign_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMA] = mycss_tokenizer_end_state_comma;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_HYPHEN_MINUS] = mycss_tokenizer_end_state_hyphen_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_FULL_STOP] = mycss_tokenizer_end_state_hyphen_minus_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS] = mycss_tokenizer_end_state_hyphen_minus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_MINUS_RSOLIDUS] = mycss_tokenizer_end_state_hyphen_minus_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_HYPHEN_MINUS_RSOLIDUS] = mycss_tokenizer_end_state_hyphen_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_FULL_STOP] = mycss_tokenizer_end_state_full_stop;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_SOLIDUS] = mycss_tokenizer_end_state_solidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_SOLIDUS_COMMENT_END] = mycss_tokenizer_end_state_solidus_comment_end;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COLON] = mycss_tokenizer_end_state_colon;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_SEMICOLON] = mycss_tokenizer_end_state_semicolon;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN] = mycss_tokenizer_end_state_less_than_sign;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS] = mycss_tokenizer_end_state_less_than_sign_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LESS_THAN_SIGN_MINUS_MINUS] = mycss_tokenizer_end_state_less_than_sign_minus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMERCIAL_AT] = mycss_tokenizer_end_state_commercial_at;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS] = mycss_tokenizer_end_state_commercial_at_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_MINUS_RSOLIDUS] = mycss_tokenizer_end_state_commercial_at_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_RSOLIDUS] = mycss_tokenizer_end_state_commercial_at_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_COMMERCIAL_AT_BACK] = mycss_tokenizer_end_state_commercial_at_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LEFT_SQUARE_BRACKET] = mycss_tokenizer_end_state_left_square_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_REVERSE_SOLIDUS] = mycss_tokenizer_end_state_reverse_solidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_RIGHT_SQUARE_BRACKET] = mycss_tokenizer_end_state_right_square_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_CIRCUMFLEX_ACCENT] = mycss_tokenizer_end_state_circumflex_accent;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LEFT_CURLY_BRACKET] = mycss_tokenizer_end_state_left_curly_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_RIGHT_CURLY_BRACKET] = mycss_tokenizer_end_state_right_curly_bracket;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_DIGIT] = mycss_tokenizer_end_state_digit;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LETTER_U] = mycss_tokenizer_end_state_letter_u;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_LETTER_U_NEXT] = mycss_tokenizer_end_state_letter_u_next;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_NAME_START_CODE_POINT] = mycss_tokenizer_end_state_name_start_code_point;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_VERTICAL_LINE] = mycss_tokenizer_end_state_vertical_line;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_TILDE] = mycss_tokenizer_end_state_tilde;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_STATE_DELIM_SINGLE_CODE_POINT] = mycss_tokenizer_end_state_delim_single_code_point;
    
    // global end
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_BACK] = mycss_tokenizer_end_global_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC] = mycss_tokenizer_end_global_state_numeric;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS] = mycss_tokenizer_end_global_state_numeric_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_MINUS_RSOLIDUS] = mycss_tokenizer_end_global_state_numeric_minus_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMERIC_RSOLIDUS] = mycss_tokenizer_end_global_state_numeric_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DIGIT] = mycss_tokenizer_end_global_state_number_digit;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DOT] = mycss_tokenizer_end_global_state_number_dot;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_DECIMAL] = mycss_tokenizer_end_global_state_number_decimal;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E] = mycss_tokenizer_end_global_state_number_e;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_PLUS_MINUS] = mycss_tokenizer_end_global_state_number_e_plus_minus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NUMBER_E_DECIMAL] = mycss_tokenizer_end_global_state_number_e_decimal;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_IDENT] = mycss_tokenizer_end_global_state_ident;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_URL] = mycss_tokenizer_end_global_state_url;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_URL_STRING_BACK] = mycss_tokenizer_end_global_state_url_string_back;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER] = mycss_tokenizer_end_global_state_url_after;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_URL_AFTER_WHITESPACE] = mycss_tokenizer_end_global_state_url_after_whitespace;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_URL_RSOLIDUS] = mycss_tokenizer_end_global_state_url_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_BAD_URL] = mycss_tokenizer_end_global_state_bad_url;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NAME] = mycss_tokenizer_end_global_state_name;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_NAME_RSOLIDUS] = mycss_tokenizer_end_global_state_name_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED] = mycss_tokenizer_end_global_state_string_double_quoted;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS] = mycss_tokenizer_end_global_state_string_double_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_DOUBLE_QUOTED_RSOLIDUS_R] = mycss_tokenizer_end_global_state_string_double_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED] = mycss_tokenizer_end_global_state_string_single_quoted;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS] = mycss_tokenizer_end_global_state_string_single_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_STRING_SINGLE_QUOTED_RSOLIDUS_R] = mycss_tokenizer_end_global_state_string_single_quoted_rsolidus;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_BEFORE] = mycss_tokenizer_end_global_state_unicode_range_before;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE] = mycss_tokenizer_end_global_state_unicode_range;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_QUESTION] = mycss_tokenizer_end_global_state_unicode_range_question;
    mycss->parse_state_func[MyCSS_TOKENIZER_STATE_LAST_ENTRY + MyCSS_TOKENIZER_GLOBAL_STATE_UNICODE_RANGE_MINUS] = mycss_tokenizer_end_global_state_unicode_range_minus;

    
    return MyCSS_STATUS_OK;
}

void mycss_tokenizer_state_destroy(mycss_t* mycss)
{
    if(mycss->parse_state_func) {
        mycore_free(mycss->parse_state_func);
        mycss->parse_state_func = NULL;
    }
}


