#include "sw_timer_config.h"

#ifndef HAS_SOFTWARE_TIMER
#error "Add HAS_SOFTWARE_TIMER"
#endif /*HAS_SOFTWARE_TIMER*/

#include "data_utils.h"


#ifdef HAS_UART
#include "uart_mcal.h"
#include "uart_custom_drv.h"
#endif

const SoftwareTimerConfig_t SoftwareTimerConfig[ ] = {
       {.num=TIMER_UART_RX_TIME_OUT,  .on_off=false,  .period_ms=3,    .phase_ms=0, .name="Uart0RxTimeOut", .dir=SW_TIMER_CNT_DIR_UP,     .mode=SW_TIMER_MODE_SINGLE,     .valid=true,
#ifdef HAS_UART
               .handler=uart0_rx_timeout,
#endif
       },
     //  {.num=1, .on_off=true,   .period_ms=3000, .phase_ms=0, .name="Extra",         .dir=SW_TIMER_CNT_DIR_DOWN, .mode=SW_TIMER_MODE_CONTINUOUS, .valid=true, .handler=hander2,},
};

SoftwareTimer_t SoftwareTimerInstance[ ]={
     {.num=TIMER_UART_RX_TIME_OUT, .valid=true,},
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
