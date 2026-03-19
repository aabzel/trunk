#ifndef CLOCK_OUT_CONST_H
#define CLOCK_OUT_CONST_H

typedef enum {
    CLOCK_OUT_CH_1 = 1,
    CLOCK_OUT_CH_2 = 2,
    CLOCK_OUT_CH_UNDEF = 0,
} ClockOutChannel_t;

typedef enum {
    CLOCK_OUT_CORE = 1,
    CLOCK_OUT_PLL0 = 2,
    CLOCK_OUT_PLL1 = 3,
    CLOCK_OUT_RTC  = 4,
    CLOCK_OUT_AON  = 5,
    CLOCK_OUT_SIRC_128K=6,
    CLOCK_OUT_BUS =7 ,
    CLOCK_OUT_FIRC =10 ,
    CLOCK_OUT_SIRC =12 ,
    CLOCK_OUT_SLOW =13 ,
    CLOCK_OUT_FOSC =14 ,
    CLOCK_OUT_SCG  =15,
    CLOCK_OUT_UNDEF = 0,
} ClockOutBus_t;

#endif /* CLOCK_OUT_CONST_H  */
