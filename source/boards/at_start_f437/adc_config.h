#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#include "adc_types.h"

typedef enum {
    ADC_CHANNEL_ADC_EXT1_IN = 1,
    ADC_CHANNEL_ADC_EXT2_IN = 2,
    ADC_CHANNEL_DIGIT_EXT1_IN = 3,
    ADC_CHANNEL_DIGIT_EXT2_IN = 4,

    ADC_CHANNEL_UNDEF = 9,
} AtStartAdcChannel_t;

/*constant compile-time known settings*/
extern const AdcConfig_t AdcConfig[];
extern const AdcChannelConfig_t AdcChannelConfig[];

extern AdcHandle_t AdcInstance[];
extern AdcChannelHandle_t AdcChannelInstance[];

uint8_t adc_get_cnt(void);
uint8_t adc_channel_get_cnt(void);

#endif /* ADC_CONFIG_H */
