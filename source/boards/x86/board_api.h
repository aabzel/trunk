#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "std_includes.h"

bool application_mcal_init(void);
bool board_init(void);
bool is_ram_addr(uint32_t addr) ;
bool application_launch(uint32_t base_address);

#endif /* BOARD_CONFIG_H */




