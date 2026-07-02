#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

typedef enum {
    TIME_SYSTICK ,
    TIME_TIMER5 ,
    TIME_HAL_TICK ,
    TIME_DWT ,
    TIME_CNT ,
}TimeLegalNum_t;

#define TIME_US_MAIN_NUM TIME_DWT

#define TIME_MAIN_NUM TIME_DWT

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
