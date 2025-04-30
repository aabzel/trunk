
#ifndef TEST_BT1026_H
#define TEST_BT1026_H

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

#ifndef HAS_BT1026
#error "It is needed HAS_BT1026 option for that component"
#endif

#ifndef HAS_TEST_SUIT_BT1026
#error "It is needed HAS_TEST_SUIT_BT1026 option for that component"
#endif

bool test_bt1026_parse(void);
bool test_bt1026_types(void);

#define TEST_SUIT_BT1026                  \
   {"bt1026_types", test_bt1026_types}, \
   {"bt1026_parse", test_bt1026_parse},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BT1026_H */
