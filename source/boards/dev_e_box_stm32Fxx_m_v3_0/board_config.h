#ifndef BOARD_LAYOUT_H
#define BOARD_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_config.h"

#ifndef USE_HAL_DRIVER
#error "that file only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#define XTAL_FREQ_HZ 12000000

bool board_init(void);

#endif /* BOARD_CONFIG_H  */
