#ifndef WORD_MISC_H
#define WORD_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#define WORD_HI_BYTE(WORD) (((WORD) >> 8) & 0xFF)
#define WORD_LO_BYTE(WORD) ((WORD)&0xFF)


uint16_t reverse_byte_order_uint16(const uint16_t in2byteVal);

bool insert_big_endian_word(const uint16_t word, uint8_t* const array );


bool fetch_big_endian_word(const uint8_t* const data,
                            const uint32_t size,
                            uint16_t* const word);


uint16_t copy_and_rev16(const uint8_t* const array);




#ifdef __cplusplus
}
#endif

#endif /* WORD_MISC_H */
