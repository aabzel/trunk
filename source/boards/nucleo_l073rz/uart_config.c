#include "uart_config.h"

#include "data_utils.h"
#include "log_config.h"

#if UART_NUM_CLI != UART_NUM_LOG
#error "UART_NUM_CLI!=UART_NUM_LOG"
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfigLuT[] = {
#ifdef HAS_LOG
    {
        .num = 2,
        .baud_rate = 460800,
        .name = "CLI",
        .rx_buff_size = 0,
        .valid = true,
    },
#endif
};

uint8_t LogUartTxArray[UART_TX_FIFO_SIZE];

UartHandle_t UartInstance[] = {
#ifdef HAS_LOG
    {
        .num = 2,
        .valid = true,
        .TxFifo =
            {
                .err_cnt = 0,
                .initDone = true,
                .array = (char*)LogUartTxArray,
                .fifoState =
                    {
                        .size = sizeof(LogUartTxArray),
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
    uint32_t cnt_conf = ARRAY_SIZE(UartConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
