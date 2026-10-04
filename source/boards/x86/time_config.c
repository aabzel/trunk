#include "time_config.h"

#include "data_utils.h"

const TimeConfig_t TimeConfig[] = {
    {
        .num = TIME_NUM_MAIN,
        .time_source = TIME_SRC_WIN_CLOCK,
        .valid = true,
    },
};

TimeHandle_t TimeInstance[] = {
    {
        .num = TIME_NUM_MAIN,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Time, time)

