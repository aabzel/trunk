#ifndef SUPER_CYCLE_H
#define SUPER_CYCLE_H


#include "std_includes.h"
#include "super_cycle_types.h"
#include "super_cycle_config.h"

void super_cycle_start(void);
bool super_cycle_init(void);
bool super_cycle_iteration(void);
bool super_cycle_check_continuity(SuperCycle_t* const Node, uint64_t loop_start_time_us);
uint64_t super_cycle_get_init_time_us(void);
uint64_t super_cycle_run_time_us(void);
uint32_t super_cycle_run_time_ms(void);


#endif /* SUPER_CYCLE_H */
