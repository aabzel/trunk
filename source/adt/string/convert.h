#ifndef STR_CONVERT_H
#define STR_CONVERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "convert_types.h"
#include "storage_const.h"
#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifndef FP_NAN
#define FP_NAN 0
#endif

#ifndef FP_INFINITE
#define FP_INFINITE 1
#endif

#ifndef FP_ZERO
#define FP_ZERO 2
#endif

#ifndef FP_SUBNORMAL
#define FP_SUBNORMAL 3
#endif

#ifndef FP_NORMAL
#define FP_NORMAL 4
#endif

#ifdef HAS_FLOAT_UTILS
#include "float_utils.h"
#endif

#ifndef HAS_STRING
#error "It is needed to define HAS_STRING_PARSER"
#endif

#ifndef MAX_PRECISION
#define MAX_PRECISION 10U
#endif

bool is_dec_digit(const char character);
bool try_strl2month(const char str[], int32_t* mon_value);
bool is_dec_str(const char str_to_check[], int32_t str_to_check_len);
bool is_hex_str(const char str_to_check[], int32_t str_to_check_len, uint8_t* const out_shift);
// 64 bit
bool try_str2uint64(const char u64_str[], uint64_t* u64_value);
bool try_str2int64(const char s64_str[], int64_t* s64_value);
bool try_strl2uint64(const char u64l_str[], int32_t u64l_str_len, uint64_t* u64l_value);
bool try_strl2int64(const char s64l_str[], int32_t s64l_str_len, int64_t* s64l_value);
bool try_strl2uint64_hex(const char u64_hex_str[], int32_t u64_hex_str_len, uint64_t* u64_hex_value);
bool try_strl2int64_hex(const char s64_hex_str[], int32_t s64_hex_str_len, int64_t* s64_hex_value);
bool try_strl2uint64_dec(const char u64_dec_str[], int32_t u64_dec_str_len, uint64_t* u64_dec_value);
bool try_strl2int64_dec(const char s64_dec_str[], int32_t s64_dec_str_len, int64_t* s64_dec_value);
// 32 bit
bool try_str2uint32(const char u32_str[], uint32_t* u32_value);
bool try_str2int32(const char s32_str[], int32_t* s32_value);
bool try_strl2uint32(const char u32l_str[], int32_t u32l_str_len, uint32_t* u32l_value);
bool try_strl2int32(const char s32l_str[], int32_t s32l_str_len, int32_t* s32l_value);
bool try_str2uint32_hex(const char u32_hex_str[], uint32_t* u32_hex_value);
bool try_strl2uint32_hex(const char u32l_hex_str[], int32_t u32l_hex_str_len, uint32_t* u32l_hex_value);
bool try_strl2int32_hex(const char s32l_hex_str[], int32_t s32l_hex_str_len, int32_t* s32l_hex_value);
bool try_strl2uint32_dec(const char u32_dec_str[], int32_t u32_dec_str_len, uint32_t* u32_dec_value);
bool try_strl2int32_dec(const char s32_dec_str[], int32_t s32_dec_str_len, int32_t* s32_dec_value);

#ifdef HAS_PARSE_16BIT_TYPES
bool try_str2uint16(const char u16_str[], uint16_t* u16_value);
bool try_str2int16(const char s16_str[], int16_t* s16_value);
bool try_strl2uint16(const char u16l_str[], int32_t u16l_str_len, uint16_t* u16l_value);
bool try_strl2int16(const char s16l_str[], int32_t s16l_str_len, int16_t* s16l_value);
bool try_strl2uint16_hex(const char u16l_hex_str[], int32_t u16l_hex_str_len, uint16_t* u16l_hex_value);
#endif

#ifdef HAS_PARSE_8BIT_TYPES
uint8_t char_to_u8(uint8_t dec_char);
bool try_str2uint8(const char u8_str[], uint8_t* u8_value);
bool try_str2int8(const char s8_str[], int8_t* s8_value);
bool try_strl2uint8(const char u8l_str[], int32_t u8l_str_len, uint8_t* u8l_value);
bool try_strl2uint8_hex(const char u8l_hex_str[], int32_t u8l_hex_str_len, uint8_t* u8l_hex_value);
//bool try_strl2uint8_hex(const char u8l_hex_str[], int32_t u8l_hex_str_len, uint8_t* u8l_hex_value);
bool try_strl2int8(const char s8l_str[], int32_t s8l_str_len, int8_t* s8l_value);
bool try_strl2int8_hex(const char s8l_hex_str[], int32_t s8l_hex_str_len, int8_t* s8l_hex_value);
#endif
bool try_str2bool(const char bool_str[], bool* bool_value);
bool try_strl2array(const char* const str_array, uint32_t len_str_in, uint8_t* const out_array, uint16_t array_size,
                    uint32_t* const out_array_len);
bool try_str2array(char* in_str_array, uint8_t* out_array, uint16_t array_size, uint32_t* const out_array_len);

uint32_t assemble_uint32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
bool is_hex_digit(const char character);
bool AsciiChar2HexNibble(char ch, uint8_t* nibble_out);
//bool array2str(const uint8_t* const bin, uint32_t len, char* const out_array, uint16_t array_size);
uint8_t AsciiChar2Dec(char ch);
uint16_t double_to_uint16(double val);

uint16_t float_to_uint16(float val);
#ifdef HAS_STR2_FLOAT
bool try_str2float(const char float_str[], float* float_value);
void ftoa_(float float_data_, int32_t float_precision_, char float_stringified_[]);

#endif

#ifdef HAS_STR2_DOUBLE
bool is_valid_double_symbol(char symbol);
void dtoa_(double double_data_, int32_t double_precision_, char double_stringified_[]);
bool try_str2double(const char double_str[], double* double_value);
bool try_strl2double(const char double_str[], int32_t u8l_hex_str_len, double* double_value);
bool number_proc_one(Text2NumberFsm_t* Node);
bool text_2_number_init(Text2NumberFsm_t* Node);
bool try_str2number(const char* const str, double* const double_value);
#endif

bool try_str2type(const char* const text, StorageType_t type, uint8_t* buff, uint32_t buff_size);
bool try_hex_char_to_u8(uint8_t hex_char, uint8_t* hex_char_to_u8_value);
bool number_compose_result(Text2NumberFsm_t* Node);

#ifdef __cplusplus
}
#endif

#endif /* STR_CONVERT_H */
