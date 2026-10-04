#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"
#include "sys_config.h"
#include "board_types.h"

#define LED_COUNT 1
#define XTAL_FREQ_HZ 8000000
extern const Wire_t Wires[];

bool board_init(void);
bool board_indicate_init_error(void);
uint32_t wires_get_cnt(void);

#endif /* BOARD_CONFIG_H  */
