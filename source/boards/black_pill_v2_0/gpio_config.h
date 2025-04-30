#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include <stdint.h>

#include "gpio_mcal.h"
#include "gpio_types.h"

#include "sys_config.h"
#include "stm32f4xx_hal.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

extern GpioConfig_t GpioConfig[];
uint32_t gpio_get_cnt(void);

#endif /* GPIO_CONFIG_H  */
