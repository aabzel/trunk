#ifndef BIN_ADC_MCAL_H
#define BIN_ADC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bin_adc_config.h"
#include "bin_adc_types.h"

#ifdef HAS_BIN_ADC_DIAG
#include "bin_adc_diag.h"
#endif

/* API */
BinAdcHandle_t* BinAdcGetNode(uint8_t num);
const BinAdcConfig_t* BinAdcGetConfig(uint8_t num);
bool BinAdcIsValidConfig(const BinAdcConfig_t* const Config);

#ifdef HAS_BIN_ADC_CUSTOM
const BinAdcInfo_t* BinAdcGetInfo(uint8_t num);
#endif

bool bin_adc_mcal_init(void);
bool bin_adc_init_custom(void);
bool bin_adc_init_common(const BinAdcConfig_t* const Config, BinAdcHandle_t* const Node);
bool bin_adc_init_node(BinAdcHandle_t* const Node);
bool bin_adc_init_one(uint8_t num);

bool bin_adc_proc_one(uint8_t num);
bool bin_adc_proc(void);

/*setters*/
bool bin_adc_rx_pad_set(const uint8_t  num, const Pad_t inPad);
bool bin_adc_sample_freq_set(const uint8_t num, const uint32_t sample_frequency_hz);
bool bin_adc_start(const uint8_t num);

/*getters*/
bool bin_adc_is_valid_num(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* BIN_ADC_MCAL_H */
