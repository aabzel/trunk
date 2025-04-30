#ifndef UART_GEN_CONST_H
#define UART_GEN_CONST_H

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#define UART_POLL_PERIOD_US 100000
#define UART_TX_TIME_OUT_MS 2500
#define UART_TX_TIMEOUT_MS 1000U
#define UART_RX_TIMEOUT_MS 300

#define UART_RX_ARRAY_SIZE 12U
#define UART_RX_FIFO_ARRAY_SIZE 20

#define UART_TX_BUFF_SIZE (20)

#define UART_TX_FIFO_SIZE (256)
#define UART_RX_FIFO_SIZE 64


typedef enum {
    UART_BAUDRATE_MIN = 110, /*Bit/s*/
    UART_BAUDRATE_MAX = 921600, /*Bit/s*/
} UartBaudrate_t;

typedef enum {
    UART_ERROR_PE,
    UART_ERROR_FE,
    UART_ERROR_NE,
    UART_ERROR_ORE
} RxUartError_t;


#endif /* UART_GEN_CONST_H */
