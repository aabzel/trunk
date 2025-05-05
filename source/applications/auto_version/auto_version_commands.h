#ifndef AUTO_VERSION_COMMANDS_H
#define AUTO_VERSION_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool cmd_auto_version_diag(int32_t argc, char* argv[]);
bool cmd_auto_version_proc(int32_t argc, char* argv[]);

#define AUTO_VERSION_COMMANDS                                                                \
    SHELL_CMD("auto_version_diag", "avd", cmd_auto_version_diag, "AutoVersionDiag"),         \
    SHELL_CMD("auto_version_proc", "avp", cmd_auto_version_proc, "AutoVersionProc"),

#ifdef __cplusplus
}
#endif

#endif /* AUTO_VERSION_COMMANDS_H */
