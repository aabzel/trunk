#ifndef UART_GEN_CONST_H
#define UART_GEN_CONST_H

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#include "uart_dep.h"

#define UART_POLL_PERIOD_US 100000
#define UART_HEARTBEAT_PERIOD_US 5000000
#define UART_TX_FIFO_WAIT_TIMEOUT_MS 100
#define UART_TX_TIME_OUT_MS 2500
#define UART_TX_TIMEOUT_MS 1000U
#define UART_RX_TIMEOUT_MS 300

#define UART_RX_ARRAY_SIZE 12U
#define UART_RX_FIFO_ARRAY_SIZE 20

#define UART_TX_BUFF_SIZE (20)

#define UART_TX_FIFO_SIZE (512)
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


typedef enum {
    UART_MCAL_PARITY_UNDEF = 0,
    UART_MCAL_PARITY_NONE,
    UART_MCAL_PARITY_ODD,
    UART_MCAL_PARITY_EVEN,
} UartParity_t;





#endif /* UART_GEN_CONST_H */
