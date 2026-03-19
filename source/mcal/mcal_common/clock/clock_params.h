#ifndef CLOCK_PARAMS_H
#define CLOCK_PARAMS_H

#include "storage_types.h"
#include "common_diag.h"

#ifdef  HAS_CLOCK_CUSTOM
#include "clock_custom_params.h"
#else
#define PARAMS_CLOCK_CUSTOM
#endif

#ifdef HAS_DIAG
#define PARAM_CLOCK_SYS_CLOCK_HZ_PARSER  .parser = U32DecToStr,
#else
#define PARAM_CLOCK_SYS_CLOCK_HZ_PARSER
#endif

#define PARAMS_CLOCK                                  \
    PARAMS_CLOCK_CUSTOM                               \
    {                                                 \
    .len = 4,                                         \
    .facility = CLOCK,                                \
    .id = PAR_ID_SYS_CLOCK_HZ,                        \
    .type = TYPE_UINT32,                              \
    .default_value = "150000000",                     \
    .name = "SysClockHz",                             \
    PARAM_CLOCK_SYS_CLOCK_HZ_PARSER                   \
    },

#endif /* CLOCK_PARAMS_H */
