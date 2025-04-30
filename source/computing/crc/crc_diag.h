#ifndef CRC_DIAG_H
#define CRC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "crc_types.h"

const char* Crc16ToStr(const Crc16_t*const  Node);

#ifdef __cplusplus
}
#endif

#endif /* CRC_DIAG_H */
