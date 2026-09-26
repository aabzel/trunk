#ifndef BIN_ADC_CONFIG_H
#define BIN_ADC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_adc_types.h"
#include "bin_adc_dep.h"

#define BIN_ADC_SAMPLE_CNT 480

extern const BinAdcConfig_t BinAdcConfig[];
extern BinAdcHandle_t BinAdcInstance[];

uint32_t bin_adc_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* BIN_ADC_CONFIG_H */
