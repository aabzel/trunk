#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "std_includes.h"
#include "clock_types.h"

//#define HSE_VALUE 25000000U /*Value of the External oscillator in Hz */
extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

void clock_config_25_168mhz(void);
void clock_config_25_100mhz(void);
void clock_config_25_120mhz(void);
void clock_config_25_96mhz(void);

bool clock_config_100mhz(void);
bool clock_init_48mhz(void) ;
bool clock_mcal_init(void);
bool clock_config_default(void) ;

#endif /* CLOCK_CONFIG_H  */
