#ifndef TEST_CORRELATOR_S16_H
#define TEST_CORRELATOR_S16_H

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

#ifndef HAS_CORRELATOR_S16
#error "It is needed HAS_CORRELATOR_S16 option for that component"
#endif

#ifndef HAS_TEST_SUIT_CORRELATOR_S16
#error "It is needed HAS_TEST_SUIT_CORRELATOR_S16 option for that component"
#endif

bool test_correlator_s16_types(void);
bool test_correlator_s16_proc(void);
bool test_correlator_s16_equal(void);
bool test_correlator_s16_performance(void);

#define TEST_SUIT_CORRELATOR_S16                            \
    {"correlator_s16_equal", test_correlator_s16_equal},               \
    {"correlator_s16_performance", test_correlator_s16_performance},               \
    {"correlator_s16_types", test_correlator_s16_types},               \
	{"correlator_s16_proc", test_correlator_s16_proc},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CORRELATOR_S16_H */
