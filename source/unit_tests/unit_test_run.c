#include "unit_test_run.h"

#include <inttypes.h>
#include <stddef.h>

#ifdef HAS_DEV_ERROR_HANDLER
#include "dev_error_handler.h"
#endif
#include "log_utils.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif
#include "print_buffer.h"
#include "terminal_codes.h"
#include "test_config.h"
#include "unit_test.h"

#define MAX_FAILED_TEST 100U
static uint32_t failed_tests[MAX_FAILED_TEST];
bool test_failed;

static void add_to_failed(uint32_t index);

static void add_to_failed(uint32_t index) {
    if(UnitTest.failed_tests_count < MAX_FAILED_TEST) {
        failed_tests[UnitTest.failed_tests_count] = index;
        UnitTest.failed_tests_count++;
    }
}

bool unit_test_run(uint32_t index) {
    bool test_res = false;
    const unit_test_info_t* ui = get_unit_test(index);
    if(NULL == ui) {
        LOG_ERROR(SYS, "Invalid unit_test number %" PRIu32, index + 1U);

        test_res = false;
    } else {
#ifdef HAS_LOG
        uint32_t cnt = unit_test_cnt();
        cli_printf("************* Run test %s .%" PRIu32 "/%" PRIu32 CRLF, ui->name, index + 1U, cnt);
        print_buf_stream_en = true;
#endif

#ifdef HAS_DEV_ERROR_HANDLER
        dev_errors_clear();
#endif
        test_res = ui->utest_func();
#ifdef HAS_LOG
        print_buf_stream_en = false;
#endif
#ifdef EMBEDDED_TEST
        log_zero_time = false;
#endif

#ifdef HAS_DEV_ERROR_HANDLER
        if(dev_errors_count_total != 0U) {
            LOG_ERROR(SYS, "Runtime error check detected. Mark test as failed. dev_errors_count_total=%" PRIu32,
                      dev_errors_count_total);
            dev_errors_dump();
            test_failed = true;
        }
#endif
        if(false == test_res) {
#ifdef HAS_LOG
            cli_putstr("!ERRTEST" CRLF);
#endif
            add_to_failed(index);
        } else {
            UnitTest.ok_tests_count++;
#ifdef HAS_LOG
            cli_putstr("!OKTEST" CRLF);
#endif
        }

#ifdef HAS_NORTOS
        wait_in_loop_ms(10);
#endif
    }

    return test_res;
}

void failed_tests_reset(void) { UnitTest.failed_tests_count = 0U; }

void failed_tests_print(void) {
    uint32_t total = unit_test_cnt();
    if(0U != UnitTest.failed_tests_count) {
        uint32_t index = 0;
        LOG_ERROR(TEST, "%u/%u test failed!", UnitTest.failed_tests_count, total);
        for(index = 0U; index < UnitTest.failed_tests_count; index++) {
            if(MAX_FAILED_TEST <= index) {
                break;
            }
            const unit_test_info_t* Node = get_unit_test(failed_tests[index]);
            LOG_ERROR(TEST, "Failed: %s .%u", Node->name, failed_tests[index] + 1U);
        }
        LOG_INFO(TEST, "total %u tests", total);
        cli_putstr(VT_SETCOLOR_NORMAL);
    } else {
        LOG_INFO(TEST, "All %u tests passed!", UnitTest.ok_tests_count);
    }
}
