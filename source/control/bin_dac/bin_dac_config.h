#ifndef BIN_DAC_CONFIG_H
#define BIN_DAC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_dac_types.h"
#include "bin_dac_dep.h"

#define BIN_DAC_TX_SIZE 1000

extern const BinDacConfig_t BinDacConfig[];
extern BinDacHandle_t BinDacInstance[];

uint32_t bin_dac_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* BIN_DAC_CONFIG_H */
