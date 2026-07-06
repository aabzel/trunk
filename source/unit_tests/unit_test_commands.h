#ifndef UNIT_TEST_COMMANDS_H
#define UNIT_TEST_COMMANDS_H

#include "std_includes.h"

#ifndef HAS_UNIT_TEST
#error "+HAS_UNIT_TEST"
#endif

#ifndef HAS_UNIT_TEST_COMMANDS
#error "+HAS_UNIT_TEST_COMMANDS"
#endif

bool cmd_unit_test_list(int32_t argc, char* argv[]);
bool cmd_unit_test_run(int32_t argc, char* argv[]);
bool cmd_unit_test_run_first_fail(int32_t argc, char* argv[]);
bool cmd_unit_test_run_by_num(int32_t argc, char* argv[]);
bool cmd_unit_test_run_by_sub_name(int32_t argc, char* argv[]);

#define UNIT_TEST_COMMANDS                                                      \
    SHELL_CMD("test_all", "ta", cmd_unit_test_list, "UnitTestsPrintAll"),      \
    SHELL_CMD("test_run", "tr", cmd_unit_test_run, "UnitTestRun"),                        \
    SHELL_CMD("test_run_by_sub_name", "trs", cmd_unit_test_run_by_sub_name, "UnitTestRunBySubName"),                        \
    SHELL_CMD("test_run_by_num", "trn", cmd_unit_test_run_by_num, "UnitTestRunByNum"),                        \
    SHELL_CMD("test_run_first", "trf", cmd_unit_test_run_first_fail, "UnitTestRunToFirstFail"),

#endif /* UNIT_TEST_COMMANDS_H */
