#ifndef BOARD_API_H
#define BOARD_API_H

#include "std_includes.h"

#include "sys_config.h"

#define BOARD_IDLE_TIME_OUT_MS 30000
#define BOARD_IDLE_TIME_OUT_ITER 1600000

#define BOARD_POLL_PERIOD_US 10000000

bool board_init_xip(void);
bool board_init(void);
bool application_launch(const uint32_t app_start_address) ;
bool application_mcal_init(void);
bool board_proc(void);

#endif /* BOARD_API_H  */
