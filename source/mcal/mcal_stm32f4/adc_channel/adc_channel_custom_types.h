#ifndef ADC_CHANNEL_STM_TYPES_H
#define ADC_CHANNEL_STM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_custom_const.h"
#include "adc_types.h"
#include "stm32f4xx_hal.h"

#define ADC_CHANNEL_CUSTOM_VARIABLES

typedef struct {
    AdcNum_t num;
    AdcChannel_t adc_channel;
    uint32_t code;
    Pad_t pad;
    bool valid;
} AdcChannelInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_CHANNEL_STM_TYPES_H  */
