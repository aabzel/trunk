#ifndef SWD_GEN_CONST_H
#define SWD_GEN_CONST_H

#ifndef HAS_SWD
#error "+HAS_SWD"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#define SWD_PERIOD_US 1

#define SWD_TX_TIME_OUT_MS 5000

#define SWD_TX_TIMEOUT_MS 4000U
#define SWD_RX_TIMEOUT_MS 300

#define SWD_RX_ARRAY_SIZE 500U
#define SWD_TX_ARRAY_SIZE 600U

#define SWD_TX_BUFF_SIZE (800U)

#define SWD_RX_FIFO_ARRAY_SIZE 100U

#define SWD_TX_FIFO_SIZE (2048*2)
#define SWD_RX_FIFO_SIZE 256

#define SWD_POLL_PERIOD_US 10000

#define SWD_MIN_BAUDRATE 110 /*Bit/s*/
#define SWD_MAX_BAUDRATE 921600 /*Bit/s*/


typedef enum {
    SWD_ERROR_PE,
    SWD_ERROR_FE,
    SWD_ERROR_NE,
    SWD_ERROR_ORE
} RxSwdError_t;


#endif /* SWD_GEN_CONST_H */
