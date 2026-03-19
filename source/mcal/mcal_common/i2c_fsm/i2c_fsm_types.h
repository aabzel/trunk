#ifndef I2C_FSM_TYPES_H
#define I2C_FSM_TYPES_H

#include <stdint.h>

#include "i2c_fsm_const.h"


#define I2C_FSM_RX_TYPES                               \
    volatile uint32_t rx_index;                        \
    volatile uint8_t* RxData;                          \
    volatile uint32_t RxDataSize;


#define I2C_FSM_TX_TYPES                               \
    volatile uint32_t tx_index;                        \
    volatile uint8_t* TxData;                          \
    volatile uint32_t TxDataSize;

#define I2C_FSM_TYPES                                  \
    I2C_FSM_TX_TYPES                                   \
    I2C_FSM_RX_TYPES                                   \
    uint32_t state_start_ms;                           \
    uint32_t start_ms;                                 \
    uint32_t spin_cnt;                                 \
    volatile bool spot_chip;                           \
    volatile bool fsm_input_exist;                     \
    volatile bool loop;                                \
    volatile I2cFsmState_t fsm_state;                  \
    volatile I2cFsmOperation_t fsm_operation;          \
    volatile I2cFsmInput_t fsm_input;                  \
    uint32_t fsm_input_cnt;

//    uint8_t reg_address; /*internal ASIC address*/
//    uint32_t stop_start_ms;
//    uint32_t start_start_ms;



#endif /* I2C_FSM_TYPES_H */
