#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /**/

#include "data_utils.h"
#include "time_mcal.h"


const TimerConfig_t TimerConfig[] = {
    {.num = 1,  .on_off = true, .dir = CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 50, .period_s = 1.0/35000.0, .name="DRV8870_1",  },
    {.num = 2 , .on_off = true, .dir = CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 20000, .period_s = MSEC_2_SEC(1), .name="1ms",  },
    {.num = 3,  .on_off = true, .dir = CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 50, .period_s = 1.0/35000.0, .name="DRV8870_2",  },
    {.num = 4 , .on_off = true, .dir=CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 500000, .period_s = MSEC_2_SEC(1000), .name="1s",  },
    {.num = 5 , .on_off = true, .dir=CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 20000, .period_s = MSEC_2_SEC(1), .name="1ms",  },
#ifdef HAS_TIMER6
    {.num = 6 , .on_off = true, .dir=CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 3000, .period_s = MSEC_2_SEC(160), .name="IrFrame", },
#endif
#ifdef HAS_TIMER8
    {.num = 8 , .on_off = true, .dir=CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 25, .period_s = USEC_2_SEC(25), .name="DRV8870",  },
#endif
    {.num = 9 , .on_off = true, .dir=CNT_DIR_UP, .valid=true, .interrupt_on = true, .cnt_period_ns = 500, .period_s = USEC_2_SEC(400), .name="LED",  },
};

TimerHandle_t TimerInstance[] = {
    {.num = 1, .valid = true,},
    {.num = 2, .valid = true,},
    {.num = 3, .valid = true,},
    {.num = 4, .valid = true,},
    {.num = 5, .valid = true,},
#ifdef HAS_TIMER6
    {.num = 6, .valid = true,},
#endif
#ifdef HAS_TIMER8
    {.num = 8, .valid = true,},
#endif
    {.num = 9, .valid = true,},
};

uint32_t timer_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TimerInstance); 
    cnt2 = ARRAY_SIZE(TimerConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
