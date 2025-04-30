#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"

#ifdef HAS_UART1
static uint8_t Uart1TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart1RxArray[16];
#endif

#ifdef HAS_UART2
static uint8_t Uart2TxArray[16];
static uint8_t Uart2RxArray[16];
#endif

#ifdef HAS_UART6
static uint8_t Uart6TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart6RxArray[16];
#endif
//#include "c_defines_generated.h"
/*TODO USE MACRO FUNCTION to compose identical config*/
/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_UART1
    {
        .num = 1,
        .baud_rate = 460800,
        .name = "UART1",
        .tx_buff_size = sizeof(Uart1TxArray),
        .TxFifoArray = Uart1TxArray,
        .rx_buff_size = sizeof(Uart1RxArray),
        .RxFifoArray = Uart1RxArray,
        .valid = true,
        .dma =
            {
                .tx = false,
                .rx = false,
            },
    },
#endif

#ifdef HAS_UART2
    {
        .num = 2,
        .baud_rate = 9600,
        .tx_buff_size = sizeof(Uart2TxArray),
        .TxFifoArray = Uart2TxArray,
        .rx_buff_size = sizeof(Uart2RxArray),
        .RxFifoArray = Uart2RxArray,
        .name = "UART2",
        .rx_buff_size = 0,
        .valid = true,
        .dma =
            {
                .tx = false,
                .rx = false,
            },
    },
#endif

#ifdef HAS_UART6
    {
        .num = 6,
        .baud_rate = 460800,
        .name = "UART6",
        .tx_buff_size = sizeof(Uart6TxArray),
        .TxFifoArray = Uart6TxArray,
        .rx_buff_size = sizeof(Uart6RxArray),
        .RxFifoArray = Uart6RxArray,
        .rx_buff_size = 0,
        .valid = true,
        .dma =
            {
                .tx = false,
                .rx = false,
            },
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
                .initDone = true,
                .array = (char*)Uart1TxArray,
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

#ifdef HAS_UART2
    {
        .num = 2,
        .valid = true,
    },

#endif

#ifdef HAS_UART6
    {
        .num = 6,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart6TxArray,
                .fifoState =
                    {
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

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
