#ifndef SOFTWARE_TIMER_ISR_H
#define SOFTWARE_TIMER_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "software_timer.h"

bool sw_timer_proc(void);

#ifdef __cplusplus
}
#endif

#endif /* SOFTWARE_TIMER_ISR_H */
