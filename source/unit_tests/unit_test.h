#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "std_includes.h"
#include "test_config.h"
#include "unit_test_types.h"

#ifdef HAS_UNIT_TEST_DIAG
#include "unit_test_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

extern bool test_failed;

bool unit_test_proc(void);
bool unit_test_init(void);

/* setter */
bool unit_test_run_ll( const unit_test_info_t* ui);
bool unit_test_run(uint32_t index);
bool unit_test_run_first_fail(const char * const key);
bool failed_tests_reset(void);
bool unit_tests_run(const char* const key);
uint32_t unit_test_run_key(const char* key) ;
bool test_components(void);

/*getters*/
bool dump_unit_test_all(void);
uint32_t test_node_to_num(const unit_test_info_t*const  Node);
void failed_tests_print(void);
const unit_test_info_t* get_unit_test(uint32_t test_index);
bool test_is_valid(const unit_test_info_t*const  Node);
bool unit_test_find_key(const char* key1, const char* key2);
bool unit_test_is_uniq(const unit_test_info_t* const curNode);

#endif /* UNIT_TEST_H */
