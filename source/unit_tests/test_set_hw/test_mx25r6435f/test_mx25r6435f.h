#ifndef TEST_MX25R6435F_H
#define TEST_MX25R6435F_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_MX25R6435F
#error "+HAS_MX25R6435F"
#endif

#ifndef HAS_TEST_MX25R6435F
#error "+HAS_MX25R6435F_TESTS"
#endif

bool test_mx25r6435f_types(void);
bool test_mx25r6435f_form_addr(void);
bool test_mx25r6435f_read(void);
bool test_mx25r6435f_write(void);

#define TEST_SUIT_MX25R6435F                                 \
		{"mx25r6435f_types", test_mx25r6435f_types},         \
		{"mx25r6435f_form_addr", test_mx25r6435f_form_addr}, \
		{"mx25r6435f_read", test_mx25r6435f_read},           \
		{"mx25r6435f_write", test_mx25r6435f_write},

#ifdef __cplusplus
}
#endif

#endif /* TEST_MX25R6435F_H */
