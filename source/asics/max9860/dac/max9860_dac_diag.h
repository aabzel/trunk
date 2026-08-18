#ifndef MAX9860_DAC_DIAG_H
#define MAX9860_DAC_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_MAX9860
#error "+HAS_MAX9860"
#endif /*HAS_MAX9860*/

#ifndef HAS_MAX9860_DIAG
#error "+HAS_MAX9860_DIAG"
#endif /*HAS_DIAG_MAX9860*/

#ifndef HAS_MAX9860_DAC_DIAG
#error "+HAS_MAX9860_DAC_DIAG"
#endif /*HAS_MAX9860_DAC_DIAG*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* AdcSideToneGainToStr(uint8_t dvst_code);
const char* DacBitClockInvertToStr(DacBitClkInvert_t dbci);
const char* DacDelayModeToStr(DacDelay_t ddly);
const char* DacGainToStr(DacGainCode_t dvg_code);
const char* DacLevelAttenuationToStr(uint8_t dva_code);

#endif /* MAX9860_DAC_DIAG_H  */
