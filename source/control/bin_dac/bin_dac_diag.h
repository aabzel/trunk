#ifndef BIN_DAC_DIAG_H
#define BIN_DAC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_dac_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BIN_DAC
#error "+HAS_BIN_DAC"
#endif

#ifndef HAS_BIN_DAC_DIAG
#error "+HAS_BIN_DAC_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool bin_dac_diag(void);
bool bin_dac_diag_one(uint8_t num);
bool bin_dac_show_sample(uint8_t num);
const char* BinDacConfigToStr(const BinDacConfig_t* const Config);
const char* BinDacNodeToStr(const BinDacHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* BIN_DAC_DIAG_H  */
