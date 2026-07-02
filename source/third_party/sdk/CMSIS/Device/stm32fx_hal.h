#ifndef STM32FX_H
#define STM32FX_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_STM32F4X
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal.h"
#endif

#ifdef HAS_STM32F7X
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32FX_H */
