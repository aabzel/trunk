#ifndef MAX9860_DIAG_H
#define MAX9860_DIAG_H

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

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool max9860_diag_low_level(const char* const key_word);
bool max9860_diag_high_level(void);
bool max9860_reg_map_hidden_diag(void);
bool max9860_reg_map_diag(char* key_word1, char* key_word2);
const char* MasterModeToStr(uint8_t mas);
const char* LrClkInvertToStr(uint8_t wci);
const char* TdmModeToStr(uint8_t tdm);
const char* StereoToStr(Stereo_t stereo);
const char* BitClkToStr(BitClockSelect_t bsel);
const char* Max9860I2sRoleToStr(Max9860I2sRole_t i2s_role);
const char* Max9860RegAddr2Name(Max9860RegAddr_t addr);
const char* Max9860StereoToStr(MaxStereo_t stereo);

#endif /* MAX9860_DIAG_H  */
