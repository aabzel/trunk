#ifndef I2C_CUSTOM_DIAG_H
#define I2C_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "i2c_custom_types.h"
#include "i2c_application.h"


bool i2c_clkctrl_diag(double base_freq_hz, uint32_t qword);
bool i2c_raw_reg_diag(uint8_t num);
bool i2c_diag_custom(void);
const char* I2cClkCtrlToStr(const I2cClkCtrl_t* const ClkCtrl);
const char* I2cErrToStr( i2c_status_type ret);
char* I2cHalState2Str(uint8_t code);
char* I2cMode2Str(uint8_t code);
char* I2cBusRole2Str(uint8_t code );
char* I2cBusState2Str(uint8_t code );
char* I2cDir2Str(uint8_t code );


#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_DIAG_H */
