#ifndef UNIT_TEST_RUN_H
#define UNIT_TEST_RUN_H

#include "std_includes.h"

extern bool test_failed;

bool unit_test_run(uint32_t index);
void failed_tests_print(void);
void failed_tests_reset(void);

#endif /* UNIT_TEST_RUN_H */
