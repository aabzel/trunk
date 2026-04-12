#ifndef I2C_AT32F43X_DRV_H
#define I2C_AT32F43X_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_types.h"
#include "connectivity_const.h"

bool i2c_at32f43x_clear_rdbf_events(I2cHandle_t* const Node);
bool i2c_at32f43x_clear_ackfail_event(I2cHandle_t* const Node);
bool i2c_at32f43x_clear_events(I2cHandle_t* const Node);
bool i2c_at32f43x_clear_stop_event(I2cHandle_t* const Node);
bool i2c_at32f43x_init_tx_ll(I2cHandle_t* const Node, ConnectivitDir_t direction);
bool i2c_at32f43x_interrupts_disable_ll(I2cHandle_t* const Node);
bool i2c_at32f43x_tx_byte(I2cHandle_t* const  Node, uint8_t byte_data);

#ifdef __cplusplus
}
#endif

#endif /* I2C_AT32F43X_DRV_H */
