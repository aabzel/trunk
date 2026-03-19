#ifndef I2C_FSM_GENERAL_CONST_H
#define I2C_FSM_GENERAL_CONST_H

#include "i2c_fsm_dep.h"

#define I2C_FSM_TIMEOUT_MS 1250U
#define I2C_FSM_STOP_WAIT_TIMEOUT_MS 200U
#define I2C_FSM_CHIP_ADDR_ACK_WAIT_TIMEOUT_MS 800U
#define I2C_FSM_CHIP_READ_DATA_TIMEOUT_MS 800U
#define I2C_FSM_MEM_ADDRESS_ACK_WAIT_TIMEOUT_MS 800U

typedef enum {
    I2C_FSM_OPERATION_EMPTY = 1,
    I2C_FSM_OPERATION_CHECK_ADDR= 2,
    I2C_FSM_OPERATION_WRITE = 3,
    I2C_FSM_OPERATION_RAED = 4,
    I2C_FSM_OPERATION_WRITE_MEM = 5,
    I2C_FSM_OPERATION_READ_MEM = 6,
    I2C_FSM_OPERATION_NOP = 7,
    I2C_FSM_OPERATION_UNDEF = 0,
} I2cFsmOperation_t;

typedef enum {
    I2C_FSM_STATE_IDLE = 1,
    I2C_FSM_STATE_WAIT_START1 = 2,// wait start done
    I2C_FSM_STATE_WAIT_TX_7BIT_ADDR = 3, // wait tx done
    I2C_FSM_STATE_WAIT_TX_DATA = 4,// wait data tx done (register address)
    I2C_FSM_STATE_WAIT_START2 = 5,// wait second start done
    I2C_FSM_STATE_WAIT_TX_CHIP_READ_ADDR = 6, // wait chip read addr
    I2C_FSM_STATE_WAIT_READ_DATA = 7, // wait chip read data
    I2C_FSM_STATE_WAIT_TX_STOP = 8,// wait stop done
    I2C_FSM_STATE_WAIT_BUSY = 9,// wait busy
    I2C_FSM_STATE_UNDEF = 0,
} I2cFsmState_t;

typedef enum {
    I2C_FSM_INPUT_NONE = 1, // No Operation
    I2C_FSM_INPUT_TX_DATA_BUFF_EMPTY = 2,//transmit data buffer empty flag. tdbe
    I2C_FSM_INPUT_RX_DATA_FULL = 3,// RDBF, got byte from slave RDBF ,Receive data buffer full flag
    I2C_FSM_INPUT_TX_MODE = 4,// TRMODE transmission mode
    I2C_FSM_INPUT_TX_DATA_DONE = 5,// transmit data complete flag. Data transfer complete flag
    I2C_FSM_INPUT_TX_DIR = 6,// transmission direction flag. DIRF
    I2C_FSM_INPUT_TX_DATA_INTERR_STATUS = 31,//tdis
    I2C_FSM_INPUT_CHIP_ADDR_ACK_TIMEOUT = 7, //
    I2C_FSM_INPUT_ACKNOWLEDGE_FAIL = 8, // ACKFAIL
    I2C_FSM_INPUT_READ_DATA_TIMEOUT = 9, //
    I2C_FSM_INPUT_RX_ACK_TIMEOUT = 10, // Rx acknowledgment time out
    I2C_FSM_INPUT_START_SIGNAL_TIMEOUT = 12,//
    I2C_FSM_INPUT_TIME_OUT = 13, // Time Out
    I2C_FSM_INPUT_BUS_BUSY = 14, //
    I2C_FSM_INPUT_BUS_ERROR = 15, //Bus error flag
    I2C_FSM_INPUT_START_DONE = 16,//start condition generation complete flag.
    I2C_FSM_INPUT_STOP_SIGNAL_TIMEOUT = 17,//
    I2C_FSM_INPUT_STOP_SIGNAL_DONE = 18,// stop condition generation complete flag.
    //I2C_FSM_INPUT_7BITADDR_ACK = 3,//i2c 0~7 bit address match flag
    I2C_FSM_INPUT_RX_ACK = 19,//i2c got acknowledgment signal
    I2C_FSM_INPUT_OWN_ADDRESS_2_RX = 20,//
    I2C_FSM_INPUT_GENERATE_START = 21,//
    I2C_FSM_INPUT_ADDRH_9_8_ACK = 22,//
    I2C_FSM_INPUT_OVERFLOW_OR_UNDERFLOW = 23,//Overrun or underrun flag
    I2C_FSM_INPUT_RX_PEC = 24,//
    I2C_FSM_INPUT_SMBUS_TIMEOUT = 25,//
    I2C_FSM_INPUT_SMBUS_ALERT = 26,//
    I2C_FSM_INPUT_SLAVE_SENDS_DATA = 27,//
    I2C_FSM_INPUT_PEC_RX_ERROR = 28,//
    I2C_FSM_INPUT_ADDR_HEAD_MATCH = 29,//
    I2C_FSM_INPUT_TX_DONE_WAIT_LOAD = 30,//Data transfer complete, waiting for data load
    I2C_FSM_INPUT_ARBITRATION_LOST = 32,//Arbitration lost flag
    I2C_FSM_INPUT_GENERAL_CALL_ADDRESS_RECEIVED = 33,//
    I2C_FSM_INPUT_SMBUS_DEVICE_ADDRESS_RX = 34,//
    I2C_FSM_INPUT_SMBUS_HOST_ADDRESS_RX = 35,//

    I2C_FSM_INPUT_UNDEF = 0,
} I2cFsmInput_t;


#endif /* I2C_FSM_GENERAL_CONST_H */
