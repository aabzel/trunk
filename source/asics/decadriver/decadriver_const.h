#ifndef DECADRIVER_CONST_H
#define DECADRIVER_CONST_H

#include "decadriver_dependencies.h"
#include "time_mcal.h"

/* Default antenna delay values for 64 MHz PRF. See NOTE 1 below. */
#ifdef HAS_DW1000_CALIBRATE
#define TX_ANT_DLY 16436
#define RX_ANT_DLY 16436
#else
#define TX_ANT_DLY 0
#define RX_ANT_DLY 0
#endif

typedef enum {
    SPI_RATE_SLOW = 0,
    SPI_RATE_FAST = 1,

    SPI_RATE_UNDEF = 2,
} SpiRate_t;

#define DECADRIVER_PERIOD_US 1000

#define DWT_INT_ALL                                                                                                    \
    (DWT_INT_TFRS | DWT_INT_LDED | DWT_INT_RFCG | DWT_INT_RPHE | DWT_INT_RFCE | DWT_INT_RFSL | DWT_INT_RFTO |          \
     DWT_INT_RXOVRR | DWT_INT_RXPTO | DWT_INT_GPIO | DWT_INT_SFDT | DWT_INT_ARFE)

#define RX_BUF_LEN 1024

#endif /* DECADRIVER_CONST_H*/
