#ifndef TEST_PLANETARIUM_H
#define TEST_PLANETARIUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_PLANETARIUM
#error "It is needed HAS_PLANETARIUM option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_planetarium_compare_phi_ref(void);
bool test_planetarium_calc_noon(void);
bool test_planetarium_calc_phi(void);
bool test_planetarium_compare_phi(void);
bool test_planetarium_calc_lambda(void);
bool test_planetarium_compare_lambda(void);

#define TEST_SUIT_PLANETARIUM                                        \
    {"planetarium_calc_noon", test_planetarium_calc_noon},           \
    {"planetarium_phi_refraction", test_planetarium_compare_phi_ref},           \
    {"planetarium_calc_phi", test_planetarium_calc_phi},   \
    {"planetarium_compare_phi", test_planetarium_compare_phi},   \
    {"planetarium_compare_lambda", test_planetarium_compare_lambda},   \
    {"planetarium_calc_lambda", test_planetarium_calc_lambda},

#ifdef __cplusplus
}
#endif

#endif /* TEST_PLANETARIUM_H */
