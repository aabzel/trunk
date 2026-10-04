#include "uart_config.h"

#include "data_utils.h"

#ifdef HAS_UART1
static uint8_t Uart1RxFifoArray[50] = {0};
static uint8_t Uart1TxFifoArray[2096] = {0};
#endif

#ifdef HAS_UART3
static uint8_t Uart3RxFifoArray[50] = {0};
static uint8_t Uart3TxFifoArray[2096] = {0};
#endif

/*constant compile-time known settings*/
const UartConfig_t SECTION_CFG_DATA UartConfig[] = {
#ifdef HAS_UART1
    {
        .num = 1,
        .word_len_bit = 8,
        .stop_bit_cnt = 2,
        .baud_rate = 460800,
        .interrupts_on = true,
        .RxFifoArray = Uart1RxFifoArray,
        .rx_buff_size = sizeof(Uart1RxFifoArray),

        .TxFifoArray = Uart1TxFifoArray,
        .tx_buff_size = sizeof(Uart1TxFifoArray),

        .irq_priority = 0,
#ifdef HAS_DMA_CHANNEL
        .dma = { .tx = false, .rx = false,},
#endif
        .parity_check = false,
        .name = "CLI",
        .momve_method = MOVE_MODE_INTERRUPT,
        .valid = true,
    },
#endif

#ifdef HAS_UART3
    {
        .num = 3,
        .word_len_bit = 8,
        .stop_bit_cnt = 2,
        .baud_rate = 460800,
        .interrupts_on = true,
        .RxFifoArray = Uart3RxFifoArray,
        .rx_buff_size = sizeof(Uart3RxFifoArray),

        .TxFifoArray = Uart3TxFifoArray,
        .tx_buff_size = sizeof(Uart3TxFifoArray),

        .irq_priority = 0,
#ifdef HAS_DMA_CHANNEL
        .dma = { .tx = false, .rx = false,},
#endif
        .parity_check = false,
        .name = "CLI",
        .momve_method = MOVE_MODE_INTERRUPT,
        .valid = true,
    },
#endif
};

/*TxFifo must be inited before main to accumulate log before HW UART driver init*/
UartHandle_t UartInstance[] = {
#ifdef HAS_UART1
    {
        .num = 1,
        .valid = true,
        .init_done = false,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = Uart1TxFifoArray,
                .fifoState =
                    {
                        .size = sizeof(Uart1TxFifoArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
    },
#endif

#ifdef HAS_UART3
    {
        .num = 3,
        .valid = true,
        .init_done = false,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = Uart3TxFifoArray,
                .fifoState =
                    {
                        .size = sizeof(Uart3TxFifoArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
    },
#endif
};

COMPONENT_GET_CNT(Uart, uart)
