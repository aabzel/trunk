#ifndef DEBUGGER_COMMANDS_H
#define DEBUGGER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_DEBUGGER_COMMANDS
#error "+HAS_DEBUGGER_COMMANDS"
#endif


bool count_all_link_command(int32_t argc, char* argv[]);
bool count_link_command(int32_t argc, char* argv[]);
bool cmd_write_memory(int32_t argc, char* argv[]);
bool cmd_launch_function(int32_t argc, char* argv[]);
bool cmd_repeat(int32_t argc, char* argv[]);
bool cmd_find_addr(int32_t argc, char* argv[]);
bool cmd_read_memory(int32_t argc, char* argv[]);
bool read_register_command(int32_t argc, char* argv[]);

#define DEBUGGER_COMMANDS                                              \
    SHELL_CMD("count_link_all",  "cla",  count_all_link_command,   "CountLinkAll"),         \
    SHELL_CMD("read_register",  "rr",  read_register_command,   "ReadRegister"),                       \
    SHELL_CMD("count_link",  "cl",  count_link_command,   "CountLink"),                                       \
    SHELL_CMD("read_mem", "rm", cmd_read_memory, "ReadMemory address"),                                           \
    SHELL_CMD("find_addr", "fadr", cmd_find_addr, "Find address by value"), \
    SHELL_CMD("repeat", "rpt", cmd_repeat, "Repeat any command N time with period"),                               \
    SHELL_CMD("launch_function", "lfun", cmd_launch_function, "LaunchAnyFunctionByAddressInROM"),     \
    SHELL_CMD("write_mem", "wm", cmd_write_memory, "WriteMemoryAddress"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*DEBUGGER_COMMANDS_H*/
