#ifndef SUPER_CYCLE_H
#define SUPER_CYCLE_H

#include "std_includes.h"
#include "super_cycle_types.h"
#include "super_cycle_config.h"
#include "compiler_const.h"

#ifdef HAS_SUPER_CYCLE_DIAG
#include "super_cycle_diag.h"
#endif

#define SUPER_CYCLE_DEFAUIT_ITERATION_MS 3
/*API*/
const SuperCycleConfig_t* SuperCycleGetConfig(uint8_t num);
SuperCycleHandle_t* SuperCycleGetNode(uint8_t num);
bool super_cycle_mcal_init(void);
bool super_cycle_init_one(uint8_t num);
bool super_cycle_proc_max_perf(void);
bool super_cycle_proc(void);
bool super_cycle_proc_one(uint8_t num);

/*setters*/
void super_cycle_start_one(uint8_t num) ;

/*getters*/
bool super_cycle_check_continuity(SuperCycleHandle_t* const Node, uint64_t loop_start_time_us);
uint8_t super_cycle_core_to_num(void);
uint32_t super_cycle_run_time_ms(void);
uint64_t super_cycle_get_init_time_us(void);
uint64_t super_cycle_run_time_us(uint8_t num);


#endif /* SUPER_CYCLE_H */
