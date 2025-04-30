#ifndef ADC_NRF5340_CONST_H
#define ADC_NRF5340_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adc_dep.h"

#define ADC_CONV_DONE_TIME_OUT_MS 1000
#define ADC_CONV_MAX_TIME_MS 2
/*TODO to figure out*/

#define ADC_REF_VOLTAGE (3.0)
#define CODE_AT_3V (3393.0)
#define CROSS_CODE_VOLTAGE (ADC_REF_VOLTAGE / CODE_AT_3V)

/*see page 523*/
#define ADC_BITNESS 12 /*TODO to figure out*/

typedef enum {
    ADC_OVERSAMPLING_BYPASS = 0,
    ADC_OVERSAMPLING_2X = 1,
    ADC_OVERSAMPLING_4X = 2,
    ADC_OVERSAMPLING_8X = 3,
    ADC_OVERSAMPLING_16X = 4,
    ADC_OVERSAMPLING_32X = 5,
    ADC_OVERSAMPLING_64X = 6,
    ADC_OVERSAMPLING_128X = 7,
    ADC_OVERSAMPLING_256X = 8,
    ADC_OVERSAMPLING_UNDEF = 9,
} AdcOversample_t;

#ifdef __cplusplus
}
#endif

#endif /* ADC_NRF5340_CONST_H  */
