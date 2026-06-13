#include "pid_config.h"

#include "data_utils.h"
#include "time_mcal.h"

const PidConfig_t SECTION_CFG_DATA PidConfig[] = {
        {
            .num = PID_NUM_SMOOTH_LAMP,
            .period_s =  0.01f,
            .units = STORAGE_UNITS_LUX,
            .p = 0.001f, // proportional part
            /* Integral part depends on low pass filter length i=1/LPForder */
            .i = 0.005f, //-0.03f 0.02f - ok for PC integral part
            .d = 0.00f,  // differential part
            .on = true,
            .manual = false,
            .valid = true,
            .target = 0.0f,
            .adc_channel_num = 0x55,
            .pwm_dac_num = 0x55,
            .name = "SMOOTH_LAMP",
        },
#ifdef HAS_LOCAL_OSCILATOR
    {
        .num = PID_NUM_LOC_OCS_PHASE,
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
#endif
};


PidHandle_t PidInstance[] = {
#ifdef HAS_LOCAL_OSCILATOR
    { .num = PID_NUM_LOC_OCS_PHASE, .valid = true, },
#endif
    { .num = PID_NUM_SMOOTH_LAMP, .valid = true, },
};

COMPONENT_GET_CNT(Pid, pid)

