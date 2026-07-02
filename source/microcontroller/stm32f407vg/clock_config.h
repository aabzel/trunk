#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "std_includes.h"
#include "clock_types.h"

extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

void clock_config_8_96_Mhz(void);
void clock_config_8_120_Mhz(void);
void clock_config_8_100_Mhz(void);
void clock_config_8_168_Mhz(void);

bool clock_init_8_48mhz(void);
bool clock_init(void);

#endif /* CLOCK_CONFIG_H  */
