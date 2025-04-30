#ifndef AXP192_COMMANDS_H
#define AXP192_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_manager.h"

bool axp192_reg_write_command(int32_t argc, char* argv[]);
bool axp192_reg_read_command(int32_t argc, char* argv[]);
bool axp192_reg_map_command(int32_t argc, char* argv[]);
bool axp192_diag_command(int32_t argc, char* argv[]);

#define AXP192_COMMANDS_BASE \
    SHELL_CMD("axp192_diag", "axd", axp192_diag_command, "AXP192 diag"),\
    SHELL_CMD("axp192_write", "axw", axp192_reg_write_command, "AXP192 writete reg"),\
    SHELL_CMD("axp192_read", "axr", axp192_reg_read_command, "AXP192 read reg"),\
    SHELL_CMD("axp192_map", "axm", axp192_reg_map_command, "AXP192 reg map"),


#define AXP192_COMMANDS \
        AXP192_COMMANDS_BASE


#ifdef __cplusplus
}
#endif

#endif /* AXP192_COMMANDS_H */
