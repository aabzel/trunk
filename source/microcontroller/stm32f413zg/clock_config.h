#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "std_includes.h"
#include "clock_types.h"

extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;


void clock_100mz_config(void);

#endif /* CLOCK_CONFIG_H  */
