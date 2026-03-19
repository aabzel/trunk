#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_UART1
static uint8_t Uart1RxFifoArray[20]={0};
static uint8_t Uart1TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART2
static uint8_t Uart2RxFifoArray[20]={0};
static uint8_t Uart2TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART3
static uint8_t Uart3RxFifoArray[20]={0};
static uint8_t Uart3TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6RxFifoArray[100]={0};
static uint8_t Uart6TxFifoArray[UART_TX_FIFO_SIZE/4];
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {

#ifdef HAS_UART1
    { .num = 1,
      .baud_rate = 460800,
      .name = "CLI",
      .dma = { .tx = false, .rx = false,},
      .interrupts_on = true,
      .irq_priority = 0,
      .momve_method = MOVE_MODE_INTERRUPT,
      .word_len_bit = 8,
      .stop_bit_cnt = 2,
      .rx_buff_size = sizeof(Uart1RxFifoArray),
      .RxFifoArray = Uart1RxFifoArray,
      .TxFifoArray = Uart1TxFifoArray,
      .tx_buff_size = sizeof(Uart1TxFifoArray),
      .parity_check = false,
      .valid = true,
    },
#endif

#ifdef HAS_UART2
    { .num = 2,
      .baud_rate = 115200,
      .dma = { .tx = false, .rx = false,},
      .name = "RS485",
      .rx_buff_size = sizeof(Uart2RxFifoArray),
      .RxFifoArray = Uart2RxFifoArray,
      .interrupts_on = true,
      .irq_priority = 0,
      .momve_method = MOVE_MODE_INTERRUPT,
      .parity_check = false,
      .stop_bit_cnt = 2,
      .TxFifoArray = Uart2TxFifoArray,
      .tx_buff_size = sizeof(Uart2TxFifoArray),
      .valid = true,
      .word_len_bit = 8,
    },
#endif

#ifdef HAS_UART3
    { 
        .num = 3,
        .baud_rate = 460800,
        .name = "CLI",
        .RxPad = {.port=PORT_B, .pin=11,},
        .TxPad = {.port=PORT_B, .pin=10,},
        .dma = { .tx = false, .rx = false,},
        .interrupts_on = true,
        .irq_priority = 0,
        .momve_method = MOVE_MODE_INTERRUPT,
        .word_len_bit = 8,
        .stop_bit_cnt = 2,
        .RxFifoArray = Uart3RxFifoArray,
        .rx_buff_size = sizeof(Uart3RxFifoArray),

        .TxFifoArray = Uart3TxFifoArray,
        .tx_buff_size = sizeof(Uart3TxFifoArray),
        .parity_check = false,
        .valid = true,
    },
#endif

#ifdef HAS_UART6
    { .num = 6,
      .baud_rate = 9600,
      .name = "GNSS",
      .rx_buff_size = sizeof(Uart6RxFifoArray),
      .RxFifoArray = Uart6RxFifoArray,
      .valid=true,},
#endif
};

UartHandle_t UartInstance[]={
#ifdef HAS_UART1
    {.num = 1,
     .valid = true,
     .TxFifo={.err_cnt = 0,
              .init_done = true,
              .array = (uint8_t *)Uart1TxFifoArray,
              .fifoState={
                  .size=sizeof(Uart1TxFifoArray),
                  .start=0,
                  .end=0,
                  .count=0,
                  .errors=false,
              },
        },
    },
#endif

#ifdef HAS_UART2
    {.num=2,
     .valid=true, .TxFifo={.err_cnt=0,
                                              .init_done=true,
                                              .array=(uint8_t *)Uart2TxFifoArray,
                                              .fifoState={
                                                          .size=sizeof(Uart2TxFifoArray),
                                                          .start=0,
                                                          .end=0,
                                                          .count=0,
                                                          .errors=false,
                                              },
    },
    },
#endif

#ifdef HAS_UART3
    {
     .num = 3,
     .valid = true,
     .TxFifo = {
                  .err_cnt = 0,
                  .init_done = true,
                  .array = (uint8_t *)Uart3TxFifoArray,
                  .fifoState = {
                        .size = sizeof(Uart3TxFifoArray),
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
     .valid = true, .TxFifo = {.err_cnt = 0,
                                              .init_done = true,
                                              .array = Uart6TxFifoArray,
                                              .fifoState = {
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



