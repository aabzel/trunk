#include "timer_utils.h"

#include "time_mcal.h"
#ifdef HAS_CLOCK
#include "clock.h"
#endif

bool time_delay_us(uint32_t delay_us) {
    bool res = false;
    uint64_t stop = time_get_us() + delay_us;
    while(time_get_us() < stop) {
        res = true;
    }
    return res;
}

double timer_2_seconds(uint64_t timer_cnt, uint64_t base_clock_hz) {
    double time_s = ((double)timer_cnt) / ((double)base_clock_hz);
    return time_s;
}
