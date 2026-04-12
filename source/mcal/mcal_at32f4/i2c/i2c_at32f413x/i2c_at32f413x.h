#ifndef I2C_AT32F413X_DRV_H
#define I2C_AT32F413X_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_types.h"
#include "connectivity_const.h"

bool i2c_at32f413x_clear_ackfail_event(I2cHandle_t* Node);
bool i2c_at32f413x_clear_addr7f_flag(I2cHandle_t* Node);
bool i2c_at32f413x_clear_rdbf_events(I2cHandle_t* Node);
bool i2c_at32f413x_clear_start_done_event(I2cHandle_t* Node);
bool i2c_at32f413x_clear_stop_event(I2cHandle_t* Node);
bool i2c_at32f413x_clear_events(I2cHandle_t* Node);
bool i2c_at32f413x_init_tx_ll(I2cHandle_t* const Node, ConnectivitDir_t direction);
bool i2c_at32f413x_interrupts_disable_ll(I2cHandle_t* const Node);
bool i2c_at32f413x_tx_byte(I2cHandle_t* Node, uint8_t byte_data);

#ifdef __cplusplus
}
#endif

#endif /* I2C_AT32F413X_DRV_H */
