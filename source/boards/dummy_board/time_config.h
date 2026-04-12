#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

typedef enum {
	TIME_SW_UNDEF = 0,
	TIME_SW_INC = 1,
	TIME_SW_SYSTICK = 2,
	TIME_SW_TIMER2 = 3,
} TimeLegalNums_t;

#ifdef HAS_TIMER
#include "timer_config.h"
#define TIME_MAIN_NUM TIME_SW_TIMER2
#else


#define TIME_MAIN_NUM TIME_SW_SYSTICK



#endif

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
