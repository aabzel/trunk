#include "test_cli.h"

#ifdef X86_64
#include <stdio.h>
#endif

#include "bit_utils.h"
#include "cli_drv.h"
#include "unit_test_check.h"

bool test_cli2(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char cmd_line2[] = "fw 0x0001a000 0x00400120 0xc138";
    int argc = 0;
    char* shell_argv[SHELL_MAX_ARG_COUNT];
    ASSERT_TRUE(cli_parse_args(cmd_line2, &argc, &shell_argv[0]));
    EXPECT_EQ(4, argc);
    EXPECT_STREQ("fw", shell_argv[0]);
    EXPECT_STREQ("0x0001a000", shell_argv[1]);
    EXPECT_STREQ("0x00400120", shell_argv[2]);
    EXPECT_STREQ("0xc138", shell_argv[3]);
    return res;
}

bool test_cli1(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    char cmd_line1[20] = "gl rst";
    int argc = 0;

    char* shell_argv[SHELL_MAX_ARG_COUNT];
    ASSERT_TRUE(cli_parse_args(cmd_line1, &argc, &shell_argv[0]));
    EXPECT_EQ(2, argc);
    EXPECT_STREQ("gl", shell_argv[0]);
    EXPECT_STREQ("rst", shell_argv[1]);
    return res;
}
