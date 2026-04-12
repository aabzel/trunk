#ifndef NVRAM_CLI_H
#define NVRAM_CLI_H

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

#ifndef HAS_NVRAM_DIAG
#error "+HAS_NVRAM_DIAG"
#endif

bool NVRAM_DeleteCommand(int32_t argc, char* argv[]);
bool NVRAM_GetCommand(int32_t argc, char* argv[]);
bool NVRAM_SetCommand(int32_t argc, char* argv[]);
bool NVRAM_DiagCommand(int32_t argc, char* argv[]);
bool NVRAM_DefaultCommand(int32_t argc, char* argv[]);
bool NVRAM_InitCommand(int32_t argc, char* argv[]);

#define NVRAM_CLI                                                                                \
    SHELL_CMD("nvram_delete", "ne", NVRAM_DeleteCommand, "NvramDelete"),                         \
    SHELL_CMD("nvram_init", "ni", NVRAM_InitCommand, "NvramInit"),                               \
    SHELL_CMD("nvram_diag", "nd", NVRAM_DiagCommand, "NvramDiag"),                               \
    SHELL_CMD("nvram_defaults", "ndef", NVRAM_DefaultCommand, "NvramDefault"),                   \
    SHELL_CMD("nvram_get", "ng", NVRAM_GetCommand, "NvramGet"),                                  \
    SHELL_CMD("nvram_set", "ns", NVRAM_SetCommand, "NvramSet"),

#ifdef __cplusplus
}
#endif

#endif /* NVRAM_CLI_H  */
