#ifndef ADC_CHANNEL_DIAG_H
#define ADC_CHANNEL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "adc_channel_types.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_diag.h"
#endif

const char* AdcChannelConfigToStr(const AdcChannelConfig_t* const Config);
const char* AdcChannelToStr(uint8_t channel);

bool AdcDiagConfigChannel(AdcChannelConfig_t* const Config);
bool adc_channel_diag(const char* const key_word1, const char* const key_word2);

#ifdef __cplusplus
}
#endif

#endif /* ADC_DIAG_H  */
