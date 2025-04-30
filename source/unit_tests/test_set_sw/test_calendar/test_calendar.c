#include "test_calendar.h"

#ifdef X86_64
#include "log.h"
#endif
#include "calendar.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "unit_test_check.h"

bool test_calendar_parse_time(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    struct tm date_time;
    EXPECT_TRUE(time_data_parse(&date_time, "Tue Dec  7 15:34:46 2021"));
    EXPECT_EQ(46, date_time.tm_sec);
    EXPECT_EQ(34, date_time.tm_min);
    EXPECT_EQ(15, date_time.tm_hour);
    EXPECT_EQ(7, date_time.tm_mday);
    EXPECT_EQ(11, date_time.tm_mon);
    EXPECT_EQ(2021, date_time.tm_year);

    EXPECT_TRUE(date_parse(&date_time, "Jan 10 2022"));
    EXPECT_EQ(10, date_time.tm_mday);
    EXPECT_EQ(0, date_time.tm_mon);
    EXPECT_EQ(2022, date_time.tm_year);
    return true;
}

bool test_calendar_set_get(void) {
    LOG_INFO(LG_CAL, "%s()", __FUNCTION__);

    set_log_level(LG_CAL, LOG_LEVEL_DEBUG);
    struct tm date_time_set;
    date_time_set.tm_sec = 11;
    date_time_set.tm_min = 57;
    date_time_set.tm_hour = 19;
    date_time_set.tm_mday = 17;
    date_time_set.tm_mon = 11;
    date_time_set.tm_year = 2021;

    EXPECT_TRUE(calendar_settime(&date_time_set));

    struct tm date_time_get = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    EXPECT_TRUE(calendar_gettime(&date_time_get));
    EXPECT_EQ(date_time_set.tm_min, date_time_get.tm_min);
    EXPECT_EQ(date_time_set.tm_hour, date_time_get.tm_hour);
    EXPECT_EQ(date_time_set.tm_mday, date_time_get.tm_mday);
    EXPECT_EQ(date_time_set.tm_mon, date_time_get.tm_mon);
    EXPECT_EQ(date_time_set.tm_year, date_time_get.tm_year);
    EXPECT_EQ(date_time_set.tm_sec, date_time_get.tm_sec);
    set_log_level(LG_CAL, LOG_LEVEL_INFO);
    return true;
}

bool test_calendar_set_get_all(void) {
#ifdef X86_64
    LOG_INFO(LG_CAL, "%s()", __FUNCTION__);
#endif
    struct tm date_time_set;
    struct tm date_time_get = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    set_log_level(LG_CAL, LOG_LEVEL_INFO);
    for(date_time_set.tm_year = 2022; date_time_set.tm_year < 2099; date_time_set.tm_year += 13) {
        for(date_time_set.tm_mon = 0; date_time_set.tm_mon <= 11; date_time_set.tm_mon++) {
            for(date_time_set.tm_mday = 1; date_time_set.tm_mday <= 28; date_time_set.tm_mday += 2) {
                for(date_time_set.tm_hour = 0; date_time_set.tm_hour <= 23; date_time_set.tm_hour += 2) {
                    for(date_time_set.tm_min = 0; date_time_set.tm_min <= 59; date_time_set.tm_min += 3) {
                        for(date_time_set.tm_sec = 0; date_time_set.tm_sec <= 59; date_time_set.tm_sec += 4) {
                            EXPECT_TRUE(is_valid_time_date(&date_time_set));
#ifdef HAS_CALENDAR_TEST_DEBUG
                            print_time_date(&date_time_set);
#endif
                            calendar_settime(&date_time_set);
                            EXPECT_TRUE(calendar_gettime(&date_time_get));
                            EXPECT_EQ(date_time_set.tm_sec, date_time_get.tm_sec);
                            EXPECT_EQ(date_time_set.tm_min, date_time_get.tm_min);
                            EXPECT_EQ(date_time_set.tm_hour, date_time_get.tm_hour);
                            EXPECT_EQ(date_time_set.tm_mday, date_time_get.tm_mday);
                            EXPECT_EQ(date_time_set.tm_mon, date_time_get.tm_mon);
                            EXPECT_EQ(date_time_set.tm_year, date_time_get.tm_year);
                        }
                    }
                }
            }
        }
    }

    return true;
}
