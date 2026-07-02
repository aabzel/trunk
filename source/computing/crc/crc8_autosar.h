#ifndef CRC8_AUTOSAR_H
#define CRC8_AUTOSAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

uint8_t crc8_autosar_calc(const void* buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* CRC8_AUTOSAR_H*/
