#ifndef CORE_CONST_H
#define CORE_CONST_H

#include "core_dep.h"

#define STACK_PATTERN 0xDEADBEEF
#define STACK_MONITOR_POLL_PERIOD_US 3000000

typedef enum {
    ARM_CORTEX_FPU_NO = 0,                      /*0: No FPU*/
    ARM_CORTEX_FPU_PRECISION_SINGLE = 1,        /*1: Single precision FPU*/
    ARM_CORTEX_FPU_PRECISION_DOUBLE_SINGLE = 2, /*2: Double + Single precision FPU*/
    ARM_CORTEX_FPU_UNDEF = 3,
} CortexFpu_t;


#endif /* CORE_CONST_H */
