#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bit_types.h"

#define SET_BIT_NUM(VAL, BIT) ((VAL) |= (1U << (BIT)))
#define RESET_BIT_NUM(VAL, BIT) ((VAL) &= ~(1U << (BIT)))

#define GET_BIT_NUM(VAL, BIT) (1 & ((VAL) >> (BIT)))
#define CHECK_BIT_NUM(VAL, BIT) ((1U << (BIT)) == ((VAL) & (1U << (BIT))))
#define IS_BIT_RESET(VAL, BIT) (0 == ((VAL) & (1 << (BIT))))


bool bit_get_u8(uint8_t byte, uint8_t bit_num);
uint8_t bit_not(const uint8_t byte);
//(1 & ((VAL) >> (BIT)))
uint32_t calc_bitness(const uint32_t value) ;
int32_t parse_n_bit_signed(uint32_t value, uint8_t bittness);
uint32_t bit_ctrl(const uint32_t in_val, const uint8_t bit_num, const uint8_t bit_val);
uint32_t calc_bitness_u64(const uint64_t value);
uint64_t generate_64bit_mask(uint8_t bit_len);
uint8_t generate_8bit_mask(uint8_t bit_len);
uint8_t generate_8bit_left_mask(uint8_t bit_len);
uint32_t generate_32bit_custom_mask(uint8_t max_bit, uint8_t min_bit);
uint32_t generate_32bit_mask(uint8_t bit_len);

uint32_t generate_32bit_left_mask(uint8_t bitlen);
uint32_t extract_subval_from_32bit(uint32_t inVal, uint8_t maxBit, uint8_t minBit);
uint8_t extract_subval_from_8bit(uint8_t inVal, uint8_t maxBit, uint8_t minBit);

uint64_t generate_64bit_left_mask(uint8_t bitlen);
uint64_t extract_subval_from_64bit(uint64_t inVal, uint8_t maxBit, uint8_t minBit);

uint32_t insert_subval_in_32bit(uint32_t orig_val, uint32_t sub_val, uint8_t max_bit, uint8_t min_bit);
uint8_t bit_summ16(uint16_t data);
uint8_t count_set_bits(uint32_t const inVal32bit);
bool bit32_control_proc(uint32_t* address_val, char cmd, uint8_t bit);
bool is_parity_odd(uint32_t const inVal);

uint8_t get_bit_from_32bit(uint32_t in_val, uint8_t bit_num);
uint16_t invert_bits16(uint16_t val);

#ifdef HAS_BIT_SWAP
uint8_t swap_bits_u8_2(uint8_t in_val);
uint32_t swap_bits_u32_f(uint32_t num32b);
uint8_t swap_bits_u8_fast(uint8_t in_val) ;
uint8_t swap_bits_u8_slow(uint8_t in_val) ;
uint8_t swap_bits_u8(uint8_t in_val);
uint16_t swap_bits_u16(uint16_t in_val);
uint32_t swap_bits_u32(uint32_t in_val);
uint32_t swap_bits_u24(uint32_t in_val);
uint64_t swap_bits_u64(uint64_t in_val);
uint64_t swap_bits_u64_v2(uint64_t in_val);
#endif

bool is_valid_bit_mask_u8(char* in_mask);
uint8_t adjust_bits_u8(uint8_t orig, char* in_mask);

#ifdef __cplusplus
}
#endif

#endif /* BIT_UTILS_H */
