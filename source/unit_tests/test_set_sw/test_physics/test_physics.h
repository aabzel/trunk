#ifndef TEST_PHYSICS_UTILS_H
#define TEST_PHYSICS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

bool test_physics_timer_to_dist(void);
bool test_physics_timer_2_sec(void);

#define TEST_SUIT_PHYSICS                                     \
        {"physics_timer_2_sec", test_physics_timer_2_sec},    \
        {"physics_timer_2_sec", test_physics_timer_to_dist},

#ifdef __cplusplus
}
#endif

#endif /* TEST_PHYSICS_UTILS_H */
