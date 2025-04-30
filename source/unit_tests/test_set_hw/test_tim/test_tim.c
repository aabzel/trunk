#include "test_tim.h"

#include "clock.h"
#include "timer_drv.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_tim_us(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t i = 0;
    uint64_t up_time_us_cur = 0;
    uint64_t up_time_us_prev = 0;
    wait_in_loop_ms(20) ;
    up_time_us_prev = tim_get_us();
    pause_1us();
    for(i = 0; i < 10000; i++) {
        up_time_us_cur = tim_get_us();
        EXPECT_GR_64(up_time_us_prev, up_time_us_cur, i);
        pause_1us();
        pause_1us();
        up_time_us_prev = up_time_us_cur;
    }
    return true;
}

bool test_tim_ms(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    uint32_t i = 0;
    uint32_t up_time_ms_cur = 0;
    uint32_t up_time_ms_prev = 0;
    up_time_ms_prev = timer_get_ms();
    pause_1ms();
    for(i = 0; i < 500; i++) {
        up_time_ms_cur = timer_get_ms();
        EXPECT_GR_64(up_time_ms_prev, up_time_ms_cur, i);
        pause_1ms();
        pause_1ms();
        up_time_ms_prev = up_time_ms_cur;
    }
    return true;
}

bool test_tim_utils(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    ASSERT_EQ(1000000 ,TimerGetCntFreq(1));
    ASSERT_EQ(1000,TimerGetCntFreq(1000));
    ASSERT_EQ(1,TimerGetCntFreq(1000000));
    return true;
}
