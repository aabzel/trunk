#ifndef TEST_IWDG_H
#define TEST_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_IWDG
#error "It is needed HAS_IWDG option for that component"
#endif

#ifdef HAS_IWDG
bool test_iwdg_types(void) ;
bool test_iwdg_set(void) ;
bool test_iwdg_get(void) ;
#define TEST_SUIT_IWDG           \
{"iwdg_types", test_iwdg_types}, \
 {"iwdg_set", test_iwdg_set},    \
 {"iwdg_get", test_iwdg_get},
#else
#define TEST_SUIT_IWDG
#endif


#ifdef __cplusplus
}
#endif

#endif /* TEST_IWDG_H */
