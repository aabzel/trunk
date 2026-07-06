#include "unit_test_diag.h"

#include "log.h"
#include "str_utils.h"
#include "test_config.h"
#include "unit_test.h"

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

const char* TestResToStr(const bool res) {
    char* name = "?";
    if(res) {
        name = VT_SETCOLOR_INFO "OkTest" VT_SETCOLOR_NORMAL;
    } else {
        name = VT_SETCOLOR_ERROR "ErrTest" VT_SETCOLOR_NORMAL;
    }
    return name;
}

static bool is_positive_val(const uint32_t ok) {
    bool res = false;
    if(ok) {
        res = true;
    }
    return res;
}

bool unit_test_find_key(const char* key1, const char* key2) {
    bool res = false;
    uint32_t index = 0;
#ifdef HAS_LOG
    LOG_INFO(TEST, "%s(),key1:%s,key2:%s", __FUNCTION__, key1, key2);
#endif

    static const table_col_t cols[] = {
        {5, "No"},
        {48, "Name"},
#ifdef HAS_CRC16
        {8, "TID"},
#endif
        {5, "Index"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = 0;
    uint32_t ok = 0;
    for(index = 0U; index < unit_test_cnt(); index++) {
        const unit_test_info_t* Node = get_unit_test(index);
        if(Node) {
#ifdef HAS_CRC16
            uint32_t name_len = strlen(Node->name);
            uint16_t crc16 = calc_crc16_ccitt_false((uint8_t*)Node->name, name_len); // TODO change to hash
#endif
            char temp[250] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, cnt);
            snprintf(temp, sizeof(temp), "%s %46s " TSEP, temp, str_limit(Node->name, 46));
#ifdef HAS_CRC16
            snprintf(temp, sizeof(temp), "%s 0x%04X " TSEP, temp, crc16);
#endif
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, index + 1U);

            res = is_contain(temp, key1, key2);
            if(res) {
#ifdef HAS_LOG
                cli_printf("%s" CRLF, temp);
#endif
                cnt++;
                ok++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    res = is_positive_val(ok);
    return res;
}

bool dump_unit_test_all(void) {
    bool res = false;
    res = unit_test_find_key("", "");
    return res;
}

const char* TestNodeToStr(const unit_test_info_t* const Node) {
    static char temp[100] = {0};
    if(Node) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sName:[%s],", temp, Node->name);
        snprintf(temp, sizeof(temp), "%sFun:%p", temp, Node->utest_func);
#ifdef HAS_UNIT_TEST_SEVERENESS
        snprintf(temp, sizeof(temp), "%sSev:%u,", temp, Node->severeness);
#endif
    }
    return temp;
}

bool unit_test_report(void) {
    bool res = false;
    LOG_INFO(TEST, "Report");
    LOG_INFO(TEST, "ok:%u/%u", UnitTest.ok_tests_count,unit_test_cnt());

    if(UnitTest.failed_tests_count) {
        LOG_ERROR(TEST, "failed:%u", UnitTest.failed_tests_count);
#ifdef HAS_STORE_FS
        res = store_fs_set( PAR_ID_UNIT_TEST_FAILED_CNT , &UnitTest.failed_tests_count);
#endif

        if(UnitTest.first_failed) {
            LOG_ERROR(TEST, "FirstFailed:[%s]", TestNodeToStr(UnitTest.first_failed));
#ifdef HAS_STORE_FS
        uint32_t name_len = strlen(UnitTest.first_failed->name);
        uint16_t crc16 = calc_crc16_ccitt_false((uint8_t*)UnitTest.first_failed->name, name_len);
        res = store_fs_set( PAR_ID_UNIT_TEST_FIRST_FAILED_HASH , &crc16);
#endif
        }

        if(UnitTest.first_failed != UnitTest.last_failed) {
            if(UnitTest.last_failed) {
                LOG_ERROR(TEST, "LastFailed:[%s]", TestNodeToStr(UnitTest.last_failed));
#ifdef HAS_STORE_FS
            uint32_t name_len = strlen(UnitTest.last_failed->name);
            uint16_t crc16 = calc_crc16_ccitt_false((uint8_t*)UnitTest.last_failed->name, name_len);
            res = store_fs_set( PAR_ID_UNIT_TEST_LAST_FAILED_HASH , &crc16);
#endif
            }
        }

    } else {
        res = true;
        LOG_INFO(TEST, "failed:%u", UnitTest.failed_tests_count);
    }

    return res;
}
