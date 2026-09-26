#ifndef IOMUX_CUSTOM_COMMANDS_H
#define IOMUX_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"

#ifndef HAS_IOMUX_COMMANDS
#error "+HAS_IOMUX_COMMANDS"
#endif

#ifndef HAS_IOMUX
#error "+HAS_IOMUX"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool iomux_diag_reg_map_command(int32_t argc, char* argv[]);

#define IOMUX_CUSTOM_COMMANDS                                                                        \
        SHELL_CMD("iomux_diag_reg_map", "iomrm", iomux_diag_reg_map_command, "IoMuxDaigRegMap"),

#ifdef __cplusplus
}
#endif

#endif /* IOMUX_CUSTOM_COMMANDS_H */
