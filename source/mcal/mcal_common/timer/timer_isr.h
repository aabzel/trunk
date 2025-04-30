#ifndef TIMER_ISR_H
#define TIMER_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "timer_custom_isr.h"
#include "timer_mcal.h"

bool TimerPeriodElapsedCallback(TimerHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_ISR_H */
