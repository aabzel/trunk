#ifndef TEST_GNSS_UTILS_H
#define TEST_GNSS_UTILS_H

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

bool test_gnss_types(void);
bool test_gnss_utils(void);
bool test_gnss_azimuth(void);
bool test_gnss_azimuth1(void);
bool test_gnss_compass(void);

#define TEST_SUIT_UTILS_GNSS                                                                                           \
    {"GnssCompass", test_gnss_compass}, {"GnssTypes", test_gnss_types}, {"GnssUtils", test_gnss_utils},                \
        {"GnssAzimuth1", test_gnss_azimuth1}, {"GnssAzimuth", test_gnss_azimuth},

#ifdef __cplusplus
}
#endif

#endif /* TEST_GNSS_UTILS_H */
