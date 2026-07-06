#include "unit_test.h"

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

#include "log.h"
#include "print_buffer.h"
#include "str_utils.h"
#include "table_utils.h"
#include "terminal_codes.h"
#include "test_config.h"
#include "writer_config.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

#ifdef HAS_STRING_PARSER
#include "convert.h"
#endif

static char test_name[100] = "";

static uint32_t unit_test_run_name(const char* name) {
    uint32_t index = 0;
    uint32_t cnt = 0U;
    UnitTest.failed_tests_count = 0;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* Node = get_unit_test(index);
        if(Node) {
            if(0 == strcmp(name, Node->name)) {
                bool res = false;
                res = unit_test_run(index);
                if(res) {
                    cnt++;
                } else {
                    UnitTest.last_failed = Node;
                    if(1 == UnitTest.failed_tests_count) {
                        LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                        UnitTest.first_failed = Node;
                    }
                }
            }
        }
    }
    return cnt;
}

bool test_is_valid(const unit_test_info_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->name) {
            if(Node->utest_func) {
                res = true;
            }
        }
    }
    return res;
}

uint32_t unit_test_run_key(const char* key) {
    uint32_t index = 0;
    LOG_WARNING(TEST, "%s() key %s", __FUNCTION__, key);
    uint32_t cnt = 0U;
    UnitTest.failed_tests_count = 0;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* Node = get_unit_test(index);
        bool res = test_is_valid(Node);
        if(res) {
            if(str_case_str(Node->name, key)) {
                res = unit_test_run(index);
                if(res) {
                    cnt++;
                } else {
                    UnitTest.last_failed = Node;
                    if(1 == UnitTest.failed_tests_count) {
                        LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                        UnitTest.first_failed = Node;
                    }
                }
            }
        }
    }
    return cnt;
}

static uint32_t unit_test_run_excluding_key(const char* key) {
    uint32_t index = 0;
    LOG_WARNING(TEST, "RunAllTestExeptKey[%s]", key);
    uint32_t cnt = 0U;
    UnitTest.failed_tests_count = 0;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* Node = get_unit_test(index);
        bool res = test_is_valid(Node);
        if(res) {
            if(NULL == str_case_str(Node->name, key)) {
                res = false;
                res = unit_test_run(index);
                if(res) {
                    cnt++;
                } else {
                    UnitTest.last_failed = Node;
                    if(1 == UnitTest.failed_tests_count) {
                        LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                        UnitTest.first_failed = Node;
                    }
                }
            }
        }
    }
    return cnt;
}

uint32_t test_node_to_num(const unit_test_info_t* const Node) {
    uint32_t index;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* CurNode = get_unit_test(index);
        if(CurNode == Node) {
            break;
        }
    }
    return index;
}

static uint32_t unit_test_run_prefix(const char* prefix) {
    uint32_t index;
    uint32_t cnt = 0U;
    UnitTest.failed_tests_count = 0;
    size_t len = strlen(prefix);
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* Node = get_unit_test(index);
        if(Node) {
            if(0 == strncmp(Node->name, prefix, len)) {
                bool res = unit_test_run_ll(Node);
                if(res) {
                    cnt++;
                } else {
                    UnitTest.last_failed = Node;
                    if(0 == UnitTest.failed_tests_count) {
                        LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                        UnitTest.first_failed = Node;
                    }
                }
            }
        }
    }
    return cnt;
}

static uint32_t unit_test_run_range(uint32_t from_index, uint32_t to_index) {
    uint32_t index = 0;
    static bool called = false;
    uint32_t cnt = 0U;
    UnitTest.failed_tests_count = 0;
    if(false == called) {
        called = true;
        LOG_INFO(TEST, "Run %u-%u", from_index, to_index);
        for(index = from_index; index <= to_index; index++) {
            const unit_test_info_t* Node = get_unit_test(index);
            if(Node) {
                bool res = unit_test_run(index);
                if(res) {
                    cnt++;
                } else {
                    UnitTest.last_failed = Node;
                    if(1 == UnitTest.failed_tests_count) {
                        LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                        UnitTest.first_failed = Node;
                    }
                }
            }
        }
        called = false;
    }
    return cnt;
}

bool unit_test_is_uniq(const unit_test_info_t* const curNode) {
    bool res = false;
    uint32_t match = 0;
    uint32_t i = 0;
    uint32_t cnt = unit_test_cnt();
    for(i = 0; i < cnt; i++) {
        unit_test_info_t* Node = get_unit_test(i);
        if(curNode == Node) {
            match++;
        }
    }

    if(1 == match) {
        res = true;
    } else {
        LOG_ERROR(TEST, "SpotDoubleTest:[%s]", TestNodeToStr(curNode));
        res = false;
    }
    return res;
}

const unit_test_info_t* get_unit_test(uint32_t test_index) {
    const unit_test_info_t* Node;
    if(unit_test_cnt() <= test_index) {
        Node = NULL;
    } else {
        Node = &test_list[test_index];
    }
    return Node;
}

bool unit_tests_run(const char* const key) {
    bool res = false;
    static bool is_callsed = false;
    UnitTest.failed_tests_count = 0;
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
                const unit_test_info_t* Node = get_unit_test(number - 1U);
                if(Node) {
                    LOG_DEBUG(TEST, "KeyWord:%s,SpotNum:%u", test_name, number);
                    res = unit_test_run_ll(Node);
                    if(res) {
                        cnt++;
                    } else {
                        UnitTest.last_failed = Node;
                        if(0 == UnitTest.failed_tests_count) {
                            LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                            UnitTest.first_failed = Node;
                        }
                    }
                }

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
        LOG_INFO(TEST, "TestDuration:%u ms=%f s=%f min", duration_ms, MSEC_2_SEC(duration_ms), MSEC_2_MIN(duration_ms));
#endif
        unit_test_report();
        if(0U == cnt) {
            LOG_ERROR(TEST, "Test:[%s] NotFound!", key);
            LOG_ERROR(TEST, "!ERRTEST" VT_SETCOLOR_NORMAL);
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
    log_level_set(TEST, LOG_LEVEL_DEBUG);
    LOG_INFO(TEST, "Test Code Base:");
    UnitTest.failed_tests_count = 0;
    uint32_t cnt = unit_test_cnt();
    LOG_INFO(TEST, "NumOfTests: %u", cnt);
    uint32_t failed_cnt = 0, total = 0;
    uint32_t passed_cnt = 0;
    unit_test_info_t* Node = NULL;
    uint32_t index = 0;
    for(index = 0; index < cnt; index++) {
        bool rest_res = false;
        rest_res = unit_test_run(index);
        if(rest_res) {
            cnt++;
            passed_cnt++;
        } else {
            UnitTest.last_failed = Node;
            if(0 == UnitTest.failed_tests_count) {
                LOG_ERROR(TEST, "FirstFailed:%s", TestNodeToStr(Node));
                UnitTest.first_failed = Node;
            }

            failed_cnt++;
            Node = (unit_test_info_t*)get_unit_test(index);
            LOG_ERROR(TEST, "Tests failed index: %u [%s]", index, Node->name);
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
    log_level_set(TEST, LOG_LEVEL_INFO);
    return res;
}

#define MAX_FAILED_TEST 100U
static uint32_t failed_tests[MAX_FAILED_TEST];
bool test_failed;

static void add_to_failed(uint32_t index) {
    if(UnitTest.failed_tests_count < MAX_FAILED_TEST) {
        failed_tests[UnitTest.failed_tests_count] = index;
        UnitTest.failed_tests_count++;
    }
}

bool unit_test_run_ll(const unit_test_info_t* Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_LOG
        print_buf_stream_en = true;
#endif

        res = Node->utest_func();
#ifdef HAS_LOG
        print_buf_stream_en = false;
#endif
        uint32_t index = test_node_to_num(Node);
        if(res) {
            UnitTest.ok_tests_count++;
        } else {
            add_to_failed(index);
        }
        uint32_t cnt = unit_test_cnt();
        cli_printf("********* test,%s,%2u/%2u,[%s],FailCnt:%u" CRLF, TestResToStr(res), index + 1U, cnt,
                   TestNodeToStr(Node), UnitTest.failed_tests_count);

#ifdef HAS_TIME
        wait_in_loop_ms(300);
#endif
    }

    return res;
}

bool unit_test_run(uint32_t index) {
    bool res = false;
    const unit_test_info_t* Node = get_unit_test(index);
    if(Node) {
        res = unit_test_run_ll(Node);
    }
    return res;
}

bool failed_tests_reset(void) {
    bool res = true;
    UnitTest.failed_tests_count = 0U;
    UnitTest.ok_tests_count = 0U;
    UnitTest.last_failed = NULL;
    UnitTest.first_failed = NULL;
    return res;
}

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

bool unit_test_proc(void) {
    bool res = false;
    LOG_PARN(TEST, "Proc");
#ifdef HAS_STORE_FS
    uint32_t failed_tests_count = 0;
    res = store_fs_get(PAR_ID_UNIT_TEST_FAILED_CNT, &failed_tests_count);
    if(res) {
        LOG_WARNING(TEST, "SpotFailedTests:%u", failed_tests_count);
    }
#endif
    return res;
}

static bool unit_test_list_is_uniq(const unit_test_info_t* const Node, uint32_t count) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t cnt = unit_test_cnt();
    for(i = 0; i < cnt; i++) {
        unit_test_info_t* curNode = get_unit_test(i);
        if(curNode) {
            res = unit_test_is_uniq(curNode);
            ok = ok_cnt_update(ok, res);
        }
    }

    if(ok == cnt) {
        LOG_INFO(TEST, "AllUnitTestsUniq:%u", ok);
        res = true;
    } else {
        LOG_ERROR(TEST, "SpotTheSameTests:%u", cnt - ok);
        res = false;
    }
    return res;
}

bool unit_test_run_first_fail(const char* const key) {
    bool res = false;
    failed_tests_reset();
    LOG_INFO(TEST, "RunUpToFirstFail:[%s]", key);
    uint32_t cnt = unit_test_cnt();
    uint32_t ok = 0;
    uint32_t index = 0;
    for(index = 0; index < cnt; index++) {
        unit_test_info_t* curNode = get_unit_test(index);
        if(curNode) {
            if(0 < strlen(key)) {
                res = str_case_str(curNode->name, key);
            } else {
                res = true;
            }
            if(res) {
                res = unit_test_run(index);
                if(res) {
                    ok++;
                } else {
                    LOG_ERROR(TEST, "FirstFailed:[%s]", TestNodeToStr(curNode));
                    UnitTest.first_failed = curNode;
                    break;
                }
            }
        }
    }
    res = unit_test_report();
    LOG_INFO(TEST, "cnt:%u", cnt);

    return res;
}

bool unit_test_init(void) {
    bool res = false;
    memset(&UnitTest, 0, sizeof(UnitTest_t));
    uint32_t count = unit_test_cnt();
    LOG_INFO(TEST, "TestCnt:%u", count);
    if(count) {
        res = unit_test_list_is_uniq(test_list, count);
    }
    return res;
}
