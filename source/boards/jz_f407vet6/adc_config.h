#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#include "adc_types.h"
#include "sys_config.h"

#define ADC_REF_VOLTAGE (3.3f)

#define ADC1_RX_SAMPLE_CNT 1024
extern uint16_t Adc1RxSamples[ADC1_RX_SAMPLE_CNT];

extern const AdcConfig_t AdcConfig[];
extern AdcHandle_t AdcInstance[];

uint32_t adc_get_cnt(void);

#endif /* ADC_CONFIG_H  */
