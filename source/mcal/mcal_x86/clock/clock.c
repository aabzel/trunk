#include "clock/clock.h"

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

bool clock_mcal_init(void) {
    LOG_WARNING(CLK, "Init..");
    bool res = true;
    return res;
}

static const ClockInfo_t ClockInfo = {
    .valid = true,
};

bool clock_frequency_get(uint16_t clock_name, uint32_t* const frequency_hz) {
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
    ClockInfo_t* Info = &ClockInfo;
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

#ifdef HAS_CLOCK_RUN_TIME_CTRL
bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    LOG_WARNING(SYS, "Set,Freq:%uHz", core_freq_hz);
    return res;
}
#endif
