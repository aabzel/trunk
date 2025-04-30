#ifndef TEST_LTR390_H
#define TEST_LTR390_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_LTR390
#error "+HAS_LTR390"
#endif

#ifndef HAS_TEST_LTR390
#error "+HAS_TEST_LTR390"
#endif

#define LTR390_TEST_INSTANCE 1


bool test_ltr390_reg_read(void);
bool test_ltr390_reg_write(void);
bool test_ltr390_connect(void);
bool test_ltr390_types(void);

#define TEST_SUIT_LTR390                                \
        {"ltr390_types", test_ltr390_types},       \
        {"ltr390_reg_read", test_ltr390_reg_read},       \
        {"ltr390_reg_write", test_ltr390_reg_write}, \
        {"ltr390_connect", test_ltr390_connect},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LTR390_H */
