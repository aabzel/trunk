#include "pid_config.h"

#include "data_utils.h"
#include "time_mcal.h"

const PidConfig_t PidConfig[] = {
    {
        .num = 1,
        .units = STORAGE_UNITS_RADIAN,
        .period_s =  (1.0f/1000.0f),
        .p = 0.00,// proportional part
        .i = -0.02,// integral part
        .d = 0.00, // differential part
        .on = true,
        .valid = true,
        .adc_channel_num = 0x55,
        .pwm_dac_num = 0x55,
        .name = "LocOcsPhase",
    },
};

PidHandle_t PidInstance[] = {
    { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Pid, pid)

