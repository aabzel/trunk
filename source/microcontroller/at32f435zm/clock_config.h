#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <stdbool.h>

#include "clock_types.h"


/*Value of the External oscillator in Hz */
extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

bool system_clock_config(void);
void system_clock_config_200mhz(void);
bool clock_config_100mhz(void);
bool clock_init(void);

#endif /* CLOCK_CONFIG_H  */
