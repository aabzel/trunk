#ifndef BIN_DAC_ISR_H
#define BIN_DAC_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_dac_config.h"
#include "bin_dac_types.h"

bool bin_dac_tx_next_ll(BinDacHandle_t* const Node) ;
bool bin_dac_tx_done(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* BIN_DAC_ISR_H */
