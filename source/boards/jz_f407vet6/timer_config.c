#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {

    { .num = TIMER_NUM_US,
      .interrupt_on = true,
      .cnt_period_ns = 1000,
      .period_s = 4290.0,
      .name = "upTimeUs",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_MS,
      .interrupt_on = true,
      .cnt_period_ns = 1000000,
      .period_s = 4294000.0,
      .name = "TimeStampMs",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_RTC,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 1.0,
      .name = "RTC",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },
};

TimerHandle_t TimerInstance[] = {
        { .num = TIMER_NUM_US, .valid = true, },
        { .num = TIMER_NUM_MS, .valid = true, },
        { .num = TIMER_NUM_RTC, .valid = true, },
};

COMPONENT_GET_CNT(Timer, timer)


