#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>

//#include "sys_config.h"
//#include "stm32f4xx_hal.h"
#ifdef HAS_GPIO
#include "gpio_config.h"
#endif /*HAS_GPIO*/

#ifndef USE_HAL_DRIVER
#error "that wile only for STM32 MCUs"
#endif /*USE_HAL_DRIVER*/

#include "board_types.h"

#define XTAL_FREQ_HZ 16000000

extern const Wire_t Wires[];

bool board_init(void);
uint32_t wires_get_cnt(void);

#endif /* BOARD_CONFIG_H  */
