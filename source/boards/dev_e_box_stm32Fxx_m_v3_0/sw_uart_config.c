#include "sw_uart_config.h"

#include "data_utils.h"
#include "gpio_types.h"

#ifdef HAS_SW_UART1
static uint8_t SwUart1TxArray[SW_UART_TX_FIFO_SIZE];
#endif

/*constant compile-time known settings*/
const SwUartConfig_t SwUartConfig[] = {
    {
        .num = 1,
        .timer_num = 99,
        .parity_check = false,
        .stop_bit_cnt = 2,
        .baud_rate = 9600,
        .name = "Debug",
        .valid = true,
        .Tx = {.port=PORT_B, .pin=2,},
        .Rx = {.port=PORT_B, .pin=5,},
    },
};

SwUartHandle_t SwUartInstance[] = {
    { .num = 1,    .valid = true,	    },
};

uint32_t sw_uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SwUartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SwUartInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
