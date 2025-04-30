#ifndef CLI_NATIVE_COMMANDS_H
#define CLI_NATIVE_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "ostream.h"

#ifdef __cplusplus
extern "C" {
#endif

extern bool show_shell_prompt;
extern bool user_mode;

#ifndef HAS_CLI_NATIVE_COMMANDS
#error "+HAS_CLI_NATIVE_COMMANDS"
#endif

bool cmd_wd_test_hw(int32_t argc, char* argv[]) ;
bool dump_cmd_result_ex(bool res, const char* message);
bool dump_cmd_result(bool res);
bool cmd_wd_test(int32_t argc, char* argv[]);
bool cmd_low_level_control(int32_t argc, char* argv[]);

#ifdef HAS_TEST_FIRMWARE_COMMANDS
bool cmd_ascii(int32_t argc, char* argv[]);
bool cmd_wd_test(int32_t argc, char* argv[]);
bool cmd_calc(int32_t argc, char* argv[]);
bool cmd_low_level_control(int32_t argc, char* argv[]);


#define TEST_FIRMWARE_COMMANDS                                                                  \
        SHELL_CMD("calc", "calc", cmd_calc, "Calculator OfDataTypes"),                        \
        SHELL_CMD("ascii", "ascii", cmd_ascii, "Print ascii"),                                  \
        SHELL_CMD("wd_test", "wd_test", cmd_wd_test, "Stop board (for watchdog test)"),         \
        SHELL_CMD("bit_ctrl", "bc", cmd_low_level_control, "Set Clear bit in memory address"),
#else
#define TEST_FIRMWARE_COMMANDS
#endif

bool cmd_echo(int32_t argc, char *argv []);
bool cli_diag_command(int32_t argc, char *argv []);
bool cmd_version(int32_t argc, char* argv[]);
bool cli_help_command(int32_t argc, char* argv[]);
bool cmd_sysinfo(int32_t argc, char* argv[]);
bool cmd_beep(int32_t argc, char* argv[]);

#define CLI_NATIVE_BASE_COMMANDS                                                                           \
    SHELL_CMD("cli_diag","clid",cli_diag_command, "CliDiag"),                                                             \
    SHELL_CMD("beep","b",cmd_beep, "CliBeep"),                                                             \
    SHELL_CMD("echo","e",cmd_echo, "SetEcho"),                                                             \
    SHELL_CMD("help", "h", cli_help_command, "PrintListOfShellCommands"),                                          \
    SHELL_CMD("version", "vi", cmd_version, "PrintVersionInformation"),                                    \
    SHELL_CMD("sysinfo", "si", cmd_sysinfo, "PrintInformationAboutThreads&OS"),

#define CLI_NATIVE_COMMANDS                                \
        CLI_NATIVE_BASE_COMMANDS                           \
        TEST_FIRMWARE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* CLI_NATIVE_COMMANDS_H */
