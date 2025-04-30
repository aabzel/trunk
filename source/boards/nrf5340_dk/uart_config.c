#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_CORE_APP
#ifdef HAS_UART0
    {
        .num = 0,
        .baud_rate = LOG_UART_BAUD_RATE,
        .name = "UART0",
#ifdef HAS_GPIO
        .TxPad =
            {
                .port = 0,
                .pin = 20,
            },
        .RxPad =
            {
                .port = 0,
                .pin = 22,
            },
#endif /*HAS_GPIO*/
        .rx_buff_size = 0,
        .valid = true,
    },
#endif /*HAS_UART0*/

#ifdef HAS_UART2
    {
        .num = 2,
        .baud_rate = 115200,
        .name = "UART2",
#ifdef HAS_GPIO
        .TxPad =
            {
                .port = 1,
                .pin = 1,
            },
        .RxPad =
            {
                .port = 1,
                .pin = 0,
            },
#endif /*HAS_GPIO*/
        .rx_buff_size = 0,
        .valid = true,
    },
#endif /*HAS_UART2*/
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
    {
        .num = 0,
        .baud_rate = LOG_UART_BAUD_RATE,
        .name = "UART0",
#ifdef HAS_GPIO
        .TxPad =
            {
                .port = 1,
                .pin = 1,
            },
        .RxPad =
            {
                .port = 1,
                .pin = 0,
            },
#endif /*HAS_GPIO*/
        .rx_buff_size = 0,
        .valid = true,
    },
#endif /*HAS_CORE_NET*/

};

#ifdef HAS_UART0
uint8_t Uart0TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART2
uint8_t Uart2TxArray[UART_TX_FIFO_SIZE];
uint8_t Uart2RxArray[UART_RX_FIFO_SIZE];
#endif

UartHandle_t UartInstance[] = {
#ifdef HAS_CORE_APP
#ifdef HAS_UART0
    {
        .num = 0,
        .valid = true,
#ifdef HAS_FIFO
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart0TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart0TxArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
#endif /*HAS_FIFO*/
    },
#endif /*HAS_UART0*/

#ifdef HAS_UART2
    {
        .num = 2,
        .valid = true,
#ifdef HAS_FIFO
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart2TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart2TxArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
        .RxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart2RxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart2RxArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
#endif /*HAS_FIFO*/
    },
#endif /*HAS_UART2*/
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
    {
        .num = UART_NUM_LOG_NET,
        .valid = true,
#ifdef HAS_FIFO
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart0TxArray,
                .fifoState =
                    {
                        .size = sizeof(Uart0TxArray),
                        .start = 0,
                        .end = 0,
                        .count = 0,
                        .errors = false,
                    },
            },
#endif /*HAS_FIFO*/
    },
#endif
};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
