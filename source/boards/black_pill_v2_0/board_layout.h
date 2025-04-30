#ifndef BOARD_LAYOUT_H
#define BOARD_LAYOUT_H

#include <stdint.h>

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#include "gpio_types.h"
#endif

#include "sys_config.h"
#include "stm32f4xx_hal.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/



#endif /* BOARD_LAYOUT_H  */
