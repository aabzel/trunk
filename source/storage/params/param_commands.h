#ifndef PARAM_COMMANDS_H
#define PARAM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_PARAM_DIAG
#error "+HAS_PARAM_DIAG"
#endif

bool cmd_param_delete(int32_t argc, char* argv[]);
bool cmd_param_get(int32_t argc, char* argv[]);
bool cmd_param_set(int32_t argc, char* argv[]);
bool cmd_param_diag(int32_t argc, char* argv[]);
bool cmd_param_default(int32_t argc, char* argv[]);
bool cmd_param_init(int32_t argc, char* argv[]);

#define PARAM_COMMANDS                                                                                                 \
    SHELL_CMD("param_delete", "pe", cmd_param_delete, "ParamDelete"),                                                       \
    SHELL_CMD("param_init", "pi", cmd_param_init, "ParamInit"),                                                       \
    SHELL_CMD("param_diag", "pd", cmd_param_diag, "ParamDiag"),                                                       \
    SHELL_CMD("param_defaults", "pdef", cmd_param_default, "ParamDefault"),                                                       \
    SHELL_CMD("param_get", "pg", cmd_param_get, "ParamGet"),                                                      \
    SHELL_CMD("param_set", "ps", cmd_param_set, "ParamSet"),

#ifdef __cplusplus
}
#endif

#endif /* PARAM_COMMANDS_H  */
