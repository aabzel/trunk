#ifndef CRC_24_Q_H
#define CRC_24_Q_H
/*CRC-24Q*/

#include "std_includes.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef MASK_24BIT
#define MASK_24BIT ( (uint32_t)0x00FFFFFFU)
#endif

uint32_t calc_crc24_q(const uint8_t* const in_data, uint32_t const len);
bool crc24_q_check(const uint8_t* const in_data, uint32_t const length, uint32_t const crc24_read);

#ifdef __cplusplus
}
#endif

#endif /* CRC_24_Q_H */
