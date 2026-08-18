#ifndef NAU8814_DIAG_H
#define NAU8814_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_types.h"

#ifdef HAS_NAU8814_ADC_DIAG
#include "nau8814_adc_diag.h"
#endif

#ifdef HAS_NAU8814_DAC_DIAG
#include "nau8814_dac_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_NAU8814
#error "+HAS_NAU8814"
#endif /*HAS_NAU8814*/

#ifndef HAS_NAU8814_DIAG
#error "+HAS_NAU8814_DIAG"
#endif /*HAS_DIAG_NAU8814*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

const char* Nau8814PllInfoToStr(const Nau8814PllInfo_t* const PllInfo);
const char* Nau8814ConfigToStr(const Nau8814Config_t* const Config);
const char* Nau8814NodeToStr(const Nau8814Handle_t* const Node);

const char* Nau8814RegAddrToName(Nau8814RegAddr_t addr);
bool nau8814_diag_low_level(uint8_t num, const char* const key_word);
bool nau8814_diag_high_level(uint8_t num);
bool nau8814_diag_pll(uint8_t num);
bool nau8814_reg_hazy(uint8_t num);
bool nau8814_reg_map_hidden_diag(uint8_t num);
bool nau8814_reg_map_diag(uint8_t num, char* key_word1, char* key_word2);

#endif /* NAU8814_DIAG_H  */
