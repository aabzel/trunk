#ifndef HEALTH_MONITOR_CONST_H
#define HEALTH_MONITOR_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_HEALTH_MONITOR
#error "+HAS_HEALTH_MONITOR"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#define ERR_MSG_SIZE 50
#define HEAL_MON_PERIOD_US (SEC_2_USEC(4))
#define SAVE_UP_TIME_PERIOD_MS (MIN_2_MS(5))

#define KL30_UNDERVOL_ERRPR_THRESHOLD_V 4.0f
#define KL30_UNDERVOL_WARNING_THRESHOLD_V 8.0f


#ifdef __cplusplus
}
#endif

#endif /* HEALTH_MONITOR_CONST_H */
