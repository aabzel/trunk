#include "test_ds3231.h"

#include <string.h>

#include "ds3231_diag.h"
#include "ds3231_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_ds3231_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;

    EXPECT_EQ(1, sizeof(Ds3231RegDate_t));
    EXPECT_EQ(1, sizeof(Ds3231RegMonth_t));
    EXPECT_EQ(1, sizeof(Ds3231RegYear_t));
    EXPECT_EQ(1, sizeof(Ds3231RegControl_t));
    EXPECT_EQ(1, sizeof(Ds3231RegSeconds_t));
    EXPECT_EQ(1, sizeof(Ds3231RegMinutes_t));
    EXPECT_EQ(1, sizeof(Ds3231RegHours_t));
    EXPECT_EQ(1, sizeof(Ds3231RegWeekDay_t));
    EXPECT_EQ(19, sizeof(RegMap_t));

    set_log_level(DS3231, LOG_LEVEL_INFO);
    return res;
}

bool test_ds3231_hash_tables(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    set_log_level(DS3231, LOG_LEVEL_INFO);

    return res;
}

bool test_ds3231_connected(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    set_log_level(I2C, LOG_LEVEL_DEBUG);
    bool res = true;
    ASSERT_TRUE(ds3231_is_connected(1));

    set_log_level(DS3231, LOG_LEVEL_INFO);
    set_log_level(I2C, LOG_LEVEL_INFO);
    return res;
}

bool test_ds3231_set_time(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;
    set_log_level(DS3231, LOG_LEVEL_INFO);
    return res;
}

bool test_ds3231_get_time(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;

    set_log_level(DS3231, LOG_LEVEL_INFO);

    return res;
}


bool test_ds3231_set_reg(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;

    set_log_level(DS3231, LOG_LEVEL_INFO);
    return res;
}


bool test_ds3231_get_reg(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;

    return res;
}


bool test_ds3231_config(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DS3231, LOG_LEVEL_DEBUG);
    bool res = true;
    HourMode_t hour_mode=ds3231_hour_mode_get(1);
    EXPECT_EQ(HOUR_MODE_24H, hour_mode);

    return res;
}
