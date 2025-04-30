#ifndef SYSTICK_CONST_H
#define SYSTICK_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "microcontroller_const.h"

#define SYSTICK_BASE 0xE000E010

#define SYSTICK_PERIOD (SYS_FREQ/1000)

typedef enum {
    STK_CLK_SRC_AHB_DIV_8=0,
    STK_CLK_SRC_AHB=1,
    STK_CLK_SRC_UNDEF=2,
}StkClkSrc_t;

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_CONST_H
