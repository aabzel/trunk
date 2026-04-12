#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "dummy_board_const.h"

#ifdef HAS_GPIO
#include "gpio_config.h"
#endif


#ifdef HAS_BOARD_INFO
#include "board_types.h"

extern const BoardConfig_t BoardConfig;


extern const Wire_t Wires[];
uint32_t wires_get_cnt(void);
#endif

bool board_init(void);

#endif /* BOARD_CONFIG_H  */
