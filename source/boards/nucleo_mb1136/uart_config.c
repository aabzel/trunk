#include "uart_config.h"

#include "data_utils.h"

/*constant compile-time known settings*/
const UartConfig_t UartConfigLuT[] = {
    { .num=2, .baud_rate=CLI_UART_BAUD_RATE, .name = "CLI", },
};

UartHandle_t UartInstance[]={
    {.num=2, },
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

