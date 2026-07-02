#include "timer_config.h"


#include "data_utils.h"
#include "time_mcal.h"
#include "physics_utils.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

const TimerConfig_t TimerConfig[] = {
    {.num = 1,  .on_off = true, .dir = TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 50, .period_s = FREQ_HZ_TO_PERIOD_S(21000)  , .name="DRV8870_1",  },

#ifdef HAS_TIMER2
    {.num = 2 , .on_off = true, .dir = TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 3000, .period_s = MSEC_2_SEC(160), .name="IrFrame",  },
#endif
    {.num = 3,  .on_off = true, .dir = TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 50, .period_s = FREQ_HZ_TO_PERIOD_S(21000) , .name="DRV8870_2",  },
    {.num = 4 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 100, .period_s = MSEC_2_SEC(1000), .name="Beep",  },
    {.num = 5 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 20000, .period_s = MSEC_2_SEC(1), .name="1ms",  },
#ifdef HAS_TIMER6
    {.num = 6 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 3000, .period_s = MSEC_2_SEC(160), .name="spare", },
#endif

#ifdef HAS_TIMER8
    {.num = 8 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 25, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="LED",  },
#endif

#ifdef HAS_TIMER10
    {.num = 10 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="LED",  },
#endif

#ifdef HAS_TIMER11
    {.num = 11 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="spare",  },
#endif

#ifdef HAS_TIMER14
    {.num = 14 , .on_off = true, .dir=TIMER_CNT_DIR_UP, .valid=true, .interrupt_on = false, .cnt_period_ns = 500, .period_s = FREQ_HZ_TO_PERIOD_S(5000), .name="spare",  },
#endif
};

TimerHandle_t TimerInstance[] = {
    {.num = 1, .valid = true,},
#ifdef HAS_TIMER2
    {.num = 2, .valid = true,},
#endif
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
    {.num = 5, .valid = true,},
#ifdef HAS_TIMER6
    {.num = 6, .valid = true,},
#endif

#ifdef HAS_TIMER8
    {.num = 8, .valid = true,},
#endif

#ifdef HAS_TIMER10
    {.num = 10, .valid = true,},
#endif

#ifdef HAS_TIMER11
    {.num = 11, .valid = true,},
#endif

#ifdef HAS_TIMER14
    {.num = 14, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Timer, timer)
