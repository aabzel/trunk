/*CRC-24Q*/
#ifndef CRC_24_Q_H
#define CRC_24_Q_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t calc_crc24_q(const uint8_t* const in_data, uint32_t const len);
bool crc24_q_check(const uint8_t* const in_data, uint32_t const length, uint32_t const crc24_read);

#ifdef __cplusplus
}
#endif

#endif /* CRC_24_Q_H */
