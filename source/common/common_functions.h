#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include "std_includes.h"
//#include "c_defines_generated.h"
#ifdef HAS_DIAG
#include "common_diag.h"
#endif

#ifdef HAS_SUPER_CYCLE

#ifndef HAS_LIMITER
#warning "+ HAS_LIMITER"
#endif

#ifndef HAS_SCHEDULER
#warning "+ HAS_SCHEDULER"
#endif /**/

#include "super_cycle_types.h"

#endif /**/

bool common_diag(void);

uint32_t ok_cnt_update(const uint32_t cur, const bool res) ;
bool try_init(bool status, uint32_t i, char* message);
bool ok_cnt_to_res(const uint32_t ok_cnt);

#ifdef HAS_SUPER_CYCLE
bool super_cycle_proc_ll(const SuperCycleHandle_t* const Node);
#endif /**/

#endif /* COMMON_FUNCTIONS_H */
