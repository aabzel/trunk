#ifndef ADC_CUSTOM_TYPES_H
#define ADC_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "adc_custom_const.h"
#include "adc_types.h"
#include "artery_at32f4xx.h"
#include "gpio_types.h"

#define ADC_CUSTOM_VARIABLES   \
        adc_type *ADCx;

typedef struct {
    AdcNum_t adc_num;
    AdcChannel_t channel;
    //uint32_t code;
    Pad_t pad;
	bool valid;
	adc_channel_select_type artery_channel;
}AdcChannelInfo_t;

typedef struct {
	uint8_t resolution;
    uint32_t code;
	bool valid;
}AdcResolutionInfo_t;

typedef struct {
    uint8_t adc_num; /*ADC num (1 2 3)*/
    adc_type *ADCx; /*Reg map in PHY memory*/
    crm_periph_clock_type clock_type;
    bool valid;
}AdcInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_TYPES_H  */
