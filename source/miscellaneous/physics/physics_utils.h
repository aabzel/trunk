#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include "std_inc.h"

#define FREQ_HZ_TO_PERIOD_S(FREQ_HZ)  (1.0f/((float)FREQ_HZ))
#define METER_TO_CENTI_METER(METER) ( (int32_t)   (((float)(METER))*100.0f)     )
#define TIMER_2_SECONDS(TIMER_CNT, TIMER_CLOCK_HZ) (((double)(TIMER_CNT)) / ((double)(TIMER_CLOCK_HZ)))

extern float physics_v_sound_m_pes_sec ;

float physics_periodS_to_freqHz(const float period_s);
float timer_2_s(uint64_t timer_cnt, uint64_t timer_clock_hz);


float value_to_centi(const float value);

#ifdef HAS_PHYSICS_RF
double FrxToV(double carrier_freq_hz, double doppler_freq_hz);
double physics_timer_to_dist(uint64_t cnt, uint64_t timer_clock_hz);
bool physics_doppler_radio_freq_calc(double velocity_mps, double freq_tx_hz, double* const freq_rx_hz_out);
uint64_t physics_dist_to_timer(double distanse_m, uint64_t timer_clock_hz);
#endif

double physics_lc_loop_calc_inductance(double f0_freq_hz, double cap_f);

bool physics_mcal_init(void);

#endif /* PHYSICS_UTILS_H  */
