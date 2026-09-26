#ifndef I2C_FSM_F413_DRV_H
#define I2C_FSM_F413_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_types.h"

bool i2c_fsm_f413x_input_get(I2cHandle_t* const Node);
bool i2c_fsm_f413x_generate_stop(I2cHandle_t* Node);
//bool i2c_fsm_proc_wait_chip_addr_ack_in_ack(I2cHandle_t* Node);

#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_F413_DRV_H */
