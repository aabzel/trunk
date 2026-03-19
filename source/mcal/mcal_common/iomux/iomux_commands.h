#ifndef IOMUX_GENERAL_COMMANDS_H
#define IOMUX_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_LOG
#include "ostream.h"
#endif

#ifdef HAS_IOMUX_CUSTOM_COMMANDS
#include "iomux_custom_commands.h"
#else
#define IOMUX_CUSTOM_COMMANDS
#endif

#ifndef HAS_IOMUX_COMMANDS
#error "+HAS_IOMUX_COMMANDS"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_IOMUX
#error "+HAS_IOMUX"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool iomux_init_command(int32_t argc, char* argv[]);
bool iomux_mux_command(int32_t argc, char* argv[]);

#define IOMUX_COMMANDS                                                         \
    IOMUX_CUSTOM_COMMANDS                                                      \
    SHELL_CMD("iomux_init", "iomi", iomux_init_command, "IoMuxInit"),          \
    SHELL_CMD("iomux_mux", "iom", iomux_mux_command, "IoMuxPinMux"),

#ifdef __cplusplus
}
#endif

#endif /* IOMUX_GENERAL_COMMANDS_H */
