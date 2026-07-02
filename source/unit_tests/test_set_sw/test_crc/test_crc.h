#ifndef TEST_CRC_H
#define TEST_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_inc.h"

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif


#ifdef HAS_CRC8

typedef struct  {
    uint8_t len;
    uint8_t buf[9];
    uint8_t crc8;
} Crc8TestCase_t;

bool test_crc8(void);

#define TEST_SUIT_CRC8 \
    {"crc8", test_crc8},

#else
#define TEST_SUIT_CRC8
#endif

#ifdef HAS_CRC24
bool test_crc24q13(void);
bool test_crc24q80(void);

#define TEST_SUIT_CRC24 \
    {"crc24_13", test_crc24q13},\
    {"crc24_80", test_crc24q80},


#else
#define TEST_SUIT_CRC24
#endif

#ifdef HAS_CRC16
bool test_crc16(void);
bool test_crc16_stream(void);

#define TEST_SUIT_CRC16     \
    {"crc16", test_crc16},  \
    {"crc16_stream", test_crc16_stream},
#else
#define TEST_SUIT_CRC16
#endif

#ifdef HAS_CRC32
bool test_crc32(void);
bool test_crc32_stream(void);

#define TEST_SUIT_CRC32 \
    {"crc32", test_crc32}, \
    {"crc32_stream", test_crc32_stream},
#else
#define TEST_SUIT_CRC32
#endif


#define TEST_SUIT_CRC    \
    TEST_SUIT_CRC8       \
    TEST_SUIT_CRC16      \
    TEST_SUIT_CRC24      \
    TEST_SUIT_CRC32

#ifdef __cplusplus
}
#endif

#endif /* TEST_CRC_H */
