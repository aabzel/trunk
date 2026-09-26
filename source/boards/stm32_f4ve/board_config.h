#ifndef BOARD_LAYOUT_H
#define BOARD_CONFIG_H

#include "std_includes.h"

#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_config.h"
#include "board_types.h"

#ifndef USE_HAL_DRIVER
#error "that file only for STM32 MCUs"
#endif

#define SYSTEM_DEBUG_PORT PORT_A
#define SYSTEM_DEBUG_PIN 6

#define XTAL_FREQ_HZ 8000000

extern const Wire_t Wires[];

uint32_t wires_get_cnt(void);
bool board_init(void);
bool board_indicate_init_error(void);

#endif /* BOARD_CONFIG_H  */
