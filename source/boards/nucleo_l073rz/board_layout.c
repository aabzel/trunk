#include "board_layout.h"

#include "data_utils.h"
#include "gpio_mcal.h"
#include "gpio_types.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "gpio_custom_const.h"

 
