#ifndef CRC_16_IBM_H
#define CRC_16_IBM_H


#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

uint16_t crc16_ibm_calc(const uint8_t * const data,  const uint32_t len);


#ifdef __cplusplus
}
#endif

#endif /* CRC_16_IBM_H */



