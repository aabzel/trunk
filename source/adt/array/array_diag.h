#ifndef ARRAY_DIAG_H
#define ARRAY_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"

bool print_hex(const uint8_t* const buff, const uint32_t size);
bool print_bin(uint8_t const* const buff, uint32_t size, uint16_t indent);
bool print_mem(const uint8_t* const addr, int32_t len, bool is_bin, bool is_ascii, bool new_line, bool is_packed);
bool array_i8_print_dec(const int8_t* const data, size_t size);
bool array_i32_print(const int32_t* const array, size_t size, double step);
bool array_i16_print(const int16_t* const array, size_t size, double step);
bool array_double_i16_print(const int16_t* const array1, const int16_t* const array2, size_t size, double step);
bool array_i8_print(const int8_t* const array, size_t size);
bool array_u32_print(const uint32_t* const array, size_t size);
bool array_16_print(const int16_t* const array, size_t size);
bool array_u16_print(const uint16_t* const array, size_t size);
bool array_u16_print_bin(const uint16_t* const array, size_t size);
bool array_u8_print(const uint8_t* const array, size_t size);
bool array_u8_print_dec(const uint8_t* const data, size_t size);
const char* ArrayToStr(const uint8_t* const array, size_t size);
const char* ArrayToAsciiStr(const uint8_t* const array, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_DIAG_H */
