#ifndef BOARD_API_H
#define BOARD_API_H

#include "std_includes.h"

#include "sys_config.h"

#define BOARD_IDLE_TIME_OUT_ITER 400000

bool board_init_xip(void);
bool board_init(void);
bool application_launch(void);
bool application_mcal_init(void);
bool board_proc(void);

#endif /* BOARD_API_H  */
