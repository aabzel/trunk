#include "clock.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"
#include "sys_config.h"
#include "time_utils.h"
#ifdef HAS_TIMER
#include "timer_drv.h"
#endif /**/
#include "clock_custom.h"

#ifdef HAS_SYSTICK
#include "systick_general.h"
#endif /**/

/*calibrate*/
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t sw_pause_ms(uint32_t delay_in_ms) {
    uint64_t cnt = 0;
    // LOG_INFO(SYS, "SwPause %u ms", delay_in_ms); del
    uint32_t t = 0;
    for(t = 0; t < delay_in_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}

uint32_t clock_core_freq_get(void) {
    crm_clocks_freq_type clocks_struct = {0};
    crm_clocks_freq_get(&clocks_struct);
    return clocks_struct.sclk_freq;
}
