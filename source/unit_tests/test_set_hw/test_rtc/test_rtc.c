#include "test_rtc.h"

#include "rtc_mcal.h"
#include "unit_test_check.h"
#include "none_blocking_pause.h"
#include "calendar.h"

bool test_rtc_is_run(uint8_t num) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LG_RTC, LOG_LEVEL_DEBUG);

    struct tm date_time1 = {0};
    struct tm date_time2 = { 0};

    ASSERT_TRUE(rtc_get(num, &date_time1));

    ASSERT_TRUE( wait_in_loop_ms(3000));

    ASSERT_TRUE(rtc_get(num, &date_time2));

    uint32_t diff = TimeDateToSeconds(&date_time2) - TimeDateToSeconds(&date_time1);

    ASSERT_GR(2,diff);

    set_log_level(LG_RTC, LOG_LEVEL_INFO);

    return res;
}

bool test_rtc_reinit(uint8_t num) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LG_RTC, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(rtc_init_one(num));
    set_log_level(LG_RTC, LOG_LEVEL_INFO);

    return res;
}

bool test_rtc_start(uint8_t num) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LG_RTC, LOG_LEVEL_DEBUG);

    ASSERT_TRUE( rtc_ctrl(num, true));
    ASSERT_TRUE( wait_in_loop_ms(2000));

    set_log_level(LG_RTC, LOG_LEVEL_INFO);

    return res;
}

#ifdef HAS_RTC0
bool test_rtc0_start(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_rtc_start(0));
    return res;
}

bool test_rtc0_is_run(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_rtc_is_run(0));
    return res;
}

bool test_rtc0_reinit(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(test_rtc_reinit(0));
    return res;
}

#endif

#ifdef HAS_RTC1


bool test_rtc1_stop_start(  void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_rtc_start(1));
    return res;
}
#endif

#ifdef HAS_RTC2

bool test_rtc2_stop_start(void  ){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE( test_rtc_start(2));
    return res;
}
#endif

