#ifndef POWER_CONFIG_H
#define POWER_CONFIG_H

#include "power_types.h"
#include "sys_config.h"

#ifndef HAS_POWER
#error "+HAS_POWER"
#endif

extern const PowerConfig_t PowerConfig[];
extern PowerHandle_t PowerInstance[];

uint32_t power_get_cnt(void);

#endif /* POWER_CONFIG_H  */
