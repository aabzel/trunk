#ifndef TIME_CONFIG_H
#define TIME_CONFIG_H

#include <stdint.h>

#include "time_types.h"

typedef enum {
    TIME_NUM_RISC_V_TIMER = 1,
    TIME_NUM_SCR1_TIMER = 2,
    TIME_NUM_SW_INCR = 3,
} TimeNumLegal_t;

#define TIME_MAIN_NUM (TIME_NUM_RISC_V_TIMER)

extern const TimeConfig_t TimeConfig[];
extern TimeHandle_t TimeInstance[];

bool time_fix(void);
uint32_t time_get_cnt(void);

#endif /* TIME_CONFIG_H  */
