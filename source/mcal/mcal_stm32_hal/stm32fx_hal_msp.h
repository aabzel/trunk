#ifndef STM32FX_HAL_MSP_H
#define STM32FX_HAL_MSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32fx_hal.h"

void HAL_MspInit(void);
void HAL_Delay(uint32_t Delay);

#ifdef __cplusplus
}
#endif

#endif /* STM32FX_HAL_MSP_H */
