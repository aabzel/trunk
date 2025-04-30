#ifndef CLOCK_DIVIDER_CONFIG_H
#define CLOCK_DIVIDER_CONFIG_H

#include <stdbool.h>

#include "clock_divider_types.h"

extern const ClockDividerConfig_t ClockDividerConfig[];
extern ClockDividerHandle_t ClockDividerInstance[];

uint32_t clock_divider_get_cnt(void);

#endif /* CLOCK_DIVIDER_CONFIG_H  */
