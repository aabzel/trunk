#ifndef TIMER_CONFIG_GENERAL_H
#define TIMER_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "timer_types.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

extern const TimerConfig_t TimerConfig[];
extern TimerHandle_t TimerInstance[];

uint32_t timer_get_cnt(void);

#endif /* TIMER_CONFIG_GENERAL_H  */
