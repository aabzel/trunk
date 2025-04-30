#include "data_utils_test.h"

#include <stdio.h>

#include "common_diag.h"
#include "data_utils.h"
#include "interval.h"
#include "log.h"
#include "macro_utils.h"
#include "unit_test_check.h"
#ifdef HAS_MATH
#include "utils_math.h"
#endif

bool test_interval_overlap(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    set_log_level(INTERVAL, LOG_LEVEL_DEBUG);
    IntervalE_t IntA;
    IntervalE_t IntB;

    IntA.start = 1;
    IntA.end = 4;
    IntB.start = 6;
    IntB.end = 8;
    ASSERT_FALSE(intervals_overlaps(&IntA, &IntB));
    ASSERT_FALSE(intervals_overlaps(&IntB, &IntA));

    IntA.start = 1;
    IntA.end = 4;
    IntB.start = 3;
    IntB.end = 5;
    ASSERT_TRUE(intervals_overlaps(&IntA, &IntB));
    ASSERT_TRUE(intervals_overlaps(&IntB, &IntA));
    set_log_level(INTERVAL, LOG_LEVEL_INFO);
    return true;
}

bool test_bin2sacii(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    uint8_t dataBin[2] = {0x12, 0xaf};
    uint8_t BinAscii[100] = "";
    ASSERT_TRUE(hex2ascii(dataBin, sizeof(dataBin), BinAscii, sizeof(BinAscii)));
    ASSERT_STREQ("12AF", (const char*)BinAscii);
    return true;
}

bool test_extract_digit(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    ASSERT_EQ(0, extract_digit(10256, 6));
    ASSERT_EQ(9, extract_digit(100389, 0));
    ASSERT_EQ(8, extract_digit(100389, 1));
    ASSERT_EQ(3, extract_digit(100389, 2));
    ASSERT_EQ(0, extract_digit(100389, 3));
    ASSERT_EQ(5, extract_digit(10256, 1));
    return true;
}

typedef struct xZeroStruct_t {
    uint16_t ff[0];
} ZeroStruct_t;

struct xZeroStruct2_t {
    uint16_t ff[0];
} zero_struct;

/*tsr data_utils+*/
bool test_data_utils(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    ASSERT_EQ(0, sizeof(ZeroStruct_t)); // 0 on PC
    ASSERT_EQ(0, sizeof(zero_struct));  // 0 on PC
#ifdef HAS_CORE_NET
    ASSERT_EQ(4, sizeof(1.1));
#else
    ASSERT_EQ(8, sizeof(1.1));
#endif
    ASSERT_EQ(4, sizeof(1.1f));
    ASSERT_EQ(8, ceil4byte(7));
    ASSERT_EQ(4, ceil4byte(4));
    ASSERT_EQ(8, ceil4byte(8));
#ifdef HAS_MATH
    ASSERT_EQ(6, two_complement_to_decimal(0x06, 7));
    ASSERT_EQ(-15, two_complement_to_decimal(0x71, 7));
    ASSERT_EQ(-23, two_complement_to_decimal(0x69, 7));

    ASSERT_EQ(parse_n_bit_signed(0x06, 7), two_complement_to_decimal(0x06, 7));
    ASSERT_EQ(parse_n_bit_signed(0x71, 7), two_complement_to_decimal(0x71, 7));
    ASSERT_EQ(parse_n_bit_signed(0x69, 7), two_complement_to_decimal(0x69, 7));
#endif

    ASSERT_TRUE(test_extract_digit());
    return true;
}

bool test_bit2bytes(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    ASSERT_EQ(0, Bits2Bytes(0));
    ASSERT_EQ(1, Bits2Bytes(7));
    ASSERT_EQ(1, Bits2Bytes(8));
    ASSERT_EQ(2, Bits2Bytes(9));
    ASSERT_EQ(5, Bits2Bytes(33));
    ASSERT_EQ(8, Bits2Bytes(64));
    return true;
}

bool test_data_sizes(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    ASSERT_EQ(8, sizeof(Type64Union_t));
    ASSERT_EQ(4, sizeof(Type32Union_t));
    ASSERT_EQ(3, sizeof(Type24Union_t));
    ASSERT_EQ(2, sizeof(Type16Union_t));
    ASSERT_EQ(2, sizeof(TypeHighSnrFmt_t));
    ASSERT_EQ(2, sizeof(TypeHighSnr_t));
    ASSERT_EQ(1, sizeof(Type8Union_t));
    return true;
}

bool test_int_shift_left(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    int32_t val = -5;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val << 8;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    ASSERT_GR(val, 0);
    val = val << 8;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val << 8;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val << 8;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val << 8;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    return true;
}

bool test_int_shift_right(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    int32_t val = -55;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    ASSERT_GR(val, 0);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    ASSERT_GR(val, 0);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    val = val >> 1;
    LOG_INFO(TEST, "val:%d 0x%08x", val, val);
    ASSERT_GR(val, 0);
    return true;
}

bool test_int_arround(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    ASSERT_TRUE(is_around_int_val(-10, -9, 5));
    ASSERT_FALSE(is_around_int_val(-10, -999, 5));

    ASSERT_TRUE(is_around_int_val(100, 101, 5));
    ASSERT_FALSE(is_around_int_val(100, 10101, 5));
    return true;
}

/*
 tsr interval+
 * */
bool test_interval_shared(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    set_log_level(INTERVAL, LOG_LEVEL_DEBUG);
    IntervalE_t IntA;
    IntervalE_t IntB;

    IntA.start = 1;
    IntA.end = 9;
    IntB.start = 6;
    IntB.end = 10;
    ASSERT_FALSE(intervals_shared(&IntA, &IntB));
    ASSERT_FALSE(intervals_shared(&IntB, &IntA));

    IntA.start = 1;
    IntA.end = 9;
    IntB.start = 6;
    IntB.end = 9;
    ASSERT_TRUE(intervals_shared(&IntA, &IntB));
    ASSERT_TRUE(intervals_shared(&IntB, &IntA));
    set_log_level(INTERVAL, LOG_LEVEL_INFO);
    return true;
}

bool test_interval_merge(void) {
    LOG_INFO(TEST, "%s().." CRLF, __FUNCTION__);
    set_log_level(INTERVAL, LOG_LEVEL_DEBUG);
    IntervalE_t IntA;
    IntervalE_t IntB;
    IntervalE_t IntC;

    IntA.start = 1;
    IntA.end = 9;
    IntB.start = 6;
    IntB.end = 10;
    ASSERT_TRUE(intervals_merge(&IntA, &IntB, &IntC));
    ASSERT_EQ(1, IntC.start);
    ASSERT_EQ(10, IntC.end);

    IntA.start = 1;
    IntA.end = 9;
    IntB.start = 6;
    IntB.end = 8;
    ASSERT_TRUE(intervals_merge(&IntA, &IntB, &IntC));
    ASSERT_EQ(1, IntC.start);
    ASSERT_EQ(9, IntC.end);
    set_log_level(INTERVAL, LOG_LEVEL_INFO);
    return true;
}

/*
https://www.exploringbinary.com/twos-complement-converter/
*/
