#ifndef DWORD_MISC_H
#define DWORD_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

uint32_t reverse_byte_order_uint32(const uint32_t in4byteVal);

bool fetch_big_endian_dword(const uint8_t* const data,
                            const uint32_t size,
                            uint32_t* const dword);

uint32_t copy_and_rev32(const uint8_t* const array) ;

#ifdef __cplusplus
}
#endif

#endif /* DWORD_MISC_H */
