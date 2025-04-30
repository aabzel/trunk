#ifndef ADC_ISR_H
#define ADC_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "adc_dep.h"
#include "adc_drv.h"
#include "nrfx_saadc.h"

#ifndef HAS_ADC_ISR
#error "+HAS_ADC_ISR"
#endif /*HAS_ADC_ISR*/

void nrfx_saadc_event_handler(nrfx_saadc_evt_t const* p_event);

#ifdef __cplusplus
}
#endif

#endif /* ADC_ISR_H */
