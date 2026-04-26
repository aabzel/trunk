#ifndef ADC_CUSTOM_ISR_H
#define ADC_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ADC
#error "+ HAS_ADC"
#endif

#include "stm32f4xx_hal.h"

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);


#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_ISR_H  */
