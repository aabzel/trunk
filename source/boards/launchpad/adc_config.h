#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#ifdef HAS_ADC
#include "adc_drv.h"

#define ADC_ITEMS_CNT 1
extern const ADCItem_t AdcItemsLUT[ADC_ITEMS_CNT];
#endif

#endif /* ADC_CONFIG_H  */
