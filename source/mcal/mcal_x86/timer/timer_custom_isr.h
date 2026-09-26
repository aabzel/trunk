#ifndef TIMER_CUSTOM_IRQ_H
#define TIMER_CUSTOM_IRQ_H

#include <stdbool.h>
#include <stdint.h>

#include "x86x.h"
#include "timer_mcal.h"

bool Fc7300xTimerOverflowIRQHandler(uint8_t num);

#endif /* TIM_DRV_H  */
