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

#include "mycss/tokenizer_end.h"

size_t mycss_tokenizer_end_run_state_single(mycss_entry_t* entry, mycss_tokenizer_state_t state, const char* css, size_t css_offset, size_t css_size)
{
    mycss_t* mycss = entry->mycss;
    mycss_tokenizer_state_f* state_f = mycss->parse_state_func;
    
    return state_f[state + MyCSS_TOKENIZER_STATE_LAST_ENTRY](entry, entry->token, css, css_offset, css_size);
}

/////////////////////////////////////////////////////////
//// whitespace
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_whitespace(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    
    if(token->length) {
        token->type = MyCSS_TOKEN_TYPE_WHITESPACE;
        MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    }
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0022 QUOTATION MARK (")
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_quotation_mark(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_quotation_mark_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0023 NUMBER SIGN (#)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_number_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_number_sign_name_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type = MyCSS_TOKEN_TYPE_HASH;
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_number_sign_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // and '#' character
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0024 DOLLAR SIGN ($)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_dollar_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0027 APOSTROPHE (')
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_apostrophe(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_apostrophe_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0028 LEFT PARENTHESIS (()
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_left_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0029 RIGHT PARENTHESIS ())
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_right_parenthesis(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002A ASTERISK (*)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_asterisk(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002B PLUS SIGN (+)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_plus_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_plus_sign_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '+' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '.' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002C COMMA (,)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_comma(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_COMMA;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002D HYPHEN-MINUS (-)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_hyphen_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_hyphen_minus_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '-' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '.' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_hyphen_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '-' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_hyphen_minus_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '-' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 2;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_hyphen_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '-' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002E FULL STOP (.)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_full_stop(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+002F SOLIDUS (/)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_solidus_comment_end(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type = MyCSS_TOKEN_TYPE_COMMENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+003A COLON (:)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_colon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_COLON;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+003B SEMICOLON (;)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_semicolon(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_SEMICOLON;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+003C LESS-THAN SIGN (<)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_less_than_sign(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
        
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_less_than_sign_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '<' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    return css_size;
}

size_t mycss_tokenizer_end_state_less_than_sign_minus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '<' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 2;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0040 COMMERCIAL AT (@)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_commercial_at(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_commercial_at_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '@' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_commercial_at_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '@' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 2;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_commercial_at_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // '@' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_commercial_at_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type = MyCSS_TOKEN_TYPE_AT_KEYWORD;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+005B LEFT SQUARE BRACKET ([)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_left_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+005C REVERSE SOLIDUS (\)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_reverse_solidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+005D RIGHT SQUARE BRACKET (])
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_right_square_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+005E CIRCUMFLEX ACCENT (^)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_circumflex_accent(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+007B LEFT CURLY BRACKET ({)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_left_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+007D RIGHT CURLY BRACKET (})
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_right_curly_bracket(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Digit
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_NUMBER;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+0055 LATIN CAPITAL LETTER U (U) || U+0075 LATIN SMALL LETTER U (u)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_letter_u(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_state_letter_u_next(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    size_t begin = token->begin;
    
    // 'u' or 'U' character
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '+' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// name-start code point
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_name_start_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+007C VERTICAL LINE (|)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_vertical_line(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// U+007E TILDE (~)
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_tilde(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// anything else
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_state_delim_single_code_point(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = css_offset - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}


/////////////////////////////////////////////////////////
//// Global

/////////////////////////////////////////////////////////
//// Global back
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a numeric
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_numeric(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_NUMBER;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_numeric_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    // numbers
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    token->type   = MyCSS_TOKEN_TYPE_NUMBER;
    
    size_t begin  = token->begin + token->length;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_numeric_minus_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    // numbers
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 2;
    token->type   = MyCSS_TOKEN_TYPE_NUMBER;
    
    size_t begin  = token->begin + token->length;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '-' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_numeric_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    // numbers
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    token->type   = MyCSS_TOKEN_TYPE_NUMBER;
    
    size_t begin  = token->begin + token->length;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '\' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a number
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_number_digit(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_number_dot(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    size_t begin  = token->begin + token->length;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    // '.' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_number_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_number_e(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    size_t begin  = token->begin + token->length;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    // 'e' or 'E' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_number_e_plus_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 2;
    size_t begin  = token->begin + token->length;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    // 'e' or 'E' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // and '+' or '-' character
    token->length = 1;
    token->begin  = begin + 1;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_number_e_decimal(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a url token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_URL;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_url_string_back(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    
    if(token->type == MyCSS_TOKEN_TYPE_BAD_STRING)
        token->type = MyCSS_TOKEN_TYPE_BAD_URL;
    else
        token->type = MyCSS_TOKEN_TYPE_URL;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_url_after(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_URL;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_url_after_whitespace(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_URL;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_url_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    token->type   = MyCSS_TOKEN_TYPE_BAD_URL;
    
    size_t begin  = token->begin + token->length;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // '\' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_bad_url(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_URL;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a string token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_string_double_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_string_double_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_string_single_quoted(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_string_single_quoted_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_BAD_STRING;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume an ident-like token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_ident(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->type = MyCSS_TOKEN_TYPE_IDENT;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a name
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_name(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    return css_size;
}

size_t mycss_tokenizer_end_global_state_name_rsolidus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    size_t begin  = token->begin + token->length;
    
    mycss_tokenizer_end_run_state_single(entry, entry->state_back, css, css_offset, css_size);
    
    // '\' character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

/////////////////////////////////////////////////////////
//// Consume a unicode-range token
////
/////////////////////////////////////////////////////////
size_t mycss_tokenizer_end_global_state_unicode_range_before(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_unicode_range(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_unicode_range_question(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    token->type   = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_size;
}

size_t mycss_tokenizer_end_global_state_unicode_range_minus(mycss_entry_t* entry, mycss_token_t* token, const char* css, size_t css_offset, size_t css_size)
{
    if(entry->help_counter == 0) {
        token->length = ((entry->current_buffer->offset + css_offset) - token->begin) - 1;
    }
    else {
        token->length = (entry->current_buffer->offset + css_offset) - token->begin;
    }
    
    token->type  = MyCSS_TOKEN_TYPE_UNICODE_RANGE;
    size_t begin = token->begin + token->length;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    
    // character
    token->length = 1;
    token->begin  = begin;
    token->type   = MyCSS_TOKEN_TYPE_DELIM;
    
    MyCSS_TOKEN_READY_CALLBACK_FUNCTION(entry, token);
    return css_offset;
}



