#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include "data_utils.h"

const TimerConfig_t SECTION_CFG_DATA TimerConfig[] = {
    { .num = TIMER_NUM_OUT3_1,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001,
      .name = "OUT3_1",
      .valid = true,
      .role = TIMER_ROLE_SLAVE,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_3,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_RISING ,
      .slave_mode =  TIMER_SLAVE_MODE_TRIGGER,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_OUT3_x,
      .role = TIMER_ROLE_SLAVE,
      .slave_mode =  TIMER_SLAVE_MODE_TRIGGER,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_1,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_RISING ,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001,
      .name = "OUT3_2,OUT3_3",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_OUT2_4,
      .role = TIMER_ROLE_SLAVE,
      .slave_mode =  TIMER_SLAVE_MODE_TRIGGER,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_1,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_RISING ,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001,
      .name = "OUT2_4",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_OUT2_x,
      .role = TIMER_ROLE_SLAVE,
      .slave_mode =  TIMER_SLAVE_MODE_TRIGGER,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_0,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_RISING ,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001,
      .name = "OUT2_2,OUT2_3,OUT2_4",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_MASTER2,
      .interrupt_on = true,
      .role = TIMER_ROLE_MASTER,
      .cnt_period_ns = 1000,
      .period_s = 0.001f,
      .name = "MASTER2",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_MASTER5,
      .interrupt_on = true,
      .cnt_period_ns = 1000,
      .role = TIMER_ROLE_MASTER,
      .period_s = 0.001f,
      .name = "MASTER5",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
    },

    { .num = TIMER_NUM_RTC,
      .role = TIMER_ROLE_MASTER,
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
    { .num = TIMER_NUM_OUT2_x, .valid = true, },
    { .num = TIMER_NUM_MASTER2, .valid = true, },
    { .num = TIMER_NUM_MASTER5, .valid = true, },
    { .num = TIMER_NUM_OUT2_4, .valid = true, },
    { .num = TIMER_NUM_OUT3_x, .valid = true, },
    { .num = TIMER_NUM_OUT3_1, .valid = true, },
    { .num = TIMER_NUM_RTC, .valid = true, },
};

COMPONENT_GET_CNT(Timer, timer)


