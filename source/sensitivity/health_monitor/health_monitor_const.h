#ifndef HEALTH_MONITOR_CONST_H
#define HEALTH_MONITOR_CONST_H


#ifndef HAS_HEALTH_MONITOR
#error "+HAS_HEALTH_MONITOR"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#define ERR_MSG_SIZE 50

#ifdef HAS_TIME
#define HEAL_MON_PERIOD_US (SEC_2_USEC(20))
#define SAVE_UP_TIME_PERIOD_MS (MIN_2_MS(5))
#else
#define HEAL_MON_PERIOD_US ((20000000))
#endif

#endif /* HEALTH_MONITOR_CONST_H */
