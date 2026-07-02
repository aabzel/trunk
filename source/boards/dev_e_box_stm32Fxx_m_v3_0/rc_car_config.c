#include "rc_car_config.h"

#include "data_utils.h"

const RcCarConfig_t RcCarConfig[] = {
    {
        .num = 1,
        .valid = true,
        .ir_samsung_num = 1,
        .motor_pwm_freq_hz = 20000.0,
        .motor_trottle_num = 1,
        .motor_steering_num = 2,
        .gear = 50.0,
        .name = "RC_CAR1",
    },
};

RcCarHandle_t RcCarInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t rc_car_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(RcCarConfig);
    cnt2 = ARRAY_SIZE(RcCarInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
