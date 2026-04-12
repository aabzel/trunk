#ifndef I2C_FSM_F43X_DRV_H
#define I2C_FSM_F43X_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_types.h"
#include "connectivity_const.h"

I2cFsmState_t  ConnectivityDirToI2cFsmF43xState(ConnectivitDir_t direction);
bool i2c_fsm_f43x_input_get(I2cHandle_t* const Node);
bool i2c_fsm_f43x_generate_stop(I2cHandle_t* Node);

#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_F43X_DRV_H */
