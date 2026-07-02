#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include "std_includes.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "stm32f4xx_hal.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif

extern const GpioConfig_t GpioConfig[];

uint32_t gpio_get_cnt(void);

#endif /* GPIO_CONFIG_H  */
