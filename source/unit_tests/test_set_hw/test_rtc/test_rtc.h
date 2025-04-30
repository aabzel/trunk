#ifndef TEST_RTC_H
#define TEST_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "test_hw_dep_check.h"

#ifndef HAS_HW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif

bool test_rtc_is_run(uint8_t num);
bool test_rtc_reinit(uint8_t num);
bool test_rtc_start(uint8_t num);

#ifdef HAS_RTC0
bool test_rtc0_start(void);
bool test_rtc0_is_run(void);
bool test_rtc0_reinit(void);

#define TEST_SUIT_RTC0  \
    {"rtc0_stop_start", test_rtc0_start} , \
    {"rtc0_is_run", test_rtc0_is_run} , \
    {"rtc0_reinit", test_rtc0_reinit} ,

#else
#define TEST_SUIT_RTC0
#endif

#ifdef HAS_RTC1
bool test_rtc1_stop_start(void);

#define TEST_SUIT_RTC1 \
    {"rtc1_stop_start", test_rtc1_stop_start} ,
#else
#define TEST_SUIT_RTC1
#endif

#ifdef HAS_RTC2
bool test_rtc2_stop_start(void);

#define TEST_SUIT_RTC2  \
	{"rtc2_stop_start", test_rtc2_stop_start},
#else
#define TEST_SUIT_RTC2
#endif


#define TEST_SUIT_RTC          \
    TEST_SUIT_RTC0                     \
    TEST_SUIT_RTC1                     \
    TEST_SUIT_RTC2


#ifdef __cplusplus
}
#endif

#endif /* TEST_RTC_H */
