#include "clock_divider_config.h"

#include "data_utils.h"

const ClockDividerConfig_t ClockDividerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .amp = 10,
        .divider = 2,
        .schmitt_trigger_num = 2,
    },
    {
        .num = 2,
        .valid = true,
        .amp = 10,
        .divider = 2,
        .schmitt_trigger_num = 3,
    },
};

ClockDividerHandle_t ClockDividerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

COMPONENT_GET_CNT(ClockDivider, clock_divider)

