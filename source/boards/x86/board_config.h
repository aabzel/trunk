#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"

bool board_init(void);
bool is_ram_addr(uint32_t addr) ;
bool board_boost(bool on_off) ;

#endif /* BOARD_CONFIG_H */




