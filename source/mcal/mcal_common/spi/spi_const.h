#ifndef SPI_GENERAL_CONST_H
#define SPI_GENERAL_CONST_H

#include "time_mcal.h"
#include "spi_dep.h"

#define SPI_VERSION "7"

#define SPI_NAME_SIZE_BYTE 30
#define SPI_TX_DONE_TIME_OUT_MS 2000
#define SPI_RX_DONE_TIME_OUT_MS 2000
#define SPI_POLL_PERIOD_US MSEC_2_USEC(500)

#define SPI_TIME_OUT_MS 3000

typedef enum {
    SPI_BIT_ORDER_MOST_SIGNIFICANT_BIT_FIRST = 1,
    SPI_BIT_ORDER_LEAST_SIGNIFICANT_BIT_FIRST = 2,
    SPI_BIT_ORDER_UNDEF = 0,
} SpiBitOrder_t;

typedef enum {
    SPI_POLARITY_LATCH_RISING = 1,
    SPI_POLARITY_LATCH_FALING = 2,
    SPI_POLARITY_UNDEF = 0,
} SpiPolarity_t;

typedef enum {
    SPI_CLK_IDLE_LEVEL_0 = 1, /*  */
    SPI_CLK_IDLE_LEVEL_1 = 2, /*  */
    SPI_CLK_IDLE_LEVEL_UNDEF = 0,
} SpiClkIdleLevel_t;

typedef enum {
    SPI_PHASE_0,
    SPI_PHASE_1
} SpiPhase_t;

typedef enum {
    SPI_DIRECTION_1WIRE = 1,
    SPI_DIRECTION_2WIRES= 2,
    SPI_DIRECTION_1WIRE_RX_ONLY = 3,
    SPI_DIRECTION_UNDEF = 0,
} SpiDirection_t;


typedef enum {
    SPI_CHIP_SEL_HW = 1,
    SPI_CHIP_SEL_SW = 2,
    SPI_CHIP_SEL_UNDEF = 0,
} ChipSelect_t;

typedef enum {
    SPI_CHIP_ENABLE = 1,
    SPI_CHIP_DISABLE = 2,

    SPI_CHIP_UNDEF = 0,
} ChipSelectSignal_t;


typedef enum {
  SPI_OP_MODE_SLAVE_TX  = 1, //He clocks, I transmit
  SPI_OP_MODE_SLAVE_RX  = 2, //He clocks,I receive
  SPI_OP_MODE_MASTER_TX = 3, //I clock, I transmit
  SPI_OP_MODE_MASTER_RX = 4,  //I clock, I receive
  SPI_OP_MODE_UNDEF = 0
} SpiOperationMode_t;

typedef enum {
    /* dual line unidirectional full-duplex mode*/
    SPI_TX_FULL_DUPLEX = 1,
    /* dual line unidirectional simplex receive-only mode*/
    SPI_TX_SIMPLEX_RX = 2,

    /* single line bidirectional half duplex mode-receiving*/
    SPI_TX_HALF_DUPLEX_RX = 3,
    /* single line bidirectional half duplex mode-receiving */
    SPI_TX_HALF_DUPLEX_TX = 4,

    SPI_TX_UNDEF = 0,
} SpiTxMode_t;

typedef enum {
    SPI_STATE_IDLE = 1,
    SPI_STATE_TX = 2,
    SPI_STATE_RX = 3,
    SPI_STATE_TX_RX = 4,

    SPI_STATE_UNDEF = 0,
} SpiState_t;

typedef enum {
    SPI_INPUT_NONE = 1,
    SPI_INPUT_TX_DONE = 2,
    SPI_INPUT_RX_DONE = 3,
    SPI_INPUT_UNDEF = 0,
} SpiInput_t;


#endif /* SPI_GENERAL_CONST_H */
