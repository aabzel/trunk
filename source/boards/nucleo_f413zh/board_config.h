#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>

#include "sys_config.h"
#ifdef HAS_BOARD_INFO
#include "board_types.h"
#endif

#ifdef HAS_GPIO
#include "gpio_config.h"
#endif /*HAS_GPIO*/


#ifdef HAS_BOARD_INFO
extern const BoardConfig_t BoardConfig;
extern const Wire_t Wires[];
uint32_t wires_get_cnt(void);
#endif


bool board_init(void);

#endif /* BOARD_CONFIG_H  */
