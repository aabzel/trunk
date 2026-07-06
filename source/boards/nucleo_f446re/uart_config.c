#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"

#ifdef HAS_UART1
static uint8_t Uart1TxArray[16];
static uint8_t Uart1RxArray[16];
#define UART1_CONFIG                                    \
    {                                                   \
        .num = 1,                                       \
        .baud_rate = 9600,                              \
        .name = "Gm671",                                \
        .interrupts_on = true,                          \
        .parity_check=false,                            \
        .stop_bit_cnt=2,                                \
        .word_len_bit=8,                                \
        .irq_priority = 3,                              \
        .momve_method = MOVE_MODE_INTERRUPT,            \
        .valid = true,                                  \
        .rx_buff_size = sizeof(Uart1RxArray),           \
        .RxFifoArray = Uart1RxArray,                    \
        .tx_buff_size = sizeof(Uart1TxArray),           \
        .TxFifoArray = Uart1TxArray,                    \
    },
#else
#define UART1_CONFIG
#endif

#ifdef HAS_UART2
static uint8_t Uart2TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart2RxArray[16];

#define UART2_CONFIG                               \
    {                                              \
        .num = 2,                                  \
        .interrupts_on = true,                     \
        .irq_priority = 3,                         \
        .parity_check=false,                       \
        .stop_bit_cnt=2,                           \
        .word_len_bit=8,                           \
        .momve_method = MOVE_MODE_INTERRUPT,       \
        .baud_rate = 460800,                       \
        .name = "CLI",                             \
        .valid = true,                             \
        .rx_buff_size = sizeof(Uart2RxArray),      \
        .RxFifoArray = Uart2RxArray,               \
        .tx_buff_size = sizeof(Uart2TxArray),      \
        .TxFifoArray = Uart2TxArray,               \
    },
#else
#define UART2_CONFIG
#endif

#ifdef HAS_UART3
static uint8_t Uart3TxArray[16];
static uint8_t Uart3RxArray[16];

#define UART3_CONFIG                                \
    {                                               \
        .num = 3,                                   \
        .baud_rate = 9600,                          \
        .interrupts_on = true,                      \
        .irq_priority = 3,                          \
        .parity_check=false,                        \
        .stop_bit_cnt=2,                            \
        .word_len_bit=8,                            \
        .momve_method = MOVE_MODE_INTERRUPT,        \
        .name = "UART3",                            \
        .valid = true,                              \
        .rx_buff_size = sizeof(Uart3RxArray),       \
        .RxFifoArray = Uart3RxArray,                \
        .tx_buff_size = sizeof(Uart3TxArray),       \
        .TxFifoArray = Uart3TxArray,                \
    },
#else
#define UART3_CONFIG
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
        UART1_CONFIG
        UART2_CONFIG
        UART3_CONFIG
};


UartHandle_t UartInstance[] = {
#ifdef HAS_UART2
    {
        .num = 2,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = Uart2TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart2TxArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
    },
#endif

#ifdef HAS_UART1
    {
        .num = 1,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = Uart1TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart1TxArray),
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
        .TxFifo =
            {
                .err_cnt = 0,
                .init_done = true,
                .array = Uart3TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart3TxArray),
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

