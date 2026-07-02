#ifndef ADC_CHANNEL_CUSTOM_DRV_H
#define ADC_CHANNEL_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_types.h"
#include "adc_channel_mcal.h"
#include "adc_custom_const.h"
#include "adc_custom_types.h"
#include "stm32fx_hal.h"

#ifndef HAS_ADC
#error "+ HAS_ADC"
#endif

bool adc_channel_init(uint8_t adc_num, AdcChannel_t adc_channel);
bool adc_channel_read(uint8_t adc_num, uint16_t adc_channel, uint32_t* code);

bool adc_init(void);
bool adc_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* ADC_CHANNEL_CUSTOM_DRV_H  */
