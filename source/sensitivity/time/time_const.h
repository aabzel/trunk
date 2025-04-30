
#ifndef TIME_CONST_H
#define TIME_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define START_YEAR 1900
#define TIME_POLL_PERIOD_US 50000000

#include "time_dep.h"
#ifdef HAS_MATH
#include "math_const.h"
#endif

#ifdef HAS_NEO_6M
#define START_YEAR (1964)
#endif

#ifdef HAS_ZED_F9P
#define START_YEAR (1900)
#endif

typedef enum {
    MON_JAN=0,
    MON_FEB=1,
    MON_MAR=2,
    MON_APR=3,
    MON_MAY=4,
    MON_JUN=5,
    MON_JUL=6,
    MON_AUG=7,
    MON_SEP=8,
    MON_OCT=9,
    MON_NOV=10,
    MON_DEC=11,

    MON_UNDEF=13,
}Month_t;

typedef enum {
    TIME_SRC_SYSTICK = 1,
    TIME_SRC_TIMER2 = 2,
    TIME_SRC_TIMER3 = 3,
    TIME_SRC_TIMER4 = 4,
    TIME_SRC_TIMER5 = 5,
    TIME_SRC_RTC = 6,
    TIME_SRC_SW_INCR = 7,
    TIME_SRC_WIN_CLOCK = 8,
    TIME_SRC_ZEPHYR_CLOCK = 9,
    TIME_SCR1_TIMER = 10, /* Kernel Timer SCR1_TIMER */
    TIME_SRC_RISC_V = 11,

    TIME_SRC_UNDEF=0,
}TimeSource_t;


#ifdef __cplusplus
}
#endif

#endif /* TIME_CONST_H */
