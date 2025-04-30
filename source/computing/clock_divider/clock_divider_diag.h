#ifndef CLOCK_DIVIDER_DIAG_H
#define CLOCK_DIVIDER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include  "clock_divider_types.h"

bool clock_divider_diag(uint8_t num);
const char* ClockDividerConfigToStr(const ClockDividerConfig_t* const Config);
const char* ClockDividerNodeToStr(const ClockDividerHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* CLOCK_DIVIDER_DIAG_H */
