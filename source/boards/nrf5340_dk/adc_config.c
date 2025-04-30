#include "adc_config.h"

#include "data_utils.h"
#include "adc_types.h"
#include "sys_config.h"

/*constant compile-time known settings*/
const AdcConfig_t AdcConfig[1] = {
    { .num=1, .valid=true, .resolution=ADC_RESOLUTION_12BIT, },
};

AdcHandle_t AdcInstance[1] = {
    {.num=1, .valid=true,},
};

const AdcChannelConfig_t AdcChannelConfig[] = {
 // {.num=ADC_1, .channel=7,  .name="AIN7", .valid=true},
    {.num=ADC_1, .channel=6,  .name="AIN6", .valid=true},
    {.num=ADC_1, .channel=5,  .name="AIN5", .valid=true},
 // {.num=ADC_1, .channel=4,  .name="AIN4", .valid=true},
 // {.num=ADC_1, .channel=3,  .name="AIN3", .valid=true},
 // {.num=ADC_1, .channel=2,  .name="AIN2", .valid=true},
    {.num=ADC_1, .channel=1,  .name="AIN1", .valid=true},
    {.num=ADC_1, .channel=0,  .name="AIN0", .valid=true}
};

AdcChannelHandle_t AdcChannels[] = {
    {.num=1, .channel=ADC_CHAN_0,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_1,  .valid=true, .code=0,},
  //{.num=1, .channel=ADC_CHAN_2,  .valid=true, .code=0,},
  //{.num=1, .channel=ADC_CHAN_3,  .valid=true, .code=0,},
  //{.num=1, .channel=ADC_CHAN_4,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_5,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_6,  .valid=true, .code=0,},
  //{.num=1, .channel=ADC_CHAN_7,  .valid=true, .code=0,},
};

uint8_t adc_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcInstance);
    if (cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}

uint8_t adc_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcChannelConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcChannels);
    if (cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}


