#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "sys_config.h"
#include "stm32f4xx_hal.h"
#include "gpio_config.h"
#include "board_types.h"



#define XTAL_FREQ_HZ 12000000

#define SYSTEM_DEBUG_PORT PORT_A
#define SYSTEM_DEBUG_PIN 1

extern const Wire_t Wires[];

bool board_init(void);
bool board_indicate_init_error(void);
uint32_t wires_get_cnt(void);

#endif /* BOARD_CONFIG_H  */
