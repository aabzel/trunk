#include "sw_timer_config.h"

#include <stddef.h>

#ifndef HAS_SOFTWARE_TIMER
#error "Add HAS_SOFTWARE_TIMER"
#endif /*HAS_SOFTWARE_TIMER*/

#include "data_utils.h"

const SoftwareTimerConfig_t SoftwareTimerConfig[ ] = {
       {.num=1,
    		   .on_off=false,
    		   .period_ms=1000,
			   .phase_ms=0, .name="1",
			   .dir=SW_TIMER_CNT_DIR_UP,
			   .mode=SW_TIMER_MODE_SINGLE,
			   .valid=true,
               .handler=NULL,
       },
     //  {.num=1, .on_off=true,   .period_ms=3000, .phase_ms=0, .name="Extra",         .dir=SW_TIMER_CNT_DIR_DOWN, .mode=SW_TIMER_MODE_CONTINUOUS, .valid=true, .handler=hander2,},
};

SoftwareTimer_t SoftwareTimerInstance[ ]={
     {.num=1, .valid=true,},
    // {.num=1, .valid=true,}
};

uint32_t software_timer_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SoftwareTimerInstance); 
    cnt2 = ARRAY_SIZE(SoftwareTimerConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
