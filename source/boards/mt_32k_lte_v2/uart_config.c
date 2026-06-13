#include "uart_config.h"

#include "log_config.h"
#include "data_utils.h"

#ifdef HAS_UART2
static uint8_t Uart2RxFifoArray[20]={0};
static uint8_t Uart2TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART3
static uint8_t Uart3RxFifoArray[20]={0};
static uint8_t Uart3TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART4
static uint8_t Uart4RxFifoArray[20]={0};
static uint8_t Uart4TxFifoArray[UART_TX_FIFO_SIZE];
#endif

#ifdef HAS_UART6
static uint8_t Uart6RxFifoArray[100]={0};
static uint8_t Uart6TxFifoArray[UART_TX_FIFO_SIZE/4];
#endif

#ifdef HAS_UART7
static uint8_t Uart7RxFifoArray[20]={0};
static uint8_t Uart7TxFifoArray[UART_TX_FIFO_SIZE];
#endif


#ifdef HAS_UART8
static uint8_t Uart8RxFifoArray[100]={0};
static uint8_t Uart8TxFifoArray[UART_TX_FIFO_SIZE/4];
#endif

/*constant compile-time known settings*/
const UartConfig_t UartConfig[] = {


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
        .baud_rate = 9600,
        .stop_bit_cnt = 1,
        .word_len_bit = 8,
        .parity_check = false,
        .name = "GNSS,[EVA_M8M]",
        .RxPad = {.port = PORT_C, .pin = 11,},
        .TxPad = {.port = PORT_C, .pin = 10,},
        .dma = { .tx = false, .rx = false,},
        .interrupts_on = true,
        .irq_priority = 0,
        .momve_method = MOVE_MODE_INTERRUPT,
        .RxFifoArray = Uart3RxFifoArray,
        .rx_buff_size = sizeof(Uart3RxFifoArray),

        .TxFifoArray = Uart3TxFifoArray,
        .tx_buff_size = sizeof(Uart3TxFifoArray),
        .valid = true,
    },
#endif

#ifdef HAS_UART4
    {
        .num = 4,
        .baud_rate = 460800,
        .stop_bit_cnt = 1,
        .word_len_bit = 8,
        .parity_check = false,
        .name = "CLI",
       // .RxPad = {.port = PORT_C, .pin = 11,},
       // .TxPad = {.port = PORT_C, .pin = 10,},
        .dma = { .tx = false, .rx = false,},
        .interrupts_on = true,
        .irq_priority = 0,
        .momve_method = MOVE_MODE_INTERRUPT,
        .RxFifoArray = Uart4RxFifoArray,
        .rx_buff_size = sizeof(Uart4RxFifoArray),
        .TxFifoArray = Uart4TxFifoArray,
        .tx_buff_size = sizeof(Uart4TxFifoArray),
        .valid = true,
    },
#endif


#ifdef HAS_UART6
    { .num = 6,
      .baud_rate = 9600,
      .name = "LIN",
      // PC7  L9637D, Lin/Kline, USART6 RX
      .RxPad = {.port=PORT_C, .pin=7,},
      // PC6  L9637D, Lin/Kline, USART6 TX, тип PP
      .TxPad = {.port=PORT_C, .pin=6,},

      .parity_check = false,
      .dma = { .tx = false, .rx = false,},
      .stop_bit_cnt = 2,
      .interrupts_on = true,
      .irq_priority = 0,
      .momve_method = MOVE_MODE_INTERRUPT,
      .word_len_bit = 8,
      .rx_buff_size = sizeof(Uart6RxFifoArray),
      .RxFifoArray = Uart6RxFifoArray,

      .TxFifoArray = Uart6TxFifoArray,
      .tx_buff_size = sizeof(Uart6TxFifoArray),

      .valid=true,},
#endif

#ifdef HAS_UART7
    { .num = 7,
      .baud_rate = 460800,
      .name = "CLI",
      .RxPad = {.port=PORT_E, .pin=7,},
      .TxPad = {.port=PORT_E, .pin=8,},
      .dma = { .tx = false, .rx = false,},
      .interrupts_on = true,
      .irq_priority = 0,
      .momve_method = MOVE_MODE_INTERRUPT,
      .word_len_bit = 8,
      .stop_bit_cnt = 2,
      .rx_buff_size = sizeof(Uart7RxFifoArray),
      .RxFifoArray = Uart7RxFifoArray,
      .TxFifoArray = Uart7TxFifoArray,
      .tx_buff_size = sizeof(Uart7TxFifoArray),
      .parity_check = false,
      .valid = true,
    },
#endif

#ifdef HAS_UART8
    {
        .num = 8,
        .baud_rate = 115200,
        .stop_bit_cnt = 1,
        .word_len_bit = 8,
        .parity_check = false,
        .name = "ESP-01",
        //.RxPad = {.port = PORT_C, .pin = 11,},
        //.TxPad = {.port = PORT_C, .pin = 10,},
        .dma = { .tx = false, .rx = false,},
        .interrupts_on = true,
        .irq_priority = 0,
        .momve_method = MOVE_MODE_INTERRUPT,
        .RxFifoArray = Uart8RxFifoArray,
        .rx_buff_size = sizeof(Uart8RxFifoArray),

        .TxFifoArray = Uart8TxFifoArray,
        .tx_buff_size = sizeof(Uart8TxFifoArray),
        .valid = true,
    },
#endif
};

UartHandle_t UartInstance[]={

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

#ifdef HAS_UART4
    {
     .num = 4,
     .valid = true,
     .TxFifo = {
                  .err_cnt = 0,
                  .init_done = true,
                  .array = (uint8_t *)Uart4TxFifoArray,
                  .fifoState = {
                        .size = sizeof(Uart4TxFifoArray),
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

#ifdef HAS_UART7
    {.num = 7,
     .valid = true,
     .TxFifo={.err_cnt = 0,
              .init_done = true,
              .array = (uint8_t *)Uart7TxFifoArray,
              .fifoState={
                  .size=sizeof(Uart7TxFifoArray),
                  .start=0,
                  .end=0,
                  .count=0,
                  .errors=false,
              },
        },
    },
#endif

#ifdef HAS_UART8
    {.num = 8,
     .valid = true, .TxFifo = {.err_cnt = 0,
                               .init_done = true,
                               .array = Uart8TxFifoArray,
                               .fifoState = {
                                   .size = sizeof(Uart8TxFifoArray),
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
