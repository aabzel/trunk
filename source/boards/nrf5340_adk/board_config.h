#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>

#ifdef HAS_GPIO
#include "gpio_config.h"
#endif /*HAS_GPIO*/

#include "board_monitor.h"
#include "board_types.h"

#define XTAL_FREQ_HZ 32000000

extern const Wire_t Wires[];

bool board_init(void);
uint32_t wires_get_cnt(void);

#endif /* BOARD_CONFIG_H  */
