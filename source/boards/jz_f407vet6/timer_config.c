#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {

    { .num = TIMER_NUM_LO_BASE,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001f,
      .name = "LoBase",
      .valid = true,
      .on_off = true,
      .dir = TIMER_CNT_DIR_UP,
      .role = TIMER_ROLE_MASTER,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_OC1,
    },

    { .num = TIMER_NUM_LO,
      .slave_input_trigger = TIMER_SLAVE_IN_TRIG_INTERNAL_TRIGGER_3,
      .slave_mode = TIMER_SLAVE_MODE_RESET,//TIMER_SLAVE_MODE_GATED,// TIMER_SLAVE_MODE_RESET,//TIMER_SLAVE_MODE_TRIGGER,//TIMER_SLAVE_MODE_GATED,
      .role = TIMER_ROLE_SLAVE, //TIMER_ROLE_MASTER,//TIMER_ROLE_SLAVE,
      .dir = TIMER_CNT_DIR_UP,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001f,
      .name = "LO",
      .valid = true,
      .on_off = true,
      .slave_trigger_polarity = TIMER_SLAVE_TRIGGER_POLARITY_INVERTED, //TIMER_SLAVE_TRIGGER_POLARITY_RISING,//TIMER_SLAVE_TRIGGER_POLARITY_RISING  ,
      .slave_trigger_prescaler = 1,
      .slave_trigger_filter = 1,
    },


    { .num = TIMER_NUM_LASER, .dir = TIMER_CNT_DIR_UP,
      .interrupt_on = false,
      .cnt_period_ns = 1000,
      .period_s = 0.001f,
      .name = "Laser",
      .valid = true,
      .on_off = true,
      .role=TIMER_ROLE_SINGLE,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_RESET,
    },

    { .num = TIMER_NUM_US, .interrupt_on = true, .cnt_period_ns = 1000, .period_s = 4290.0f,
      .name = "upTimeUs", .valid = true, .on_off = true, .dir = TIMER_CNT_DIR_UP,
      .role=TIMER_ROLE_SINGLE,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_RESET,
    },

    { .num = TIMER_NUM_MS, .interrupt_on = true, .cnt_period_ns = 10000000, .period_s = 4294000.0,
      .name = "TimeStampMs", .valid = true, .on_off = true, .dir = TIMER_CNT_DIR_UP,
      .role=TIMER_ROLE_SINGLE,
      .master_out_trigger = TIMER_MASTER_OUT_TRG_RESET,
    },





};

TimerHandle_t TimerInstance[] = {
        { .num = TIMER_NUM_US, .valid = true, },
        { .num = TIMER_NUM_MS, .valid = true, },
        { .num = TIMER_NUM_LASER, .valid = true, },
        { .num = TIMER_NUM_LO_BASE, .valid = true, },
        { .num = TIMER_NUM_LO, .valid = true, },

};

COMPONENT_GET_CNT(Timer, timer)


