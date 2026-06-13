#include "pid_config.h"

#include "data_utils.h"
#include "time_mcal.h"

const PidConfig_t PidConfig[] = {
    {
        .num = 1,
        .period_s =  0.001f,
        .units = STORAGE_UNITS_RADIAN,
        .p = 0.0f,// proportional part
        /* Integral part depends on low pass filter length i=1/LPForder */
        .i = 0.03f,//-0.03f 0.02f - ok for PC integral part
        .d = -0.06f, // differential part
        .on = true,
        .manual = false,
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

