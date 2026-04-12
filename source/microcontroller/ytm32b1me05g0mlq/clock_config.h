#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <stdbool.h>

#include "clock_types.h"

extern ClockConfig_t ClockConfig;
extern ClockHandle_t ClockInstance;

#define CLOCK_MANAGER_ACTIVE_INDEX  0U
#define CLOCK_MANAGER_CONFIG_CNT                           1U /*!< Count of user configuration */
#define CLOCK_MANAGER_CALLBACK_CNT                         0U /*!< Count of user Callbacks */

bool system_clock_config(void);
bool clock_init(void);

#endif /* CLOCK_CONFIG_H  */
