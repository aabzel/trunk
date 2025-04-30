#ifndef CLOCK_MCAL_CONST_H
#define CLOCK_MCAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_dep.h"
#ifdef HAS_CLOCK_CUSTOM
#include "clock_custom_const.h"
#endif

typedef enum {
    CLOCK_SRC_INTERNAL = 1,
    CLOCK_SRC_EXTERNAL = 2,
    CLOCK_SRC_RTC = 3,
    CLOCK_SRC_EXTERNAL_32MHZ = 4,

    CLOCK_SRC_UNDEF = 0,
} ClockSource_t;

typedef enum{
    CLK_HI_FREQ_32MHZ = 32000000,
    CLK_HI_FREQ_25MHZ = 25000000,
    CLK_HI_FREQ_12MHZ = 12000000,
    CLK_HI_FREQ_16MHZ = 16000000,
    CLK_HI_FREQ_8MHZ  = 8000000,

    CLK_HI_FREQ_UNDEF = 0,
}ClockHiFreqSrc_t;

typedef enum {
    CLK_LOW_FREQ_32KHZ = 32768,

    CLK_LOW_FREQ_UNDEF = 0,
}ClockLowFreqSrc_t ;

typedef enum {
    CLK_DOMAIN_HI_FREQ = 1,
    CLK_DOMAIN_LOW_FREQ = 2,
    CLK_DOMAIN_AUDIO_FREQ = 4,
    CLK_DOMAIN_EXTRA_HI_FREQ = 5,

    CLK_DOMAIN_UNDEF = 0,
}ClockDomain_t;

#define CLOCK_BUS_AHB_ALL                                    \
    CLOCK_BUS_AHB,    /*Advanced High-performance Bus*/      \
    CLOCK_BUS_AHB1,    /*Advanced High-performance Bus1*/    \
    CLOCK_BUS_AHB2,    /*Advanced High-performance Bus2*/    \
    CLOCK_BUS_AHB3,    /*Advanced High-performance Bus2*/

#define CLOCK_BUS_APB_ALL                                    \
    CLOCK_BUS_APB1,    /*Advanced Peripheral Bus1 */         \
    CLOCK_BUS_APB1_TIMERS,    /*Advanced Peripheral Bus1 */  \
    CLOCK_BUS_APB2,    /*Advanced Peripheral Bus2*/          \
    CLOCK_BUS_APB2_TIMERS,    /*Advanced Peripheral Bus2*/


typedef enum {
    CLOCK_BUS_APB_ALL
    CLOCK_BUS_AHB_ALL

    CLOCK_BUS_INTERNAL,     /**/
    CLOCK_BUS_XTALL,        /**/
    CLOCK_BUS_AHB_TIMERS,   /**/
    CLOCK_BUS_LOW_POWER,    /**/
    CLOCK_BUS_SYS,     /*system clock*/

    CLOCK_BUS_UNDEF,
}ClockBus_t;



#ifdef __cplusplus
}
#endif

#endif /* CLOCK_MCAL_CONST_H */
