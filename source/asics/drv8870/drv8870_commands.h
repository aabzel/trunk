#ifndef DRV8870_COMMANDS_H
#define DRV8870_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_DRV8870
#error "+ HAS_DRV8870"
#endif

#ifndef HAS_DRV8870_COMMANDS
#error "+ HAS_DRV8870_COMMANDS"
#endif

bool drv8870_diag_command(int32_t argc, char* argv[]);
bool drv8870_init_command(int32_t argc, char* argv[]);
bool drv8870_set_command(int32_t argc, char* argv[]);
bool drv8870_freq_command(int32_t argc, char* argv[]);
bool drv8870_test_command(int32_t argc, char* argv[]);

#define DRV8870_COMMANDS                                                                                  \
        SHELL_CMD("drv8870_test", "d88t", drv8870_test_command, "Drv8870Test"),                           \
        SHELL_CMD("drv8870_freq", "d88f", drv8870_freq_command, "Drv8870Freq"),                           \
        SHELL_CMD("drv8870_set", "d88s", drv8870_set_command, "Drv8870Set"),                              \
        SHELL_CMD("drv8870_diag", "d88d", drv8870_diag_command, "Drv8870Diag"),                           \
        SHELL_CMD("drv8870_init", "d88i", drv8870_init_command, "Drv8870Init"),

#ifdef __cplusplus
}
#endif

#endif /* DRV8870_COMMANDS_H */
