#include "float_utils_test.h"

#include <math.h>
#include <stdio.h>

#include "data_utils.h"
#include "float_utils.h"
#include "log.h"
#include "unit_test_check.h"

#if 0
static const HsnrTestCase_t HsnrTestCaseLut[] = {{0xf700, 3.75},
                                                 {0x0ffe, -1.0 * pow(2.0, -23.0)},
                                                 {0xd800, -1.0},
                                                 {0xf600, 3.5},
                                                 {0xf500, 3.25},
                                                 {0xf400, 3.0},
                                                 {0xf2e0, 2.71875},
                                                 {0x0000, 0.0},
                                                 {0xf000, 2.0},
                                                 {0xe600, 1.75},
                                                 {0xe400, 1.5},
                                                 {0xe000, 1.0},
                                                 {0xf491, 3.1416015625},
                                                 {0xec00, -1.5},
                                                 {0xe800, -2.0},
                                                 {0xfc00, -3.0},
                                                 {0xf800, -4.0},
                                                 {0xf7ff, 4095.0 * pow(2.0, -10.0)},
                                                 {0xf7fe, 4094.0 * pow(2.0, -10.0)},
                                                 {0xf701, 3841.0 * pow(2.0, -10.0)},
                                                 {0xe001, 2049.0 * pow(2.0, -11.0)},
                                                 {0xd7ff, 4095.0 * pow(2.0, -12.0)},
                                                 {0x2700, 30 * pow(2.0, -16.0)},
                                                 {0x17ff, 4095.0 * pow(2.0, -24.0)},
                                                 {0x17fe, 2047.0 * pow(2.0, -23.0)},
                                                 {0x1700, 15.0 * pow(2.0, -16.0)},
                                                 {0x1001, 2049.0 * pow(2.0, -24.0)},
                                                 {0x1000, 1.0 * pow(2.0, -13.0)},
                                                 {0x07ff, 2047.0 * pow(2.0, -24.0)},
                                                 {0x0003, 3.0 * pow(2.0, -24.0)},
                                                 {0x0002, 1.0 * pow(2.0, -23.0)},
                                                 {0x0001, 1.0 * pow(2.0, -24.0)},
                                                 {0x0fff, -1.0 * pow(2.0, -24.0)},
                                                 {0x0ffd, -3.0 * pow(2.0, -24.0)},
                                                 {0x0801, -2047.0 * pow(2.0, -24.0)},
                                                 {0x0800, -1.0 * pow(2.0, -13.0)},
                                                 {0xd801, -4095.0 * pow(2.0, -12.0)},
                                                 {0xefff, -2049.0 * pow(2.0, -11.0)},
                                                 {0xeffe, -1025.0 * pow(2.0, -10.0)},
                                                 {0xe802, -4094.0 * pow(2.0, -11.0)},
                                                 {0xe801, -4095.0 * pow(2.0, -11.0)},
                                                 {0xffff, -2049.0 * pow(2.0, -10.0)},
                                                 {0xfffe, -1025.0 * pow(2.0, -9.0)},
                                                 {0xf802, -2047.0 * pow(2.0, -9.0)},
                                                 {0xf801, -4095.0 * pow(2.0, -10.0)}};
#endif

#define PRECISION 0.2f
bool test_float_utils(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    float val = 0.0f;
    bool res = IS_FLOAT_EQUAL_ABSOLUTE(0.1f, 0.1f, PRECISION);
    ASSERT_TRUE(res);

    res = IS_FLOAT_EQUAL_ABSOLUTE(10.0f, 0.1f, PRECISION);
    EXPECT_FALSE(res);

    ASSERT_TRUE(is_float_equal_absolute(0.1f, 0.1f, PRECISION));

    val = float_max(2000.0f, 100.0f);
    res = IS_FLOAT_EQUAL_ABSOLUTE(2000.0f, val, PRECISION);
    ASSERT_TRUE(res);

    val = float_max(200.0f, 3000.0f);
    res = IS_FLOAT_EQUAL_ABSOLUTE(3000.0f, val, PRECISION);
    ASSERT_TRUE(res);

    return true;
}

bool test_hsnr_to_double(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
#if 0
    set_log_level(TEST, LOG_LEVEL_INFO);
    uint32_t i = 0;
    double calc_value = 0.0;
    for(i = 0; i < ARRAY_SIZE(HsnrTestCaseLut); i++) {
        LOG_DEBUG(TEST, "Test No:%d", i);
        calc_value = high_snr_decode(HsnrTestCaseLut[i].hsnr);
        ASSERT_TRUE(is_double_equal_absolute(HsnrTestCaseLut[i].value, calc_value, 0.00001));
    }
    set_log_level(TEST, LOG_LEVEL_INFO);
#endif
    return true;
}

bool test_float_to_fixed_point(void) {
    LOG_INFO(TEST, "%s()", __FUNCTION__);
    set_log_level(TEST, LOG_LEVEL_INFO);

    FloatFixPoint_t FixPoint = {0};
    FixPoint.fractional = 0;
    FixPoint.integer = 0;
    ASSERT_TRUE(float_to_integer_and_fractional(1.12, 2, &FixPoint));
    ASSERT_EQ(1, FixPoint.integer);
    ASSERT_EQ(12, FixPoint.fractional);

    FixPoint.fractional = 0;
    FixPoint.integer = 0;
    ASSERT_TRUE(float_to_integer_and_fractional(-20.567, 3, &FixPoint));
    ASSERT_EQ(-20, FixPoint.integer);
    ASSERT_EQ(567, FixPoint.fractional);

    FixPoint.fractional = 0;
    FixPoint.integer = 0;
    ASSERT_TRUE(float_to_integer_and_fractional(0.0, 4, &FixPoint));
    ASSERT_EQ(0, FixPoint.integer);
    ASSERT_EQ(0, FixPoint.fractional);

    set_log_level(TEST, LOG_LEVEL_INFO);
    return true;
}
