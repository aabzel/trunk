#ifndef TEST_PYRAMID_ACCEL_CALIB_H
#define TEST_PYRAMID_ACCEL_CALIB_H

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

#ifndef HAS_PYRAMID_ACCEL_CALIB
#error "It is needed HAS_PYRAMID_ACCEL_CALIB option for that component"
#endif

#ifndef HAS_TEST_SUIT_PYRAMID_ACCEL_CALIB
#error "It is needed HAS_TEST_SUIT_PYRAMID_ACCEL_CALIB option for that component"
#endif

bool test_pyramid_accel_calib_ideal(void);

#define TEST_SUIT_PYRAMID_ACCEL_CALIB                            \
    {"pyramid_accel_calib_ideal", test_pyramid_accel_calib_ideal},

#ifdef __cplusplus
}
#endif

#endif /* TEST_PYRAMID_ACCEL_CALIB_H */
