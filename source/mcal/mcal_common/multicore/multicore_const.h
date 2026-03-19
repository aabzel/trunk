#ifndef MULTICORE_GENERAL_CONST_H
#define MULTICORE_GENERAL_CONST_H

#include "multicore_dep.h"

#define MULTICORE_COMPONENT_VERSION "1"

#define CORE_1_VECTOR_ADDR 0x01200000U
#define CORE_2_VECTOR_ADDR 0x01400000U

typedef enum {
    CPU_CORE_0 = 0,
    CPU_CORE_1 = 1,
    CPU_CORE_2 = 2,
    CPU_CORE_UNDEF = 255,
}CpuCoreNumber_t;

#endif /* MULTICORE_GENERAL_CONST_H */
