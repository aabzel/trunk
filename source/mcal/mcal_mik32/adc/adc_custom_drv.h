
#ifndef ADC_CUSTOM_DRV_H
#define ADC_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "adc_drv.h"
#include "adc_custom_const.h"
#include "adc_custom_types.h"
#include "adc_types.h"
#include "mik32_hal.h"

#ifndef HAS_ADC
#error "+ HAS_ADC"
#endif

bool adc_init_channel(uint8_t adc_num, AdcChannel_t adc_channel);
bool adc_init(void);
bool adc_proc(void);
bool adc_channel_read(uint8_t adc_num, uint16_t adc_channel, uint32_t* code);

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_DRV_H  */
