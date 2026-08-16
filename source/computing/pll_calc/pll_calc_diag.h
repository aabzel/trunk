#ifndef PLL_CALC_DIAG_H
#define PLL_CALC_DIAG_H

#include "std_includes.h"
#include "pll_types.h"


const char* PllArtetyToStr(const PllArtety_t*const PllArtety);
const char* PllConfigToStr(const PllFc7300Config_t* const Config);
const char* PllStm32ConfigToStr(const PllStm32Config_t * const Config);

bool pll_calc_stm_all(const uint32_t xtal_freq_hz, const uint32_t sys_freq_hz_step  );

#endif /* PLL_CALC_DIAG_H */
