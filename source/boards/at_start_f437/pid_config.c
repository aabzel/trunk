#include "pid_config.h"

#include "adc_config.h"
#include "pwm_dac_config.h"
#include "data_utils.h"

const PidConfig_t PidConfig[] = {
    {.name="ADC_EXT1_IN",   .pwm_dac_num=PWM_DAC_NUM_ADC1, .num=PID_NUM_ADC_EXT_OUT1, .adc_channel_num=ADC_CHANNEL_ADC_EXT1_IN,   .unit=UNITS_VOLTS, .period_us=100000, .p=0.0, .i=-0.5,  .d=0.0, .on=false, .valid=true, },
    {.name="ADC_EXT2_IN",   .pwm_dac_num=PWM_DAC_NUM_ADC2, .num=PID_NUM_ADC_EXT_OUT2, .adc_channel_num=ADC_CHANNEL_ADC_EXT2_IN,   .unit=UNITS_VOLTS, .period_us=100000, .p=0.0, .i=-0.5,  .d=0.0, .on=false, .valid=true, },
    {.name="DIGIT_EXT1_IN", .pwm_dac_num=PWM_DAC_NUM_EXT1, .num=PID_NUM_DIGIT_EXT_OUT2, .adc_channel_num=ADC_CHANNEL_DIGIT_EXT1_IN, .unit=UNITS_VOLTS, .period_us=100000, .p=0.0, .i=-0.5,  .d=0.0, .on=false, .valid=true, },
    {.name="DIGIT_EXT2_IN", .pwm_dac_num=PWM_DAC_NUM_EXT2, .num=PID_NUM_DIGIT_EXT_OUT1, .adc_channel_num=ADC_CHANNEL_DIGIT_EXT2_IN, .unit=UNITS_VOLTS, .period_us=100000, .p=0.0, .i=-0.5,  .d=0.0, .on=false, .valid=true, },
};

PidHandle_t PidInstance[]= {
    {.num=PID_NUM_ADC_EXT_OUT1, .valid=true, },
    {.num=PID_NUM_ADC_EXT_OUT2, .valid=true, },
    {.num=PID_NUM_DIGIT_EXT_OUT2, .valid=true, },
    {.num=PID_NUM_DIGIT_EXT_OUT1, .valid=true, },
};

uint32_t pid_get_cnt(void) {
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    uint32_t cnt = 0;
    cnt1 =  ARRAY_SIZE(PidConfig);
    cnt2 =  ARRAY_SIZE(PidInstance);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}




