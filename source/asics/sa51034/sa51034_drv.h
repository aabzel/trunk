#ifndef SA51034_DRV_H
#define SA51034_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "sa51034_config.h"
#include "sa51034_types.h"
#ifdef HAS_SA51034_DIAG
#include "sa51034_diag.h"
#endif

/*map functions*/
Gain_t Sa51GainCodeToGain(Sa51GainCode_t code);

double Sa51PowerLimitCodeToVolts(Sa51PowerLimit_t code);

Sa51SwFrequency_t Sa51FrequencyToCode(uint32_t frequency_hz);
uint32_t Sa51FrequencyCodeToHz(Sa51SwFrequency_t f_code);

extern const Sa51034RegInfo_t Sa51RegInfo[];

uint32_t sa51034_static_reg_cnt(void);

/*API*/
Sa51034Handle_t* Sa51034GetNode(uint8_t num);
const Sa51034Config_t* Sa51034GetConfig(uint8_t num);
const Sa51034RegInfo_t* Sa51034RegAddrToInfo(Sa51034RegAddr_t addr);
bool sa51034_mcal_init(void);
bool sa51034_proc(void);
bool sa51034_init_one(uint8_t num);
bool sa51034_proc_one(uint8_t num);
bool sa51034_check(uint8_t num);
bool sa51034_is_connected(uint8_t num);
bool sa51034_is_valid_addr(uint8_t reg_addr);
bool sa51034_init_custom(void);

/*getters*/
bool sa51034_reg_read(uint8_t num, Sa51034RegAddr_t reg_addr, uint8_t* const reg_val);
bool sa51034_reg_read_ll(Sa51034Handle_t* Node, Sa51034RegAddr_t addr, uint8_t* const reg_val);
bool sa51034_reg_read_all(uint8_t num);
bool sa51034_gain_get(uint8_t num, Gain_t* const gain_db);
bool sa51034_frequency_get(uint8_t num, uint32_t* const frequency_hz);
bool sa51034_power_limit_get(uint8_t num, double* const power_limit);
uint32_t sa51034_reg_cnt(void);

/*setters*/
bool sa51034_power_limit_set(uint8_t num, double power_limit);
bool sa51034_frequency_set(uint8_t num, uint32_t frequency_hz);
bool sa51034_gain_set(uint8_t num, Gain_t gain_db);
bool sa51034_reg_write_ll(Sa51034Handle_t* Node, Sa51034RegAddr_t addr, uint8_t value);
bool sa51034_reg_write(uint8_t num, Sa51034RegAddr_t reg_addr, uint8_t reg_val);
bool sa51034_reg_write_verify(uint8_t num, Sa51034RegAddr_t reg_addr, uint8_t value);
bool sa51034_reg_write_lazy(uint8_t num, Sa51034RegAddr_t reg_addr, uint8_t value);
bool sa51034_reg_write_by_bitmask(uint8_t num, Sa51034RegAddr_t reg_addr, char* bit_mask);
bool sa51034_reset(uint8_t num);

#endif /* SA51034_DRV_H */
