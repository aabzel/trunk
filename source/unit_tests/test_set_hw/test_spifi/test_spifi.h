#ifndef TEST_SPIFI_H
#define TEST_SPIFI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif

#ifndef HAS_TEST_SPIFI
#error "+HAS_SPIFI_TESTS"
#endif

#define TEST_ADDESS 1024*1024
#define SPIFI_PAGE_SIZE 256

bool test_spifi_types(void);
bool test_spifi_read(void);
bool test_spifi_write(void);

#define TEST_SUIT_SPIFI                            \
        {"spifi_types", test_spifi_types},         \
        {"spifi_read", test_spifi_read},           \
        {"spifi_write", test_spifi_write},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SPIFI_H */
