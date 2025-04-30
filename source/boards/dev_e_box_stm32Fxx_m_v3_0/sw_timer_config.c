#include "sw_timer_config.h"

#ifndef HAS_SOFTWARE_TIMER
#error "Add HAS_SOFTWARE_TIMER"
#endif /*HAS_SOFTWARE_TIMER*/

#include "data_utils.h"

#if 0
static bool hander1(void){
	return true;
}
#endif

static bool hander2(void){
	return true;
}

const SoftwareTimerConfig_t SoftwareTimerConfig[ ] = {
       {.num=1, .on_off=true,   .spare=false,  .period_ms=40000, .phase_ms=0, .name="Pastilda", .dir=SW_TIMER_CNT_DIR_UP, .mode=SW_TIMER_MODE_SINGLE, .valid=true, .handler=hander2,},
       {.num=2, .on_off=false,  .spare=true,  .period_ms=20000, .phase_ms=0, .name="Test", .dir=SW_TIMER_CNT_DIR_UP, .mode=SW_TIMER_MODE_SINGLE, .valid=true, .handler=hander2,},
       {.num=3, .on_off=false,  .spare=true,  .period_ms=20000, .phase_ms=0, .name="Test", .dir=SW_TIMER_CNT_DIR_UP, .mode=SW_TIMER_MODE_SINGLE, .valid=true, .handler=hander2,}
   //    {.num=0, .on_off=false,  .period_ms=3,    .phase_ms=0, .name="UartRxTimeOut", .dir=SW_TIMER_CNT_DIR_UP,     .mode=SW_TIMER_MODE_SINGLE,     .valid=true, .handler=hander1,},
     //  {.num=1, .on_off=true,   .period_ms=3000, .phase_ms=0, .name="UartRxTimeOut", .dir=SW_TIMER_CNT_DIR_DOWN, .mode=SW_TIMER_MODE_CONTINUOUS, .valid=true, .handler=hander1,},
};

SoftwareTimer_t SoftwareTimerInstance[ ]={
     {.num=1, .valid=true, .spare=false, .isr=false,  .on_off=false, },
     {.num=2, .valid=true, .spare=true, .isr=false,  .on_off=false, },
     {.num=3, .valid=true, .spare=true,  .isr=false,  .on_off=false, }
 //    {.num=0, .valid=true,},
   //  {.num=1, .valid=true,},
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
