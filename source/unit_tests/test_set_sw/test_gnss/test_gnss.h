#ifndef TEST_GNSS_H
#define TEST_GNSS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_gnss_zigzag_traversal(void);
bool test_gnss_correlation(void);
bool test_gnss_correlation_diff(void);
bool test_gnss_types(void);
bool test_gnss_utils(void);
bool test_gnss_azimuth(void);
bool test_gnss_azimuth1(void);
bool test_gnss_compass(void);

#define TEST_SUIT_GNSS                                                \
    {"gnss_compass", test_gnss_compass},                              \
    {"gnss_correlation_diff", test_gnss_correlation_diff},                              \
    {"gnss_correlation", test_gnss_correlation},                 \
    {"gnss_zigzag_traversal", test_gnss_zigzag_traversal},            \
    {"gnss_types", test_gnss_types},                                  \
    {"gnss_utils", test_gnss_utils},                                  \
    {"gnss_azimuth1", test_gnss_azimuth1},                            \
    {"gnss_azimuth", test_gnss_azimuth},

#ifdef __cplusplus
}
#endif

#endif /* TEST_GNSS_H */
