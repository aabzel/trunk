#include "sw_uart_config.h"

#include "data_utils.h"
#include "gpio_types.h"

#ifdef HAS_SW_UART1
//static uint8_t SwUart1TxArray[SW_UART_TX_FIFO_SIZE];
#endif

static uint8_t ByteRxFiFo[100] = {0};
static uint8_t ByteTxFiFo[4000] = {0};

#define SW_UART_CONFIG_TX                         \
        .Tx = {.port = PORT_A, .pin = 4,},        \
        .tx_over_sampling  = 4,                   \
        .tx_timer_num = 1,                        \
        .bin_dac_num = 1,                         \
        .TxFifoMem = ByteTxFiFo,                  \
        .tx_fifo_mem_size = ARRAY_SIZE(ByteTxFiFo),

#define SW_UART_CONFIG_RX                        \
        .rx_over_sampling  = 8,                  \
        .rx_timer_num = 8,                       \
        .Rx = {.port = PORT_A, .pin = 1,},       \
        .bin_adc_num = 1,                        \
        .RxFifoMem = ByteRxFiFo,                 \
        .rx_fifo_mem_size = ARRAY_SIZE(ByteRxFiFo),

/*constant compile-time known settings*/
const SwUartConfig_t SECTION_CFG_DATA SwUartConfig[] = {
    {
         SW_UART_CONFIG_RX
         SW_UART_CONFIG_TX
        .num = 1,
        .parity_check = false,
        .stop_bit_cnt = 2,
        .baud_rate = 9600,
        .name = "Debug",
        .valid = true,
    },
};

SwUartHandle_t SwUartInstance[] = {
    { .num = 1,  .valid = true, },
};

COMPONENT_GET_CNT(SwUart, sw_uart)

