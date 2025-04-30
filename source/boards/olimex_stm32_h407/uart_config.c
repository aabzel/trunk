#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_UART3
uint8_t Uart3RxArray[20]={0};
#endif

#ifdef HAS_UART6
uint8_t Uart6RxArray[100]={0};
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_UART3
    { .num=3,
            .baud_rate=460800,
            .name = "UART3",
            .rx_buff_size = sizeof(Uart3RxArray),
            .RxFifoArray = Uart3RxArray,
            .valid=true,},
#endif

#ifdef HAS_UART6
    { .num = 6,
      .baud_rate = 9600,
      .name = "USART6",
      .rx_buff_size = sizeof(Uart6RxArray),
      .RxFifoArray = Uart6RxArray,
      .valid=true,},
#endif
};

#ifdef HAS_UART3
static uint8_t Uart3TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6TxArray[UART_TX_FIFO_SIZE/4];
#endif

UartHandle_t UartInstance[]={
#ifdef HAS_UART
    {.num=3, .valid=true, .TxFifo={.err_cnt=0,
                                              .initDone=true,
                                              .array=(char *)Uart3TxArray,
                                              .fifoState={
                                                          .size=sizeof(Uart3TxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },
#endif

#ifdef HAS_UART6
    {.num=6, .valid=true, .TxFifo={.err_cnt=0,
                                              .initDone=true,
                                              .array=(char *)Uart6TxArray,
                                              .fifoState={
                                                          .size=sizeof(Uart6TxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
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

