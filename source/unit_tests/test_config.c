#include "test_config.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_STRING_PARSER
#include "convert.h"
#endif

#include "data_utils.h"
#include "debug_info.h"

#ifdef HAS_LOG
#include "log_utils.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_HW_TESTS
#include "test_hw_list.h"
#endif /*HAS_HW_TESTS*/

#ifdef HAS_SW_TESTS
#include "test_sw_list.h"
#endif /*HAS_SW_TESTS*/

#include "unit_test_check.h"
#include "writer_generic.h"

UnitTest_t UnitTest = {
    .failed_tests_count = 0,
    .ok_tests_count = 0,
};

/*Compile time assemble array */
const unit_test_info_t test_list[] = {
#ifdef HAS_SW_TESTS
    TEST_SUIT_SW
#endif /*HAS_SW_TESTS*/

#ifdef HAS_HW_TESTS
        TEST_SUIT_HW
#endif /*HAS_HW_TESTS*/

};

uint32_t unit_test_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(test_list);
    return cnt;
}
