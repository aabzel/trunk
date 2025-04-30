#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"

#if UART_NUM_CLI != UART_NUM_LOG
#error "UART_NUM_CLI!=UART_NUM_LOG"
#endif

static uint8_t Uart1TxArray[16];
static uint8_t Uart1RxArray[16];

static uint8_t Uart2TxArray[UART_TX_FIFO_SIZE];
static uint8_t Uart2RxArray[16];

static uint8_t Uart3TxArray[16];
static uint8_t Uart3RxArray[16];

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
    {
        .num = 2,
        .baud_rate = 460800,
        .name = "CLI",
        .rx_buff_size = 0,
        .valid = true,
	    .rx_buff_size = sizeof(Uart2RxArray),
	    .RxFifoArray = Uart2RxArray,
	    .tx_buff_size = sizeof(Uart2TxArray),
	    .TxFifoArray = Uart2TxArray,
    },
    {
        .num = 1,
        .baud_rate = 9600,
        .name = "UART1",
        .rx_buff_size = 0,
        .valid = true,
	    .rx_buff_size = sizeof(Uart1RxArray),
	    .RxFifoArray = Uart1RxArray,
	    .tx_buff_size = sizeof(Uart1TxArray),
	    .TxFifoArray = Uart1TxArray,
    },
    {
        .num = 3,
        .baud_rate = 9600,
        .name = "UART3",
        .rx_buff_size = 0,
        .valid = true,
	    .rx_buff_size = sizeof(Uart3RxArray),
	    .RxFifoArray = Uart3RxArray,
	    .tx_buff_size = sizeof(Uart3TxArray),
	    .TxFifoArray = Uart3TxArray,
    },
};


UartHandle_t UartInstance[] = {
    {
        .num = 2,
        .valid = true,
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
    },
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
    {
        .num = 3,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)Uart3TxArray,
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
