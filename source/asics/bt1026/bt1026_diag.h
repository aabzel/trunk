#ifndef BT1026_DIAG_H
#define BT1026_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "bt1026_types.h"

#ifndef HAS_BT1026
#error "+HAS_BT1026"
#endif

bool parse_i2s_config(uint8_t byte_val);
char* Bt1026ResolutionToStr(uint8_t code);
char* Bt1026SampleRateToStr(uint8_t code);
char* Bt1026I2sBusRoleToStr(uint8_t code);

#endif /* BT1026_DIAG_H  */
