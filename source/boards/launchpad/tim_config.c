#include "tim_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

const TimerConfig_t TimerConfig[BOARD_GPTIMERPARTSCOUNT] = {
                                              {.num=0, .bitness=32, .name="Us",  .cnt_period_us = 1, .period_ms = TIMER0_UPTIME_PERIOD_MS},
                                              {.num=1, .bitness=0,  .name="",    .cnt_period_us = 1, .period_ms = 2},
                                              {.num=2, .bitness=32, .name="RTC", .cnt_period_us = 1, .period_ms = 1000U},
                                              {.num=3, .bitness=0,  .name="",    .cnt_period_us = 1, .period_ms = 100},
                                              {.num=4, .bitness=32, .name="Ms",  .cnt_period_us = 5, .period_ms = 1}, /*1m s int*/
                                              {.num=5, .bitness=0,  .name="",    .cnt_period_us = 1, .period_ms = 500},
                                              {.num=6, .bitness=32, .name="",    .cnt_period_us = 1, .period_ms = 100},
                                              {.num=7, .bitness=0,  .name="",    .cnt_period_us = 1, .period_ms = 100}};

TimerHandle_t TimerInstance[BOARD_GPTIMERPARTSCOUNT] = {
{.num=0,},
{.num=1,},
{.num=2,},
{.num=3,},
{.num=4,},
{.num=5,},
{.num=6,},
{.num=7,},
};
