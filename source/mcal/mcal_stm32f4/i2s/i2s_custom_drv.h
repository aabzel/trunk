#ifndef I2S_STM32_DRIVER_H
#define I2S_STM32_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "i2s_types.h"
#include "i2s_custom_types.h"
#include "stm32f4xx_hal.h"

SPI_TypeDef* I2sGetBaseAddr(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_DRIVER_H */
