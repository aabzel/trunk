#ifndef MULTICORE_GENERAL_CONST_H
#define MULTICORE_GENERAL_CONST_H

#include "multicore_dep.h"

#define MULTICORE_COMPONENT_VERSION "3"


#define MULTICORE_POLL_PERIOD_US 5000000


typedef enum {
    CPU_CORE_0 = 0,
    CPU_CORE_1 = 1,
    CPU_CORE_2 = 2,
    CPU_CORE_UNDEF = 255,
}CpuCoreNumber_t;

#endif /* MULTICORE_GENERAL_CONST_H */
