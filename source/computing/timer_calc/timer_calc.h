#ifndef TIMER_CALC_H
#define TIMER_CALC_H

#include <stdbool.h>
#include <stdint.h>

#include "timer_types.h"


bool timer_calc_artery(double freq_apb_hz,
		double freq_sinal_hz,
		uint8_t resolution_bit,
		TimerArtety_t* const Node);

#endif /* TIMER_CALC_H */
