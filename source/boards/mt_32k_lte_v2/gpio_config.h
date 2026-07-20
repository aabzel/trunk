#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H

#include "std_includes.h"
#include "gpio_mcal.h"
#include "gpio_types.h"

#include "sys_config.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif

#define SYSTEM_DEBUG_PORT PORT_A
#define SYSTEM_DEBUG_PIN 6

extern const GpioConfig_t GpioConfig[];

uint32_t gpio_get_cnt(void);

#endif /* GPIO_CONFIG_H  */
