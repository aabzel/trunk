#ifndef TEST_CALENDAR_H
#define TEST_CALENDAR_H

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

#if 1
bool test_calendar_set_get_all(void);
#define TEST_SUIT_CALENDAR_EXT {"CalendarSetGetAll", test_calendar_set_get_all},
#else
#define TEST_SUIT_CALENDAR_EXT
#endif

bool test_calendar_parse_time(void);
bool test_calendar_set_get(void);
bool test_calendar_set_get_all(void);

#define TEST_SUIT_CALENDAR                                                                                             \
    {"CalendarSetGet", test_calendar_set_get}, {"CalendarParseTime", test_calendar_parse_time}, TEST_SUIT_CALENDAR_EXT

#ifdef __cplusplus
}
#endif

#endif /* TEST_CALENDAR_H */
