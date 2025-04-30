#ifndef ADC_NRF_DEP_H
#define ADC_NRF_DEP_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_ADC
#error "+HAS_ADC"
#endif /*HAS_ADC*/

#ifndef HAS_ADC1
#error "+HAS_ADC1"
#endif /*HAS_ADC1*/

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif /*HAS_GPIO*/

#ifndef NRFX_SAADC_ENABLED
#error "+NRFX_SAADC_ENABLED"
#endif /*NRFX_SAADC_ENABLED*/

#endif /* ADC_NRF_DEP_H  */
