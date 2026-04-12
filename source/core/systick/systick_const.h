#ifndef SYSTICK_MCAL_CONST_H
#define SYSTICK_MCAL_CONST_H

#include "systick_dep.h"

#define SYSTICK_MAX_VAL 0x00FFFFFF

typedef enum {
    SYSTICK_CLK_SRC_EXT = 0,
    SYSTICK_CLK_SRC_PROC = 1,
    SYSTICK_CLK_SRC_UNDEF = 2,
}SysTickClkSrc_t;

typedef enum {
    SYSTICK_EN_OFF = 0,
    SYSTICK_EN_ON = 1,
    SYSTICK_EN_UNDEF = 2,
}SysTickEnable_t;

#endif /* SYSTICK_MCAL_CONST_H*/
