#ifndef ADC_DIAG_H
#define ADC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_diag.h"
#endif

#include "adc_types.h"

const char* AdcConfigToStr(const AdcConfig_t* const Config);
const char* AdcNodeToStr(const AdcHandle_t* const Node);
const char* AdcChannelConfigToStr(const AdcChannelConfig_t* const Config);
bool AdcDiagConfigChannel(AdcChannelConfig_t* const Config);

const char* AdcNum2Str(uint8_t adr_num);
const char* AdcChannel2Str(uint8_t channel);

bool adc_channel_diag(const char* const key_word1, const char* const key_word2);
bool adc_diag_isr(const char* const key_word1, const char* const key_word2);
bool adc_diag(const char* const key1, const char* const key2);

#ifdef __cplusplus
}
#endif

#endif /* ADC_DIAG_H  */
