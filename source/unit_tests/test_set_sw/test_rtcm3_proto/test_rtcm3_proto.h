#ifndef TEST_RTCM3_PROTO_H
#define TEST_RTCM3_PROTO_H

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

extern const uint8_t rtcm3_message2[39];
extern const uint8_t rtcm3_message[36];

bool test_rtcm3_array(void);
bool test_rtcm3_proto_1(void);
bool test_rtcm3_types(void);

#define TEST_SUIT_RTCM3_PROTO                                                                                          \
    {"rtcm3_array", test_rtcm3_array}, {"rtcm3_proto", test_rtcm3_proto_1}, {"rtcm3_types", test_rtcm3_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_RTCM3_PROTO_H */
