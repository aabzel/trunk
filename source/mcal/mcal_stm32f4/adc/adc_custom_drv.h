
#ifndef ADC_CUSTOM_DRV_H
#define ADC_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_mcal.h"
#include "adc_custom_const.h"
#include "adc_custom_types.h"
#include "adc_types.h"
#include "stm32f4xx_hal.h"
#include "adc_channel_const.h"

#ifndef HAS_ADC
#error "+ HAS_ADC"
#endif

bool adc_init(void);
bool adc_proc(void);
uint8_t ADC_HandleTypeDefToNum(const ADC_HandleTypeDef* const hadc);
AdcHandle_t* AdcHalHandle2Handle(const ADC_HandleTypeDef* const hadc);

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_DRV_H  */
