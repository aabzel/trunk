#include "test_csv.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "csv.h"
#include "log.h"
#include "time_mcal.h"
#include "unit_test_check.h"

bool test_csv_cnt(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    ASSERT_EQ(1, csv_cnt("a", ';'));
    ASSERT_EQ(2, csv_cnt(";", ';'));
    ASSERT_EQ(3, csv_cnt(";;", ';'));
    ASSERT_EQ(4, csv_cnt(",,,", ','));
    ASSERT_EQ(1, csv_cnt("4452", ';'));
    ASSERT_EQ(6, csv_cnt("7354, 1105.000,20.75, 16:07:44, 14/7/2023, 1517952720", ','));
    ASSERT_EQ(3, csv_cnt("ll wm8731 debug;ll i2c debug;tsr 127", ';'));
    ASSERT_EQ(1, csv_cnt("", ';'));

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_parse_double(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    double value = 0.0;
    ASSERT_FALSE(csv_parse_double("3975,   1.667,  27.50, 21:20:36, 7/8/2023, 1520045092", 100, &value));

    ASSERT_TRUE(csv_parse_double("3975,   1.667,  27.50, 21:20:36, 7/8/2023, 1520045092", 5, &value));
    ASSERT_EQ_DOUBLE(1520045092.0, value);

    ASSERT_TRUE(csv_parse_double("4452,0.000,17.00, 00:00:18, 14/7/2023, 1517894674", 1, &value));
    ASSERT_EQ_DOUBLE(0.000, value);

    ASSERT_TRUE(csv_parse_double("7354, 1105.000,20.75, 16:07:44, 14/7/2023, 1517952720", 1, &value));
    ASSERT_EQ_DOUBLE(1105.0, value);

    ASSERT_TRUE(csv_parse_double("12610,0.083,20.50, 21:26:20, 15/7/2023, 1518058236", 1, &value));
    ASSERT_EQ_DOUBLE(0.083, value);

    ASSERT_TRUE(csv_parse_double("12610,0.083,20.50, 21:26:20, 15/7/2023, 1518058236", 2, &value));
    ASSERT_EQ_DOUBLE(20.5, value);

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_parse_text(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    char sub_text[80] = "";
    memset(sub_text, 0, sizeof(sub_text));
    ASSERT_FALSE(csv_parse_text("aa;bb;cc", ';', 3, sub_text, sizeof(sub_text)));
    ASSERT_FALSE(csv_parse_text("aa;bb;cc", ';', 100, sub_text, sizeof(sub_text)));

    ASSERT_TRUE(csv_parse_text(";;c;;", ';', 2, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("c", sub_text);

    ASSERT_TRUE(csv_parse_text("", ';', 0, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("", sub_text);

    ASSERT_TRUE(csv_parse_text("h", ';', 0, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("h", sub_text);

    ASSERT_TRUE(csv_parse_text("ll wm8731 debug;ll i2c debug;tsr 127", ';', 0, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("ll wm8731 debug", sub_text);

    ASSERT_TRUE(csv_parse_text("ll wm8731 debug;ll i2c debug;tsr 127", ';', 1, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("ll i2c debug", sub_text);

    ASSERT_TRUE(csv_parse_text("ll wm8731 debug;ll i2c debug;tsr 127", ';', 2, sub_text, sizeof(sub_text)));
    ASSERT_STREQ("tsr 127", sub_text);

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_parse_text_overflow(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    char sub_text[5] = "";
    memset(sub_text, 0, sizeof(sub_text));

    ASSERT_FALSE(csv_parse_text("aa;123456789;cc", ';', 1, sub_text, sizeof(sub_text)));

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_parse_last_text(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(CSV, LOG_LEVEL_DEBUG);
    char buffer[100] = {0};
    strcpy(buffer, "C:/projects/source/sensitivity/accelerometer/accelerometer.c");
    char sub_text[80] = {0};
    ASSERT_TRUE(csv_parse_last_text(buffer, '/', sub_text, sizeof(sub_text)));
    ASSERT_STREQ("accelerometer.c", sub_text);

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_fetch_text(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    bool res = true;
    uint32_t offset = 0;
    char buffer[100] = {0};
    strcpy(buffer, "aaa bb ccc");
    size_t size = strlen(buffer);
    ASSERT_TRUE(csv_fetch_text(buffer, size, ' ', 1, &offset));
    LOG_INFO(CSV, "OffSet:%u", offset);
    LOG_INFO(CSV, "[%s]", &buffer[offset]);
    ASSERT_STREQ("bb ccc", &buffer[offset]);

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_fetch_text_zeros(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CSV, LOG_LEVEL_DEBUG);

    bool res = true;
    uint32_t offset = 0;
    char buffer[100] = {0};
    strcpy(buffer, "aaa bb ccc");
    size_t size = strlen(buffer);
    int ret = replace_char(buffer, ' ', 0x00);
    LOG_INFO(CSV, "repl:%u cnt", ret);
    ASSERT_TRUE(csv_fetch_text(buffer, size, 0x00, 1, &offset));
    LOG_INFO(CSV, "OffSet:%u", offset);
    LOG_INFO(CSV, "[%s]", &buffer[offset]);
    ASSERT_STREQ("bb", &buffer[offset]);

    set_log_level(CSV, LOG_LEVEL_INFO);
    return res;
}

bool test_csv_strlen_perf(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CSV, LOG_LEVEL_INFO);
    bool res = true;

    uint32_t start_ms = time_get_ms32();
    uint32_t len = strlen("ewr 2047 0x25252535 0x0025");
    uint32_t end_ms = time_get_ms32();
    uint32_t duration = end_ms - start_ms;
    ASSERT_GR(duration, 400);
    ASSERT_EQ(26, len);

    LOG_INFO(TEST, "%u ms", duration);
    return res;
}

bool test_csv_cnt_perf(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CSV, LOG_LEVEL_INFO);
    bool res = true;

    uint32_t start_ms = time_get_ms32();
    uint32_t cnt = csv_cnt("ewr 2047 0x25252535 0x0025", ' ');
    uint32_t end_ms = time_get_ms32();
    uint32_t duration = end_ms - start_ms;
    ASSERT_GR(duration, 400);
    ASSERT_EQ(4, cnt);

    LOG_INFO(TEST, "%u ms", duration);
    return res;
}

#define CVS_TEST_LINE "ewr 2047 0x25252535 0x0025"
bool test_csv_fetch_text_perf(void) {
    bool res = true;
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CSV, LOG_LEVEL_INFO);

    size_t size = strlen(CVS_TEST_LINE);
    uint32_t offset = 0;

    uint32_t start_ms = time_get_ms32();
    ASSERT_TRUE(csv_fetch_text(CVS_TEST_LINE, size, ' ', 0, &offset));
    ASSERT_TRUE(csv_fetch_text(CVS_TEST_LINE, size, ' ', 1, &offset));
    ASSERT_TRUE(csv_fetch_text(CVS_TEST_LINE, size, ' ', 2, &offset));
    ASSERT_TRUE(csv_fetch_text(CVS_TEST_LINE, size, ' ', 3, &offset));
    uint32_t end_ms = time_get_ms32();
    uint32_t duration = end_ms - start_ms;
    ASSERT_GR(duration, 1000)
    LOG_INFO(TEST, "%u ms", duration);

    return res;
}
