#include "time_config.h"

#include "data_utils.h"

const TimeConfig_t TimeConfig[] = {
        { .num = TIME_SYSTICK, .time_source = TIME_SRC_SYSTICK, .valid = true, },
        { .num = TIME_TIMER2, .time_source = TIME_SRC_TIMER2, .valid = true, },
        { .num = TIME_TIMER5, .time_source = TIME_SRC_TIMER5, .valid = true, },
        { .num = TIME_PCAN_TIMESTAMP, .time_source = TIME_SRC_PCAN_TIMESTAMP, .valid = true, },
        { .num = TIME_HAL_TICK, .time_source = TIME_SRC_HAL_TICK, .valid = true, },
        { .num = TIME_DWT, .time_source = TIME_SRC_DWT, .valid = true, },
};

TimeHandle_t TimeInstance[] = {
        { .num = TIME_SYSTICK, .valid = true, },
        { .num = TIME_TIMER2, .valid = true, },
        { .num = TIME_TIMER5, .valid = true, },
        { .num = TIME_PCAN_TIMESTAMP, .valid = true, },
        { .num = TIME_HAL_TICK, .valid = true, },
        { .num = TIME_DWT, .valid = true, },
};

COMPONENT_GET_CNT(Time, time)
