#ifndef BOARD_TASKS_H
#define BOARD_TASKS_H


#ifdef HAS_AT_START_F437_PROC
#include "board_at_start_f437.h"
#define AT_START_F437_TASK {.name="AtStartF437", .period_us=AT_START_F437_POLL_PERIOD_US, .limiter.function=at_start_f437_proc,},
#else
#define AT_START_F437_TASK
#endif /**/

#ifdef HAS_TERA_TEST_PROC
#include "board_tera_test.h"
#define TERA_TEST_TASK                                                                                      \
           {.name="TERA_TEST", .period_us=TERA_TEST_PERIOD_US, .limiter.function=tera_test_proc,},          \
           {.name="TerTPrm",   .period_us=TERA_TEST_PARAM_PERIOD_US, .limiter.function=tera_test_param_proc,},
#else
#define	TERA_TEST_TASK
#endif /**/


#define BOARD_TASKS              \
    AT_START_F437_TASK           \
    TERA_TEST_TASK



#endif /* BOARD_TASKS_H */
