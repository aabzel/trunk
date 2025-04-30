#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include <stdbool.h>
#include <stdint.h>

#define TIMER_2_SECONDS(TIMER_CNT, TIMER_CLOCK_HZ) (((double)(TIMER_CNT)) / ((double)(TIMER_CLOCK_HZ)))

bool physics_doppler_radio_freq_calc(double velocity_mps, double freq_tx_hz, double* const freq_rx_hz_out);
uint64_t physics_dist_to_timer(double distanse_m, uint64_t timer_clock_hz);
double FrxToV(double carrier_freq_hz, double doppler_freq_hz);
double timer_2_s(uint64_t timer_cnt, uint64_t timer_clock_hz);
double physics_timer_to_dist(uint64_t cnt, uint64_t timer_clock_hz);

#endif /* PHYSICS_UTILS_H  */
