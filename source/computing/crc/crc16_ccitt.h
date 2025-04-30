#ifndef CRC_16_CCITT_FALSE_H
#define CRC_16_CCITT_FALSE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "crc_types.h"

#define INIT_VALUE (0xFFFFU)
#define LOOK_UP_TABLE_SIZE (256U)
#define CRC16_SIZE 2

extern const uint16_t crc16LookUpTable[LOOK_UP_TABLE_SIZE];

uint16_t calc_crc16_ccitt_false_stream(const uint8_t* const in_data, uint32_t chunk_size, bool init,
                                       uint16_t prev_crc16);
uint16_t calc_crc16_ccitt_false(const uint8_t* const in_data, uint32_t const length);
bool crc16_check(const uint8_t* in_data, uint32_t const length, uint16_t crc16_read, uint16_t* const out_crc16_calc);

#ifdef __cplusplus
}
#endif

#endif /* CRC_16_CCITT_FALSE_H */
