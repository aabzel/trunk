#ifndef PLL_CALC_TYPES_H
#define PLL_CALC_TYPES_H

#include <stdint.h>

#include "pll_calc_const.h"

typedef struct {
    int32_t error_freq_hz; /* Frequency setting error   */
    uint32_t xtall_freq_hz; /* HSE   */
    int32_t core_freq_hz; /*    SYSCLK */
    uint32_t M; /*  HSE/M M=[2...63] */
    uint32_t N; /*  N*(HSE/M)  N=[50.....432]   */
    uint32_t P; /*  (N*(HSE/M))/P P=[2; 4; 6; 8]*/
    uint32_t Q; /*  (N*(HSE/M))/Q (must be 48MHz) Q=[2...15] */
}PllStm32Config_t;


typedef struct {
    uint32_t xtall_freq_hz;
    uint32_t core_freq_hz;
//#ifdef HAS_AT32F43X
    uint32_t ms; //
    uint32_t ns; //
    uint32_t fr;
//#endif

//#ifdef HAS_AT32F413
    uint32_t pllhexdiv; // divider
    uint32_t pllmult; // mult
//#endif
}PllArtety_t;


typedef struct {
    /*SCG_PLL0CFG  SOURCE  Configures the input clock source for PLL   0 1*/
    uint8_t source;

    /*PLL Reference Clock Divider 0...31*/
    uint8_t pre_div;

    /*PLL Post Divider 0, 1, 2, 3*/
    uint8_t post_div;

    /*PLL Multiplier Multiplier = MULT bits + 1 Note: Multiplier needs to be greater than 96 (MULT needs to be greater than 95).*/
    uint16_t mult;

    /*DIVCORE After main clock select mux (2bit) Valid */
    uint8_t div_core;

    /*frequency setting error*/
    uint32_t error_hz;
}PllFc7300Config_t;


#endif /* PLL_CALC_TYPES_H */
