#include "uart_config.h"

#include "data_utils.h"

#ifdef HAS_UART1
static uint8_t Uart1TxFifoArray[UART_TX_FIFO_SIZE];
static uint8_t Uart1RxFifoArray[UART_RX_FIFO_SIZE];
#endif

#ifdef HAS_UART2
static uint8_t Uart2TxFifoArray[2048];
static uint8_t Uart2RxFifoArray[UART_RX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6TxFifoArray[UART_TX_FIFO_SIZE];
static uint8_t Uart6RxFifoArray[UART_RX_FIFO_SIZE];
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_UART1
    {
        .num = 1,
        .baud_rate = 115200,
        .word_len_bit = 8,
        .stop_bit_cnt = 2,
        .parity_check = false,
        .RxPad = {.port=PORT_A, .pin=10,},
        .TxPad = {.port=PORT_A, .pin=9,},
        .name = "ESP-01",
        .irq_priority = 0,
      //  .dma = { .tx = false, .rx = false,},
        .momve_method = MOVE_MODE_INTERRUPT,
        .interrupts_on = true,
        .TxFifoArray = Uart1TxFifoArray,
        .tx_buff_size = sizeof(Uart1TxFifoArray),

        .RxFifoArray = Uart1RxFifoArray,
        .rx_buff_size = sizeof(Uart1RxFifoArray),

        .valid = true,
    },
#endif

#ifdef HAS_UART2
    {
        .num = 2,
        .baud_rate = 460800,
        .name = "CLI",
        .RxPad = {.port=PORT_A, .pin=3,},
        .TxPad = {.port=PORT_A, .pin=2,},
     //   .dma = { .tx = false, .rx = false,},
        .interrupts_on = true,
        .irq_priority = 0,
        .momve_method = MOVE_MODE_INTERRUPT,
        .word_len_bit = 8,
        .stop_bit_cnt = 2,
        .RxFifoArray = Uart2RxFifoArray,
        .rx_buff_size = sizeof(Uart2RxFifoArray),

        .TxFifoArray = Uart2TxFifoArray,
        .tx_buff_size = sizeof(Uart2TxFifoArray),
        .parity_check = false,
        .valid = true,
    },
#endif

#ifdef HAS_UART6
    {
        .num = 6,
        .baud_rate = 9600,
        .name = "GNSS",
        .RxPad = {.port=PORT_A, .pin=12,},
        .TxPad = {.port=PORT_A, .pin=11,},
        .interrupts_on = true,
     //   .dma = { .tx = false, .rx = false,},
        .momve_method = MOVE_MODE_INTERRUPT,
        .word_len_bit = 8,

        .irq_priority = 0,
        .RxFifoArray = Uart6RxFifoArray,
        .rx_buff_size = sizeof(Uart6RxFifoArray),

        .TxFifoArray = Uart6TxFifoArray,
        .tx_buff_size = sizeof(Uart6TxFifoArray),
        .stop_bit_cnt = 2,
        .parity_check = false,
        .valid = true,
    },
#endif
};


UartHandle_t UartInstance[] = {
#ifdef HAS_UART1
        {
            .num = 1,
            .valid = true,
            .TxFifo =
                {
                    .err_cnt = 0,
                    .init_done = true,
                    .array = (uint8_t*)Uart1TxFifoArray,
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

#ifdef HAS_UART2
    {
        .num = 2,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = (uint8_t*)Uart2TxFifoArray,
                .fifoState =
                    {
                        .size = sizeof(Uart2TxFifoArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
    },
#endif

#ifdef HAS_UART6
    {
        .num = 6,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = (uint8_t*)Uart6TxFifoArray,
                .fifoState =
                    {
                        .size = sizeof(Uart6TxFifoArray),
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
