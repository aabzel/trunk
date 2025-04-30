#ifndef TEST_TIMER_H
#define TEST_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_TIMER
#error "It is needed HAS_TIMER option for that component"
#endif

bool test_tim_us(void) ;
bool test_tim_ms(void) ;
bool test_tim_utils(void) ;

#define TEST_SUIT_TIM        \
    {"timer_utils", test_tim_utils}, \
    {"timer_us", test_tim_us}, \
    {"timer_ms", test_tim_ms},

#ifdef __cplusplus
}
#endif

#endif /* TEST_TIMER_H */
