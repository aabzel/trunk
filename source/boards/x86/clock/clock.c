#include "clock.h"

#include <stdbool.h>
#include <stdint.h>

#include "clock_config.h"
#include "clock_custom.h"
#include "log.h"


bool delay_ms(uint32_t delay_ms) {
    bool res = false;
    return res;
}

/*TODO calibrate for nrf5340*/
uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

/*TODO calibrate for nrf5340*/
uint64_t pause_1us(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 29700; in++) {
        cnt++;
    }
    return cnt;
}


bool clock_control(ClockDomain_t domain, bool on_off) {
    bool res = false;
    return res;
}


bool clock_init(void) {
    LOG_WARNING(CLK, "Init..");
    bool res = false;
    return res;
}



bool clock_core_freq_set(uint32_t core_freq_hz) {
    bool res = false;
    /*TODO*/
    return res;
}
