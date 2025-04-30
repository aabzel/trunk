#include "test_convert.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "convert.h"
#include "oprintf.h"

#include "unit_test_check.h"

static const uint8_t ExpArray[128] = {
    0x00, 0x40, 0x01, 0x20, 0x4D, 0x56, 0x04, 0x00, 0xA3, 0x4F, 0x02, 0x00, 0x4F, 0x2D, 0x02, 0x00, 0x7B, 0x40, 0x02,
    0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B,
    0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00,
    0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02,
    0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40,
    0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00, 0x7B, 0x40, 0x02, 0x00};

static const char arg1[] = "0x004001204D560400A34F02004F2D02007B4002007B4002007B400200000000000000000000000000000000007"
                           "B4002007B400200000000007B4002007B4002007B4002007B4002007B4002007B4002007B4002007B4002007B40"
                           "02007B4002007B4002007B4002007B4002007B4002007B4002007B4002007B4002007B400200";

bool test_convert_try_str2array(void) {
    uint8_t array[256];
    memset(array, 0, sizeof(array));
    size_t out_array_len = 0;
    ASSERT_TRUE(try_str2array((char*)arg1, array, sizeof(array), &out_array_len));
    ASSERT_EQ(128, out_array_len);
    EXPECT_EQ_MEM(ExpArray, array, sizeof(ExpArray));
    return true;
}

bool test_convert_try_str2int8(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    int8_t value = 0;
    ASSERT_TRUE(try_str2int8("-128", &value));
    ASSERT_EQ(INT8_MIN, value);
    ASSERT_FALSE(try_str2int8("", &value));
    ASSERT_FALSE(try_str2int8("-129", &value));
    ASSERT_FALSE(try_str2int8("128", &value));

    ASSERT_TRUE(try_str2int8("0", &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_str2int8("127", &value));
    ASSERT_EQ(INT8_MAX, value);
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

bool test_convert_try_str2uint8_invalid(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t value;
    ASSERT_FALSE(try_str2uint8("", &value));
    ASSERT_FALSE(try_str2uint8("A", &value));
    ASSERT_FALSE(try_str2uint8("zzz", &value));
    return true;
}

bool test_convert_is_dec_str(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_TRUE(is_dec_str("1234", 4));
    ASSERT_FALSE(is_dec_str("0x1234", 6));
    ASSERT_FALSE(is_dec_str("Fabc", 4));
    ASSERT_FALSE(is_dec_str("qwer", 6));
    return true;
}

bool test_convert_is_hex_str(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t shift_value = 0U;
    ASSERT_TRUE(is_hex_str("0xFabc", 6, &shift_value));
    ASSERT_EQ(2U, shift_value);

    ASSERT_TRUE(is_hex_str("1234", 4, &shift_value));

    ASSERT_TRUE(is_hex_str("0x1234", 6, &shift_value));
    ASSERT_EQ(2U, shift_value);

    ASSERT_TRUE(is_hex_str("Fabc", 4, &shift_value));
    ASSERT_EQ(0U, shift_value);
    ASSERT_FALSE(is_hex_str("0xqwer", 6, &shift_value));
    return true;
}

bool test_convert_try_str2uint8(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t value;
    ASSERT_FALSE(try_str2uint8("256", &value));
    ASSERT_FALSE(try_str2uint8("-1", &value));

    ASSERT_TRUE(try_str2uint8("0", &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_str2uint8("255", &value));
    ASSERT_EQ(UINT8_MAX, value);
    ASSERT_TRUE(try_str2uint8("0xFF", &value));
    ASSERT_EQ(UINT8_MAX, value);
    return true;
}

bool test_convert_try_strl2uint16_hex(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint16_t value;
    ASSERT_FALSE(try_strl2uint16_hex("", 0, &value));
    ASSERT_FALSE(try_strl2uint16_hex("-1", 2, &value));
    ASSERT_FALSE(try_strl2uint16_hex("0", 0, &value));

    ASSERT_TRUE(try_strl2uint16_hex("1234", 4, &value));
    ASSERT_EQ(0x1234, value);

    ASSERT_TRUE(try_strl2uint16_hex("FFF", 3, &value));
    ASSERT_EQ(0xFFF, value);

    ASSERT_TRUE(try_strl2uint16_hex("0", 1, &value));
    ASSERT_EQ(0, value);

    ASSERT_TRUE(try_strl2uint16_hex("FF", 2, &value));
    ASSERT_EQ(0xFF, value);
    return true;
}

bool test_convert_try_strl2uint8_hex(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t value;
    ASSERT_FALSE(try_strl2uint8_hex("", -1, &value));
    ASSERT_FALSE(try_strl2uint8_hex("FFF", -1, &value));
    ASSERT_FALSE(try_strl2uint8_hex("-1", -1, &value));
    ASSERT_FALSE(try_strl2uint8_hex("0", 0, &value));

    ASSERT_TRUE(try_strl2uint8_hex("0", -1, &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_strl2uint8_hex("FF", -1, &value));
    ASSERT_EQ(UINT8_MAX, value);
    return true;
}

bool test_convert_try_str2int16(void) {
    int16_t value;
    ASSERT_FALSE(try_str2int16("", &value));
    ASSERT_FALSE(try_str2int16("-327679", &value));
    ASSERT_FALSE(try_str2int16("32768", &value));

    ASSERT_TRUE(try_str2int16("-32768", &value));
    ASSERT_EQ(INT16_MIN, value);
    ASSERT_TRUE(try_str2int16("0", &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_str2int16("32767", &value));
    ASSERT_EQ(INT16_MAX, value);
    return true;
}

bool test_convert_try_str2uint16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint16_t value;
    ASSERT_FALSE(try_str2uint16("", &value));
    ASSERT_FALSE(try_str2uint16("65536", &value));
    ASSERT_FALSE(try_str2uint16("-1", &value));

    value = 0U;
    ASSERT_TRUE(try_str2uint16("0xABCD", &value));
    ASSERT_EQ((uint16_t)43981, value);

    ASSERT_TRUE(try_str2uint16("0", &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_str2uint16("65535", &value));
    ASSERT_EQ(UINT16_MAX, value);
    return true;
}

bool test_convert_try_str2int32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t value;
    ASSERT_FALSE(try_str2int32("", &value));
    ASSERT_FALSE(try_str2int32("-2147483649", &value));
    ASSERT_FALSE(try_str2int32("2147483648", &value));

    ASSERT_TRUE(try_str2int32("-2147483648", &value));
    ASSERT_EQ(INT32_MIN, value);
    ASSERT_TRUE(try_str2int32("0", &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_str2int32("2147483647", &value));
    ASSERT_EQ(INT32_MAX, value);

    ASSERT_TRUE(try_str2int32("0x12345678", &value));
    ASSERT_EQ(0x12345678, value);
    ASSERT_TRUE(try_str2int32("0x78ABCDEF", &value));
    ASSERT_EQ(0x78ABCDEF, value);
    ASSERT_TRUE(try_str2int32("0x78abcdef", &value));
    ASSERT_EQ(0x78ABCDEF, value);
    ASSERT_TRUE(try_str2int32("0x7FFFFFFF", &value));
    ASSERT_EQ(0x7FFFFFFF, value);
    ASSERT_FALSE(try_str2int32("0x8FFFFFFF", &value));
    ASSERT_FALSE(try_str2int32("0x7QFFFFFF", &value));
    ASSERT_FALSE(try_str2int32("0x7/FFFFFF", &value));
    return true;
}

bool test_convert_try_str2uint32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t value = 0;

    ASSERT_TRUE(try_str2uint32("96", &value));
    ASSERT_EQ(96, value);

    ASSERT_FALSE(try_str2uint32("", &value));
    ASSERT_FALSE(try_str2uint32("4294967296", &value));
    ASSERT_FALSE(try_str2uint32("-1", &value));

    ASSERT_TRUE(try_str2uint32("0", &value));
    ASSERT_EQ(0u, value);

    ASSERT_TRUE(try_str2uint32("4294967295", &value));
    ASSERT_EQ(UINT32_MAX, value);
    return true;
}

bool test_convert_try_str2luint32_hex(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t value;

    ASSERT_FALSE(try_strl2uint32_hex("0x12345", 7, &value));
    ASSERT_FALSE(try_strl2uint32_hex("12345", 0, &value));
    ASSERT_TRUE(try_strl2uint32_hex("12345", -1, &value));
    ASSERT_EQ(0x12345U, value);
    ASSERT_FALSE(try_strl2uint32_hex("12345~", -1, &value));
    ASSERT_FALSE(try_strl2uint32_hex("123456789", -1, &value));
    return true;
}

bool test_convert_try_str2luint32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t value = 0;
    ASSERT_FALSE(try_strl2uint32("3*4B", 2, &value));
    ASSERT_EQ(0, value);
    ASSERT_TRUE(try_strl2uint32("140222,,,A,V*1B", 6, &value));
    ASSERT_EQ(140222, value);

    ASSERT_FALSE(try_strl2uint32("12345", 0, &value));
    ASSERT_TRUE(try_strl2uint32("12345", -1, &value));
    ASSERT_EQ(12345U, value);
    ASSERT_FALSE(try_strl2uint32("12345~", -1, &value));
    ASSERT_TRUE(try_strl2uint32("12345A", -1, &value));
    ASSERT_EQ(0x12345A, value);
    return true;
}

bool test_convert_try_str_ascii2nimble(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint8_t nibble = 0xFF;
    ASSERT_FALSE(AsciiChar2HexNibble('r', &nibble));
    ASSERT_FALSE(AsciiChar2HexNibble('6', NULL));

    ASSERT_TRUE(AsciiChar2HexNibble('1', &nibble));
    ASSERT_EQ(0x01, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('2', &nibble));
    ASSERT_EQ(0x02, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('3', &nibble));
    ASSERT_EQ(0x03, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('4', &nibble));
    ASSERT_EQ(0x04, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('5', &nibble));
    ASSERT_EQ(0x05, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('6', &nibble));
    ASSERT_EQ(0x06, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('7', &nibble));
    ASSERT_EQ(0x07, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('8', &nibble));
    ASSERT_EQ(0x08, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('9', &nibble));
    ASSERT_EQ(0x09, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('A', &nibble));
    ASSERT_EQ(0x0A, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('B', &nibble));
    ASSERT_EQ(0x0B, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('C', &nibble));
    ASSERT_EQ(0x0C, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('D', &nibble));
    ASSERT_EQ(0x0D, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('E', &nibble));
    ASSERT_EQ(0x0E, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('F', &nibble));
    ASSERT_EQ(0x0F, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('a', &nibble));
    ASSERT_EQ(0x0A, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('b', &nibble));
    ASSERT_EQ(0x0B, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('c', &nibble));
    ASSERT_EQ(0x0C, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('d', &nibble));
    ASSERT_EQ(0x0D, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('e', &nibble));
    ASSERT_EQ(0x0E, nibble);

    ASSERT_TRUE(AsciiChar2HexNibble('f', &nibble));
    ASSERT_EQ(0x0F, nibble);

    return true;
}

bool test_convert_try_str2lint32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    int32_t value = -1;
    char inStr[40] = "";

    strncpy(inStr, "+1", sizeof(inStr));
    ASSERT_TRUE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(1, value);

    strncpy(inStr, " 7", sizeof(inStr));
    ASSERT_TRUE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(7, value);

    strncpy(inStr, "2024", sizeof(inStr));
    ASSERT_TRUE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(2024, value);

    strncpy(inStr, "words and 987", sizeof(inStr));
    ASSERT_FALSE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(0, value);

    strncpy(inStr, "hs", sizeof(inStr));
    ASSERT_FALSE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(0, value);

    strncpy(inStr, "20000000000000000000", sizeof(inStr));
    ASSERT_FALSE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(0, value);

    strncpy(inStr, "-91283472332", sizeof(inStr));
    ASSERT_FALSE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(0, value);

    strncpy(inStr, "4193 with words", sizeof(inStr));
    ASSERT_FALSE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(0, value);

    strncpy(inStr, "-42", sizeof(inStr));
    ASSERT_TRUE(try_strl2int32(inStr, strlen(inStr), &value));
    ASSERT_EQ(-42, value);

    ASSERT_FALSE(try_strl2int32("12345", 0, &value));
    ASSERT_TRUE(try_strl2int32("12345", -1, &value));
    ASSERT_EQ(12345, value);
    ASSERT_FALSE(try_strl2int32("12345~", -1, &value));
    ASSERT_TRUE(try_strl2int32("12345A", -1, &value));
    ASSERT_EQ(0x12345A, value);
    ASSERT_FALSE(try_strl2int32("12345678901234567", -1, &value));
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

bool test_convert_try_str2uint32_hex(void) {
    uint32_t value;
    ASSERT_TRUE(try_str2uint32_hex("abCd", &value));
    ASSERT_EQ((uint32_t)43981, value);

    ASSERT_TRUE(try_str2uint32_hex("12345", &value));
    ASSERT_EQ(0x12345U, value);
    return true;
}

bool test_convert_try_str2lint64(void) {
    int64_t value;
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(try_strl2int64("12345", -1, &value));
    ASSERT_EQ(12345, value);

    ASSERT_FALSE(try_strl2int64("12345", 0, &value));
    ASSERT_FALSE(try_strl2int64("12345~", -1, &value));
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

bool test_convert_try_str2luint64(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    uint64_t value = 0;
    ASSERT_FALSE(try_strl2uint64("12345~", -1, &value));

    ASSERT_TRUE(try_strl2uint64("12345", -1, &value));
    ASSERT_EQ(12345U, value);

    ASSERT_FALSE(try_strl2uint64("12345", 0, &value));

    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return true;
}

bool test_convert_try_str2int64(void) {
    int64_t value;
    ASSERT_FALSE(try_str2int64("", &value));
    ASSERT_FALSE(try_str2int64("-", &value));
    ASSERT_FALSE(try_str2int64("-9223372036854775808", &value));
    ASSERT_FALSE(try_str2int64("9223372036854775808", &value));
    ASSERT_FALSE(try_str2int64("0xabcdefgh", &value));
    ASSERT_FALSE(try_str2int64("0x10000000000000000", &value));

    ASSERT_TRUE(try_str2int64("-9223372036854775807", &value));
    ASSERT_EQ(-INT64_MAX, value);

    ASSERT_TRUE(try_str2int64("9223372036854775807", &value));
    ASSERT_EQ(INT64_MAX, value);

    ASSERT_TRUE(try_str2int64("0X123456789ABCDEF", &value));
    ASSERT_EQ(0x123456789ABCDEF, value);

    ASSERT_TRUE(try_str2int64("0x123456789abcdef", &value));
    ASSERT_EQ(0x123456789abcdef, value);

    ASSERT_TRUE(try_str2int64("0x7FFFFFFFFFFFFFF", &value));
    ASSERT_EQ(0x7ffffffffffffff, value);
    return true;
}

bool test_convert_try_str2uint64(void) {
    uint64_t value;
    ASSERT_FALSE(try_str2uint64("", &value));
    ASSERT_FALSE(try_str2uint64("-", &value));
    ASSERT_FALSE(try_str2uint64("18446744073709551616", &value));
    ASSERT_FALSE(try_str2uint64("0xabcdefgh", &value));
    ASSERT_FALSE(try_str2uint64("0x100000000000000000", &value));

    ASSERT_TRUE(try_str2uint64("0", &value));
    ASSERT_EQ(0U, value);

    ASSERT_TRUE(try_str2uint64("18446744073709551615", &value));
    ASSERT_EQ(UINT64_MAX, value);

    ASSERT_TRUE(try_str2uint64("0X123456789ABCDEF", &value));
    ASSERT_EQ(0x123456789ABCDEFULL, value);

    ASSERT_TRUE(try_str2uint64("0x123456789abcdef", &value));
    ASSERT_EQ(0x123456789abcdefULL, value);

    ASSERT_TRUE(try_str2uint64("0x7FFFFFFFFFFFFFF", &value));
    ASSERT_EQ(0x7ffffffffffffffULL, value);

    ASSERT_TRUE(try_str2uint64("0xFFFFFFFFFFFFFFF", &value));
    ASSERT_EQ(0xfffffffffffffffULL, value);
    return true;
}

bool test_convert_try_str2float(void) {
    float value = 0;
    float* valueNull = NULL;

    // uncleare ".e1" +E3

    ASSERT_TRUE(try_str2float("005047e+6", &value));
    ASSERT_TRUE(try_str2float("-.3e6", &value));

    ASSERT_TRUE(try_str2float("1", &value));
    ASSERT_NEAR(1.0f, value, 0.01f);

    ASSERT_TRUE(try_str2float("2e10", &value));
    ASSERT_NEAR(2e10, value, 0.01);

    ASSERT_TRUE(try_str2float(".1", &value));
    ASSERT_NEAR(0.1f, value, 0.01);

    ASSERT_TRUE(try_str2float("0.1", &value));
    ASSERT_NEAR(0.1f, value, 0.01);

    ASSERT_TRUE(try_str2float("3.", &value));
    ASSERT_NEAR(3.0f, value, 0.01);

    ASSERT_TRUE(try_str2float("0", &value));
    ASSERT_NEAR(0.0f, value, 0.01);

    ASSERT_TRUE(try_str2float(".2e35", &value));
    ASSERT_NEAR(2e34, value, 1e27);

    ASSERT_FALSE(try_str2float("4e+", &value));
    ASSERT_FALSE(try_str2float("..", &value));
    ASSERT_FALSE(try_str2float("+.", &value));
    ASSERT_FALSE(try_str2float(".1.", &value));
    ASSERT_FALSE(try_str2float("6+1", &value));
    ASSERT_FALSE(try_str2float("53K", &value));
    ASSERT_FALSE(try_str2float(" 4e3.", &value));
    ASSERT_FALSE(try_str2float("0..", &value));
    ASSERT_FALSE(try_str2float(".  ", &value));
    ASSERT_FALSE(try_str2float("abc", &value));
    ASSERT_FALSE(try_str2float("0e", &value));
    ASSERT_FALSE(try_str2float("1 4", &value));
    ASSERT_FALSE(try_str2float("1t", &value));
    ASSERT_FALSE(try_str2float("078332e437", &value));
    ASSERT_FALSE(try_str2float("1e1000", &value));
    ASSERT_FALSE(try_str2float("1e50", &value));
    ASSERT_FALSE(try_str2float("-1e50", &value));
    ASSERT_FALSE(try_str2float("1e-50", &value));

    ASSERT_TRUE(try_str2float("12345678", &value));
    ASSERT_NEAR(12345678, value, 0.0001);

    ASSERT_TRUE(try_str2float("1e-1", &value));
    ASSERT_NEAR(0.1F, value, 0.0001);

    ASSERT_TRUE(try_str2float("1e2", &value));
    ASSERT_NEAR(100, value, 0.0001);

    ASSERT_TRUE(try_str2float("0.0", &value));
    ASSERT_NEAR(0.0, value, 0.0001);

    ASSERT_TRUE(try_str2float("-17", &value));
    ASSERT_NEAR(-17.0, value, 0.0001);

    ASSERT_FALSE(try_str2float("-28", valueNull));
    return true;
}

bool test_convert_try_strl2double(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    double value = 0.0;
    ASSERT_TRUE(try_strl2double("5551.85827,N,03725.60947,E", 10, &value));
    ASSERT_NEAR(5551.85827, value, 0.0001);
    return true;
}

typedef struct {
    char* input_str;
    bool is_double;
    double value;
} ParseDoubleTestCase_t;

// Unclear "+E3"     ".e1"  "4e+"
static const ParseDoubleTestCase_t ParseDoubleTestCase[] = {
    {
        .input_str = "23456789012345678901",
        .is_double = true,
        .value = 23456789012345678901.0,
    }, /*uint64 overflow*/
    {
        .input_str = "12345678901234567890",
        .is_double = true,
        .value = 12345678901234567890.0,
    },
    {
        .input_str = "-.9",
        .is_double = true,
        .value = -0.9,
    },
    {
        .input_str = "abc",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "-8115e957",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "3.",
        .is_double = true,
        .value = 3.0,
    },
    {
        .input_str = "2e0",
        .is_double = true,
        .value = 2.0,
    },
    {
        .input_str = "4e+",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = ".",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "e9",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "-0.1",
        .is_double = true,
        .value = -0.1,
    },
    {
        .input_str = "-90E3",
        .is_double = true,
        .value = -90000,
    },
    {
        .input_str = "005047e+6",
        .is_double = true,
        .value = 5047.0 * 1000000.0,
    },
    {
        .input_str = ".0",
        .is_double = true,
        .value = 0.0,
    },
    {
        .input_str = "+.",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "4.",
        .is_double = true,
        .value = 4.0,
    },
    {
        .input_str = " -1520003945\r",
        .is_double = true,
        .value = -1520003945.0,
    },
    {
        .input_str = " 1520003945\n",
        .is_double = true,
        .value = 1520003945.0,
    },
    {
        .input_str = "+3.14",
        .is_double = true,
        .value = 3.14,
    },
    {
        .input_str = "008",
        .is_double = true,
        .value = 8,
    },
    {
        .input_str = "12345678",
        .is_double = true,
        .value = 12345678,
    },
    {
        .input_str = "1e-1",
        .is_double = true,
        .value = 0.1,
    },
    {
        .input_str = "1e+1",
        .is_double = true,
        .value = 10,
    },
    {
        .input_str = "1e2",
        .is_double = true,
        .value = 100,
    },
    {
        .input_str = "+1e2",
        .is_double = true,
        .value = 100,
    },
    {
        .input_str = "-1e2",
        .is_double = true,
        .value = -100,
    },
    {
        .input_str = "2e10",
        .is_double = true,
        .value = 20000000000,
    },
    {
        .input_str = "0089",
        .is_double = true,
        .value = 89,
    },
    {
        .input_str = "2",
        .is_double = true,
        .value = 2,
    },
    {
        .input_str = "21055406075",
        .is_double = true,
        .value = 21055406075,
    },
    {
        .input_str = "+1.2e2",
        .is_double = true,
        .value = 120,
    },
    {
        .input_str = " 1520003945",
        .is_double = true,
        .value = 1520003945.0,
    },
    {
        .input_str = " 1520003945\r",
        .is_double = true,
        .value = 1520003945.0,
    },
    {
        .input_str = "+.",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "6+1",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "..",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "e3",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "95a54e53",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "959440.94f",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "-+3",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "--6",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "6e6.5",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e2.5",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "99e2.5",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1a",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e-1000",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e1000",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1t",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e10000000",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "1e-10000000",
        .is_double = false,
        .value = 0.0,
    },
    {
        .input_str = "0",
        .is_double = true,
        .value = 0.0,
    },
    {
        .input_str = "3e-3",
        .is_double = true,
        .value = 0.003,
    },
};

/*TODO: compose diag
 *
 * 1200 -> 1.2k
 *  120 -> 120
 * const char* NumToStr(double);
 */

static const ParseDoubleTestCase_t ParseDoubleSuffixTestCase[] = {
    {
        .input_str = "1.5M",
        .is_double = true,
        .value = 1500000.0,
    },
    {
        .input_str = "10M",
        .is_double = true,
        .value = 10000000.0,
    },
    {
        .input_str = "u",
        .is_double = true,
        .value = 0.000001,
    },
    {
        .input_str = "m",
        .is_double = true,
        .value = 0.001,
    },
    {
        .input_str = "k",
        .is_double = true,
        .value = 1000.0,
    },
    {
        .input_str = "M",
        .is_double = true,
        .value = 1000000.0,
    },
    {
        .input_str = "n",
        .is_double = true,
        .value = 0.000000001,
    },
    {
        .input_str = "12.5k",
        .is_double = true,
        .value = 12500.0,
    },
    {
        .input_str = "10n",
        .is_double = true,
        .value = 0.00000001,
    },
    {
        .input_str = "G",
        .is_double = true,
        .value = 1000000000.0,
    },
    {
        .input_str = "1",
        .is_double = true,
        .value = 1.0,
    },
    {
        .input_str = "10G",
        .is_double = true,
        .value = 10000000000.0,
    },
    {
        .input_str = "1m",
        .is_double = true,
        .value = 0.001,
    },
    {
        .input_str = "1u",
        .is_double = true,
        .value = 0.000001,
    },
    {
        .input_str = "10k",
        .is_double = true,
        .value = 10000.0,
    },
    {
        .input_str = "10",
        .is_double = true,
        .value = 10.0,
    },
};
/*
 * tsr suffix+
 * */
bool test_try_str2suffix_number(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LINE, LOG_LEVEL_DEBUG);
    char lText[160] = "";
    double value = 0.0;

    uint32_t i = 0;
    uint32_t err_cnt = 0;
    uint32_t cnt = ARRAY_SIZE(ParseDoubleSuffixTestCase);
    for(i = 0; i < cnt; i++) {
        value = 100.0;
        res = try_str2number(ParseDoubleSuffixTestCase[i].input_str, &value);
        ASSERT_EQ(res, ParseDoubleSuffixTestCase[i].is_double);
        if(res) {
            sprintf(lText, "Exp:  %f, \nReal: %f\n", ParseDoubleSuffixTestCase[i].value, value);
            cli_printf("%s", lText);
            res = is_double_equal_absolute(ParseDoubleSuffixTestCase[i].value, value, 0.0001);
            ASSERT_TRUE(res)
            if(false == res) {
                err_cnt++;
                res = false;
                LOG_ERROR(LINE, "WrongParse [%s] Result %f", ParseDoubleSuffixTestCase[i].value, value);
            } else {
                LOG_INFO(LINE, "OkParse [%s] Result %lf", ParseDoubleSuffixTestCase[i].input_str, value);
            }

            ASSERT_NEAR(ParseDoubleSuffixTestCase[i].value, value, 0.0001);
        } else {
            err_cnt++;
        }
    }
    if(err_cnt) {
        res = false;
    } else {
        res = true;
    }

    set_log_level(LINE, LOG_LEVEL_INFO);
    return res;
}

bool test_convert_try_str2number(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LINE, LOG_LEVEL_DEBUG);
    char lText[160] = "";
    double value = 0.0;

    // Unclear "+E3"     ".e1"  "4e+"
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ParseDoubleTestCase);
    for(i = 0; i < cnt; i++) {
        value = 100.0;
        res = try_str2number(ParseDoubleTestCase[i].input_str, &value);
        ASSERT_EQ(res, ParseDoubleTestCase[i].is_double);
        if(res) {
            sprintf(lText, "Exp:  %f, \nReal: %f\n", ParseDoubleTestCase[i].value, value);
            cli_printf("%s", lText);
            res = is_double_equal_absolute(ParseDoubleTestCase[i].value, value, 0.0001);
            ASSERT_TRUE(res)
            if(false == res) {
                LOG_ERROR(LINE, "WrongParse [%s] Result %f", ParseDoubleTestCase[i].value, value);
            } else {
                LOG_INFO(LINE, "OkParse [%s] Result %lf", ParseDoubleTestCase[i].input_str, value);
            }

            ASSERT_NEAR(ParseDoubleTestCase[i].value, value, 0.0001);
        }
    }

    ASSERT_TRUE(try_str2number("-.3e6", &value)); // 0.3* 1000000.0
    ASSERT_TRUE(try_str2number("1e+11", &value)); // 100000000000
    ASSERT_TRUE(try_str2number("1e11", &value));
    ASSERT_TRUE(try_str2number("46.e3", &value));
    ASSERT_TRUE(try_str2number("53.5e93", &value));
    ASSERT_TRUE(try_str2number("+6e-1", &value));
    ASSERT_TRUE(try_str2number("3e+7", &value));
    ASSERT_TRUE(try_str2number("1e50", &value));
    ASSERT_TRUE(try_str2number("0", &value));
    ASSERT_TRUE(try_str2number("1e-50", &value));
    ASSERT_TRUE(try_str2number("-1e02", &value));

    set_log_level(LINE, LOG_LEVEL_INFO);
    return true;
}

#ifdef HAS_PC
bool test_sscanf(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    // bool out_res  = true;
    bool loc_res = true;
    set_log_level(LINE, LOG_LEVEL_DEBUG);
    double value = 0.0;

    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ParseDoubleTestCase);
    for(i = 0; i < cnt; i++) {
        value = 0.0;
        // LOG_INFO(TEST,"i=%u, In[%s], Exp %f",i,ParseDoubleTestCase[i].input_str,ParseDoubleTestCase[i].value);
        int ret = sscanf(ParseDoubleTestCase[i].input_str, "%lf", &value);
        if(ParseDoubleTestCase[i].is_double) {
            if(1 != ret) {
                LOG_ERROR(LINE, "UnableTo parse [%s]", ParseDoubleTestCase[i].input_str);
                res = false;
            } else {
                loc_res = is_double_equal_absolute(ParseDoubleTestCase[i].value, value, 0.0001);
                if(false == loc_res) {
                    LOG_ERROR(LINE, "WrongParse [%s] Result %f", ParseDoubleTestCase[i].value, value);
                } else {
                    LOG_INFO(LINE, "OkParse [%s] Result %f", ParseDoubleTestCase[i].input_str, value);
                }
            }
        } else {
            if(1 == ret) {
                LOG_ERROR(LINE, "Unnecessary parsing ret %d, [%s] Result:%f", ret, ParseDoubleTestCase[i].input_str,
                          value);
                res = false;
            }
            // ASSERT_EQ(0,ret);
        }
    }

    // ASSERT_TRUE(try_str2number("-.3e6", &value));// 0.3* 1000000.0
    // ASSERT_TRUE(try_str2number("1e+11", &value)); // 100000000000
    // ASSERT_TRUE(try_str2number("1e11", &value));
    // ASSERT_TRUE(try_str2number("46.e3", &value));
    // ASSERT_TRUE(try_str2number("53.5e93", &value));
    // ASSERT_TRUE(try_str2number("+6e-1", &value));
    // ASSERT_TRUE(try_str2number("3e+7", &value));
    // ASSERT_TRUE(try_str2number("1e50", &value));
    // ASSERT_TRUE(try_str2number("1e-50", &value));
    // ASSERT_TRUE(try_str2number("-1e02", &value));

    set_log_level(LINE, LOG_LEVEL_INFO);
    return res;
}
#endif

bool test_convert_try_str2double(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(LINE, LOG_LEVEL_DEBUG);

    double value = 0.0;

    EXPECT_TRUE(try_str2double(" 1520003945\r", &value));
    LOG_INFO(LINE, "Val:%f", value);
    EXPECT_NEAR(1520003945.0, value, 0.0001);

    EXPECT_TRUE(try_str2double(" -1520003945\r", &value));
    LOG_INFO(LINE, "Val:%f", value);
    EXPECT_NEAR(-1520003945.0, value, 0.0001);

    EXPECT_TRUE(try_str2double(" 1520003945\n", &value));
    LOG_INFO(LINE, "Val:%f", value);
    EXPECT_NEAR(1520003945.0, value, 0.0001);

    EXPECT_TRUE(try_str2double(" 1520003945", &value));
    LOG_INFO(LINE, "Val:%f", value);
    EXPECT_NEAR(1520003945.0, value, 0.0001);

    ASSERT_TRUE(try_str2double("0", &value));
    ASSERT_FALSE(try_str2double("", &value));
    ASSERT_FALSE(try_str2double("1t", &value));
    ASSERT_FALSE(try_str2double("1e1000", &value));
    ASSERT_FALSE(try_str2double("1e-1000", &value));
    ASSERT_TRUE(try_str2double("1e50", &value));
    ASSERT_TRUE(try_str2double("1e-50", &value));

    ASSERT_FALSE(try_str2double("1e10000000", &value));
    ASSERT_FALSE(try_str2double("1e-10000000", &value));

    ASSERT_TRUE(try_str2double("12345678", &value));
    ASSERT_NEAR(12345678, value, 0.0001);

    ASSERT_TRUE(try_str2double("1e-1", &value));
    ASSERT_NEAR(0.1, value, 0.0001);

    ASSERT_TRUE(try_str2double("1e+1", &value));
    ASSERT_NEAR(10, value, 0.0001);

    ASSERT_TRUE(try_str2double("1e2", &value));
    ASSERT_NEAR(100, value, 0.0001);

    ASSERT_TRUE(try_str2double("+1e2", &value));
    ASSERT_NEAR(100, value, 0.0001);

    ASSERT_TRUE(try_str2double("-1e2", &value));
    ASSERT_NEAR(-100, value, 0.0001);

    ASSERT_TRUE(try_str2double("+1.2e2", &value));
    ASSERT_NEAR(120, value, 0.0001);

    ASSERT_TRUE(try_str2double("21055406075", &value));
    ASSERT_NEAR(21055406075, value, 0.0001);

    set_log_level(LINE, LOG_LEVEL_INFO);
    return res;
}

bool test_convert_try_str2bool(void) {
    bool value;
    ASSERT_TRUE(try_str2bool("yes", &value));
    ASSERT_TRUE(value);
    ASSERT_TRUE(try_str2bool("true", &value));
    ASSERT_TRUE(value);
    ASSERT_TRUE(try_str2bool("on", &value));
    ASSERT_TRUE(value);
    ASSERT_TRUE(try_str2bool("1", &value));
    ASSERT_TRUE(value);
    ASSERT_TRUE(try_str2bool("no", &value));
    ASSERT_FALSE(value);
    ASSERT_TRUE(try_str2bool("false", &value));
    ASSERT_FALSE(value);
    ASSERT_TRUE(try_str2bool("off", &value));
    ASSERT_FALSE(value);
    ASSERT_TRUE(try_str2bool("0", &value));
    ASSERT_FALSE(value);
    ASSERT_FALSE(try_str2bool(NULL, &value));
    ASSERT_FALSE(try_str2bool("xxx", &value));
    return true;
}

bool test_convert_Ltoa32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_STREQ("0", rx_ltoa64(0));
    ASSERT_STREQ("-1", rx_ltoa64(-1));
    ASSERT_STREQ("9223372036854775807", rx_ltoa64(INT64_MAX));
    ASSERT_STREQ("-9223372036854775808", rx_ltoa64(INT64_MIN));
    return true;
}

bool test_convert_Ltoa64(void) {
    ASSERT_STREQ("0", rx_ltoa64(0));
    ASSERT_STREQ("-1", rx_ltoa64(-1));
    ASSERT_STREQ("9223372036854775807", rx_ltoa64(INT64_MAX));
    ASSERT_STREQ("-9223372036854775808", rx_ltoa64(INT64_MIN));
    return true;
}

bool test_convert_ULtoa32(void) {
    ASSERT_STREQ("0", rx_utoa64(0));
    ASSERT_STREQ("18446744073709551615", rx_utoa64(UINT64_MAX));
    return true;
}

bool test_convert_ULtoa64(void) {
    ASSERT_STREQ("0", rx_utoa64(0));
    ASSERT_STREQ("18446744073709551615", rx_utoa64(UINT64_MAX));
    return true;
}

bool test_convert_Ltoa32_(void) {
    uint32_t len;
    char str[132];
    ASSERT_STREQ("0", ltoa32_(0, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("-1", ltoa32_(-1, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("2147483647", ltoa32_(INT32_MAX, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("-2147483648", ltoa32_(INT32_MIN, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    return true;
}

bool test_convert_Ltoa64_(void) {
    uint32_t len;
    char str[132];
    ASSERT_STREQ("0", ltoa64_(0, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("-1", ltoa64_(-1, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("9223372036854775807", ltoa64_(INT64_MAX, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("-9223372036854775808", ltoa64_(INT64_MIN, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    return true;
}

bool test_convert_ULtoa32_(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t len;
    char str[132];
    ASSERT_STREQ("0", utoa32_(0, str, 10, &len));
    ASSERT_EQ(1U, len);
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("4294967295", utoa32_(UINT32_MAX, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    return true;
}

bool test_convert_ULtoa64_(void) {
    uint32_t len;
    char str[132];
    ASSERT_STREQ("0", utoa64_(0, str, 10, &len));
    ASSERT_EQ(1U, len);
    ASSERT_EQ(len, strlen(str));
    ASSERT_STREQ("18446744073709551615", utoa64_(UINT64_MAX, str, 10, &len));
    ASSERT_EQ(len, strlen(str));
    return true;
}

bool test_convert_ULtoa_hex64(void) {
    ASSERT_STREQ("0", utoa_hex64(0));
    ASSERT_STREQ("FFFFFFFFFFFFFFFF", utoa_hex64(UINT64_MAX));
    ASSERT_STREQ("123456789ABCDEF0", utoa_hex64(0x123456789ABCDEF0UL));
    return true;
}

bool test_convert_ULtoa_hex32(void) {
    ASSERT_STREQ("0", utoa_hex32(0));
    ASSERT_STREQ("FFFFFFFF", utoa_hex32(UINT32_MAX));
    ASSERT_STREQ("ABCDEF01", utoa_hex32(0xABCDEF01));
    return true;
}

bool test_convert_str_sizeof(void) {
    ASSERT_EQ(16U, sizeof("255.255.255.255"));
    return true;
}

bool test_convert_dtoa(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char str[100] = "";
    double val = 12345678912345678.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12345678912345678", str);

    val = 1234567891234567.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1234567891234567", str);

    val = 123456789123456.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("123456789123456", str);

    val = 12345678912345.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12345678912345", str);

    val = 1234567891234.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1234567891234", str);

    val = 123456789123.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("123456789123", str);

    val = 12345678912.;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12345678912", str);

    val = 1234567891.2;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1234567891", str);

    val = 123456789.12;
    dtoa_(val, -1, str);
    ASSERT_STREQ("123456789", str);

    val = 12345678.912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12345679", str);

    val = 1234567.8912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1234567.9", str);

    val = 123456.78912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("123456.79", str);

    val = 12345.678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12345.679", str);

    val = 1234.5678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1234.5679", str);

    val = 123.45678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("123.45679", str);

    val = 12.345678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("12.345679", str);

    val = 1.2345678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("1.2345679", str);

    val = 0.12345678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("0.12345679", str);

    val = 0.012345678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("0.012345679", str);

    val = 0.0012345678912;
    dtoa_(val, -1, str);
    ASSERT_STREQ("0.0012345679", str);

    val = 1e20;
    dtoa_(val, -1, str);
#if defined(EMBEDDED_TEST)
    ASSERT_STREQ("18446744073709551615", str);
#else
    ASSERT_STREQ("0", str);
#endif
    return true;
}

bool test_convert_dtoa_trim_zero(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    char str[100] = "";
    double val = 100;
    dtoa_(val, -1, str);
    ASSERT_STREQ("100", str);
    return true;
}

bool test_convert_dtoa_nan(void) {
    char str[100] = "";
    double val = NAN;
    dtoa_(val, -1, str);
    ASSERT_STREQ("NAN", str);
    return true;
}

/*fails*/
bool test_convert_dtoa_inf(void) {
    char str[100] = "";
    double val = INFINITY;
    dtoa_(val, -1, str);
    ASSERT_STREQ("INF", str);
    return true;
}

bool test_convert_ftoa_nan(void) {
    char str[100] = "";
    float val = NAN;
    ftoa_(val, -1, str);
    ASSERT_STREQ("NAN", str);
    return true;
}

bool test_convert_ftoa_inf(void) {
    char str[100] = "";
    float val = INFINITY;
    ftoa_(val, -1, str);
    ASSERT_STREQ("INF", str);
    return true;
}

bool test_convert_rx_dtoa(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    double t = 1e10;
    ASSERT_STREQ("10000000000", rx_dtoa(t));
    return true;
}

bool test_convert_ltoa_hex64(void) {
    int64_t t = 0x1234567890ABCDEF;
    const char* str = ltoa_hex64(t);
    ASSERT_STREQ("1234567890ABCDEF", str);

    str = ltoa_hex64(-1);
    ASSERT_STREQ("-1", str);
    return true;
}

bool test_convert_bool2name(void) {
    ASSERT_STREQ("on", bool2name(true));
    ASSERT_STREQ("off", bool2name(false));
    ASSERT_STREQ("on", bool2name(55U));
    ASSERT_STREQ("on", bool2name(1U));
    ASSERT_STREQ("off", bool2name(0U));
    return true;
}

bool test_convert_utoa_bin32(void) {
    ASSERT_STREQ("1010_1010_1010_1010_1010_1010_1010_1010", utoa_bin32(0xAAAAAAAA));
    ASSERT_STREQ("0101_0101_0101_0101_0101_0101_0101_0101", utoa_bin32(0x55555555));
    ASSERT_STREQ("0000_0000_0000_0000_0000_0000_0000_0000", utoa_bin32(0x00000000));
    ASSERT_STREQ("1111_1111_1111_1111_1111_1111_1111_1111", utoa_bin32(0xFFFFFFFF));
    ASSERT_STREQ("0001_0010_0011_0100_0101_0110_0111_1000", utoa_bin32(0x12345678));
    return true;
}

bool test_convert_utoa_bin24(void) {
    ASSERT_STREQ("1010_1010_1010_1010_1010_1010", utoa_bin24(0xAAAAAA));
    ASSERT_STREQ("0101_0101_0101_0101_0101_0101", utoa_bin24(0x555555));
    ASSERT_STREQ("0000_0000_0000_0000_0000_0000", utoa_bin24(0x000000));
    ASSERT_STREQ("1111_1111_1111_1111_1111_1111", utoa_bin24(0xFFFFFF));
    ASSERT_STREQ("0011_0100_0101_0110_0111_1000", utoa_bin24(0x345678));
    return true;
}

bool test_convert_utoa_bin16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_STREQ("1010_1010_1010_1010", utoa_bin16(0xAAAA));
    ASSERT_STREQ("0101_0101_0101_0101", utoa_bin16(0x5555));
    ASSERT_STREQ("0000_0000_0000_0000", utoa_bin16(0x0000));
    ASSERT_STREQ("1111_1111_1111_1111", utoa_bin16(0xFFFF));
    ASSERT_STREQ("0001_0010_0011_0100", utoa_bin16(0x1234));
    return true;
}

bool test_convert_utoa_bin16_plain(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_STREQ("1010101010101010", utoa_bin16_plain(0xAAAA));
    ASSERT_STREQ("0101010101010101", utoa_bin16_plain(0x5555));
    ASSERT_STREQ("0000000000000000", utoa_bin16_plain(0x0000));
    ASSERT_STREQ("1111111111111111", utoa_bin16_plain(0xFFFF));
    ASSERT_STREQ("0001001000110100", utoa_bin16_plain(0x1234));
    return true;
}

bool test_double_to_str(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    ASSERT_STREQ("1.00p", DoubleToStr(0.000000000001));
    ASSERT_STREQ("1.00f", DoubleToStr(0.000000000000001));
    ASSERT_STREQ("10.00f", DoubleToStr(0.00000000000001));
    ASSERT_STREQ("100.00f", DoubleToStr(0.0000000000001));
    ASSERT_STREQ("10.00p", DoubleToStr(0.00000000001));
    ASSERT_STREQ("100.00p", DoubleToStr(0.0000000001));
    ASSERT_STREQ("1.00n", DoubleToStr(0.000000001));
    ASSERT_STREQ("10.00n", DoubleToStr(0.00000001));
    ASSERT_STREQ("100.00n", DoubleToStr(0.0000001));
    ASSERT_STREQ("1.00u", DoubleToStr(0.000001));
    ASSERT_STREQ("10.00u", DoubleToStr(0.00001));
    ASSERT_STREQ("100.00u", DoubleToStr(0.0001));
    ASSERT_STREQ("1.00m", DoubleToStr(0.001));
    ASSERT_STREQ("1.00c", DoubleToStr(0.01));
    ASSERT_STREQ("1.00d", DoubleToStr(0.1));
    ASSERT_STREQ("1.00", DoubleToStr(1.0));
    ASSERT_STREQ("10.00", DoubleToStr(10.0));
    ASSERT_STREQ("1.00k", DoubleToStr(1000.0));
    ASSERT_STREQ("1.00M", DoubleToStr(1000000.0));
    ASSERT_STREQ("1.00G", DoubleToStr(1000000000.0));

    log_level_get_set(LINE, LOG_LEVEL_INFO);

    return true;
}

bool test_convert_assemble_uint32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t qword_val = 0x00000000;
    qword_val = assemble_uint32(0x01, 0x02, 0x03, 0x04);
    ASSERT_EQ(0x01020304, qword_val);
    qword_val = assemble_uint32(0x04, 0x03, 0x02, 0x01);
    ASSERT_EQ(0x04030201, qword_val);
    return true;
}

bool test_convert_char_2_dec(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(0, char_to_u8('0'));
    ASSERT_EQ(1, char_to_u8('1'));
    ASSERT_EQ(2, char_to_u8('2'));
    ASSERT_EQ(3, char_to_u8('3'));
    ASSERT_EQ(4, char_to_u8('4'));
    ASSERT_EQ(5, char_to_u8('5'));
    ASSERT_EQ(6, char_to_u8('6'));
    ASSERT_EQ(7, char_to_u8('7'));
    ASSERT_EQ(8, char_to_u8('8'));
    ASSERT_EQ(9, char_to_u8('9'));
    ASSERT_EQ(0, char_to_u8('a'));
    ASSERT_EQ(0, char_to_u8('e'));
    ASSERT_EQ(0, char_to_u8('k'));
    return true;
}

bool test_parse_data_type(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    return res;
}

bool test_try_str2type(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    uint8_t buff[16] = {0};
    log_level_get_set(LINE, LOG_LEVEL_DEBUG);
    ASSERT_TRUE(try_str2type("2000", TYPE_UINT16, buff, sizeof(buff)));
    uint16_t word = 0;
    memcpy(&word, buff, 2);
    ASSERT_EQ(2000, word);
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    return res;
}
