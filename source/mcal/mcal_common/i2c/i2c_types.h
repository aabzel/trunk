#ifndef I2C_MCAL_TYPES_H
#define I2C_MCAL_TYPES_H

#include "std_includes.h"
#include "data_types.h"
#include "gpio_types.h"
#include "i2c_const.h"
#include "interfaces_types.h"

#ifdef HAS_I2C_CUSTOM
#include "i2c_custom_types.h"
#else
#define I2C_CUSTOM_TYPES
#endif

#ifdef HAS_I2C_FSM
#include "i2c_fsm_types.h"
#else
#define I2C_FSM_TYPES
#endif

typedef struct {
    bool main;
    uint8_t chip_addr;
    uint8_t chip_addr_read;
    uint8_t chip_addr_write;
    char* name;
} I2cRecord_t;

#define I2C_COMMAN_VARIABLES                                                                                           \
    bool valid;                                                                                                        \
    uint8_t num;                                                                                                       \
    bool interrupt_on;

typedef struct {
    I2C_COMMAN_VARIABLES
    uint32_t clock_speed;
    char* name;
    uint16_t own_addr;
    uint8_t interrupt_priority;
#ifdef HAS_GPIO
    Pad_t PadScl;
    Pad_t PadSda;
#endif
} I2cConfig_t;

#define I2C_TX_INTERRUPT_VARIABLES    \
    volatile uint32_t tx_cpl_cnt;                                                                                      \
    volatile bool tx_int;                                                                                              \
    volatile bool tx_done;                                                                                             \
    volatile uint32_t tx_cnt;

#define I2C_RX_INTERRUPT_VARIABLES    \
    volatile bool rx_done;                                                                                             \
    volatile bool rx_int;                                                                                              \
    volatile uint8_t rx_byte;                                                                                          \
    volatile uint8_t* rx_buff;                                                                                         \
    volatile uint32_t rx_cnt;

#define I2C_INTERRUPT_VARIABLES   \
    I2C_TX_INTERRUPT_VARIABLES  \
    I2C_RX_INTERRUPT_VARIABLES  \
    volatile bool err_done;                                                                                            \
    volatile bool in_progress;                                                                                         \
    volatile bool it_done;                                                                                             \
    volatile bool stop_done;                                                                                           \
    volatile bool rx_it_proc_done;                                                                                     \
    volatile bool address_match;                                                                                       \
    volatile bool done_it;                                                                                             \
    volatile bool ack_fail;                                                                                            \
    volatile bool ack_done;                                                                                            \
    volatile FlowCnt_t cnt;                                                                                            \
    volatile uint32_t error_cnt;                                                                                       \
    volatile uint32_t done_cnt;                                                                                        \
    volatile uint32_t error_overrun_cnt;                                                                               \
    volatile uint32_t error_nack_cnt;                                                                                  \
    volatile uint32_t error_bus_cnt;                                                                                   \
    volatile uint32_t error_data_cnt;                                                                                  \
    volatile uint32_t it_cnt;

typedef struct {
    I2C_FSM_TYPES
    I2C_COMMAN_VARIABLES
    I2C_INTERRUPT_VARIABLES
    I2C_CUSTOM_TYPES

  //  bool unknown_chip;

//    uint32_t tx_size;
    uint32_t read_size; //TODO use RxDataSize from FSM
    uint32_t chip_addr10;


    uint32_t total_read_byte;
    uint32_t total_write_byte;
    volatile uint8_t slave_addr;     // base address
    uint8_t rx_byte_it;
    uint32_t tx_time_out;
    U32Value_t tx_rate;
    U32Value_t rx_rate;
    FlowCnt_t cnt_prev;
    uint32_t rx_buff_size;
    uint32_t error_cnt_prev;

    bool init_done;
} I2cHandle_t;


#endif /* I2C_MCAL_TYPES_H */
