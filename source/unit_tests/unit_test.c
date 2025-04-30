#include "unit_test.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

#ifdef HAS_CLOCK
#include "clock.h" // TODO DEL
#endif             /*HAS_CLOCK*/

#ifdef HAS_TIME
#include "time_mcal.h"
#endif /*HAS_TIME*/

#ifdef HAS_TIMER
//#include "timer_utils.h"
#endif /*HAS_TIMER*/

#ifdef HAS_STRING_PARSER
#include "convert.h"
#endif

#include "log.h"

#include "str_utils.h"
#include "terminal_codes.h"
#include "test_config.h"
#include "unit_test_run.h"

static uint32_t unit_test_run_range(uint32_t from_index, uint32_t to_index) {
    uint32_t index = 0;
    static bool called = false;
    uint32_t cnt = 0U;
    if(false == called) {
        called = true;
        LOG_INFO(SYS, "Run %u-%u", from_index, to_index);
        for(index = from_index; index <= to_index; index++) {
            cnt += unit_test_run(index);
        }
        called = false;
    }
    return cnt;
}

static uint32_t unit_test_run_name(const char* name) {
    uint32_t index = 0;
    uint32_t cnt = 0U;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if(ui) {
            if(0 == strcmp(name, ui->name)) {
                cnt += unit_test_run(index);
            }
        }
    }
    return cnt;
}

static uint32_t unit_test_run_key(const char* key) {
    uint32_t index = 0;
    LOG_WARNING(TEST, "%s() key %s", __FUNCTION__, key);
    uint32_t cnt = 0U;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if((ui) && (NULL != ui->name)) {
            if(NULL != str_case_str(ui->name, key)) {
                cnt += unit_test_run(index);
            }
        }
    }
    return cnt;
}

static uint32_t unit_test_run_excluding_key(const char* key) {
    uint32_t index = 0;
    LOG_WARNING(TEST, "RunAllTestExeptKey[%s]", key);
    uint32_t cnt = 0U;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if((ui) && (NULL != ui->name)) {
            if(NULL == str_case_str(ui->name, key)) {
                cnt += unit_test_run(index);
            }
        }
    }
    return cnt;
}

static uint32_t unit_test_run_prefix(const char* prefix) {
    uint32_t index;
    uint32_t cnt = 0U;
    size_t len = strlen(prefix);
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if(ui) {
            if(0 == strncmp(ui->name, prefix, len)) {
                cnt += unit_test_run(index);
            }
        }
    }
    return cnt;
}

static bool unit_test_list_is_uniq(const unit_test_info_t* const Node, uint32_t count) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = unit_test_cnt();
    for(i = 0; i < cnt; i++) {
#warning TODO:  check uniq tests cnt
    }
    return res;
}

bool unit_test_init(void) {
    bool res = false;

    memset(&UnitTest, 0, sizeof(UnitTest_t));

    uint32_t count = unit_test_cnt();
    LOG_INFO(SYS, "TestCnt:%u", count);

    res = unit_test_list_is_uniq(test_list, count);
    res = true;
    return res;
}

const unit_test_info_t* get_unit_test(uint32_t test_index) {
    const unit_test_info_t* res;
    if(unit_test_cnt() <= test_index) {
        res = NULL;
    } else {
        res = &test_list[test_index];
    }
    return res;
}

void dump_unit_test_all(void) {
    uint32_t index = 0;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if(ui) {
#ifdef HAS_LOG
            cli_putstr(ui->name);
            cli_putstr(".");
            cli_putstr(rx_utoa32(index + 1U));
            cli_putstr(CRLF);
#endif /*HAS_LOG*/
        }
    }
}

void dump_unit_test_key(const char* key) {
    uint32_t index = 0;
#ifdef HAS_LOG
    LOG_INFO(TEST, "%s() key %s", __FUNCTION__, key);
#endif /*HAS_LOG*/
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* ui = get_unit_test(index);
        if(ui) {
            if(NULL != str_case_str(ui->name, key)) {
#ifdef HAS_LOG
                cli_putstr(ui->name);
                cli_putstr(".");
                cli_putstr(rx_utoa32(index + 1U));
                cli_putstr(CRLF);
                // cli_flush();
#endif /*HAS_LOG*/
            }
        }
    }
}

static char test_name[100] = "";
bool unit_tests_run(const char* const key) {
    bool res = false;
    static bool is_callsed = false;
    (void)is_callsed;
    if(false == is_callsed) {
        is_callsed = true;

        LOG_INFO(TEST, "key [%s]", key);
        uint32_t cnt = 0U;

        failed_tests_reset();

        (void)strncpy(test_name, key, sizeof(test_name));
        test_name[sizeof(test_name) - 1U] = '\0';
#ifdef HAS_TIME
        uint32_t start_up_time_ms = time_get_ms32();
#endif
        if(0U == cnt) {
            if(0 == strcmp(test_name, "*")) {
                cnt = unit_test_run_range(0U, unit_test_cnt() - 1U);
            } else if(strchr(test_name, (int16_t)'+') != NULL) {
                char* p = strchr(test_name, (int16_t)'+');
                *p = '\0';
                cnt = unit_test_run_key(test_name);
            } else if(strchr(test_name, (int16_t)'^') != NULL) {
                char* p = strchr(test_name, (int16_t)'^');
                if(p) {
                    *p = '\0';
                    cnt = unit_test_run_excluding_key(test_name);
                }
            } else if(strchr(test_name, (int32_t)'*') != NULL) {
                char* p = strchr(test_name, (int32_t)'*');
                *p = '\0';
                cnt = unit_test_run_prefix(test_name);
            } else {
            }
        }

        if(0U == cnt) {
            uint32_t number = 0;
            res = try_str2uint32(test_name, &number);
            if(res) {
                LOG_INFO(TEST, "KeyWord:%s,SpotNum:%u", test_name, number);
                cnt = unit_test_run(number - 1U);
            } else {
                LOG_WARNING(TEST, "KeyWord:%s,NoNum", test_name);
            }
        }
        if(0U == cnt) {
            cnt = unit_test_run_name(test_name);
        }
        if(0U == cnt) {
            if(strchr(test_name, (int32_t)'-') != NULL) {
                bool ok = true;
                uint32_t from_number = 0, to_number = 0;
                char* p = strchr(test_name, (int32_t)'-');
                *p = '\0';
                p++;
                if(false == try_str2uint32(test_name, &from_number)) {
                    ok = false;
                    LOG_ERROR(TEST, "Invalid \"from\" test number %s", test_name);
                }
                if(false == try_str2uint32(p, &to_number)) {
                    ok = false;
                    LOG_ERROR(TEST, "Invalid \"to\" test number %s", p);
                }
                if(ok) {
                    cnt = unit_test_run_range(from_number - 1U, to_number - 1U);
                }
            }
        }
#ifdef HAS_TIME
        uint32_t end_time_ms = time_get_ms32();
        uint32_t duration_ms = 0;
        duration_ms = end_time_ms - start_up_time_ms;
        LOG_INFO(TEST, "Test duration %u ms =%f s= %f min" CRLF, duration_ms, MSEC_2_SEC(duration_ms),
                 MSEC_2_MIN(duration_ms));
#endif
        if(0U == cnt) {
            cli_printf(VT_SETCOLOR_RED "Test %s not found!" CRLF, key);
            cli_putstr("!ERRTEST" VT_SETCOLOR_NORMAL CRLF);
        }
        if(0U < cnt) {
            failed_tests_print();
        }

        is_callsed = false;
    }
    return res;
}

bool test_components(void) {
    bool res = false;
    set_log_level(SYS, LOG_LEVEL_DEBUG);
    LOG_INFO(TEST, "Test Code Base:");

    uint32_t cnt = unit_test_cnt();
    LOG_INFO(TEST, "NumOfTests: %u", cnt);
    bool rest_res = false;
    uint32_t failed_cnt = 0, total = 0;
    uint32_t passed_cnt = 0;
    uint32_t index = 0;
    unit_test_info_t* ui = NULL;
    for(index = 0; index < cnt; index++) {
        rest_res = unit_test_run(index);
        if(false == rest_res) {
            failed_cnt++;
            ui = (unit_test_info_t*)get_unit_test(index);
            LOG_ERROR(SYS, "Tests failed index: %u [%s]", index, ui->name);
        } else {
            passed_cnt++;
        }
        total++;
    }

    if(0 < failed_cnt) {
        LOG_ERROR(TEST, "Tests Failure: %u/%u", failed_cnt, total);
        res = false;
    } else {
        LOG_INFO(TEST, "Tests Passed: %u", total);
        res = true;
    }
    set_log_level(TEST, LOG_LEVEL_INFO);
    return res;
}
