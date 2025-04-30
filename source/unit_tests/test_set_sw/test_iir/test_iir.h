#ifndef TEST_IIR_H
#define TEST_IIR_H

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

#ifndef HAS_IIR
#error "It is needed HAS_IIR option for that component"
#endif

#ifndef HAS_TEST_SUIT_IIR
#error "It is needed HAS_TEST_SUIT_IIR option for that component"
#endif

bool test_iir_types(void);
bool test_iir_proc(void);
bool test_iir_performance(void);
bool test_iir_impulse_response(void);

#define TEST_SUIT_IIR                            \
    {"iir_performance", test_iir_performance},               \
    {"iir_impulse_response", test_iir_impulse_response},               \
    {"iir_types", test_iir_types},               \
	{"iir_proc", test_iir_proc},

#ifdef __cplusplus
}
#endif

#endif /* TEST_IIR_H */
