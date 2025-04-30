
#ifndef TEST_SCHMITT_TRIGGER_H
#define TEST_SCHMITT_TRIGGER_H

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

#ifndef HAS_SCHMITT_TRIGGER
#error "It is needed HAS_SCHMITT_TRIGGER option for that component"
#endif

#ifndef HAS_TEST_SUIT_SCHMITT_TRIGGER
#error "It is needed HAS_TEST_SUIT_SCHMITT_TRIGGER option for that component"
#endif

bool test_schmitt_trigger_up(void);
bool test_schmitt_trigger_down(void);

#define TEST_SUIT_SCHMITT_TRIGGER                                                           \
   {"schmitt_trigger_up", test_schmitt_trigger_up},       \
   {"schmitt_trigger_down", test_schmitt_trigger_down},     \

#ifdef __cplusplus
}
#endif

#endif /* TEST_SCHMITT_TRIGGER_H */
