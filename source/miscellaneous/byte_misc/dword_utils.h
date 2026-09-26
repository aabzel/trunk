#ifndef DWORD_MISC_H
#define DWORD_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "data_types.h"

uint64_t invert_dec(const uint32_t value);
uint32_t rank_dec(const uint32_t de);
uint32_t u32_decimal_rank(const uint32_t value);
uint32_t max32u(uint32_t max32u_x1, uint32_t max32u_x2);
uint32_t min32u(uint32_t min32u_x1, uint32_t min32u_x2);
uint32_t uint32_limiter(const uint32_t in_val, const uint32_t max);
uint32_t copy_and_rev32(const uint8_t* const array) ;
uint32_t reverse_byte_order_uint32(const uint32_t in4byteVal);
uint8_t extract_digit(uint32_t in_num, uint8_t digit_index);
int32_t max32(int32_t max32_x1, int32_t max32_x2);
int32_t min32(int32_t min32_x1, int32_t min32_x2);
int32_t int32_range_limiter(const int32_t in_val, const int32_t min, const int32_t max);
bool data_u32_init(U32Value_t* const Node) ;
bool swap_u32_xor(uint32_t* const a, uint32_t* const b);
bool is_range_uint32(const uint32_t in_val, const uint32_t min, const uint32_t max);
bool fetch_big_endian_dword(const uint8_t* const data,
                            const uint32_t size,
                            uint32_t* const dword);

uint32_t binary_coded_decimal_to_u32(const uint8_t* const data,
                                     const uint32_t nimble_cnt);
bool u32_to_binary_coded_decimal(const uint32_t value, uint8_t* const data, uint32_t* const nimble_cnt);

#ifdef __cplusplus
}
#endif

#endif /* DWORD_MISC_H */
