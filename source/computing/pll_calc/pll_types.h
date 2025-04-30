#ifndef PLL_CALC_TYPES_H
#define PLL_CALC_TYPES_H

#include <stdint.h>

#include "pll_calc_const.h"

typedef struct {
    uint32_t xtall_freq_hz;
    uint32_t core_freq_hz;
#ifdef HAS_AT32F43X
    uint32_t ms; //
    uint32_t ns; //
    uint32_t fr;
#endif

#ifdef HAS_AT32F413
    uint32_t pllhexdiv; // divider
    uint32_t pllmult; // mult
#endif
}PllArtety_t;

#endif /* PLL_CALC_TYPES_H */
