#ifndef CRC8_AUTOSAR_H
#define CRC8_AUTOSAR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t crc8_autosar_calc(const void* buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* CRC8_AUTOSAR_H*/
