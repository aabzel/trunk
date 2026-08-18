#ifndef BH1750_COMMANDS_H
#define BH1750_COMMANDS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_BH1750
#error "+ HAS_BH1750"
#endif

#ifndef HAS_I2C_DIAG
#warning "+ HAS_I2C_DIAG"
#endif

#ifndef HAS_BH1750_COMMANDS
#error "+HAS_BH1750_COMMANDS"
#endif

bool bh1750_reset_command(int32_t argc, char* argv[]);
bool bh1750_init_command(int32_t argc, char* argv[]);
bool bh1750_diag_command(int32_t argc, char* argv[]);
bool bh1750_send_opcode_command(int32_t argc, char* argv[]);
bool bh1750_read_light_command(int32_t argc, char* argv[]);

#define BH1750_COMMANDS                                                                              \
    SHELL_CMD("bh1750_reset", "bhr", bh1750_reset_command, "Bh1750Rreset"),                          \
    SHELL_CMD("bh1750_read_light", "brl", bh1750_read_light_command, "Bh1750ReadLight"),             \
    SHELL_CMD("bh1750_diag", "bhd", bh1750_diag_command, "Bh1750Diag"),                              \
    SHELL_CMD("bh1750_send_opcode", "bso", bh1750_send_opcode_command, "Bh1750SendOpCode"),          \
    SHELL_CMD("bh1750_init", "bhi", bh1750_init_command, "Bh1750Init"),

#ifdef __cplusplus
}
#endif

#endif /* BH1750_COMMANDS_H */
