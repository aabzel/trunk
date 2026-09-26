#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_UART1
static uint8_t Uart1RxArray[20] = {0};
static uint8_t Uart1TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6RxArray[100] = {0};
static uint8_t Uart6TxArray[20];
#endif

#ifdef HAS_UART1
#define CONFIG_UART1                                     \
    {                                                    \
        .num = 1,                                        \
        .baud_rate = 460800,                             \
        .name = "CLI",                                   \
        .dma = { .tx = false, .rx = false,},             \
        .interrupts_on = true,                           \
        .irq_priority = 0,                               \
        .momve_method = MOVE_MODE_INTERRUPT,             \
        .word_len_bit = 8,                               \
        .stop_bit_cnt = 2,                               \
        .rx_buff_size = sizeof(Uart1RxArray),            \
        .RxFifoArray = Uart1RxArray,                     \
        .TxFifoArray = Uart1TxArray,                     \
        .tx_buff_size = sizeof(Uart1TxArray),            \
        .parity_check = false,                           \
        .valid = true,                                   \
    },
#else
#define CONFIG_UART1
#endif

#ifdef HAS_UART6
#define CONFIG_UART6                                     \
    {                                                    \
        .num = 6,                                        \
        .baud_rate = 9600,                               \
        .name = "GNSS",                                  \
        .dma = { .tx = false, .rx = false,},             \
        .interrupts_on = true,                           \
        .irq_priority = 0,                               \
        .momve_method = MOVE_MODE_INTERRUPT,             \
        .word_len_bit = 8,                               \
        .stop_bit_cnt = 2,                               \
        .rx_buff_size = sizeof(Uart6RxArray),            \
        .RxFifoArray = Uart6RxArray,                     \
        .TxFifoArray = Uart6TxArray,                     \
        .tx_buff_size = sizeof(Uart6TxArray),            \
        .parity_check = false,                           \
        .valid = true,                                   \
    },
#else
#define CONFIG_UART1
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
        CONFIG_UART1
        CONFIG_UART6

};

UartHandle_t UartInstance[] = {
#ifdef HAS_UART1
    {
     .num = 1,
     .valid = true,
     .TxFifo = {.err_cnt = 0,
              .init_done = true,
              .array = Uart1TxArray,
              .fifoState = {
                          .size = sizeof(Uart1TxArray),
                          .start = 0,
                          .end = 0,
                          .count = 0,
                          .errors = false,
                         },
             },
    },
#endif

#ifdef HAS_UART6
        {.num = 6,
         .valid = true,
         .TxFifo = {.err_cnt = 0,
                  .init_done = true,
                  .array = Uart6TxArray,
                  .fifoState = {
                               .size = sizeof(Uart6TxArray),
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
