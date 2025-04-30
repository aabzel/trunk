#ifndef SCR1_TIMER_CONFIG_H
#define SCR1_TIMER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "scr1_timer_types.h"

#ifndef HAS_SCR1_TIMER
#error "+HAS_SCR1_TIMER"
#endif

extern Scr1TimerConfig_t Scr1TimerConfig;
extern Scr1Timer_t Scr1TimerInstance;


#ifdef __cplusplus
}
#endif

#endif // SCR1_TIMER_CONFIG_H
