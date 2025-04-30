#ifndef I2S_STM_DIAG_H
#define I2S_STM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "stm32f4xx_hal.h"

const char* I2sOdd2Str(uint8_t code);
const char* I2sBit2Str(uint8_t code);
const char* I2sRole2Str(uint8_t code);
const char* SerialMode2Str(uint8_t code);
const char* I2sStd2Str(uint8_t code);
const char* I2sChlen2Str(uint8_t code);
const char* HalI2sState2Str(HAL_I2S_StateTypeDef state);

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM_DIAG_H */
