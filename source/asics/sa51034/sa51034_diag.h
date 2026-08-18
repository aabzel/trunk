#ifndef SA51034_DIAG_H
#define SA51034_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "sa51034_types.h"


#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SA51034
#error "+HAS_SA51034"
#endif /*HAS_SA51034*/

#ifndef HAS_SA51034_DIAG
#error "+HAS_SA51034_DIAG"
#endif /*HAS_DIAG_SA51034*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

uint32_t Sa51FrequencyCodeToHz(Sa51SwFrequency_t code);
Gain_t Sa51GainCodeToGain(Sa51GainCode_t code);
const char* Sa51034ConfigToStr(const Sa51034Config_t* const Config);
const char* Sa51034NodeToStr(const Sa51034Handle_t* const Node);

const char* Sa51034RegAddrToName(Sa51034RegAddr_t addr);
bool sa51034_diag_low_level(uint8_t num, const char* const key_word);
bool sa51034_diag_high_level(uint8_t num);
bool sa51034_diag_pll(uint8_t num);
bool sa51034_reg_hazy(uint8_t num);
bool sa51034_reg_map_hidden_diag(uint8_t num);
bool sa51034_reg_map_diag(uint8_t num, char* key_word1, char* key_word2);

#endif /* SA51034_DIAG_H  */
