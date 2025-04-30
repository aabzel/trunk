#ifndef TEST_DS3231_H
#define TEST_DS3231_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_DS3231
#error "+HAS_DS3231"
#endif

#ifndef HAS_TEST_DS3231
#error "+HAS_TEST_DS3231"
#endif

bool test_ds3231_connected(void);
bool test_ds3231_types(void);
bool test_ds3231_config(void);
bool test_ds3231_set_time(void);
bool test_ds3231_get_time(void);
bool test_ds3231_set_reg(void);
bool test_ds3231_get_reg(void);
bool test_ds3231_hash_tables(void);


#define TEST_SUIT_DS3231                               \
    {"ds3231_types", test_ds3231_types},              \
    {"ds3231_connect", test_ds3231_connected},        \
    {"ds3231_hash_tables", test_ds3231_hash_tables},  \
    {"ds3231_set_reg", test_ds3231_set_reg},              \
    {"ds3231_get_reg", test_ds3231_get_reg},              \
    {"ds3231_config", test_ds3231_config},              \
    {"ds3231_get_time", test_ds3231_get_time},                   \
    {"ds3231_set_time", test_ds3231_set_time},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DS3231_H */
