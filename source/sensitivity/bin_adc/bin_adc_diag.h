#ifndef BIN_ADC_DIAG_H
#define BIN_ADC_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_adc_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_BIN_ADC
#error "+HAS_BIN_ADC"
#endif

#ifndef HAS_BIN_ADC_DIAG
#error "+HAS_BIN_ADC_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool bin_adc_diag(void);
bool bin_adc_diag_one(uint8_t num);
bool bin_adc_show_sample(uint8_t num);
bool bin_adc_raw_reg_diag(uint8_t num);
const char* BinAdcConfigToStr(const BinAdcConfig_t* const Config);
const char* BinAdcNodeToStr(const BinAdcHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* BIN_ADC_DIAG_H  */
