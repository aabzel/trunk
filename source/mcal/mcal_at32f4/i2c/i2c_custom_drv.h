#ifndef I2C_CUSTOM_DRIVER_H
#define I2C_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_types.h"
#include "i2c_custom_diag.h"
#include "i2c_custom_types.h"
#include "i2c_custom_isr.h"
#include "mcal_types.h"
#include "std_includes.h"

#ifdef HAS_AT32F413X
#include "i2c_at32f413x.h"
#endif

#ifdef HAS_AT32F43X
#include "i2c_at32f43x.h"
#endif

extern const Reg32_t I2cReg[];

bool i2c_check_addr_v0(uint8_t num, uint8_t i2c_addr);
bool i2c_div_set(uint8_t num, uint8_t div);
bool i2c_div_get(uint8_t num, uint8_t* const div);
uint32_t I2cCalcArteryClkCtrlQword(double i2c_freq_hz, double apb1_freq_hz);

#ifdef HAS_AT32F43X
bool i2c_at32f43x_check_addr(uint8_t num, uint8_t i2c_addr) ;
#endif


#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_DRIVER_H */
