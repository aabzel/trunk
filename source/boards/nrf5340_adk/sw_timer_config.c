#include "sw_timer_config.h"

#ifndef HAS_SOFTWARE_TIMER
#error "Add HAS_SOFTWARE_TIMER"
#endif /*HAS_SOFTWARE_TIMER*/

#include "data_utils.h"


#ifdef HAS_UART
#include "uart_drv.h"
#include "uart_nrf_drv.h"
#endif

static bool hander2(void){
	return true;
}

const SoftwareTimerConfig_t SoftwareTimerConfig[ ] = {
    {.num=SW_TIMER_TEST_NUM, .on_off=true,   .period_ms=20000, .phase_ms=0, .name="Test", .dir=SW_TIMER_CNT_DIR_UP, .mode=SW_TIMER_MODE_SINGLE, .valid=true, .handler=hander2,}
};

SoftwareTimer_t SoftwareTimerInstance[ ]={
    {.num=SW_TIMER_TEST_NUM, .valid=true, .isr=false,}
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
