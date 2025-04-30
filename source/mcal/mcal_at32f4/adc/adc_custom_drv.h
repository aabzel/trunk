#ifndef ADC_CUSTOM_DRV_H
#define ADC_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "adc_mcal.h"
#include "adc_custom_types.h"
#include "adc_custom_isr.h"
#include "adc_types.h"
#include "artery_at32f4xx.h"

bool adc_init_channel(uint8_t adc_num, AdcChannel_t channel);
bool adc_init(void);
bool adc_proc(void);
bool adc_channel_read(uint8_t adc_num, uint16_t channel, uint32_t* code);
const AdcInfo_t* AdcGetInfo(uint8_t num);
#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_DRV_H  */
