#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <stdbool.h>

#include "clock_types.h"

#define HSE_VALUE   12000000U  /*Value of the External oscillator in Hz */
extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;


//bool clock_init(void);
bool clock_init_48mhz(void);
bool clock_config_100mhz(void);

#endif /* CLOCK_CONFIG_H  */
