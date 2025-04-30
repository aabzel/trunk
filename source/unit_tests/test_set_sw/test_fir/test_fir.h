
#ifndef TEST_FIR_H
#define TEST_FIR_H

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

#ifndef HAS_FIR
#error "It is needed HAS_FIR option for that component"
#endif

#ifndef HAS_TEST_SUIT_FIR
#error "It is needed HAS_TEST_SUIT_FIR option for that component"
#endif

bool test_fir_types(void);
bool test_fir_proc(void);
bool test_fir_performance(void);
bool test_fir_impulse_response(void);

#define TEST_SUIT_FIR                            \
    {"fir_performance", test_fir_performance},               \
    {"fir_impulse_response", test_fir_impulse_response},               \
    {"fir_types", test_fir_types},               \
	{"fir_proc", test_fir_proc},

#ifdef __cplusplus
}
#endif

#endif /* TEST_FIR_H */
