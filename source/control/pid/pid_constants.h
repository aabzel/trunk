#ifndef PID_CONSTANTS_H
#define PID_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "pid_dep.h"
#include "time_mcal.h"



#define PID_POLL_PERIOD_US MSEC_2_USEC(1)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*PID_CONSTANTS_H*/
