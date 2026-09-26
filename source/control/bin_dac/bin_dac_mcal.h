#ifndef BIN_DAC_MCAL_H
#define BIN_DAC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_dac_config.h"
#include "bin_dac_types.h"
#include "bin_dac_isr.h"

#ifdef HAS_BIN_DAC_DIAG
#include "bin_dac_diag.h"
#endif


/* API */
BinDacHandle_t* BinDacGetNode(uint8_t num);
const BinDacConfig_t* BinDacGetConfig(uint8_t num);
bool BinDacIsValidConfig(const BinDacConfig_t* const Config);

#ifdef HAS_BIN_DAC_CUSTOM
const BinDacInfo_t* BinDacGetInfo(uint8_t num);
#endif

bool bin_dac_mcal_init(void);
bool bin_dac_init_custom(void);
bool bin_dac_init_common(const BinDacConfig_t* const Config, BinDacHandle_t* const Node);
bool bin_dac_init_node(BinDacHandle_t* const Node);
bool bin_dac_init_one(uint8_t num);

bool bin_dac_proc_one(uint8_t num);
bool bin_dac_proc(void);

/*setters*/
bool bin_dac_tx_next(const uint8_t num);
bool bin_dac_tx_pad_set(uint8_t num, const Pad_t txPad);
bool bin_dac_part_size_set(const uint8_t num, const uint32_t part_size);
bool bin_dac_sample_freq_set(uint8_t num, const uint32_t sample_freq_hz);
bool bin_dac_sample_tx_ll( BinDacHandle_t *Node, const uint8_t* const bit_values, const uint32_t size);
bool bin_dac_sample_tx(uint8_t num, const uint8_t* const data, const uint32_t size);
bool bin_dac_bsrr_tx(uint8_t num, const uint32_t* const data_bsrr, const uint32_t size);
bool bin_dac_push_samples(uint8_t num, const uint8_t* const bit_values, const uint32_t size);

/*getters*/
int32_t bin_dac_fifo_cnt_get(const uint8_t num);
bool bin_dac_is_valid_num(const uint8_t num);
uint32_t bin_dac_sample_freq_get(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* BIN_DAC_MCAL_H */
