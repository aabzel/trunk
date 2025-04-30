#ifndef UNIT_TEST_TYPES_H
#define UNIT_TEST_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef bool (*utest_funct_t)(void);

typedef struct {
    const char* const name;
    const utest_funct_t utest_func;
} unit_test_info_t;


typedef struct {
	uint32_t failed_tests_count;
	uint32_t ok_tests_count  ;
	//uint32_t count  ;
}UnitTest_t;


#endif /* UNIT_TEST_TYPES_H */
