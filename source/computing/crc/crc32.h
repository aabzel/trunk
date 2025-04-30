#ifndef CRC32_H
#define CRC32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

uint32_t crc32_calc(const void* const data_8, uint32_t len_8);
uint32_t crc32_stream_calc(uint32_t seed_crc32, const void* const buf, uint32_t bufLen);

#ifdef __cplusplus
}
#endif

#endif /* CRC32_H */
