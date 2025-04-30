#ifndef TEST_SOFTWARE_TIMER_H
#define TEST_SOFTWARE_TIMER_H

#include <stdbool.h>
#include <stdint.h>

bool test_sw_timer_set_single(void);
bool test_sw_timer_get_spare(void);
bool test_sw_timer_set_contin(void);

#define TEST_SUIT_SOFTWARE_TIMER                           \
    {"sw_timer_get_spare", test_sw_timer_get_spare},        \
    {"SwTimerSetSingle", test_sw_timer_set_single},        \
    {"SwTimerSetContin", test_sw_timer_set_contin},
    

#endif /* TEST_SOFTWARE_TIMER_H */
