#ifndef ADC_CHANNEL_CONFIG_H
#define ADC_CHANNEL_CONFIG_H

#include "adc_channel_types.h"
#include "sys_config.h"

extern const AdcChannelConfig_t AdcChannelConfig[];
extern AdcChannelHandle_t AdcChannelInstance[];

uint32_t adc_channel_get_cnt(void);

#endif /* ADC_CONFIG_H  */
