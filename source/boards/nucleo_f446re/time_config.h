#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

typedef enum {
    TIME_SYSTICK = 1,
    TIME_TIMER2 = 2,
    TIME_TIMER5 = 3,
    TIME_PCAN_TIMESTAMP = 4,
    TIME_HAL_TICK = 5,
    TIME_DWT= 6,
}TimeLegalNum_t;

#define TIME_MAIN_NUM TIME_DWT

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
