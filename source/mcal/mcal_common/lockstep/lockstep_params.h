#ifndef LOCKSTEP_PARAMS_H
#define LOCKSTEP_PARAMS_H

#include "storage_types.h"
#include "common_diag.h"

#define PARAMS_LOCKSTEP                               \
    {                                                 \
    .facility = LOCKSTEP,                             \
    .id = PAR_ID_LOCKSTEP_CNT,                        \
    .len = 4,                                         \
    .type = TYPE_UINT32,                              \
    .default_value = "0",                             \
    .name = "LockStepCnt",                            \
    .parser = U32DecToStr,                            \
    },

#endif /* LOCKSTEP_PARAMS_H */
