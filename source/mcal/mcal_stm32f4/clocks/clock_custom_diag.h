#ifndef CLOCK_CUSTOM_DIAG_H
#define CLOCK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_CLOCK
#error "+HAS_CLOCK"
#endif

#include "clock_custom_types.h"

const char * Bus2Str(uint8_t code);
bool periph_clock_diag(char *keyWord1,char *keyWord2);

#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_DIAG_H
