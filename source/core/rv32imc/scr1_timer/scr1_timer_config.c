#include "scr1_timer_config.h"

Scr1TimerConfig_t Scr1TimerConfig = {
    .base_addr = SCR1_TIMER_BASE,
    .tick_s = 0.000001,
    .clock_source = CLOCK_SRC_EXTERNAL_32MHZ,
    .valid = true,
};

Scr1Timer_t Scr1TimerInstance = {
    .valid = true,
    .int_cnt = 0,
    .err_cnt = 0,
    .scr1_timer_up_time_us = 0,
    .Scr1TimerRegMapPtr = (Scr1TimerRegs_t*)SCR1_TIMER_BASE,
};
