#ifndef BOARD_LAYOUT_H
#define BOARD_LAYOUT_H

#include <stdint.h>

#include "gpio_mcal.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_types.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/


extern Pin_t PinTable[];

uint32_t pin_get_cnt(void);

#endif /* BOARD_LAYOUT_H  */
