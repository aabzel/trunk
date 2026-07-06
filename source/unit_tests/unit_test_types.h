#ifndef UNIT_TEST_TYPES_H
#define UNIT_TEST_TYPES_H

#include "std_includes.h"
#include "unit_test_const.h"

typedef bool (*utest_funct_t)(void);

typedef struct {
    const char* const name;
    const utest_funct_t utest_func;
#ifdef HAS_UNIT_TEST_SEVERENESS
    uint8_t severeness;               /*0-The most severe test; 0xff - the least severe test */
#endif
    bool integration;
} unit_test_info_t;

typedef struct {
    uint32_t ok_tests_count;
    uint32_t failed_tests_count;     /*For NVRAM*/
    unit_test_info_t* last_failed;   /*For NVRAM*/
    unit_test_info_t* first_failed;  /*For NVRAM*/
}UnitTest_t;


#endif /* UNIT_TEST_TYPES_H */
