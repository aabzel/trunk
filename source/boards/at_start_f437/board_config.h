#ifndef BOARD_LAYOUT_H
#define BOARD_CONFIG_H

#include "std_includes.h"
//#include "sys_config.h"
#include "gpio_config.h"
#include "at_start_f437_const.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"

extern const BoardConfig_t BoardConfig;


extern const Wire_t Wires[];
uint32_t wires_get_cnt(void);
#endif

bool board_init(void);

#endif /* BOARD_CONFIG_H  */
