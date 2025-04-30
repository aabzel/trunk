#ifndef TIMER_CONST_H
#define TIMER_CONST_H

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include "sys_config.h"

#include "timer_dep.h"

//#define TIMER_CLOCK_HZ SYS_FREQ
//#define TIMER_CLOCK_HZ 16000000

typedef enum {
    CNT_DIR_DOWN = 1,
    CNT_DIR_UP = 2,
    CNT_DIR_UNDEF = 0,
}TimerDir_t;

typedef enum {
    TIMER_CC_CHAN_0=0,
    TIMER_CC_CHAN_1=1,
    TIMER_CC_CHAN_2=2,
    TIMER_CC_CHAN_3=3,
    TIMER_CC_CHAN_4=4,
    TIMER_CC_CHAN_5=5,

    TIMER_CC_UNDEF=55,
}TimerCapComChannel_t;

typedef enum{
    TIMER_OC_CHAN_0=0,
    TIMER_OC_CHAN_1=1,
    TIMER_OC_CHAN_2=2,
    TIMER_OC_CHAN_3=3,
    TIMER_OC_UNDEF=4,
}TimerOutChannel_t;


#endif /* TIMER_CONST_H */
