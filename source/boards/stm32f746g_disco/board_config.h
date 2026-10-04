#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "sys_config.h"
#include "gpio_config.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"
#endif

#define LED_COUNT 1
#define XTAL_FREQ_HZ 25000000
#define PCB_NAME "SRF70-1302-STM32F746G_DISCO"

#define SYSTEM_DEBUG_PORT PORT_I
#define SYSTEM_DEBUG_PIN 1

#ifdef HAS_BOARD_INFO
extern const Wire_t Wires[];
#endif

bool board_init(void);
uint32_t wires_get_cnt(void);
bool board_indicate_init_error(void);

#endif /* BOARD_CONFIG_H  */
