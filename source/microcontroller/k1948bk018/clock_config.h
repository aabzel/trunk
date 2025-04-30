#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <stdbool.h>

#include "clock_types.h"

extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

bool system_clock_config(void);
//bool clock_init(void);

#endif /* CLOCK_CONFIG_H  */
