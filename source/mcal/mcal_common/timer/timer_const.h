#ifndef TIMER_CONST_H
#define TIMER_CONST_H

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

//#include "microcontroller_const.h"

#include "timer_dep.h"

//#define TIMER_CLOCK_HZ SYS_FREQ
//#define TIMER_CLOCK_HZ 16000000

typedef enum {
    TIMER_CNT_DIR_DOWN = 1,
    TIMER_CNT_DIR_UP = 2,
    TIMER_CNT_DIR_UP_DOWN = 3,
    TIMER_CNT_DIR_UNDEF = 0,
} TimerDir_t;

typedef enum {
    TIMER_CC_CHAN_0 = 0,
    TIMER_CC_CHAN_1 = 1,
    TIMER_CC_CHAN_2 = 2,
    TIMER_CC_CHAN_3 = 3,
    TIMER_CC_CHAN_4 = 4,
    TIMER_CC_CHAN_5 = 5,

    TIMER_CC_UNDEF = 55,
} TimerCapComChannel_t;

typedef enum {
    TIMER_OUT_CHANNEL_0 = 0,
    TIMER_OUT_CHANNEL_1 = 1,
    TIMER_OUT_CHANNEL_2 = 2,
    TIMER_OUT_CHANNEL_3 = 3,
    TIMER_OUT_CHANNEL_4 = 4,
    TIMER_OUT_CHANNEL_ALL = 5,
    TIMER_OUT_CHANNEL_UNDEF = 6,
} TimerOutChannel_t;

#endif /* TIMER_CONST_H */
