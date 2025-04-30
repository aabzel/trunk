#ifndef PLL_CALC_H
#define PLL_CALC_H


#include <std_includes.h>

#include "pll_calc_diag.h"
#include "pll_types.h"

#ifdef HAS_AT32F43X
bool pll_calc_artery_f43x(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety);
#endif

#ifdef HAS_AT32F413
bool pll_calc_artery_f413(int32_t freq_xtal_hz, int32_t freq_sys_hz, PllArtety_t* const PllArtety);
#endif
bool pll_calc_artery(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety);

#endif /* PLL_CALC_H */
