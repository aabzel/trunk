#ifndef PLL_CALC_CONST_H
#define PLL_CALC_CONST_H

#include "pll_calc_dep.h"

#define PLL_USB_CLOCK_HZ 48000000U
#define PLL_XTALL_FREQ_HZ   24000000U
#define PLL_CLK_MIN   150000000U
#define FIRC_CLOCK    96000000U
#define PLL_VCO_CLK_MAX                  640000000U
#define PLL_VCO_CLK_MIN                  240000000U
#define PLL_CLK_MIN                      150000000U
#define PLL_CLK_MAX                      300000000U
#define PLL_FEEDBACK_CLK_MAX             4000000U
#define PLL_FEEDBACK_CLK_MIN             2000000U
#define FIRC_FREQ_HZ 96000000

/*
 FOSC Fast Oscillator
 FIRC Fast Internal Reference Clock
 */
typedef enum {
    FC73X_CLOCK_PLL_SOURCE_FOSC = 0,
    FC73X_CLOCK_PLL_SOURCE_FIRC_DIV2 = 1,
    FC73X_CLOCK_PLL_SOURCE_UNDEF = 2,
}Fc7ClockPllSource_t;


/*PLL Post Divider*/
typedef enum {
    FC7_CLOCK_POSR_DIV_2   = 0 ,
    FC7_CLOCK_POSR_DIV_2_   = 1 ,
    FC7_CLOCK_POSR_DIV_4   = 2 ,
    FC7_CLOCK_POSR_DIV_8   = 3 ,
    FC7_CLOCK_POSR_DIV_UNDEF   = 4 ,
}Fc73xClockPostDiv_t;

#endif /* PLL_CALC_CONST_H */

