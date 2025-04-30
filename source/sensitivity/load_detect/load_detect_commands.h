
#ifndef LOAD_DETECT_COMMANDS_H
#define LOAD_DETECT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_LOAD_DETECT_COMMANDS
#error "+HAS_LOAD_DETECT_COMMANDS"
#endif  /*HAS_LOAD_DETECT_COMMANDS*/

bool load_detect_init_command(int32_t argc, char* argv[]);
bool load_detect_enable_command(int32_t argc, char* argv[]);
bool load_detect_enable_pin_command(int32_t argc, char* argv[]);
bool load_detect_diag_command(int32_t argc, char* argv[]);
bool load_detect_pin_diag_command(int32_t argc, char* argv[]);

#define LOAD_DETECT_COMMANDS                                                                         \
    SHELL_CMD("load_detect_init", "ldi", load_detect_init_command, "LoadDetectInit"),                \
    SHELL_CMD("load_detect_en", "lde", load_detect_enable_command, "LoadDetectEnable"),              \
	SHELL_CMD("load_detect_pin_en", "ldpe", load_detect_enable_pin_command, "LoadDetectPinEnable"),  \
    SHELL_CMD("load_detect_pin_diag", "ldpd", load_detect_pin_diag_command, "LoadDetectPinDiag"),    \
    SHELL_CMD("load_detect_diag", "ldd", load_detect_diag_command, "LoadDetectDiag"),

#ifdef __cplusplus
}
#endif

#endif /* LOAD_DETECT_COMMANDS_H */
