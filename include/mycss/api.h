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

#ifndef MyCSS_MyCSS_API_H
#define MyCSS_MyCSS_API_H
#pragma once

/**
 * @file mycss/api.h
 *
 * Fast C/C++ CSS Parser (Cascading Style Sheets). Using threads.
 * 
 * C99 and POSIX Threads!
 * This is part of big project.
 * All projects (and this too) is based on myhtml (https://github.com/lexborisov/myhtml)
 *
 * By https://www.w3.org/TR/css-syntax-3/ specification.
 *
 */

#define MyCSS_VERSION_MAJOR 0
#define MyCSS_VERSION_MINOR 1
#define MyCSS_VERSION_PATCH 0

#include <mycore/myosi.h>
#include <mycore/incoming.h>
#include <mycore/mystring.h>
#include <mycore/utils/mchar_async.h>
#include <myencoding/myosi.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct mycss statuses
 */
// base
// base
/*
 Very important!!!
*/
enum mycss_status {
    MyCSS_STATUS_OK                                     = 0x000000,
    MyCSS_STATUS_ERROR_MEMORY_ALLOCATION                = 0x010001,
    MyCSS_STATUS_ERROR_TOKENIZER_STATE_ALLOCATION       = 0x010020,
    MyCSS_STATUS_ERROR_TOKENIZER_INCOMING_BUFFER_ADD    = 0x010021,
    MyCSS_STATUS_ERROR_TOKENIZER_TOKEN_ALLOCATION       = 0x010022,
    MyCSS_STATUS_ERROR_INCOMING_BUFFER_INIT             = 0x010030,
    MyCSS_STATUS_ERROR_ENTRY_INCOMING_BUFFER_CREATE     = 0x010039,
    MyCSS_STATUS_ERROR_ENTRY_INCOMING_BUFFER_INIT       = 0x010040,
    MyCSS_STATUS_ERROR_ENTRY_TOKEN_INCOMING_BUFFER_INIT = 0x010041,
    MyCSS_STATUS_ERROR_ENTRY_TOKEN_NODE_ADD             = 0x010042,
    MyCSS_STATUS_ERROR_SELECTORS_CREATE                 = 0x010100,
    MyCSS_STATUS_ERROR_SELECTORS_ENTRIES_CREATE         = 0x010101,
    MyCSS_STATUS_ERROR_SELECTORS_ENTRIES_INIT           = 0x010102,
    MyCSS_STATUS_ERROR_SELECTORS_ENTRIES_NODE_ADD       = 0x010103,
    MyCSS_STATUS_ERROR_SELECTORS_LIST_CREATE            = 0x010104,
    MyCSS_STATUS_ERROR_SELECTORS_LIST_INIT              = 0x010105,
    MyCSS_STATUS_ERROR_SELECTORS_LIST_ADD_NODE          = 0x010106,
    MyCSS_STATUS_ERROR_NAMESPACE_CREATE                 = 0x010200,
    MyCSS_STATUS_ERROR_NAMESPACE_INIT                   = 0x010201,
    MyCSS_STATUS_ERROR_NAMESPACE_ENTRIES_CREATE         = 0x010202,
    MyCSS_STATUS_ERROR_NAMESPACE_ENTRIES_INIT           = 0x010203,
    MyCSS_STATUS_ERROR_NAMESPACE_NODE_ADD               = 0x010204,
    MyCSS_STATUS_ERROR_MEDIA_CREATE                     = 0x010404,
    MyCSS_STATUS_ERROR_STRING_CREATE                    = 0x010501,
    MyCSS_STATUS_ERROR_STRING_INIT                      = 0x010502,
    MyCSS_STATUS_ERROR_STRING_NODE_INIT                 = 0x010503,
    MyCSS_STATUS_ERROR_AN_PLUS_B_CREATE                 = 0x010600,
    MyCSS_STATUS_ERROR_AN_PLUS_B_INIT                   = 0x010601,
    MyCSS_STATUS_ERROR_DECLARATION_CREATE               = 0x010700,
    MyCSS_STATUS_ERROR_DECLARATION_INIT                 = 0x010701,
    MyCSS_STATUS_ERROR_DECLARATION_ENTRY_CREATE         = 0x010702,
    MyCSS_STATUS_ERROR_DECLARATION_ENTRY_INIT           = 0x010703,
    MyCSS_STATUS_ERROR_PARSER_LIST_CREATE               = 0x010800
}
typedef mycss_status_t;

#define MyCSS_FAILED(_status_) ((_status_) != MyCSS_STATUS_OK)

/**
 * Tokenizer Token types
 */
enum mycss_token_type {
    MyCSS_TOKEN_TYPE_UNDEF                = 0x0000,
    MyCSS_TOKEN_TYPE_WHITESPACE           = 0x0001,
    MyCSS_TOKEN_TYPE_IDENT                = 0x0002,
    MyCSS_TOKEN_TYPE_FUNCTION             = 0x0003,
    MyCSS_TOKEN_TYPE_AT_KEYWORD           = 0x0004,
    MyCSS_TOKEN_TYPE_HASH                 = 0x0005,
    MyCSS_TOKEN_TYPE_STRING               = 0x0006,
    MyCSS_TOKEN_TYPE_URL                  = 0x0007,
    MyCSS_TOKEN_TYPE_NUMBER               = 0x0008,
    MyCSS_TOKEN_TYPE_DIMENSION            = 0x0009,
    MyCSS_TOKEN_TYPE_PERCENTAGE           = 0x000a,
    MyCSS_TOKEN_TYPE_INCLUDE_MATCH        = 0x000b,
    MyCSS_TOKEN_TYPE_DASH_MATCH           = 0x000c,
    MyCSS_TOKEN_TYPE_PREFIX_MATCH         = 0x000d,
    MyCSS_TOKEN_TYPE_SUFFIX_MATCH         = 0x000e,
    MyCSS_TOKEN_TYPE_SUBSTRING_MATCH      = 0x000f,
    MyCSS_TOKEN_TYPE_COLUMN               = 0x0010,
    MyCSS_TOKEN_TYPE_CDO                  = 0x0011,
    MyCSS_TOKEN_TYPE_CDC                  = 0x0012,
    MyCSS_TOKEN_TYPE_BAD_STRING           = 0x0013,
    MyCSS_TOKEN_TYPE_DELIM                = 0x0014,
    MyCSS_TOKEN_TYPE_LEFT_PARENTHESIS     = 0x0015,
    MyCSS_TOKEN_TYPE_RIGHT_PARENTHESIS    = 0x0016,
    MyCSS_TOKEN_TYPE_COMMA                = 0x0017,
    MyCSS_TOKEN_TYPE_COLON                = 0x0018,
    MyCSS_TOKEN_TYPE_SEMICOLON            = 0x0019,
    MyCSS_TOKEN_TYPE_LEFT_SQUARE_BRACKET  = 0x001a,
    MyCSS_TOKEN_TYPE_RIGHT_SQUARE_BRACKET = 0x001b,
    MyCSS_TOKEN_TYPE_LEFT_CURLY_BRACKET   = 0x001c,
    MyCSS_TOKEN_TYPE_RIGHT_CURLY_BRACKET  = 0x001d,
    MyCSS_TOKEN_TYPE_BAD_URL              = 0x001e,
    MyCSS_TOKEN_TYPE_COMMENT              = 0x001f,
    MyCSS_TOKEN_TYPE_UNICODE_RANGE        = 0x0020,
    MyCSS_TOKEN_TYPE_EOF                  = 0x0021,
    MyCSS_TOKEN_TYPE_LAST_ENTRY           = 0x0022
}
typedef mycss_token_type_t;

/**
 * @struct mycss_t MyCSS
 *
 * Basic structure. Create once for using many times.
*/
typedef struct mycss mycss_t;

/**
 * @struct mycss_entry_t MyCSS_ENTRY
 *
 * Secondary structure. Create once for using many times.
 */
typedef struct mycss_entry mycss_entry_t;

/**
 * @struct mycss_token_t MyCSS_TOKEN
 *
 * Tokenizer data structure.
 */
typedef struct mycss_token mycss_token_t;

/**
 * @struct mycss_token_done_callback_f
 *
 * Callback for token is ready
 */
typedef mycss_token_t*
(*mycss_token_ready_callback_f)(mycss_entry_t* entry, mycss_token_t* token);

/***********************************************************************************
 *
 * MyCSS
 *
 ***********************************************************************************/

/**
 * Create a MyCSS structure
 *
 * @return mycss_t* if successful, otherwise an NULL value.
 */
mycss_t*
mycss_create(void);

/**
 * Allocating and Initialization resources for a MyCSS structure
 *
 * @param[in] mycss_t*
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status value.
 */
mystatus_t
mycss_init(mycss_t* mycss);

/**
 * Destroy of a MyCSS structure
 *
 * @param[in] mycss_t*
 * @param[in] call free() function for mycss_t* object? true or false
 *
 * @return NULL if successful, otherwise an MyCSS structure.
 */
mycss_t*
mycss_destroy(mycss_t* mycss, bool self_destroy);

/**
 * Parsing CSS
 *
 * @param[in] previously created structure mycss_entry_t*
 * @param[in] Now is not working! Coming Soon. Input character encoding; Default: MyENCODING_UTF_8 or MyENCODING_DEFAULT or 0
 * @param[in] CSS data
 * @param[in] CSS data size
 *
 * All input character encoding decode to utf-8
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status
 */
mystatus_t
mycss_parse(mycss_entry_t* entry, myencoding_t encoding, const char* css, size_t css_size);

/**
 * Parsing CSS chunk. For End Parsing call mycss_parse_chunk_end function
 *
 * @param[in] previously created structure mycss_entry_t*
 * @param[in] CSS data
 * @param[in] CSS data size
 *
 * All input character encoding decode to utf-8
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status
 */
mystatus_t
mycss_parse_chunk(mycss_entry_t* entry, const char* css, size_t css_size);

/**
 * End of parsing CSS chunks
 *
 * @param[in] mycss_entry_t*
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status
 */
mystatus_t
mycss_parse_chunk_end(mycss_entry_t* entry);

/***********************************************************************************
 *
 * MyCSS_ENTRY
 *
 ***********************************************************************************/

/**
 * Create a MyCSS_ENTRY structure
 *
 * @return mycss_entry_t* if successful, otherwise an NULL value.
 */
mycss_entry_t*
mycss_entry_create(void);

/**
 * Allocating and Initialization resources for a MyCSS_ENTRY structure
 *
 * @param[in] mycss_t*
 * @param[in] mycss_entry_t*
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status value.
 */
mystatus_t
mycss_entry_init(mycss_t* mycss, mycss_entry_t* entry);

/**
 * Clear all structures
 *
 * @param[in] mycss_entry_t*
 *
 * @return MyCSS_STATUS_OK if successful, otherwise an error status value.
 */
mystatus_t
mycss_entry_clean_all(mycss_entry_t* entry);

/**
 * Destroy of a MyCSS_ENTRY structure
 *
 * @param[in] mycss_entry_t*
 * @param[in] call free() function for mycss_entry_t* object? true or false
 *
 * @return NULL if successful, otherwise an MyCSS_ENTRY structure.
 */
mycss_entry_t*
mycss_entry_destroy(mycss_entry_t* entry, bool self_destroy);

/**
 * Set or Get current callback function for token is ready
 *
 * @param[in] mycss_entry_t*
 * @param[in] mycss_token_ready_callback_f
 *   function which will be returned when the token is ready
 *   or NULL for only return current function
 *
 * @example_function
 *   mycss_token_t * your_name_callback(mycss_entry_t* entry, mycss_token_t* token) {
 *       return token;
 *   }
 *
 * @example See tokenizer_high_level.c in examples directory
 *
 * @return mycss_token_ready_callback_f structure
 */
mycss_token_ready_callback_f
mycss_entry_token_ready_callback(mycss_entry_t* entry,
                                 mycss_token_ready_callback_f callback_f);

/**
 * Get tokens count
 *
 * @param[in] mycss_entry_t*
 *
 * @return count of token
 */
size_t
mycss_entry_token_count(mycss_entry_t* entry);

/**
 * Get current Incoming Buffer
 * See MyHTML_INCOMING in https://github.com/lexborisov/myhtml
 *
 * @param[in] mycss_entry_t*
 *
 * @return mycore_incoming_buffer_t* if successful, otherwise an NULL value.
 */
mycore_incoming_buffer_t*
mycss_entry_incoming_buffer_current(mycss_entry_t* entry);

/**
 * Get first Incoming Buffer from list
 * See MyHTML_INCOMING in https://github.com/lexborisov/myhtml
 *
 * @param[in] mycss_entry_t*
 *
 * @return mycore_incoming_buffer_t* if successful, otherwise an NULL value.
 */
mycore_incoming_buffer_t*
mycss_entry_incoming_buffer_first(mycss_entry_t* entry);

/***********************************************************************************
 *
 * MyCSS_TOKEN
 *
 ***********************************************************************************/

/**
 * Get begin position of Token
 *
 * @param[in] mycss_token_t*
 *
 * @return size_t, begin position for token
 */
size_t
mycss_token_begin(mycss_token_t* token);

/**
 * Get length of Token
 *
 * @param[in] mycss_token_t*
 *
 * @return size_t, length of token
 */
size_t
mycss_token_length(mycss_token_t* token);

/**
 * Get begin position and length for Token
 *
 * @param[in] mycss_token_t*
 * @param[out] size_t*, optional, token length
 *
 * @return size_t, begin position for token
 */
size_t
mycss_token_position(mycss_token_t* token, size_t *return_length);

/**
 * Get Token type
 *
 * @param[in] mycss_token_t*
 *
 * @return mycss_token_type_t
 */
mycss_token_type_t
mycss_token_type(mycss_token_t* token);

/**
 * Get Token name by Token type
 *
 * @param[in] mycss_token_type_t
 *
 * @return token name terminated with a null character ('\0')
 */
const char*
mycss_token_name_by_type(mycss_token_type_t type);

/**
 * Converting raw token data (your input const char*)
 * to strict string as required by the specification
 *
 * @param[in] mycss_entry_t*
 * @param[in] mycss_token_t*, token from which data will be obtained
 * @param[in] mycore_string_t*, a pointer to the row in which the data will be written
 * @param[in] initialization mycore_string_t* object
 *
 * @return length of processed data
 */
size_t
mycss_token_data_to_string(mycss_entry_t* entry, mycss_token_t* token,
                           mycore_string_t* str, bool init_string);

/***********************************************************************************
 *
 * MyCSS_ENCODING
 *
 * @description It is inherited from the main project MyHTML
 *   See https://github.com/lexborisov/myhtml
 *
 ***********************************************************************************/

/**
 * Set character encoding for input stream
 *
 * @param[in] mycss_entry_t*
 * @param[in] Input character encoding. 
 *   See https://github.com/lexborisov/myhtml/blob/master/source/myhtml/api.h 
 *   myencoding_t
 *
 */
void
mycss_encoding_set(mycss_entry_t* entry, myencoding_t encoding);

/**
 * Get character encoding for current stream
 *
 * @param[in] mycss_entry_t*
 *
 * @return myencoding_t
 */
myencoding_t
mycss_encoding_get(mycss_entry_t* entry);

/**
 * Get encoding from @charset "...";
 *
 * See for information:
 * https://www.w3.org/TR/css-syntax-3/#get-an-encoding
 * https://www.w3.org/TR/css-syntax-3/#charset-rule
 * myencoding_by_name in https://github.com/lexborisov/myhtml/blob/master/source/myhtml/api.h
 *
 * If @charset rule is missing or encoding not found return MyENCODING_UTF_8 by default
 *
 * @param[in] css data stream
 * @param[in] css data stream size
 *
 * @return myencoding_t
 */
myencoding_t
mycss_encoding_check_charset_rule(const char* css, size_t size);

/***********************************************************************************
 *
 * MyCSS_CONVERT
 *
 * @description It is inherited from the main project MyHTML
 *   See https://github.com/lexborisov/myhtml
 *
 ***********************************************************************************/

/**
 * Convert data to double number
 *
 * @param[in]  data to convert
 * @param[in]  data size
 * @param[out] converting result
 * @param[out] is integer or float
 *
 * @return length of data converting
 */
size_t
mycss_convert_data_to_double(const char* data, size_t size, double* return_num, bool* is_float);

/**
 * Convert data to unicode range code point
 * See https://www.w3.org/TR/css-syntax-3/#unicode-range-token-diagram
 * See https://www.w3.org/TR/css-syntax-3/#consume-a-unicode-range-token
 *
 * @param[in]  data to convert
 * @param[in]  data size
 * @param[out] start range converting result
 * @param[out] end range converting result
 *
 * @return length of data converting
 */
size_t
mycss_convert_unicode_range_to_codepoint(const char *data, size_t size, size_t *start, size_t *end);

/**
 * Convert hex data to code point
 *
 * @param[in]  data to convert
 * @param[in]  data size
 * @param[out] result codepoint
 * @param[in]  how much length can be consumed
 *
 * @return length of data converting
 */
size_t
mycss_convert_hex_to_codepoint(const char *data, size_t size, size_t *codepoint, unsigned int max_consumed);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MyCSS_MyCSS_API_H */
