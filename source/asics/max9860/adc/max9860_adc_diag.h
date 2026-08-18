#ifndef MAX9860_ADC_DIAG_H
#define MAX9860_ADC_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_adc_const.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_MAX9860
#error "+HAS_MAX9860"
#endif /*HAS_MAX9860*/

#ifndef HAS_MAX9860_DIAG
#error "+HAS_MAX9860_DIAG"
#endif /*HAS_DIAG_MAX9860*/

#ifndef HAS_MAX9860_ADC_DIAG
#error "+HAS_MAX9860_ADC_DIAG"
#endif /*HAS_MAX9860_ADC_DIAG*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* NoiseGateAttenuationToStr(NoiseGateAttenuation_t ng_code);
const char* SdOutHighInpedanceModeToStr(HighImpedanceZ_t hiz);
const char* AdcBitClkInvertToStr(AdcBitClkInvert_t abci);
const char* AdcDelayToStr(AdcDelayMode_t adly);
const char* AdcOutputLevelToStr(uint8_t adcrl);
const char* MicrophonePreampGainToStr(AdcPreampGain_t pam);
const char* MicrophoneProgrammableGainAmplifierToStr(uint8_t pgam);
const char* AdcLeftEnToStr(AdcEnable_t code);
const char* AdcRightEnToStr(AdcEnable_t code);
const char* AGCSRCToStr(AGCSrc_t code);
const char* AGCReleaseTimeToStr(AGCReleaseTime_t code);
const char* AGCAttackTimeToStr(AGCAttackTime_t code);
const char* AGCHoldTimeToStr(AGCHoldTime_t code);

#endif /* MAX9860_ADC_DIAG_H  */
