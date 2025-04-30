#include "test_planetarium.h"

#include <stdio.h>
#include <time.h>

#include "float_utils.h"
#include "planetarium.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "unit_test_check.h"

bool test_planetarium_calc_noon(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    struct tm time_date_sunrise = {0};
    struct tm time_date_sunset = {0};
    struct tm time_date_noon = {0};

    EXPECT_TRUE(time_get_cur(&time_date_sunrise));
    EXPECT_TRUE(time_get_cur(&time_date_sunset));
    EXPECT_TRUE(time_get_cur(&time_date_noon));

    time_date_sunrise.tm_hour = 4;
    time_date_sunrise.tm_min = 3;
    time_date_sunrise.tm_sec = 43;
    time_date_sunrise.tm_mday = 28;
    time_date_sunrise.tm_mon = 4;
    time_date_sunrise.tm_year -= 1900;

    time_date_sunset.tm_hour = 20;
    time_date_sunset.tm_min = 52;
    time_date_sunset.tm_sec = 47;
    time_date_sunset.tm_mday = 28;
    time_date_sunset.tm_mon = 4;
    time_date_sunset.tm_year = time_date_sunset.tm_year - 1900;

    EXPECT_TRUE(print_time_date("SunRise", &time_date_sunrise, true));
    EXPECT_TRUE(print_time_date("SunSet", &time_date_sunset, true));

    EXPECT_TRUE(calc_noon_time(&time_date_sunrise, &time_date_sunset, &time_date_noon));
    EXPECT_TRUE(print_time_date("SunNoon", &time_date_noon, true));

    EXPECT_EQ(2023, time_date_noon.tm_year);
    EXPECT_EQ(4, time_date_noon.tm_mon);
    // EXPECT_EQ( 46   ,  time_date_noon.tm_sec         );
    EXPECT_BETWEEN(27, time_date_noon.tm_min, 28);
    EXPECT_EQ(12, time_date_noon.tm_hour);
    EXPECT_EQ(28, time_date_noon.tm_mday);
    // EXPECT_EQ( 0   ,  time_date_noon.tm_wday         );
    // EXPECT_EQ( 0   ,  time_date_noon.tm_yday         );
    // EXPECT_EQ( 0   ,  time_date_noon.tm_isdst       );

    return res;
}

/*
https://www.exploringbinary.com/twos-complement-converter/
*/
bool test_planetarium_calc_phi(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    double phi_deg = 0.0;
    struct tm date_time;

    res = time_get_cur(&date_time);
    date_time.tm_sec = 0;
    date_time.tm_min = 18;
    date_time.tm_hour = 23;
    date_time.tm_mday = 1;
    date_time.tm_mon = 5;
    date_time.tm_year = 2023;
    // date_time.tm_wday=0;
    // date_time.tm_yday=0;
    // date_time.tm_isdst=0;

    EXPECT_TRUE(calc_phi_v2(16.716, &date_time, &phi_deg));
    LOG_INFO(TEST, "phi %f Deg", phi_deg);
    EXPECT_EQ_SOFT(55.863345, phi_deg, 5);

    date_time.tm_sec = 0;
    date_time.tm_min = 18;
    date_time.tm_hour = 23;
    date_time.tm_mday = 6;
    date_time.tm_mon = MON_NOV;
    date_time.tm_year = 2023;

    EXPECT_TRUE(calc_phi_v2(8.9, &date_time, &phi_deg));
    LOG_INFO(TEST, "phi %f Deg", phi_deg);
    EXPECT_EQ_SOFT(55.970685, phi_deg, 5);

    return res;
}

bool test_planetarium_calc_lambda(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    log_level_get_set(PLANETARIUM, LOG_LEVEL_DEBUG);
    double lambda_deg = 0.0;
    struct tm noon_time = {0};

    noon_time.tm_hour = 9;
    noon_time.tm_min = 28;
    noon_time.tm_sec = 19;
    noon_time.tm_mday = 28;
    noon_time.tm_mon = MON_AUG;
    noon_time.tm_year = 2018;
    // noon_time.tm_wday=0;
    //  noon_time.tm_yday=0;
    // noon_time.tm_isdst=0;
    lambda_deg = 0.0;
    EXPECT_TRUE(calc_lambda(&noon_time, &lambda_deg));
    LOG_INFO(TEST, "lambda %f deg", lambda_deg);
    EXPECT_EQ_SOFT(37.61778, lambda_deg, 5);

    res = time_get_cur(&noon_time);
    noon_time.tm_sec = 19;
    noon_time.tm_min = 28;
    noon_time.tm_hour = 9;
    // noon_time.tm_mday=1;
    // noon_time.tm_mon=5;
    // noon_time.tm_year=2023;
    // noon_time.tm_wday=0;
    //  noon_time.tm_yday=0;
    // noon_time.tm_isdst=0;
    lambda_deg = 0.0;
    EXPECT_TRUE(calc_lambda(&noon_time, &lambda_deg));
    LOG_INFO(TEST, "lambda %f deg", lambda_deg);
    EXPECT_EQ_SOFT(37.61778, lambda_deg, 5);
    //-------------------------

    log_level_get_set(PLANETARIUM, LOG_LEVEL_INFO);

    return res;
}

bool test_planetarium_compare_lambda(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    double lambda1_deg = 0.0;
    double lambda2_deg = 0.0;
    struct tm noon_time = {0};

    res = time_get_cur(&noon_time);

    for(noon_time.tm_hour = 0; noon_time.tm_hour <= 23; noon_time.tm_hour += 4) {
        for(noon_time.tm_min = 0; noon_time.tm_min <= 59; noon_time.tm_min += 32) {
            for(noon_time.tm_sec = 0; noon_time.tm_sec <= 59; noon_time.tm_sec += 33) {
                LOG_INFO(TEST, "NoonTime %s ", Time2StrShort(&noon_time));
                ASSERT_TRUE(calc_lambda(&noon_time, &lambda1_deg));
                LOG_INFO(TEST, "lambda1 %f deg", lambda1_deg);
                ASSERT_TRUE(calc_lambda_slow(&noon_time, &lambda2_deg));
                LOG_INFO(TEST, "lambda2 %f deg", lambda2_deg);
                ASSERT_TRUE(is_double_equal_absolute(lambda1_deg, lambda2_deg, 5.0));
            }
        }
    }

    return res;
}

bool test_planetarium_compare_phi(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    double phi_fast = 0.0;
    double phi_slow = 0.0;
    double day_length_duration_h = 0.0;
    double sun_declination_deg = 0.0;

    for(day_length_duration_h = 2.0; day_length_duration_h < 20.0; day_length_duration_h += 5.34) {
        for(sun_declination_deg = -23.0; sun_declination_deg < 23.0; sun_declination_deg += 15.1) {
            LOG_INFO(TEST, "DayDur %f h, Delta %f Deg ", day_length_duration_h, sun_declination_deg);
            phi_fast = calc_phi_fast(day_length_duration_h, sun_declination_deg);
            LOG_INFO(TEST, "phiFast %f deg", phi_fast);
            phi_slow = calc_phi_slow(day_length_duration_h, sun_declination_deg);
            LOG_INFO(TEST, "phiSlow %f deg", phi_slow);
            ASSERT_TRUE(is_double_equal_absolute(phi_slow, phi_fast, 4.0)); /*5 ok*/
        }
    }
    return res;
}

bool test_planetarium_compare_phi_ref(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;

    double phi_space = 0.0;
    double phi_diff = 0.0;
    double phi_refraction = 0.0;
    double day_length_duration_h = 0.0;
    double sun_declination_deg = 0.0;

    for(day_length_duration_h = 2.0; day_length_duration_h < 23.0; day_length_duration_h += 5.34) {
        for(sun_declination_deg = -23.0; sun_declination_deg < 23.0; sun_declination_deg += 9.1) {
            LOG_INFO(TEST, "DayDur:%f h,Delta:%f Deg ", day_length_duration_h, sun_declination_deg);
            phi_space = calc_phi_fast(day_length_duration_h, sun_declination_deg);
            LOG_INFO(TEST, "PhiSpace:%f Deg", phi_space);
            phi_refraction = calc_phi_refraction(day_length_duration_h, sun_declination_deg);
            LOG_INFO(TEST, "PhiRefra:%f Deg", phi_refraction);
            phi_diff = phi_refraction - phi_space;
            LOG_INFO(TEST, "PhiDiff:%f Deg", phi_diff);
            ASSERT_TRUE(is_double_equal_absolute(phi_refraction, phi_space, 8.0)); /*5 ok*/
        }
    }
    return res;
}
