#ifndef W25Q32JV_COMMANDS_H
#define W25Q32JV_COMMANDS_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_W25Q32JV
#error "+ HAS_W25Q32JV"
#endif

#ifndef HAS_W25Q32JV_COMMANDS
#error "+ HAS_W25Q32JV_COMMANDS"
#endif

bool w25q32jv_reg_read_command(int32_t argc, char* argv[]);

#define W25Q32JV_COMMANDS                                                     \
    SHELL_CMD("w25q32jv_reg_read", "w25rr", w25q32jv_reg_read_command, "W25RegRead"),

#ifdef __cplusplus
}
#endif

#endif /* W25Q32JV_COMMANDS_H */
