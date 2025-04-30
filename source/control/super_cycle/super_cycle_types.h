#ifndef SUPER_CYCLE_TYPES_H
#define SUPER_CYCLE_TYPES_H

#include "std_includes.h"

#ifdef HAS_MISCELLANEOUS
#include "data_types.h"
#endif
#include "super_cycle_dep.h"

typedef struct {
   uint64_t init_end_time_us;
   uint32_t init_end_time_ms;
   volatile uint64_t start_time_us;
   volatile uint32_t start_time_ms;
   uint32_t error;
   uint64_t prev_start_time_us;
   uint64_t spin_cnt;
#ifdef HAS_MISCELLANEOUS
   U32Value_t duration_us;
#endif
   int32_t iteration_sleep_ms;
   bool run;
   bool init;
}SuperCycle_t;


#endif /* SUPER_CYCLE_TYPES_H */
