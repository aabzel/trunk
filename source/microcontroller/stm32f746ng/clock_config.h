#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "std_includes.h"
#include "clock_types.h"

extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

bool clock_init_48mhz(void);
void clock_init_200mhz(void);
void PeriphCommonClock_Config(void);
bool clock_init(void);

#endif /* CLOCK_CONFIG_H  */
