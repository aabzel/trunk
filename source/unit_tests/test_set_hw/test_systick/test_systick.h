#ifndef TEST_SYSTICK_H
#define TEST_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_SYSTICK
#error "It is needed HAS_SYSTICK option for that component"
#endif

bool test_systick_types(void);

#define TEST_SUIT_SYSTICK                     \
    {"SysTickType", test_systick_types},      
 
#ifdef __cplusplus
}
#endif

#endif /* TEST_SYSTICK_H */
