#ifndef TIMER_CALC_TYPES_H
#define TIMER_CALC_TYPES_H

#include <stdint.h>

#include "timer_calc_const.h"

typedef struct {
    uint32_t prescaler;
    uint32_t period;
}TimerArtety_t;

#endif /* TIMER_CALC_TYPES_H */
