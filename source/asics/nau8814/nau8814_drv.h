#ifndef NAU8814_DRV_H
#define NAU8814_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "nau8814_config.h"
#include "nau8814_dep.h"
#include "nau8814_types.h"
#ifdef HAS_NAU8814_DIAG
#include "nau8814_diag.h"
#endif

#ifdef HAS_NAU8814_ADC
#include "nau8814_adc.h"
#endif

#ifdef HAS_NAU8814_DAC
#include "nau8814_dac.h"
#endif

/*map functions*/
uint8_t NauPllNcodeToValue(NauPllN_t code);
NauPllN_t NauPllNToCode(uint8_t plln);

uint8_t NauPllDcodeToValue(NauPllMclk_t d_code);
double NauMasterClockSelectionToValue(NauMclkSel_t code);

extern const Nau8814RegInfo_t RegInfo[];

uint32_t nau8814_static_reg_cnt(void);

/*API*/
uint16_t nau8814_make_frame(Nau8814RegAddr_t addr, uint16_t reg_value);
uint8_t nau8814_compose_register_address(uint8_t const register_address);
Nau8814Handle_t* Nau8814GetNode(uint8_t num);
const Nau8814Config_t* Nau8814GetConfig(uint8_t num);
const Nau8814RegInfo_t* Nau8814RegAddrToInfo(Nau8814RegAddr_t addr);
bool nau8814_mcal_init(void);
bool nau8814_proc(void);
bool nau8814_pll_init(uint8_t num);
bool nau8814_init_one(uint8_t num);
bool nau8814_proc_one(uint8_t num);
bool nau8814_check(uint8_t num);
bool nau8814_is_connected(uint8_t num);
bool nau8814_is_valid_addr(uint8_t reg_addr);
bool nau8814_init_custom(void);
bool nau8814_calc_pll(uint32_t mclk_hz, uint32_t fs_hz, uint32_t k_step);

/*getters*/
bool nau8814_reg_read(uint8_t num, Nau8814RegAddr_t reg_addr, uint16_t* const reg_val);
bool nau8814_reg_read_ll(Nau8814Handle_t* Node, Nau8814RegAddr_t addr, uint16_t* const word);
bool nau8814_reg_read_all(uint8_t num);
bool nau8814_i2s_role_get(uint8_t num, IfBusRole_t* const i2s_role);
bool nau8814_pll_k_get(uint8_t num, uint32_t* const pll_k);
bool nau8814_pll_d_get(uint8_t num, uint8_t* const pll_d);
bool nau8814_pll_n_get(uint8_t num, uint8_t* const pll_n);
bool nau8814_master_clock_div_get(uint8_t num, double* const divider);
uint32_t nau8814_reg_cnt(void);

/*setters*/
bool nau8814_reg_write_ll(Nau8814Handle_t* Node, Nau8814RegAddr_t addr, uint16_t word);
bool nau8814_reg_write(uint8_t num, Nau8814RegAddr_t reg_addr, uint16_t reg_val);
bool nau8814_pll_k_set(uint8_t num, uint32_t pll_k);
bool nau8814_pll_n_set(uint8_t num, uint8_t plln);
bool nau8814_reg_write_verify(uint8_t num, Nau8814RegAddr_t reg_addr, uint16_t word);
bool nau8814_reg_write_lazy(uint8_t num, Nau8814RegAddr_t reg_addr, uint16_t word);
bool nau8814_reg_write_by_bitmask(uint8_t num, Nau8814RegAddr_t reg_addr, char* bit_mask);
bool nau8814_reset(uint8_t num);
bool nau8814_i2s_role_set(uint8_t num, IfBusRole_t i2s_role);

#endif /* NAU8814_DRV_H */
