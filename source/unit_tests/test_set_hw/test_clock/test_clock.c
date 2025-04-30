#include "test_clock.h"

#include <string.h>
#include <gpio.h>

#include "clock_diag.h"
#include "clock_drv.h"
#include "unit_test_check.h"

bool test_clock_us(void) {
    uint32_t i = 0;
    uint64_t up_time_us_cur = 0;
    uint64_t up_time_us_prev = 0;
    wait_in_loop_ms(20);
    up_time_us_prev = time_get_us();
    pause_1us();
    for(i = 0; i < 500; i++) {
        up_time_us_cur = time_get_us();
        ASSERT_GR_64(up_time_us_prev, up_time_us_cur, i);
        pause_1us();
        pause_1us();
        up_time_us_prev = up_time_us_cur;
    }
    return true;
}

bool test_clock_ms(void) {
    uint32_t i = 0;
    uint32_t up_time_ms_cur = 0;
    uint32_t up_time_ms_prev = 0;
    up_time_ms_prev = time_get_ms32();
    pause_1ms();
    for(i = 0; i < 500; i++) {
        up_time_ms_cur = time_get_ms32();
        ASSERT_GR_64(up_time_ms_prev, up_time_ms_cur, i);
        pause_1ms();
        pause_1ms();
        up_time_ms_prev = up_time_ms_cur;
    }
    return true;
}
