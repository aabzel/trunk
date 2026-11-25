#ifndef I2C_FSM_CUSTOM_DRV_H
#define I2C_FSM_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "i2c_mcal.h"
#include "i2c_fsm_diag.h"
#include "i2c_fsm_types.h"
#include "mcal_types.h"


bool i2c_fsm_proc_wait_chip_addr_ack_in_ack(I2cHandle_t* Node);
bool i2c_fsm_input_get(I2cHandle_t* const Node);
bool i2c_fsm_generate_start(I2cHandle_t* Node, uint8_t number) ;
bool i2c_fsm_generate_stop(I2cHandle_t *Node) ;
bool i2c_fsm_reinit_one(uint8_t num);

bool i2c_fsm_proc_frame_idle(I2cHandle_t* Node);
bool i2c_fsm_proc_frame_wait_start1_done(I2cHandle_t* Node);
bool i2c_fsm_proc_frame_wait_tx_7bitaddr_done(I2cHandle_t* Node);
bool i2c_fsm_proc_frame_wait_tx_data_done(I2cHandle_t *Node);
bool i2c_fsm_proc_frame_wait_start2_done(I2cHandle_t* Node);
bool i2c_fsm_proc_frame_wait_chip_read_addr_done(I2cHandle_t *Node);
bool i2c_fsm_proc_frame_wait_read_data(I2cHandle_t *Node) ;
bool i2c_fsm_proc_frame_wait_stop_done(I2cHandle_t* Node);
bool i2c_fsm_proc_frame_wait_busy(I2cHandle_t* Node);
bool i2c_fsm_proc_timeout(I2cHandle_t* Node);

//bool i2c_fsm_input_get( I2cHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_CUSTOM_DRV_H */
