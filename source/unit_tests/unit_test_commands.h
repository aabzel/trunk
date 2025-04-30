#ifndef UNIT_TEST_COMMANDS_H
#define UNIT_TEST_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_UNIT_TEST
#error "+HAS_UNIT_TEST"
#endif

#ifndef HAS_UNIT_TEST_COMMANDS
#error "+HAS_UNIT_TEST_COMMANDS"
#endif

bool cmd_unit_test_list(int32_t argc, char* argv[]);
bool cmd_unit_test_run(int32_t argc, char* argv[]);

#define UNIT_TEST_COMMANDS                                                      \
    SHELL_CMD("test_all", "tsa", cmd_unit_test_list, "PrintAllUnitTests"),      \
    SHELL_CMD("test_run", "tsr", cmd_unit_test_run, "RunTest"),

#endif /* UNIT_TEST_COMMANDS_H */
