#include "clock_mcal.h"

#include <sys/timeb.h>
#include <time.h>

#include "clock_custom.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"
#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif
//#include "c_defines_generated.h"

#ifdef HAS_X86
uint32_t start_time_ms;
uint32_t g_up_time_ms;
time_t start_time = 0;
struct timeb start_time_b;
#endif

bool clock_core_mux_get(ClockMux_t* const clock_mux) {
    bool res = false;
    return res;
}

bool clock_core_mux_set(const ClockMux_t clock_mux) {
    uint32_t core_freq_hz = 0;
    return core_freq_hz;
}

uint32_t pc_clock_get_ms(void) {
    uint32_t time_ms = 0;
    clock_t cur_clock = 0;
    cur_clock = clock();
    time_ms = (uint32_t)((1000 * cur_clock) / CLOCKS_PER_SEC);

    return time_ms;
}

uint64_t pc_clock_get_us(void) {
    uint64_t time_us = 0;
    clock_t cur_clock = clock();
    time_us = (uint64_t)((1000000U * ((uint64_t)cur_clock)) / ((uint64_t)CLOCKS_PER_SEC));
    return time_us;
}

bool clock_x86_init(void) {
    LOG_WARNING(CLK, "Init..");
    bool res = true;
#if 0
    ftime(&start_time_b);
    res = true;
    LOG_INFO(TIME,
             "time = %u.%03u, "
             "timezone = %d, "
             "dstflag = %d\n",
             start_time_b.time, start_time_b.millitm, start_time_b.timezone, start_time_b.dstflag);

    struct tm* timeinfo;
    time(&start_time);
    timeinfo = localtime(&start_time);
    LOG_INFO(TIME, "start time local: %u [%s]", start_time, asctime(timeinfo));
    start_time_ms = start_time_b.millitm + start_time_b.time * 1000;
#endif

    return res;
}

bool clock_mcal_init(void) {
    LOG_WARNING(CLK, "Init..");
    bool res = true;
#if 0
    ftime(&start_time_b);
    res = true;
    LOG_INFO(TIME,
             "time = %u.%03u, "
             "timezone = %d, "
             "dstflag = %d\n",
             start_time_b.time, start_time_b.millitm, start_time_b.timezone, start_time_b.dstflag);

    struct tm* timeinfo;
    time(&start_time);
    timeinfo = localtime(&start_time);
    LOG_INFO(TIME, "start time local: %u [%s]", start_time, asctime(timeinfo));
    start_time_ms = start_time_b.millitm + start_time_b.time * 1000;
#endif

    return res;
}

static const ClockInfo_t ClockInfo = {
    .valid = true,
};

bool clock_frequency_get(ClockBus_t clock_name, uint32_t* const frequency_hz) {
    bool res = false;
    return res;
}

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

const ClockInfo_t* ClockGetInfo(uint8_t num) {
    (void)num;
    const ClockInfo_t* Info = &ClockInfo;
    return Info;
}

uint64_t sw_pause_ms(uint32_t delay_in_ms) {
    uint64_t cnt = 0;
    uint32_t i, j;
    for(i = 0U; i < delay_in_ms; i++) {
        for(j = 0U; j < 10000U; j++) {
            __asm("nop");
            cnt++;
        }
    }
    return cnt;
}

#if 0
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

uint32_t clock_core_freq_get(void) {
    // TODO
    return 0;
}

bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    LOG_WARNING(SYS, "Set,Freq:%uHz", core_freq_hz);
    return res;
}

uint32_t HAL_GetTick(void) {
    uint32_t up_time_ms = 0;
    up_time_ms = time_get_ms32();
    return up_time_ms;
}
