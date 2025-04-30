#include "adc_config.h"

#include "log_config.h"
#include "data_utils.h"
#include "adc_const.h"

/*constant compile-time known settings*/
const AdcConfig_t AdcConfig[] = {
#ifdef HAS_ADC1
    { .num=1, .valid=true, .resolution=12, },
#endif

};

AdcHandle_t AdcInstance[]={
#ifdef HAS_ADC1
    {.num=1, .valid=true,    },
#endif

};

const AdcChannelConfig_t AdcChannelConfig[]={
#ifdef HAS_ADC1
    {.num=1, .channel=ADC_CHAN_0,  .name="Ch0", .valid=true,},
    {.num=1, .channel=ADC_CHAN_1,  .name="Ch1", .valid=true,},
    {.num=1, .channel=ADC_CHAN_2,  .name="Ch2", .valid=true,},
    {.num=1, .channel=ADC_CHAN_3,  .name="Ch3", .valid=true,},
    {.num=1, .channel=ADC_CHAN_4,  .name="Ch4", .valid=true,},
    {.num=1, .channel=ADC_CHAN_5,  .name="Ch5", .valid=true,},
    {.num=1, .channel=ADC_CHAN_6,  .name="Ch6", .valid=true,},
    {.num=1, .channel=ADC_CHAN_7,  .name="Ch7", .valid=true,},
    {.num=1, .channel=ADC_CHAN_8,  .name="Ch8", .valid=true,},
    {.num=1, .channel=ADC_CHAN_9,  .name="Ch9", .valid=true,},
    {.num=1, .channel=ADC_CHAN_10, .name="Ch10", .valid=true,},
    {.num=1, .channel=ADC_CHAN_11, .name="Ch11", .valid=true,},
    {.num=1, .channel=ADC_CHAN_12, .name="Ch12", .valid=true,},
    {.num=1, .channel=ADC_CHAN_13, .name="Ch13", .valid=true,},
    {.num=1, .channel=ADC_CHAN_14, .name="Ch14", .valid=true,},
    {.num=1, .channel=ADC_CHAN_15, .name="Ch15", .valid=true,},
    {.num=1, .channel=ADC_CHAN_16, .name="Ch16", .valid=true,},
    {.num=1, .channel=ADC_CHAN_17, .name="Ch17", .valid=true,},
    {.num=1, .channel=ADC_CHAN_18, .name="Ch18", .valid=true,},
#endif

};

AdcChannelHandle_t AdcChannels[]={
#ifdef HAS_ADC1
    {.num=1, .channel=ADC_CHAN_0,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_1,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_2,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_3,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_4,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_5,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_6,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_7,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_8,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_9,  .valid=true, .code=0,},
    {.num=1, .channel=ADC_CHAN_10,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_11,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_12,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_13,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_14,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_15,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_16,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_17,  .valid=true,.code=0,},
    {.num=1, .channel=ADC_CHAN_18,  .valid=true,.code=0,},
#endif

};

uint32_t adc_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcInstance);
    if(cnt_conf==cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}

uint32_t adc_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcChannelConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcChannels);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}


