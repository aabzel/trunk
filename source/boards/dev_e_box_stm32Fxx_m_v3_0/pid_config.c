#include "pid_config.h"

#include "data_utils.h"
#include "time_mcal.h"

const PidConfig_t SECTION_CFG_DATA PidConfig[] = {
    {
        .num = 1,
        .unit = UNITS_RADIANS,
        .period_us =  SEC_2_USEC(1.0/44100.0), // 1/44100
        .p = 0.00,// proportional part
        .i = -0.002,// integral part
        .d = 0.00, // differential part
        .on = true,
        .valid = true,
        .name = "PhaseErr",
    },
};


PidHandle_t PidInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Pid, pid)

