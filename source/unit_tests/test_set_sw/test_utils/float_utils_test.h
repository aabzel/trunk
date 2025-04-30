#ifndef TEST_FLOAT_UTILS_H
#define TEST_FLOAT_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

typedef struct xHsnrTestCase_t {
    uint16_t hsnr;
    double value;
} HsnrTestCase_t;


bool test_hsnr_to_double(void);
bool test_float_utils(void);
bool test_float_to_fixed_point(void);

#define TEST_SUIT_UTILS_FLOAT  \
    {"float_utils", test_float_utils}, \
    {"float_to_fixed_point", test_float_to_fixed_point}, \
	{"hsnr_to_double", test_hsnr_to_double},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FLOAT_UTILS_H */
