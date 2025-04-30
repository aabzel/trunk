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

uint64_t physics_dist_to_timer(double distanse_m, uint64_t timer_clock_hz) {
    double tof_s = distanse_m / SPEED_OF_LIGHT_MPS;
    uint64_t cnt = 0;
    // cnt = ((uint64_t)(tof_s * ((double)timer_clock_hz)));

    cnt = (uint64_t)SEC_TO_TIMER_PERIOD(tof_s, timer_clock_hz);
    double tof_ns = 0.0;
    tof_ns = SEC_2_NSEC(tof_s);
    LOG_INFO(SYS, "Dist %f m ->TOF %f ns= %llu tick", distanse_m, tof_ns, cnt);
    return cnt;
}

double physics_timer_to_dist(uint64_t cnt, uint64_t timer_clock_hz) {
    LOG_DEBUG(SYS, "Clk %llu Hz Cnt %llu tick", timer_clock_hz, cnt);
    double distanse_m = 0.0;
    if(cnt) {
        double tof_s = TIMER_2_SECONDS(cnt, timer_clock_hz);
        distanse_m = tof_s * SPEED_OF_LIGHT_MPS;
        double tof_ns = 0.0;
        tof_ns = SEC_2_NSEC(tof_s);
        LOG_DEBUG(SYS, "Cnt %llu tick=TOF %f ns -> Dist %f m", cnt, tof_ns, distanse_m);
        LOG_DEBUG(SYS, "Return Dist %f m", distanse_m);
    } else {
        LOG_ERROR(SYS, "Cnt:0!");
    }
    return distanse_m;
}

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
        LOG_INFO(SYS, "CalcDoppler FreqTx:%f Hz,SpeedOfSv:%f m/s,FreqRx:%f Hz", freq_tx_hz, velocity_mps, freq_rx_hz);
        *freq_rx_hz_out = freq_rx_hz;
        res = true;
    }
    return res;
}
