#include "physics_utils.h"

#ifdef HAS_CLOCK
#include "clock_utils.h"
#endif
#include "log.h"
#include "physics_const.h"
#include "time_mcal.h"

#ifndef SEC_TO_TIMER_PERIOD
#define SEC_TO_TIMER_PERIOD(SEC_S, TIMER_CLOCK_HZ) (((double)(SEC_S)) * ((double)(TIMER_CLOCK_HZ)))
#endif

#ifdef HAS_PHYSICS_RF
uint64_t physics_dist_to_timer(double distanse_m, uint64_t timer_clock_hz) {
    double tof_s = distanse_m / SPEED_OF_LIGHT_MPS;
    uint64_t cnt = 0;
    // cnt = ((uint64_t)(tof_s * ((double)timer_clock_hz)));

    cnt = (uint64_t)SEC_TO_TIMER_PERIOD(tof_s, timer_clock_hz);
    double tof_ns = 0.0;
    tof_ns = SEC_2_NSEC(tof_s);
    LOG_INFO(PHYSICS, "Dist %f m ->TOF %f ns= %llu tick", distanse_m, tof_ns, cnt);
    return cnt;
}
#endif

#ifdef HAS_PHYSICS_RF
double physics_timer_to_dist(uint64_t cnt, uint64_t timer_clock_hz) {
    LOG_DEBUG(PHYSICS, "Clk %llu Hz Cnt %llu tick", timer_clock_hz, cnt);
    double distanse_m = 0.0;
    if(cnt) {
        double tof_s = TIMER_2_SECONDS(cnt, timer_clock_hz);
        distanse_m = tof_s * SPEED_OF_LIGHT_MPS;
        double tof_ns = 0.0;
        tof_ns = SEC_2_NSEC(tof_s);
        LOG_DEBUG(PHYSICS, "Cnt %llu tick=TOF %f ns -> Dist %f m", cnt, tof_ns, distanse_m);
        LOG_DEBUG(PHYSICS, "Return Dist %f m", distanse_m);
    } else {
        LOG_ERROR(PHYSICS, "Cnt:0!");
    }
    return distanse_m;
}
#endif

#ifdef HAS_PHYSICS_RF
double FrxToV(double carrier_freq_hz, double doppler_freq_hz) {
    double speed_ms = 0.0;
    speed_ms = SPEED_OF_LIGHT_MPS * (1.0 - doppler_freq_hz / carrier_freq_hz);
    return speed_ms;
}
bool physics_doppler_radio_freq_calc(double velocity_mps, double freq_tx_hz, double* const freq_rx_hz_out) {
    bool res = false;
    if(freq_rx_hz_out) {
        double freq_rx_hz = 0.0;
        freq_rx_hz = freq_tx_hz / (1.0 - (velocity_mps / SPEED_OF_LIGHT_MPS));
        LOG_INFO(PHYSICS, "CalcDoppler FreqTx:%f Hz,SpeedOfSv:%f m/s,FreqRx:%f Hz", freq_tx_hz, velocity_mps,
                 freq_rx_hz);
        *freq_rx_hz_out = freq_rx_hz;
        res = true;
    }
    return res;
}
#endif

float physics_periodS_to_freqHz(const float period_s) {
    float freq_hz = 0.0f;
    freq_hz = 1.0f / period_s;
    LOG_DEBUG(PHYSICS, "T=%f s->F:%f Hz", period_s, freq_hz);
    return freq_hz;
}

double physics_lc_loop_calc_inductance(const double f0_freq_hz, const double cap_f) {
    double inductance_hr = 0.0;
    double temp = 2.0 * M_PI * f0_freq_hz;
    inductance_hr = 1.0 / (cap_f * temp * temp);
    double r_crit = 2.0 * sqrt(inductance_hr / cap_f);
    LOG_INFO(SYS, CRLF "Freq:%f Hz," CRLF "C:%f F," CRLF "L:%f H," CRLF "R_crit=%f Om", f0_freq_hz, cap_f,
             inductance_hr, r_crit);
    return inductance_hr;
}
