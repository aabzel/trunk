#ifndef ADC_CUSTOM_TYPES_H
#define ADC_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_custom_const.h"
#include "stm32fx_hal.h"

#define ADC_CUSTOM_VARIABLES  \
       ADC_HandleTypeDef adc_h;

typedef struct {
    uint8_t resolution;
    uint32_t code;
    bool valid;
} AdcResolutionInfo_t;

typedef struct {
    uint8_t adc_num;
    ADC_TypeDef *instance;
    bool valid;
    int16_t irq_n;
} AdcInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_TYPES_H  */
