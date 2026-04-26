#ifndef DAC_CHANNEL_DIAG_H
#define DAC_CHANNEL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dac_channel_types.h"

#ifdef HAS_DAC_CHANNEL_CUSTOM
#include "dac_channel_custom_diag.h"
#endif

const char* DacChannelConfigToStr(const DacChannelConfig_t* const Config);
const char* DacChannelToStr(uint8_t channel);

bool DacChannelDiagConfig(DacChannelConfig_t* const Config);
bool dac_channel_diag(const char* const key_word1, const char* const key_word2);

#ifdef __cplusplus
}
#endif

#endif /* DAC_DIAG_H  */
