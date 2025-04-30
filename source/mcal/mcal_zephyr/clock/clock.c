#include "clock.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/kernel.h>

#include "time_mcal.h"

bool clock_init(void){
    bool res = true;
    /*Already initialized in kernel*/
    return res;
}

#if 0
uint32_t time_get_ms32(void) {
    uint32_t time_ms = 0;
    time_ms = (uint32_t) k_uptime_get();
    return time_ms;
}

uint64_t time_get_ms64(void) {
	uint64_t time_ms = 0;
    time_ms = (uint64_t) k_uptime_get();
    return time_ms;
}
#endif

uint64_t diff_us = 0;


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

uint32_t clock_core_freq_get(void){
    LOG_ERROR(CLK, "NotImplemented");
    return 0;
}


bool delay_ms(uint32_t wait_pause_ms) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(CLK, "Pause %u ms", wait_pause_ms);
#endif
    k_yield();
    int32_t ret = k_msleep(wait_pause_ms);
    if(0==ret){
    	res = true;
    }
#if 0
    uint32_t start_ms = 0U;
    uint32_t curr_ms = 0U;
    start_ms = time_get_ms32();
    bool loop = true;
    while(loop) {
        curr_ms = time_get_ms32();
        if(wait_pause_ms < (curr_ms - start_ms)) {
            res = true;
            loop = false;
            break;
        }
    }
#endif
    return res;
}
