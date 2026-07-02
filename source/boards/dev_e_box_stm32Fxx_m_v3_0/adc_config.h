#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#include "adc_types.h"
#include "sys_config.h"

#define ADC_NUM 1

extern const AdcConfig_t AdcConfig[ADC_NUM];
extern const AdcChannelConfig_t AdcChannelConfig[];
extern AdcHandle_t AdcInstance[ADC_NUM];
extern AdcChannelHandle_t AdcChannels[];

uint32_t adc_get_cnt(void);
uint32_t adc_channel_get_cnt(void);

#endif /* ADC_CONFIG_H  */
