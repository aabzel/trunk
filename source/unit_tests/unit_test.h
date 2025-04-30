#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdint.h>

#include "test_config.h"
#include "unit_test_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool unit_tests_run(const char* const key);
bool test_components(void);
bool unit_test_init(void);
const unit_test_info_t* get_unit_test(uint32_t test_index);
void dump_unit_test_all(void);
void dump_unit_test_key(const char* key);

#endif /* UNIT_TEST_H */
