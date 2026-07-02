#ifndef I2S_STM_DIAG_H
#define I2S_STM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "stm32fx_hal.h"

const char* I2sOddToStr(uint8_t code);
const char* I2sBitToStr(uint8_t code);
const char* I2sRoleToStr(uint8_t code);
const char* SerialModeToStr(uint8_t code);
const char* I2sStdToStr(uint8_t code);
const char* I2sChlenToStr(uint8_t code);
const char* HalI2sStateToStr(HAL_I2S_StateTypeDef state);


bool i2s_custom_diag_low_level(void) ;
bool i2s_custom_diag(void) ;
bool i2s_custom_diag_sample(void);

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM_DIAG_H */
