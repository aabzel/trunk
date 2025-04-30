#include "pwm_dac_config.h"

#include "adc_config.h"
#include "data_utils.h"
#include "pwm_config.h"
#ifdef HAS_PID
#include "pid_config.h"
#endif

const PwmDacConfig_t PwmDacConfig[] = {
    {
        .num = PWM_DAC_TEST,
        .target_voltage = 1.5,
        .pid_num = 1,
        .name = "TEST",
        .adc_channel_num = ADC_CHANNEL_ADC_EXT1_IN,
        .pwm_num = PWM_NUM_TEST,
        .R = 46600,
        .C = 0.001,
        .v_max = 3.3,
        .valid = true,
    },
};

PwmDacHandle_t PwmDacInstance[] = {
    {
        .num = PWM_DAC_TEST,
        .valid = true,
    },
    //{.num=PWM_DAC_NUM_ADC2, .valid=true, },
    //{.num=PWM_DAC_NUM_EXT1, .valid=true, },
    //{.num=PWM_DAC_NUM_EXT2, .valid=true, },
};

uint32_t pwm_dac_get_cnt(void) {
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    uint32_t cnt = 0;
    cnt1 = ARRAY_SIZE(PwmDacConfig);
    cnt2 = ARRAY_SIZE(PwmDacInstance);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
