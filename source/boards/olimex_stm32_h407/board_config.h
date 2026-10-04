#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_config.h"
#include "board_types.h"

#ifndef USE_HAL_DRIVER
#error "that file only for STM32 MCUs"
#endif

extern const Wire_t Wires[];

#define XTAL_FREQ_HZ (HSE_VALUE)

#define SYSTEM_DEBUG_PORT PORT_C
#define SYSTEM_DEBUG_PIN 13

uint32_t wires_get_cnt(void);
bool keyboard_reboot(void);
bool board_init(void);

#endif /* BOARD_CONFIG_H  */
