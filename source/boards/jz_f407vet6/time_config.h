#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H


#include "std_includes.h"
#include "time_types.h"

typedef enum {
    TIME_NUM_SYSTICK ,
    TIME_NUM_TIMER2,
    TIME_NUM_TIMER5 ,
    TIME_NUM_PCAN_TIMESTAMP,
    TIME_NUM_HAL_TICK ,
    TIME_NUM_DWT,
    TIME_NUM_CNT,
}TimeLegalNum_t;

#define TIME_US_MAIN_NUM TIME_NUM_DWT
#define TIME_MAIN_NUM TIME_NUM_DWT

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
