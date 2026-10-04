#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

typedef enum {
    TIME_NUM_UNDEF = 0,
    TIME_NUM_MAIN,
    TIME_NUM_CNT
}TimeLegalNums_t;

#define TIME_MAIN_NUM TIME_NUM_MAIN
#define TIME_US_MAIN_NUM TIME_MAIN_NUM

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
