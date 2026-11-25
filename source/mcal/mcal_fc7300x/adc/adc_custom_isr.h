#ifndef ADC_CUSTOM_ISR_H
#define ADC_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

bool AdcIRQHandler(uint8_t num) ;

#ifdef __cplusplus
}
#endif

#endif /* ADC_CUSTOM_ISR_H  */
