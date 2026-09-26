#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_config.h"
#include "board_types.h"

/*
https://stm32-base.org/boards/STM32F407ZGT6-STM32F4XX.html
*/
#define XTAL_FREQ_HZ 8000000

#define SYSTEM_DEBUG_PORT PORT_F
#define SYSTEM_DEBUG_PIN 9

extern const Wire_t Wires[];

bool board_init(void);
bool board_boost(bool on_off);
bool board_indicate_init_error(void);
uint32_t wires_get_cnt(void);

#endif /* BOARD_CONFIG_H  */
