#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#include <stdbool.h>
#include <stdint.h>

//#include "c_defines_generated.h"

#ifdef HAS_SUPER_CYCLE

#ifndef HAS_LIMITER
#warning "+ HAS_LIMITER"
#endif

#ifndef HAS_TASK
#warning "+ HAS_TASK"
#endif /*HAS_TASKS*/

#endif /*HAS_SUPER_CYCLE*/

bool try_init(bool status, char* message);

#ifdef HAS_SUPER_CYCLE
void super_cycle_proc(uint64_t loop_start_time);
#endif /*HAS_SUPER_CYCLE*/

#endif /* COMMON_FUNCTIONS_H */
