/*
 test is based on https://crccalc.com/
 */

#include "test_crc.h"

#include "crc16_ccitt.h"
#include "crc24_q.h"
#include "crc32.h"
#include "crc8_autosar.h"
#include "crc8_sae_j1850.h"
#include "data_utils.h"
#include "unit_test_check.h"

#define TEST_PAYLOAD (const uint8_t*)"12345678"

#define CRC32_RES0 ((uint32_t)0x00000000UL)
#define CRC32_RES4 ((uint32_t)0x9BE3E0A3UL)
#define CRC32_RES5 ((uint32_t)0xCBF53A1CUL)
#define CRC32_RES6 ((uint32_t)0x0972D361UL)
#define CRC32_RES7 ((uint32_t)0x5003699FUL)
#define CRC32_RES8 ((uint32_t)0x9AE0DAAFUL)

#ifdef HAS_CRC8_AUTOSAR
static const Crc8TestCase_t cases_crc8_auto[] = {
    {.len = 4, .buf = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x12},
    {.len = 3, .buf = {0xF2, 0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0xC2},
    {.len = 4, .buf = {0x0F, 0xAA, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0xC6},
    {.len = 4, .buf = {0x00, 0xFF, 0x55, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x77},
    {.len = 9, .buf = {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}, .crc8 = 0x11},
    {.len = 3, .buf = {0x92, 0x6B, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x33},
    {.len = 4, .buf = {0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x6C},
};
#endif

static const Crc8TestCase_t cases_crc8_j1850[] = {
    {.len = 4, .buf = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x59},
    {.len = 3, .buf = {0xF2, 0x01, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x37},
    {.len = 4, .buf = {0x0F, 0xAA, 0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x79},
    {.len = 4, .buf = {0x00, 0xFF, 0x55, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0xB8},
    {.len = 9, .buf = {0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF}, .crc8 = 0xCB},
    {.len = 3, .buf = {0x92, 0x6B, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x8C},
    {.len = 4, .buf = {0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00}, .crc8 = 0x74},
};

#ifdef HAS_CRC8_AUTOSAR
static bool test_crc8_autosar(void) {
    uint32_t i = 0;
    bool res = true;
    for(i = 0; i < ARRAY_SIZE(cases_crc8_auto); i++) {
        uint8_t crc8 = crc8_autosar_calc(cases_crc8_auto[i].buf, cases_crc8_auto[i].len);
        EXPECT_EQ(crc8, cases_crc8_auto[i].crc8);
    }
    return res;
}
#endif

static bool test_crc8_sae_j1850(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t i = 0;
    bool res = true;
    for(i = 0; i < ARRAY_SIZE(cases_crc8_j1850); i++) {
        uint8_t crc8 = crc8_sae_j1850_calc(cases_crc8_j1850[i].buf, cases_crc8_j1850[i].len);
        EXPECT_EQ(crc8, cases_crc8_j1850[i].crc8);
    }
    return res;
}

bool test_crc8(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
#ifdef HAS_CRC8_AUTOSAR
    ASSERT_TRUE(test_crc8_autosar());
#endif
    ASSERT_TRUE(test_crc8_sae_j1850());
    return res;
}

bool test_crc16(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint16_t crc16 = 0;
    bool res = true;
    crc16 = calc_crc16_ccitt_false(TEST_PAYLOAD, 8);
    EXPECT_EQ(0xA12B, crc16);
    return res;
}

/*
 * https://crccalc.com/
 */
bool test_crc16_stream(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    uint16_t crc16_cur = 0;
    uint8_t data[9] = {0};
    memcpy(data, TEST_PAYLOAD, 8);
    crc16_cur = calc_crc16_ccitt_false_stream(&data[0], 4, true, 0);
    crc16_cur = calc_crc16_ccitt_false_stream(&data[4], 4, false, crc16_cur);
    EXPECT_EQ(0xA12B, crc16_cur);
    return res;
}

/*crc24 0x244B24*/
const uint8_t rtcm3frame80[83] = {0xD3, 0x00, 0x50, 0x43, 0xC0, 0x00, 0xD4, 0x8B, 0x66, 0x3E, 0x00, 0x00, 0x04, 0x02,
                                  0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x7F, 0xA6, 0xA2, 0x23,
                                  0x21, 0x28, 0x23, 0x24, 0xD1, 0x9A, 0xE8, 0x9E, 0xAD, 0xA5, 0x8E, 0x6F, 0x18, 0x80,
                                  0x3A, 0xB0, 0x44, 0x42, 0xA4, 0x44, 0x6A, 0x7A, 0x84, 0x95, 0xD4, 0x78, 0x0F, 0xB5,
                                  0x51, 0xDE, 0xAD, 0x20, 0x80, 0xAD, 0x4B, 0xF8, 0x89, 0x98, 0x2D, 0xB7, 0x80, 0xA1,
                                  0x48, 0xCD, 0x7F, 0xFF, 0xFF, 0x80, 0x4C, 0xFE, 0x36, 0x67, 0x84, 0xF0, 0x00};

/*crc24  0x0C17FB*/
const uint8_t rtcm3frame13[22] = {0xD3, 0x00, 0x13, 0x3E, 0xD0, 0x00, 0x03, 0x86, 0xA2, 0x16, 0xA1,
                                  0x25, 0x85, 0x13, 0x8B, 0xFB, 0xA2, 0x0C, 0x3C, 0xE2, 0x79, 0x9D};

bool test_crc24q13(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t crc24 = 0;
    bool res = true;
    crc24 = calc_crc24_q(rtcm3frame13, sizeof(rtcm3frame13));
    EXPECT_EQ(0x0C17FB, crc24);
    ASSERT_TRUE(crc24_q_check(rtcm3frame13, sizeof(rtcm3frame13), 0x0C17FB));
    return res;
}

bool test_crc24q80(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    uint32_t crc24 = 0;
    bool res = true;
    crc24 = calc_crc24_q(rtcm3frame80, sizeof(rtcm3frame80));
    EXPECT_EQ(0x244B24, crc24);
    ASSERT_TRUE(crc24_q_check(rtcm3frame80, sizeof(rtcm3frame80), 0x244B24));
    return res;
}

static bool test_calc_crc32(void) {
    bool res = true;
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    EXPECT_EQ(CRC32_RES0, crc32_calc(TEST_PAYLOAD, 0));
    EXPECT_EQ(CRC32_RES4, crc32_calc(TEST_PAYLOAD, 4));
    EXPECT_EQ(CRC32_RES5, crc32_calc(TEST_PAYLOAD, 5));
    EXPECT_EQ(CRC32_RES6, crc32_calc(TEST_PAYLOAD, 6));
    EXPECT_EQ(CRC32_RES7, crc32_calc(TEST_PAYLOAD, 7));
    EXPECT_EQ(CRC32_RES8, crc32_calc(TEST_PAYLOAD, 8));
    return res;
}

bool test_crc32(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    ASSERT_TRUE(test_calc_crc32());
    return res;
}

bool test_crc32_stream(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    uint32_t crc32_cur = 0;
    uint8_t data[9] = {0};
    memcpy(data, TEST_PAYLOAD, 8);

    crc32_cur = crc32_stream_calc(0U, data, 8);
    LOG_INFO(TEST, "CRC32:0x%09x", crc32_cur);
    EXPECT_EQ(CRC32_RES8, crc32_cur);

    crc32_cur = crc32_stream_calc(0U, data, 4);
    LOG_INFO(TEST, "CRC32:0x%09x", crc32_cur);
    EXPECT_EQ(CRC32_RES4, crc32_cur);

    crc32_cur = crc32_stream_calc(crc32_cur, &data[4], 4);
    LOG_INFO(TEST, "CRC32:0x%09x", crc32_cur); // 0x00000304c
    EXPECT_EQ(CRC32_RES8, crc32_cur);
    return res;
}
