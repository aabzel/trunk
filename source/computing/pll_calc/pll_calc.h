#ifndef PLL_CALC_H
#define PLL_CALC_H

#include "std_includes.h"
#include "pll_calc_diag.h"
#include "pll_types.h"

bool pll_calc_artery_f43x(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety);
bool pll_calc_artery_f413(int32_t freq_xtal_hz, int32_t freq_sys_hz, PllArtety_t* const PllArtety);
bool pll_calc_artery(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety);
bool pll_calc_stm32_config(const uint32_t freq_xtal_hz, const uint32_t in_need_freq_sys_hz, PllStm32Config_t* const Config);
bool pll_stm32_is_valid_config(const PllStm32Config_t* const Config);

bool pll_calc_fc7300_config(const uint32_t in_freq_hz, const uint32_t set_freq_hz, PllFc7300Config_t* const Config);
int32_t pll_fc7300_calc(const PllFc7300Config_t* const Node);

int32_t Fc7ClockSourceToValue(const Fc7ClockPllSource_t source) ;
uint32_t Fc7ClockPostDivToValue(const Fc73xClockPostDiv_t post_div) ;

#endif /* PLL_CALC_H */
