#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

/*
  UART1 - CLI
  UART2 - WiFi module
  UART6 - GNSS module
 */


#ifdef HAS_UART1
static uint8_t Uart1RxArray[2];
static uint8_t Uart1TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART2
static uint8_t Uart2RxArray[2];
static uint8_t Uart2TxArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6RxArray[2];
static uint8_t Uart6TxArray[UART_TX_FIFO_SIZE/4];
#endif


/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {
#ifdef HAS_UART1
    { .num = 1,
      .baud_rate = 460800,
      .name = "UART1",
      .rx_buff_size = 0,
      .valid = true,},
#endif

#ifdef HAS_UART2
    { .num=2,
      .baud_rate=460800,
      .name = "CLI",
      .RxFifoArray=Uart2RxArray,
      .rx_buff_size=ARRAY_SIZE(Uart2RxArray),
      .word_len_bit=8,
      .TxFifoArray=Uart2TxArray,
      .tx_buff_size=ARRAY_SIZE(Uart2TxArray),
//    uint32_t rx_buff_size;
  //  uint8_t* RxFifoArray;
      .stop_bit_cnt=1,
      .momve_method=MOVE_MODE_INTERRUPT,
      .parity_check=false,
      .interrupts_on=true,
      .valid=true,
    },
#endif

#ifdef HAS_UART6
    { .num=6,
            .baud_rate=460800,
            .name = "UART6",
            .rx_buff_size=0,
            .valid=true,
    },
#endif
};

UartHandle_t UartInstance[]={
#ifdef HAS_UART1
    {.num=1, .valid=true, .TxFifo={.err_cnt=0,
                                              .init_done=true,
                                              .array=(uint8_t *)Uart1TxArray,
                                              .fifoState={
                                                          .size=sizeof(Uart1TxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },
#endif

#ifdef HAS_UART2
    {.num=2, .valid=true, .TxFifo={.err_cnt=0,
                                              .init_done=true,
                                              .array=(uint8_t *)Uart2TxArray,
                                              .fifoState={
                                                          .size=sizeof(Uart2TxArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },
#endif


#ifdef HAS_UART6
    {.num=6, 
     .valid=true, 
     .TxFifo={.err_cnt=0,
              .initDone=true,
                                              .array=(uint8_t *)Uart6TxArray,
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

COMPONENT_GET_CNT(Uart, uart)
