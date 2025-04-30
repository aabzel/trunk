#ifndef TEST_LIST_H
#define TEST_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "unit_test_types.h"

extern UnitTest_t UnitTest;
extern const unit_test_info_t test_list[];

uint32_t unit_test_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*TEST_LIST_H*/
