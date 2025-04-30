#include "timer_config.h"
//#include "c_defines_generated.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"
#include "debugger.h"

const TimerConfig_t TimerConfig[] = {
#ifdef HAS_TIMER1
    {
        .num = 1,
        .cnt_period_ns = 1,
        .dir = CNT_DIR_UP,
        .period_ns = 81,
        .name = "AudioCodec",
        .valid = true,
        .interrupt_on = false,
		 .on_off = true,
    },
#endif

#ifdef HAS_TIMER2
    {
        .num = 2,
        .cnt_period_ns = 5000,
        .dir = CNT_DIR_UP,
        .period_ms = 10,
        .name = "UpTime",
        .valid = true,
        .interrupt_on = true,
		 .on_off = true,
    },
#endif

#ifdef HAS_TIMER3
    {
        .num = 3,
        .cnt_period_ns = 20000,
        .dir = CNT_DIR_UP,
        .period_ms = 100000,
        .name = "InCap",
        .valid = true,
        .interrupt_on = true,
		 .on_off = true,
    },
#endif

#ifdef HAS_TIMER4
    {
        .num = 4,
        .cnt_period_ns = 400,
        .dir = CNT_DIR_UP,
        .period_us = 4000,
        .name = "PDM",
        .valid = true,
        .interrupt_on = true,
		 .on_off = true,
    },
#endif

#ifdef HAS_TIMER5
    {
        .num = 5,
        .cnt_period_ns = 80000,
        .dir = CNT_DIR_UP,
        .period_ms = 1000,
        .name = "1ms",
        .valid = true,
        .interrupt_on = true,
		 .on_off = true,
    },
#endif

#ifdef HAS_TIMER8
    {
        .num = 8,
        .period_us = 85333,
        .cnt_period_ns = 10000,
        .dir = CNT_DIR_UP,
        .name = "ForI2SProcTrig",
        .valid = true,
        .interrupt_on = true,
        .on_off = false,
    },
#endif

#ifdef HAS_TIMER9
    {
        .num = 9,
        .cnt_period_ns = 2000,
        .dir = CNT_DIR_UP,
        .period_ms = 100,
        .name = "EnsPwm",
        .valid = true,
        .interrupt_on = true,
         .on_off = true,
    },
#endif

#ifdef HAS_TIMER20
    {
        .num = 20,
        .cnt_period_ns = 50,
        .dir = CNT_DIR_UP,
        .period_ms = 1000,
        .name = "PWMDAC",
        .valid = true,
        .interrupt_on = true,
		 .on_off = true,
    },
#endif
};

TimerHandle_t TimerInstance[] = {
#ifdef HAS_TIMER1
    {
        .num = 1,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER2
    {
        .num = 2,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER3
    {
        .num = 3,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER4
    {
        .num = 4,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER5
    {
        .num = 5,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER6
    {
        .num = 6,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER8
    {
        .num = 8,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER9
    {
        .num = 9,
        .valid = true,
    },
#endif

#ifdef HAS_TIMER20
    {
        .num = 20,
        .valid = true,
    },
#endif
};

uint32_t timer_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TimerInstance);
    cnt2 = ARRAY_SIZE(TimerConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    } else {
        cnt = 0;
        ASSERT_CRITICAL(0)
    }
    return cnt;
}
