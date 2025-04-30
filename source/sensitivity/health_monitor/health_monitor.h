#ifndef HEALTH_MONITOR_H
#define HEALTH_MONITOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_CLOCK
#include "clock.h" //TODO DEL
#endif /*HAS_CLOCK*/

#ifndef HAS_HEALTH_MONITOR
#error "+HAS_HEALTH_MONITOR"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#include "health_monitor_types.h"

extern HealthMon_t HealthMon;

bool health_monitor_reset(void);
bool health_monotor_init(void);
bool health_monotor_proc(void);
bool health_monotor_save_up_time(void);

#ifdef __cplusplus
}
#endif

#endif /* HEALTH_MONITOR_H */
