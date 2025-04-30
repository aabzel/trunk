#ifndef ADC_STM_TYPES_H
#define ADC_STM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "adc_custom_const.h"
#include "adc_types.h"
#include "stm32f4xx_hal.h"

typedef struct {
    AdcNum_t num;
    AdcChannel_t adc_channel;
    uint32_t code;
    Pad_t pad;
	bool valid;
}AdcChannelInfo_t;

typedef struct {
	uint8_t resolution;
    uint32_t code;
	bool valid;
}AdcResolutionInfo_t;

typedef struct {
	uint8_t adc_num;
	ADC_TypeDef* instance;
	bool valid;
}AdcInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* ADC_STM_TYPES_H  */
