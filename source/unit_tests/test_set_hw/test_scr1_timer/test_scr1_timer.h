#ifndef TEST_SCR1_TIMER_H
#define TEST_SCR1_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "test_hw_dep_check.h"

#ifndef HAS_TEST_SCR1_TIMER
#error "It is needed HAS_SCR1_TIMER_TESTS option for that component"
#endif

#ifndef HAS_SCR1_TIMER
#error "It is needed HAS_SCR1_TIMER option for that component"
#endif

bool test_scr1_timer_types(void);

#define TEST_SUIT_SCR1_TIMER                         \
        {"scr1_timerType", test_scr1_timer_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SCR1_TIMER_H */
