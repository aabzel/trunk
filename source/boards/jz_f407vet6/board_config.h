#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "gpio_config.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"
#endif

#ifndef USE_HAL_DRIVER
//#error "that file only for STM32 MCUs"
#endif

#define BOARD_POLL_PERIOD_US 100000
#define XTAL_FREQ_HZ 25000000

#ifdef HAS_BOARD_INFO
extern const Wire_t Wires[];
uint32_t wires_get_cnt(void);
#endif

bool board_init(void);
bool board_proc(void);
bool board_indicate_init_error(void);

#endif /* BOARD_CONFIG_H  */
