#ifndef POWER_CONST_H
#define POWER_CONST_H

#include "power_dep.h"

#ifdef HAS_POWER_CUSTOM
#include "power_custom_const.h"
#endif

#define POWER_POLL_PERIOD_US MSEC_2_USEC(10)

typedef enum {
    POWER_MODE_ACTIVE= 1,
    POWER_MODE_SLEEP= 2,
    POWER_MODE_DEEPSLEEP= 4,
    POWER_MODE_STANDBY= 5,
    POWER_MODE_POWER_DOWN= 6,

    POWER_MODE_UNDEF = 0,
} PowerMode_t;





#endif /* POWER_CONST_H */
