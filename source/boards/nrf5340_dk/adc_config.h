
#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#include "adc_types.h"

#define ADC_CHAN_WITH_1_5V (ADC_CHAN_0)
#define ADC_CHAN_WITH_3V (ADC_CHAN_1)
#define ADC_CHAN_WITH_0V (ADC_CHAN_5)

/*constant compile-time known settings*/
extern const AdcConfig_t AdcConfig[];
extern const AdcChannelConfig_t AdcChannelConfig[];

extern AdcHandle_t AdcInstance[];
extern AdcChannelHandle_t AdcChannels[];

uint8_t adc_get_cnt(void) ;
uint8_t adc_channel_get_cnt(void);

#endif /* ADC_CONFIG_H */
