#include "uart_config.h"

#include <hw_memmap.h>
#include <hw_ints.h>

#include "data_utils.h"

/*constant compile-time known settings*/
const UartConfig_t UartConfigLuT[] = {
    {.num=0, .base = UART0_BASE, .baud_rate = 460800,  .name = "CLI", .valid=true, /*.int_num=INT_UART0_COMB*/},
    {.num=1, .base = UART1_BASE, .baud_rate = 460800,  .name = "Ext", .valid=true, /*.int_num=INT_UART1_COMB*/}
};

extern UartHandle_t UartInstance[]={
    {.num=0, .valid=true,},
    {.num=1, .valid=true,}
};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

