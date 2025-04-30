#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>
#include <stdbool.h>

#include "sys_config.h"
#include "gpio_config.h"

#define LED_COUNT 1
#define XTAL_FREQ_HZ 8000000

bool board_init(void);

#endif /* BOARD_CONFIG_H  */
