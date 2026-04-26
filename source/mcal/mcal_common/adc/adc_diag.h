#ifndef ADC_DIAG_H
#define ADC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_types.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_diag.h"
#endif

const char* AdcConfigToStr(const AdcConfig_t* const Config);

const char* AdcNodeToStr(const AdcHandle_t* const Node);
const char* AdcNumToStr(uint8_t adc_num);
bool adc_diag_isr(const char* const key_word1, const char* const key_word2);
bool adc_diag(const char* const key1, const char* const key2);

#ifdef __cplusplus
}
#endif

#endif /* ADC_DIAG_H  */
