#ifndef CLOCK_PARAMS_H
#define CLOCK_PARAMS_H

#include "param_types.h"


#define PARAMS_CLOCK                                \
    {                                               \
    .facility=CLOCK,                                \
    .id=PAR_ID_SYS_CLOCK_HZ,                        \
    .len=4,                                         \
    .type=TYPE_UINT32,                              \
    .default_value="200000000",                     \
    .name="SysClockHz"                              \
    },

#endif /* CLOCK_PARAMS_H  */
