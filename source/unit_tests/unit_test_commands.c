#include "unit_test_commands.h"

#include "convert.h"

#ifdef HAS_LOG
#include "log.h"
#include "log_utils.h"
#endif

#include "unit_test.h"

bool cmd_unit_test_list(int32_t argc, char* argv[]) {
    bool res = true;
    LOG_INFO(SYS, "%s() key %u", __FUNCTION__, argc);
    if((0 != argc) && (1 != argc)) {
        cli_putstr(""
                   "Usage: tsa - Print all test" CRLF
                   "Usage: tsa sample - Print all test that contain sub name \"sample\"" CRLF);
        res = false;
    }
    if(0 == argc) {
        dump_unit_test_all();
    }
    if(1 == argc) {
        dump_unit_test_key(argv[0]);
    }
    cli_putstr("!OKTEST" CRLF);
    // cli_flush();
    return res;
}

bool cmd_unit_test_run(int32_t argc, char* argv[]) {
    bool res = false;
    cli_printf("%s() argc %d" CRLF, __FUNCTION__, argc);
    UnitTest.ok_tests_count = 0;
    int32_t repeat_count = 1;

    switch(argc) {
    case 1: {
        repeat_count = 1;
        res = true;
    } break;
    case 2: {
        res = try_str2int32(argv[1], &repeat_count);
        if(res) {
            if(0U == repeat_count) {
                cli_printf("Test repeat count can't be equal to zero" CRLF);
                res = false;
            }
        } else {
            LOG_ERROR(TEST, "Can't convert string [%s] to test repeat count", argv[1]);
            res = false;
        }

    } break;
    default: {
        res = false;
    } break;
    }

    if(res) {
        LOG_INFO(TEST, "key1 [%s] %u time", argv[0], repeat_count);
        while(0 != repeat_count) {
            unit_tests_run(argv[0]);
            repeat_count--;
        }
    } else {
        cli_putstr("test_run bad format" CRLF "Usage: tsr test_name [repeat_count]" CRLF);
        cli_putstr("  test_name: test name pattern, test sequential number or test range" CRLF);
        cli_putstr("  repeat_count: repeat test call count, valid values 1-255(default=1)" CRLF "examples:" CRLF);
        cli_putstr("  tsr *               : run all test" CRLF);
        cli_putstr("  tsr simple*         : run all tests which names starting with \"simple\"" CRLF);
        cli_putstr("  tsr simple+         : run all tests which names contain string \"simple\"" CRLF);
        cli_putstr("  tsr simple^         : run all tests excluding which names contain string \"simple\"" CRLF);
        cli_putstr("  tsr simple_test     : run test with name \"simple_test\"" CRLF);
        cli_putstr("  tsr 13              : run test with sequential number 13" CRLF);
        cli_putstr("  tsr 1-13            : run tests with sequential numbers in range 1-13" CRLF);
        cli_putstr("  tsr simple_test 10  : run test with name \"simple_test\" ten times" CRLF);
        cli_putstr("  tsr 1-13 10         : run tests with sequential numbers in range 1-13 ten times" CRLF);
    }

    set_log_level(SUPER_CYCLE, LOG_LEVEL_INFO);
    return res;
}
