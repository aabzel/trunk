#ifndef TIM_CONFIG_H
#define TIM_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "tim_const.h"
#include "tim_types.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#define TIMER0_UPTIME_PERIOD_MS 88000

extern const TimerConfig_t TimerConfig[BOARD_GPTIMERPARTSCOUNT];
extern TimerHandle_t TimerInstance[BOARD_GPTIMERPARTSCOUNT];

#endif /* TIM_CONFIG_H  */
