#include "pid_config.h"

#include "data_utils.h"
#include "time_mcal.h"

const PidConfig_t PidConfig[] = {
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
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t pid_get_cnt(void) {
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    uint32_t cnt = 0;
    cnt1 = ARRAY_SIZE(PidConfig);
    cnt2 = ARRAY_SIZE(PidInstance);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
