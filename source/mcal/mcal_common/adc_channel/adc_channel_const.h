#ifndef ADC_CHANNEL_GENERAL_CONST_H
#define ADC_CHANNEL_GENERAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_ADC_CHANNEL_CUSTOM
#include "adc_channel_custom_const.h"
#endif

#include "adc_channel_dep.h"
#include "bit_const.h"
#include "time_mcal.h"

#define ADC_CHANNEL_PERIOD_US MSEC_2_USEC(5)

typedef enum {
    ADC_CHAN_0 = 0,
    ADC_CHAN_1 = 1,
    ADC_CHAN_2 = 2,
    ADC_CHAN_3 = 3,
    ADC_CHAN_4 = 4,
    ADC_CHAN_5 = 5,
    ADC_CHAN_6 = 6,
    ADC_CHAN_7 = 7,
    ADC_CHAN_8 = 8,
    ADC_CHAN_9 = 9,
    ADC_CHAN_10 = 10,
    ADC_CHAN_11 = 11,
    ADC_CHAN_12 = 12,
    ADC_CHAN_13 = 13,
    ADC_CHAN_14 = 14,
    ADC_CHAN_15 = 15,
    ADC_CHAN_16 = 16,
    ADC_CHAN_17 = 17,
    ADC_CHAN_18 = 18,

    ADC_CHAN_UNDEF = 19,
} AdcChannel_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_GENERAL_CONST_H  */
