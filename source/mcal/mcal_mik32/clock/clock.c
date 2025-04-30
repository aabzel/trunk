#include "clock.h"

#include "clock_config.h"
#include "clock_custom.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "std_includes.h"

/*calibrate*/
#ifdef HAS_CLOCK_EXT
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}
#endif

#ifdef HAS_CLOCK_EXT
uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}
#endif

#ifdef HAS_CLOCK_EXT
uint64_t sw_pause_ms(uint32_t delay_in_ms) {
    uint64_t cnt = 0;
    // LOG_INFO(SYS, "SwPause %u ms", delay_in_ms); del
    uint32_t t = 0;
    for(t = 0; t < delay_in_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}
#endif

uint32_t clock_core_freq_get(void) { return 0; }

bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;

    return res;
}
