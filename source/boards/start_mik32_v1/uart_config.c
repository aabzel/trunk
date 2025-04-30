#include "uart_config.h"

#ifdef HAS_LOG
#include "log_config.h"
#endif
#include "data_utils.h"

#ifdef HAS_UART0
uint8_t Uart0RxArray[2] = {0};
#endif

#ifdef HAS_UART1
uint8_t Uart1RxArray[2] = {0};
#endif


/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_UART0
    {
       .num = 0, .baud_rate = 57600, .rx_buff_size = sizeof(Uart0RxArray), .RxFifoArray = Uart0RxArray,
       .valid = true, .interrupts_on = true, .momve_method = MOVE_MODE_INTERRUPT,
       .parity_check = false, .stop_bit_cnt = 2, .word_len_bit = 8,
#ifdef HAS_LOG
       .name = "UART0",
#endif
    },
#endif


#ifdef HAS_UART1
    { .num = 1, .baud_rate = 57600, .rx_buff_size = sizeof(Uart1RxArray), .RxFifoArray = Uart1RxArray,
      .valid = true, .interrupts_on = true, .momve_method = MOVE_MODE_INTERRUPT,
      .parity_check = false, .stop_bit_cnt = 2, .word_len_bit = 8,
#ifdef HAS_LOG
      .name = "UART1",
#endif
    },
#endif
};

#ifdef HAS_UART0
static uint8_t Uart0TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART1
static uint8_t Uart1TxArray[UART_TX_FIFO_SIZE];
#endif

UartHandle_t UartInstance[]={
#ifdef HAS_UART0
    {.num = 0, .valid=true, .TxFifo={.err_cnt=0,
                                     .initDone=true,
                                     .array=(char *)Uart0TxArray,
                                     .fifoState = {
                                                          .size=sizeof(Uart0TxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },
#endif

#ifdef HAS_UART1
    {.num = 1, .valid = true, .TxFifo = {.err_cnt = 0,
                                         .initDone = true,
                                         .array = (char *)Uart1TxArray,
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
};

uint32_t uart_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(UartConfig);
    uint32_t cnt_ints = ARRAY_SIZE(UartInstance);
    if(cnt_conf==cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

