#include "clock.h"

#include "std_includes.h"
#include "clock_config.h"
#include "log.h"
#include "stm32fx_hal.h"
//#include "time_mcal.h"

#include "clock_custom.h"

#ifdef HAS_SYSTICK
//#include "systick_general.h"
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

uint32_t clock_freq_get(const ClockBus_t clock_bus) {
    uint32_t clock_freq_hz = 0;
    switch(clock_bus) {
    case CLOCK_BUS_SYS: {
        clock_freq_hz = HAL_RCC_GetSysClockFreq();

    } break;
    case CLOCK_BUS_APB2: {
        clock_freq_hz = HAL_RCC_GetPCLK2Freq();

    } break;
    case CLOCK_BUS_APB1: {
        clock_freq_hz = HAL_RCC_GetPCLK1Freq();

    } break;
    case CLOCK_BUS_AHB: {
        clock_freq_hz = HAL_RCC_GetHCLKFreq();

    } break;
    default:
        clock_freq_hz = 0;
        break;
    }

    return clock_freq_hz;
}

uint32_t clock_core_freq_get(void) { return 0; }

bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    res = clock_init_48mhz();
    return res;
}
