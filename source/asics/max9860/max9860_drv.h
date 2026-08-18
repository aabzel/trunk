#ifndef MAX9860_DRV_H
#define MAX9860_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "max9860_config.h"
#include "max9860_const.h"
#include "max9860_dep.h"
#include "max9860_types.h"

#ifdef HAS_MAX9860_ADC
#include "max9860_adc_drv.h"
#endif

#ifdef HAS_MAX9860_DAC
#include "max9860_dac_drv.h"
#endif

extern const Max9860RegName_t RegNameLUT[];

uint32_t max9860_static_reg_cnt(void);
const Max9860RegName_t* max9860RegAddr2Node(Max9860RegAddr_t reg_addr);

bool max9860_check(void);
bool max9860_save_mode_set(void);
bool max9860_is_connected(void);
bool max9860_init(void);
bool max9860_interface_set(const Max9860Config_t* const Config);
bool max9860_bus_role_set(Max9860I2sRole_t i2s_role);
bool max9860_sample_rate_set(const Max9860Config_t* const Config);
bool max9860_reg_set(uint8_t reg_addr, uint8_t reg_val);
bool max9860_reg_set_verify(uint8_t reg_addr, uint8_t reg_val);
bool max9860_reg_get(uint8_t reg_addr, uint8_t* const reg_val);
bool max9860_is_valid_addr(uint8_t reg_addr);
bool max9860_reg_read_all(void);
bool max9860_proc(void);
bool max9860_write_lazy_reg(uint8_t reg_addr, uint8_t reg_val);
bool max9860_write_reg_by_bitmask(uint8_t reg_addr, char* bit_mask);
bool max9860_reset(void);
bool is_valid_voice_filter(DigitalFilter_t digital_filter);
bool max9860_voice_filter_set(Converter_t converter, DigitalFilter_t digital_filter);
Max9860I2sRole_t max9860_bus_role_get(void);
uint32_t max9860_reg_cnt(void);
DigitalFilter_t max9860_voice_filter_get(Converter_t converter);
uint32_t max9860_pcm_2_32bit_sample(int32_t tx_sample);

#endif /* MAX9860_DRV_H */
