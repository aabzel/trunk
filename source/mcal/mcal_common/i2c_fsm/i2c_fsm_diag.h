#ifndef I2C_FSM_DIAG_H
#define I2C_FSM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#include "i2c_fsm_types.h"
#include "i2c_types.h"

const char* I2cFsmInputToStr(I2cFsmInput_t fsm_input);
const char* I2cFsmStateToStr(I2cFsmState_t fsm_state);
const char* I2cFsmOperationToStr(I2cFsmOperation_t operation);

bool i2c_fsm_diag(void);
bool i2c_fsm_diag_one(uint8_t num);
bool i2c_fsm_scan_base_diag(uint8_t num);
const char* I2cFsmNodeToStr(I2cHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_DIAG_H */
