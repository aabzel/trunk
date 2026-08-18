#ifndef BC127_COMMANDS_H
#define BC127_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_BC127
#error "+ HAS_BC127"
#endif

#ifndef HAS_BC127_COMMANDS
#error "+ HAS_BC127_COMMANDS"
#endif

bool bc127_get_command(int32_t argc, char* argv[]);
bool bc127_send_command(int32_t argc, char* argv[]);
bool bc127_init_command(int32_t argc, char* argv[]);
bool bc127_diag_command(int32_t argc, char* argv[]);
bool bc127_reset_command(int32_t argc, char* argv[]);
bool bc127_get_volume_command(int32_t argc, char* argv[]);
bool bc127_set_volume_command(int32_t argc, char* argv[]);

#define BC127_COMMANDS                                                                                                 \
    SHELL_CMD("bc127_set_vol", "bsv", bc127_set_volume_command, "Bc127SetVolume"),                                     \
        SHELL_CMD("bc127_get_vol", "bgv", bc127_get_volume_command, "Bc127GetVolume"),                                 \
        SHELL_CMD("bc127_diag", "bcd", bc127_diag_command, "Bc127Diag"),                                               \
        SHELL_CMD("bc127_send", "bcs", bc127_send_command, "Bc127Send"),                                               \
        SHELL_CMD("bc127_get", "bcg", bc127_get_command, "Bc127Get"),                                                  \
        SHELL_CMD("bc127_init", "bci", bc127_init_command, "Bc127Init"),                                               \
        SHELL_CMD("bc127_reset", "bct", bc127_reset_command, "Bc127Reset"),

#ifdef __cplusplus
}
#endif

#endif /* BC127_COMMANDS_H */
