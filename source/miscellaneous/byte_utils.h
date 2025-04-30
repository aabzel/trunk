#ifndef BYTE_UTILS_H
#define BYTE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#define HI_NIBBLE(b) (((b) >> 4) & 0x0F)
#define LO_NIBBLE(b) ((b)&0x0F)

#define WORD_HI_BYTE(WORD) (((WORD) >> 8) & 0xFF)
#define WORD_LO_BYTE(WORD) ((WORD)&0xFF)

bool reverse_byte_order_array(uint8_t* const in_out_array, uint32_t len);
int32_t reverse_byte_order_int24(const int32_t in3byteVal);
uint16_t reverse_byte_order_uint16(const uint16_t in2byteVal);
uint32_t reverse_byte_order_uint24(const uint32_t in3byteVal);
uint32_t reverse_byte_order_uint32(const uint32_t in4byteVal);
uint64_t reverse_byte_order_uint64(const uint64_t in4byteVal);
uint8_t swap_nibbles(uint8_t const data);

uint16_t copy_and_rev16(const uint8_t* const array);
uint32_t copy_and_rev32(const uint8_t* const array);
uint64_t copy_and_rev64(const uint8_t* const array);

uint32_t reverse_half_word_order_uint32(const uint32_t word);

#ifdef __cplusplus
}
#endif

#endif /* BYTE_UTILS_H */
