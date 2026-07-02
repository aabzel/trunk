#ifndef SUPER_CYCLE_CORE_CONFIG_H
#define SUPER_CYCLE_CORE_CONFIG_H

#include "std_includes.h"
#include "super_cycle_types.h"

typedef enum {
   SUPER_CYCLE_CORE_0 = 1,
   SUPER_CYCLE_CORE_UNDEF = 0,
}LegalSuperCycle_t;


extern const SuperCycleConfig_t SuperCycleConfig[];
extern SuperCycleHandle_t SuperCycleInstance[];

uint32_t super_cycle_get_cnt(void);

#endif /* SUPER_CYCLE_CORE_CONFIG_H  */

