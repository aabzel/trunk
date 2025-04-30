#include "test_time_utils.h"

#include <stdio.h>
#include <time.h>

#include "float_utils.h"
#include "time_diag.h"
#include "time_mcal.h"
#ifdef HAS_CALENDAR
#include "calendar.h"
#endif


#include "unit_test_check.h"

bool test_time_types(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    bool res = true;
    ASSERT_EQ(9 * 4, sizeof(struct tm));
    return res;
}

static bool test_date_utils_1(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    bool res = true;
    struct tm time_stamp = {0};
    EXPECT_FALSE(parse_date_from_val(288821, &time_stamp));
    EXPECT_FALSE(parse_date_from_val(320721, &time_stamp));
    return res;
}

static bool test_date_utils_2(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    struct tm time_stamp = {0};
    bool res = true;
    ASSERT_TRUE(parse_date_from_val(280721, &time_stamp));
    ASSERT_EQ(2021, time_stamp.tm_year);
    ASSERT_EQ(28, time_stamp.tm_mday);
    ASSERT_EQ(6, time_stamp.tm_mon);
    return res;
}

static bool test_time_mcal_1(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    struct tm time_stamp = {0};
    bool res = true;
    EXPECT_FALSE(parse_time_from_val(100389, &time_stamp));
    EXPECT_FALSE(parse_time_from_val(108846, &time_stamp));
    EXPECT_FALSE(parse_time_from_val(250346, &time_stamp));
    return res;
}

static bool test_time_mcal_2(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    struct tm time_stamp = {0};
    bool res = true;
    ASSERT_TRUE(parse_time_from_val(100346, &time_stamp));
    ASSERT_EQ(10, time_stamp.tm_hour);
    ASSERT_EQ(03, time_stamp.tm_min);
    ASSERT_EQ(46, time_stamp.tm_sec);
    return res;
}

/*tsr time_mcal+*/
bool test_time_mcal(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    bool res = true;
#if 0
    uint32_t duration_us = 0;
    uint32_t duration_ms = 0;
    duration_us = calc_transfer_time_us(460800, 128);
    EXPECT_BETWEEN(3000, duration_us, 3500);
    ASSERT_TRUE(is_float_equal_absolute(3333.3f, (float)duration_us, 100.0f));

    duration_us = calc_transfer_time_us(38400, 128);
    EXPECT_BETWEEN(40000 - 10, duration_us, 40000 + 10);
    ASSERT_TRUE(is_float_equal_absolute(40000.0f, (float)duration_us, 100.0f));

    duration_ms = calc_transfer_time_ms(460800, 128);
    EXPECT_BETWEEN(3, duration_ms, 4);
    ASSERT_TRUE(is_float_equal_absolute(3.3f, (float)duration_ms, 0.9f));

    duration_ms = calc_transfer_time_ms(38400, 128);
    EXPECT_BETWEEN(40 - 2, duration_ms, 40 + 2);
    ASSERT_TRUE(is_float_equal_absolute(40.0f, (float)duration_ms, 100.0f));
#endif

    ASSERT_TRUE(test_time_mcal_1());
    ASSERT_TRUE(test_time_mcal_2());
    ASSERT_TRUE(test_date_utils_1());
    ASSERT_TRUE(test_date_utils_2());
    return res;
}

bool test_time_cmp(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    set_log_level(SYS, LOG_LEVEL_DEBUG);
    bool res = true;
    struct tm date_time1 = {.tm_sec = 30, .tm_min = 27, .tm_hour = 23, .tm_mday = 20, .tm_mon = 1, .tm_year = 122};

    struct tm date_time2 = {.tm_sec = 32, .tm_min = 27, .tm_hour = 23, .tm_mday = 20, .tm_mon = 1, .tm_year = 122};
    EXPECT_GR(0, time_date_cmp(&date_time1, &date_time2));
    EXPECT_GR(time_date_cmp(&date_time2, &date_time1), 0);
    set_log_level(SYS, LOG_LEVEL_INFO);
    return res;
}
bool test_time_stamp(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    set_log_level(TIME, LOG_LEVEL_DEBUG);
    struct tm date_time_set = {
        .tm_sec = 30,
        .tm_min = 2,
        .tm_hour = 20,
        .tm_mday = 7,
        .tm_mon = 2,
        .tm_year = 2022,
    };
    ASSERT_TRUE(is_valid_time_date(&date_time_set));

#ifdef HAS_CALENDAR
    struct tm date_time_restore;
    uint32_t time_stamp = TimeDateToSeconds(&date_time_set);
    ASSERT_TRUE(SecondsToTimeDate(time_stamp, &date_time_restore));
    ASSERT_TRUE(is_valid_time_date(&date_time_restore));
    ASSERT_TRUE(is_time_date_equal(&date_time_restore, &date_time_set));
#endif

    set_log_level(TIME, LOG_LEVEL_INFO);
    return true;
}

bool test_time_stamp2(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    set_log_level(TIME, LOG_LEVEL_DEBUG);
    struct tm date_time_set = {
        .tm_sec = 9,
        .tm_min = 12,
        .tm_hour = 14,
        .tm_mday = 18,
        .tm_mon = 4,
        .tm_year = 2022,
        .tm_wday = 6,
        .tm_yday = 137,
        .tm_isdst = -1,
    };
    ASSERT_TRUE(is_valid_time_date(&date_time_set));
#ifdef HAS_CALENDAR
    struct tm date_time_restore;
    uint32_t time_stamp = TimeDateToSeconds(&date_time_set);
    ASSERT_TRUE(SecondsToTimeDate(time_stamp, &date_time_restore));
    ASSERT_TRUE(is_valid_time_date(&date_time_restore));
    ASSERT_TRUE(is_time_date_equal(&date_time_restore, &date_time_set));
#endif
    set_log_level(TIME, LOG_LEVEL_INFO);
    return true;
}

bool test_time_parse(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    set_log_level(TIME, LOG_LEVEL_DEBUG);

    struct tm time_set;
    ASSERT_TRUE(time_parse(&time_set, "01:58:04"));
    ASSERT_EQ(1, time_set.tm_hour);
    ASSERT_EQ(58, time_set.tm_min);
    ASSERT_EQ(4, time_set.tm_sec);
    ASSERT_TRUE(print_time(&time_set));

    ASSERT_EQ(90, time_duration_parse("1.5m"))
    ASSERT_EQ(120, time_duration_parse("2m"))
    ASSERT_EQ(30, time_duration_parse("30"))
    ASSERT_EQ(20, time_duration_parse("20s"))
    ASSERT_EQ(7200, time_duration_parse("2h"))
    set_log_level(TIME, LOG_LEVEL_INFO);
    return true;
}

/*
https://www.exploringbinary.com/twos-complement-converter/
*/
