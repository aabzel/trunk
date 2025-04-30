#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

#ifdef HAS_TIMER
#include "timer_config.h"

#define TIME_MAIN_NUM 1
#else
#define TIME_MAIN_NUM 1
#endif


extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
