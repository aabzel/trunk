#ifndef TIMER_CUSTOM_IRQ_H
#define TIMER_CUSTOM_IRQ_H

#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"
#include "timer_mcal.h"

bool ArteryTimerOverflowIRQHandler(uint8_t num);

#endif /* TIM_DRV_H  */
