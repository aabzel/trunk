#ifndef UNIT_TEST_DIAG_H
#define UNIT_TEST_DIAG_H

#include "std_includes.h"
#include "unit_test_types.h"

const char* TestResToStr(const bool test_res);
const char* TestNodeToStr(const unit_test_info_t* const Node);
bool unit_test_find_key(const char* key1, const char* key2);
bool dump_unit_test_all(void);
bool unit_test_report(void);

#endif /* UNIT_TEST_DIAG_H */



