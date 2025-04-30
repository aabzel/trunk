#include "adc_config.h"

#include "adc_types.h"
#include "data_utils.h"
#include "sys_config.h"

/*constant compile-time known settings*/
const AdcConfig_t AdcConfig[] = {
    {
        .num = 1,
        .valid = true,
        .resolution = ADC_RESOLUTION_12BIT,
        .v_ref_voltage = 3.3,
    },
    {
        .num = 2,
        .valid = true,
        .resolution = ADC_RESOLUTION_12BIT,
        .v_ref_voltage = 3.3,
    },
    {
        .num = 3,
        .valid = true,
        .resolution = ADC_RESOLUTION_12BIT,
        .v_ref_voltage = 3.3,
    },
};

AdcHandle_t AdcInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
    {
        .num = 3,
        .valid = true,
    },
};

#define ADC_CONFIG(ADC_CHANNEL_LOGIC_NUM, ADC_X, CHANN, SCALE, SECUEN, NAME, PORT_X, PIN_X)                            \
    {                                                                                                                  \
        .num = ADC_CHANNEL_LOGIC_NUM,                                                                                  \
        .adc_num = ADC_X,                                                                                              \
        .channel = CHANN,                                                                                              \
        .scale = SCALE,                                                                                                \
        .sequence = SECUEN,                                                                                            \
        .name = #NAME,                                                                                                 \
        .valid = true,                                                                                                 \
        .Pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_X,                                                                                        \
                .pin = PIN_X,                                                                                          \
            },                                                                                                         \
    },

#define ADC_CONFIG_ALL                                                                                                 \
    ADC_CONFIG(ADC_CHANNEL_DIGIT_EXT1_IN, ADC_3, 14, 16.347594, 1, DIGIT_EXT1_IN, PORT_F, 4)                           \
    ADC_CONFIG(ADC_CHANNEL_DIGIT_EXT2_IN, ADC_3, 15, 16.347594, 2, DIGIT_EXT2_IN, PORT_F, 5)                           \
    ADC_CONFIG(ADC_CHANNEL_ADC_EXT1_IN, ADC_1, 0, 16.347594, 3, ADC_EXT1_IN, PORT_A, 0)                                \
    ADC_CONFIG(ADC_CHANNEL_ADC_EXT2_IN, ADC_2, 1, 16.347594, 4, ADC_EXT2_IN, PORT_A, 1)

const AdcChannelConfig_t AdcChannelConfig[] = {ADC_CONFIG_ALL};

AdcChannelHandle_t AdcChannelInstance[] = {
    {
        .num = ADC_CHANNEL_DIGIT_EXT1_IN,
        .valid = true,
    },
    {
        .num = ADC_CHANNEL_DIGIT_EXT2_IN,
        .valid = true,
    },
    {
        .num = ADC_CHANNEL_ADC_EXT1_IN,
        .valid = true,
    },
    {
        .num = ADC_CHANNEL_ADC_EXT2_IN,
        .valid = true,
    },

};

uint8_t adc_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}

uint8_t adc_channel_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(AdcChannelConfig);
    uint32_t cnt_ints = ARRAY_SIZE(AdcChannelInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
