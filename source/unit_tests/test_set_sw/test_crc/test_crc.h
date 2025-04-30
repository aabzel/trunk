#ifndef TEST_CRC_H
#define TEST_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif


#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

typedef struct  {
    uint8_t len;
    uint8_t buf[9];
    uint8_t crc8;
} Crc8TestCase_t;

bool test_crc8(void);
bool test_crc32(void);
bool test_crc32_stream(void);
bool test_crc24q13(void);
bool test_crc24q80(void);
bool test_crc16(void);
bool test_crc16_stream(void);

#define TEST_SUIT_CRC \
    {"crc32", test_crc32}, \
    {"crc32_stream", test_crc32_stream}, \
    {"crc8", test_crc8}, \
    {"crc16", test_crc16}, \
    {"crc16_stream", test_crc16_stream}, \
    {"crc24_13", test_crc24q13},\
    {"crc24_80", test_crc24q80},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CRC_H */
