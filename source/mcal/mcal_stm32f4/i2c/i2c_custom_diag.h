#ifndef I2C_STM_DIAG_H
#define I2C_STM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stm32f4xx_hal.h"

char* I2cHalState2Str(uint8_t code);
char* I2cMode2Str(uint8_t code);
char* I2cBusRole2Str(uint8_t code );
char* I2cBusState2Str(uint8_t code );
char* I2cDir2Str(uint8_t code );
int8_t get_i2c_index(I2C_TypeDef* I2Cx) ;

#ifdef __cplusplus
}
#endif

#endif /* I2C_STM_DIAG_H */
