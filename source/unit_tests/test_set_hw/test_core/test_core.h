#ifndef TEST_CORE_H
#define TEST_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_CORE
#error "+HAS_CORE"
#endif

#ifndef HAS_TEST_CORE
#error "+HAS_TEST_CORE"
#endif

bool test_core_is_interrupt(void);

#define TEST_SUIT_CORE                                       \
    {"core_is_interrupt", test_core_is_interrupt},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CORE_H */
